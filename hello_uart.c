/**
 *
 * This program takes gps data from KMC-38GPS Speaker-mic unit via UART and reformats it by padding
 * empty fields with zeros to make it compatible with VX8 Yaesu gps protocol and passes it to the radio.
 * It performs the necessary data transformations and puts reformatted data back to the uart.
 *
 *  Created on: 16 April 2024
 *      Author: Bartosz Grzelak 2E0VBG
 *     Version: 1.0
 *    Language: C
 *       Files: GpsDataDefinitions.h GpsDataDefinitions.c GpsMain.c
 *
 * This code is provided under the terms of the BSD 3-Clause License:
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/adc.h"
#include "GpsDataDefinitions.h"
#include <malloc.h>

// Uart variables
#define UART_ID uart0
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE

#define GPS_READ_BUFFER_LENGHT 512
#define BAUD_RATE 9600
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// Gpio Variables

#define GPS_POWER 26
#define PTT_GPIO 4
#define RED_LED_POWER 18
#define GREEN_LED_POWER 19
#define BLUE_LED_POWER 20

char GPS_sentence[GPS_READ_BUFFER_LENGHT] = ""; // Uart chart buffer

int GPS_sentence_index = 0;          // GPS Sentance index
bool GPS_sentence_word_start = true; // GPS Sentence start?
bool GPS_Uart_Rx_Start = false;      // GPS read start?
bool GPS_Uart_Rx = false;            // GPS read sentence from uart
bool GPS_Uart_Tx = false;            // GPS write sentence from uart
bool GPS_Add_To_Buffer = true;       // Safeguard, add new data to the buffer?
bool Debug_Hart_Beat = false;        // Debug print bool
bool Debug_Mode = false;             // Debug Mode
bool GPS_Fix_Found = false;          // GPS fix is achieved​
bool PTT_State = false;
bool Run = true;

/*!
 * \brief Get total hardware memory
 * \return Total memory
 */
uint32_t getTotalHeap(void)
{
    extern char __StackLimit, __bss_end__;
    return &__StackLimit - &__bss_end__;
}

/*!
 * \brief Get total free memory available
 * \return uint32_t of free memory
 */
uint32_t getFreeHeap(void)
{
    struct mallinfo m = mallinfo();
    return getTotalHeap() - m.uordblks;
}

/*!
 * \brief Alarm call back function, called every second. Triggers gps data read.
 */
int64_t GPS_Uart_Rx_Callback(alarm_id_t id, void *user_data)
{
    GPS_Uart_Tx = true;
    if (Debug_Mode)
    {
        Debug_Hart_Beat = true;
    }
    return 0;
}

/*!
 * \brief Ptt button call back function, called when ptt is pressed.
 */
void Ptt_callback(uint gpio, uint32_t events)
{
    while (gpio_get(gpio) == 0)
    {
        gpio_put(RED_LED_POWER, 1);
        gpio_put(GREEN_LED_POWER, 1);
        gpio_put(BLUE_LED_POWER, 1);

        gpio_put(GPS_POWER, 0);
        gpio_put(RED_LED_POWER, 0);
    }
    gpio_put(GPS_POWER, 1);
    gpio_put(RED_LED_POWER, 1);
}

int get_voltage()
{
    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();

    if ((result * conversion_factor) < 3.0f)
    {
        gpio_put(RED_LED_POWER, 0);
        gpio_put(GREEN_LED_POWER, 1);
        gpio_put(BLUE_LED_POWER, 1);
        gpio_put(GPS_POWER, 0);
        Run = false;
        gpio_set_irq_enabled_with_callback(PTT_GPIO, 0x4u, false, &Ptt_callback);
        while (true)
        {
            sleep_ms(10000);
        }
    }

    // printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
}

/*!
 * \brief Main program.
 */
int main()
{

    // Uart settings ->
    uart_init(UART_ID, BAUD_RATE);
    stdio_init_all();

    adc_init();
    adc_gpio_init(27);
    adc_select_input(1);

    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);
    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);

    // Gpio settings ->

    gpio_init(RED_LED_POWER);
    gpio_init(GREEN_LED_POWER);
    gpio_init(BLUE_LED_POWER);
    gpio_init(GPS_POWER);

    gpio_set_dir(PTT_GPIO, GPIO_IN);
    gpio_set_dir(GPS_POWER, GPIO_OUT);
    gpio_set_dir(RED_LED_POWER, GPIO_OUT);
    gpio_set_dir(GREEN_LED_POWER, GPIO_OUT);
    gpio_set_dir(BLUE_LED_POWER, GPIO_OUT);

    gpio_put(GPS_POWER, 1);
    gpio_put(RED_LED_POWER, 1);
    gpio_put(GREEN_LED_POWER, 1);
    gpio_put(BLUE_LED_POWER, 1);

    // Interrupts ->

    gpio_set_irq_enabled_with_callback(PTT_GPIO, 0x4u, true, &Ptt_callback);

    // Local variables  ->

    int i = 0;
    int bufferIndex = 0;
    char x;
    GPS_Uart_Rx = true;

    // Main routine ->

    while (true)
    {

        get_voltage();
        gpio_put(GPS_POWER, 0);

        // Check if usb connected, if so turn on debug mode
        if (stdio_usb_connected())
        {
            Debug_Mode = true;
        }
        else
        {
            Debug_Mode = false;
        }

        gpio_put(GPS_POWER, 1);

        if (GPS_Uart_Rx)
        {

            if (GPS_Uart_Rx_Start == false)
            {
                // Read gps data from uart

                if (uart_getc(UART_ID) != '\n')
                {
                    GPS_Uart_Rx_Start = false;
                }
                else
                {
                    GPS_Uart_Rx_Start = true;
                }
            }
            else
            {
                gpio_put(RED_LED_POWER, 1);
                gpio_put(GREEN_LED_POWER, 1);
                gpio_put(BLUE_LED_POWER, 1);

                x = uart_getc(UART_ID);
                if (x == '\n')
                {
                    if (i >= 7)
                    {
                        i = 0;

                        GPS_Uart_Rx_Start = false;
                        GPS_Add_To_Buffer = true;
                        GPS_Uart_Rx = false;
                        bufferIndex = 0;

                        if (GPS_Word_Initialiser(GPS_sentence, GPS_READ_BUFFER_LENGHT))
                        {
                            GPS_Add_To_Buffer = true;
                        }
                        else
                        {
                            GPS_Add_To_Buffer = false;
                        }
                        add_alarm_in_ms(1000, GPS_Uart_Rx_Callback, NULL, false);
                    }
                    else
                    {
                        i++;
                    }
                }
                if (GPS_Add_To_Buffer)
                {
                    GPS_sentence[bufferIndex++] = x;
                }
            }
        }

        // gpio_put(GPS_POWER, 0);

        if (GPS_Uart_Tx)
        {

            if (GPS_Fix_Found)
            {
                gpio_put(GREEN_LED_POWER, 0);
                gpio_put(BLUE_LED_POWER, 1);
            }
            else
            {
                gpio_put(BLUE_LED_POWER, 0);
                gpio_put(GREEN_LED_POWER, 1);
            }

            char *TempString = NULL;

            if (GPS_Word_Types_Set_Table[0])
            {
                TempString = GPGGA_to_string($GPS_GPGGA);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("00: %s\n", TempString);
                }

                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[1])
            {
                TempString = GPGGA_to_string($GPS_GPGGA);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("01: %s\n", TempString);
                }

                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[2])
            {
                TempString = GPGSA_to_string($GPS_GPGSA);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("02: %s\n", TempString);
                }

                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[3])
            {
                TempString = GPGSV_to_string($GPS_GPGSV_1);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("03: %s\n", TempString);
                }

                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[4])
            {
                TempString = GPGSV_to_string($GPS_GPGSV_2);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("04: %s\n", TempString);
                }

                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[5])
            {
                TempString = GPGSV_to_string($GPS_GPGSV_3);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("05: %s\n", TempString);
                }

                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[6])
            {
                TempString = GPGSV_to_string($GPS_GPGSV_4);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("06: %s\n", TempString);
                }

                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[7])
            {

                TempString = GPRMC_to_string($GPS_GPRMC);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (strcmp($GPS_GPRMC.Status, "A") == 0)
                {
                    GPS_Fix_Found = true;
                }
                else
                {
                    GPS_Fix_Found = false;
                }

                if (Debug_Mode)
                {
                    printf("07: %s\n", TempString);
                }
                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[8])
            {
                TempString = GPVTG_to_string($GPS_GPVTG);

                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("08: %s\n", TempString);
                }
                free(TempString);
            }
            if (GPS_Word_Types_Set_Table[9])
            {
                TempString = GPZDA_to_string($GPS_GPZDA);
                uart_puts(UART_ID, TempString);
                uart_puts(UART_ID, "\r\n");

                if (Debug_Mode)
                {
                    printf("09: %s\n", TempString);
                }
                free(TempString);
            }

            GPS_Uart_Rx = true;
            GPS_Uart_Tx = false;
        }

        // if debug mode enabled, print memory statistics

        if (Debug_Hart_Beat)
        {
            if (Debug_Mode)
            {
                gpio_put(RED_LED_POWER, 0);
                printf("Memory allocated: %d\n", getFreeHeap());
                Debug_Hart_Beat = false;
            }
        }

        //
    }
}
