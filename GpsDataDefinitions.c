
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GpsDataDefinitions.h"

int GPS_Word_Types_Set_Table[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

GPS_GPGGA $GPS_GPGGA; // Static GPGGA packet
GPS_GPGLL $GPS_GPGLL; // Static GPGLL packet
GPS_GPGSA $GPS_GPGSA; // Static GPGSA packet

GPS_GPGSV $GPS_GPGSV_1; // First static GPGSV packet
GPS_GPGSV $GPS_GPGSV_2; // Second static GPGSV packet
GPS_GPGSV $GPS_GPGSV_3; // Third static GPGSV packet
GPS_GPGSV $GPS_GPGSV_4; // Fourth static GPGSV packet

GPS_GPRMC $GPS_GPRMC; // Static GPRMC packet
GPS_GPVTG $GPS_GPVTG; // Static GPVTG packet
GPS_GPZDA $GPS_GPZDA; // Static GPZDA packet

int GPS_Word_Checksum_Validation(char *string, char *checksum)
{
    // Compute the checksum by XORing all the character values in the string.
    int TempChecksum = 0;
    char hexsum[3]; // two characters for the hexadecimal representation and one for the null terminator

    for (int i = 0; i < strlen(string); i++)
    {
        TempChecksum = TempChecksum ^ string[i];
    }

    // Convert it to hexadecimal (base-16, upper case, most significant nybble first).

    sprintf(hexsum, "%02X", TempChecksum);

    // Compare two checksums and return 1 if checksums match

    if (strcmp(checksum, hexsum) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Pad_string(char *string, int length)
{
    int Baselength = strlen(string);
    char TempStr[15];

    int Char_Count = strlen(string);
    strcpy(TempStr, string);
    for (int x = 0; x < length - Char_Count; x++)
    {
        strcat(TempStr, "0");
    }
    strcpy(string, TempStr);
}

char *GPGGA_to_string(GPS_GPGGA GPGGA)
{
    char *NewOutStr = malloc(100 * sizeof(char));
    char buffer[15];

    memset(NewOutStr, 0, 100);

    strcat(NewOutStr, GPGGA.MessageID);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%010.3f", GPGGA.UTC);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%09.4f", GPGGA.Latitude);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGGA.Direction_of_latitude);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%010.4f", GPGGA.Longitude);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGGA.Direction_of_longitude);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGGA.GPS_Quality_indicator);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGGA.Sat_In_Use); // Pad two
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%04.1f", GPGGA.HDOP);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%07.1f", GPGGA.Altitude);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGGA.Altitude_Unit);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%06.1f", GPGGA.Undulation);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGGA.Undulation_Units);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%05.1f", GPGGA.Age);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGGA.Reference_ID); // Pad four

    strcat(NewOutStr, GPGGA.checksum);

    return NewOutStr;
}

char *GPGLL_to_string(GPS_GPGLL GPGLL)
{
    char *NewOutStr = malloc(100 * sizeof(char));
    char buffer[15];

    memset(NewOutStr, 0, 100);

    strcat(NewOutStr, GPGLL.MessageID);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%09.4f", GPGLL.Latitude);

    strcat(NewOutStr, buffer);

    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGLL.Direction_of_latitude);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%010.4f", GPGLL.Longitude);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGLL.Direction_of_longitude);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%010.3f", GPGLL.UTC);

    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGLL.Status);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGLL.checksum);

    return NewOutStr;
}

char *GPGSA_to_string(GPS_GPGSA GPGSA)
{
    char *NewOutStr = malloc(100 * sizeof(char));
    char buffer[15];

    memset(NewOutStr, 0, 100);

    strcat(NewOutStr, GPGSA.MessageID);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGSA.Mode_1);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGSA.Mode_2);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGSA.Sat_ID_1);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGSA.Sat_ID_2);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGSA.Sat_ID_3);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGSA.Sat_ID_4);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPGSA.Sat_ID_5);
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_6);  Not in use
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_7);  Not in use
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_8);  Not in use
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_8);  Not in use
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_9);  Not in use
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_10); Not in use
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_11); Not in use
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSA.Sat_ID_12); Not in use

    snprintf(buffer, 15, "%01.1f", GPGSA.PDOP);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%01.1f", GPGSA.HDOP);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%01.1f", GPGSA.VDOP);
    strcat(NewOutStr, buffer);

    strcat(NewOutStr, GPGSA.checksum);

    return NewOutStr;
}

char *GPGSV_to_string(GPS_GPGSV GPGSV)
{
    char *NewOutStr = malloc(100 * sizeof(char));

    memset(NewOutStr, 0, 100);

    strcat(NewOutStr, GPGSV.MessageID);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Messages_Count);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Message_number);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Satellites_in_view);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Sat_ID_1);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Elevation_1);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Azimuth_1);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Signal_to_noise_1);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Sat_ID_2);
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSV.Elevation_2);  Not In Use

    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSV.Azimuth_2); Not In Use

    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Signal_to_noise_2);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Sat_ID_3);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Elevation_3);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Azimuth_3);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Signal_to_noise_3);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Sat_ID_4);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Elevation_4);
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPGSV.Azimuth_4);
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPGSV.Signal_to_noise_4); Not In Use

    strcat(NewOutStr, GPGSV.checksum);

    return NewOutStr;
}

char *GPRMC_to_string(GPS_GPRMC GPRMC)
{
    char *NewOutStr = malloc(100 * sizeof(char));
    char buffer[15];

    memset(NewOutStr, 0, 100);

    strcat(NewOutStr, GPRMC.MessageID);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%010.3f", GPRMC.UTC);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPRMC.Status);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%09.4f", GPRMC.Latitude);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPRMC.Direction_of_latitude);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%010.4f", GPRMC.Longitude);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPRMC.Direction_of_longitude);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%07.2f", GPRMC.Speed_knot);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%06.2f", GPRMC.True_course);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPRMC.Date_Stamp);
    strcat(NewOutStr, ",");

    // snprintf(buffer, 15, "%03.2f", GPRMC.Variation);   Not In Use
    // strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPRMC.checksum);

    return NewOutStr;
}

char *GPVTG_to_string(GPS_GPVTG GPVTG)
{
    char *NewOutStr = malloc(100 * sizeof(char));
    char buffer[15];

    memset(NewOutStr, 0, 100);

    strcat(NewOutStr, GPVTG.MessageID);
    strcat(NewOutStr, ",");

    // snprintf(buffer, 15, "%06.3f", GPVTG.Track_true); Not in use
    // strcat(NewOutStr, buffer); Not in use
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPVTG.T_Indicator);
    strcat(NewOutStr, ",");

    // snprintf(buffer, 15, "%04.4f", GPVTG.Track_mag);
    // strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPVTG.M_Indicator);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%04.2f", GPVTG.Speed_knot);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPVTG.N_Indicator);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%03.1f", GPVTG.Speed_Km);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPVTG.K_Indicator);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPVTG.Mode_ind);

    strcat(NewOutStr, GPVTG.checksum);

    return NewOutStr;
}

char *GPZDA_to_string(GPS_GPZDA GPZDA)
{
    char *NewOutStr = malloc(100 * sizeof(char));
    char buffer[15];

    memset(NewOutStr, 0, 100);

    strcat(NewOutStr, GPZDA.MessageID);
    strcat(NewOutStr, ",");

    snprintf(buffer, 15, "%07.3f", GPZDA.UTC);
    strcat(NewOutStr, buffer);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPZDA.Day);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPZDA.Month);
    strcat(NewOutStr, ",");

    strcat(NewOutStr, GPZDA.Year);
    strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPZDA.Zone_description); Not in use
    // strcat(NewOutStr, ",");

    // strcat(NewOutStr, GPZDA.Zone_minutes);  Not in use
    strcat(NewOutStr, ",");
    strcat(NewOutStr, GPZDA.checksum);

    return NewOutStr;
}

void GPS_Data_populate(char **GPS_Data, int Type)
{

    switch (Type)
    {
    case 0: // GPS_GPGGA
    {
        strcpy($GPS_GPGGA.MessageID, GPS_Header_Types[0]);

        $GPS_GPGGA.UTC = atof(GPS_Data[0]);
        $GPS_GPGGA.Latitude = atof(GPS_Data[1]);
        strcpy($GPS_GPGGA.Direction_of_latitude, GPS_Data[2]);
        $GPS_GPGGA.Longitude = atof(GPS_Data[3]);
        strcpy($GPS_GPGGA.Direction_of_longitude, GPS_Data[4]);
        strcpy($GPS_GPGGA.GPS_Quality_indicator, GPS_Data[5]);

        Pad_string(GPS_Data[6], 2);

        strcpy($GPS_GPGGA.Sat_In_Use, GPS_Data[6]);

        $GPS_GPGGA.HDOP = atof(GPS_Data[7]);
        $GPS_GPGGA.Altitude = atof(GPS_Data[8]);

        strcpy($GPS_GPGGA.Altitude_Unit, GPS_Data[9]);

        $GPS_GPGGA.Undulation = atof(GPS_Data[10]);

        strcpy($GPS_GPGGA.Undulation_Units, GPS_Data[11]);

        $GPS_GPGGA.Age = atof(GPS_Data[12]);

        Pad_string(GPS_Data[13], 4);

        strcpy($GPS_GPGGA.Reference_ID, GPS_Data[13]);
        strcpy($GPS_GPGGA.checksum, GPS_Data[14]);

        GPS_Word_Types_Set_Table[0] = 1;

        break;
    }
    case 1: // GPS_GPGLL
    {
        strcpy($GPS_GPGLL.MessageID, GPS_Header_Types[1]);

        $GPS_GPGLL.Latitude = atof(GPS_Data[0]);
        strcpy($GPS_GPGLL.Direction_of_latitude, GPS_Data[1]);
        $GPS_GPGLL.Longitude = atof(GPS_Data[2]);
        strcpy($GPS_GPGLL.Direction_of_longitude, GPS_Data[3]);
        $GPS_GPGLL.UTC = atof(GPS_Data[4]);
        strcpy($GPS_GPGLL.Status, GPS_Data[5]);

        strcpy($GPS_GPGLL.Mode_ind, GPS_Data[6]);

        strcpy($GPS_GPGLL.checksum, GPS_Data[7]);

        GPS_Word_Types_Set_Table[1] = 1;

        break;
    }
    case 2: // GPS_GPGSA
    {
        // GPS_GPGSA _GPS_GPGSA;

        strcpy($GPS_GPGSA.MessageID, GPS_Header_Types[2]);

        strcpy($GPS_GPGSA.Mode_1, GPS_Data[0]);
        strcpy($GPS_GPGSA.Mode_2, GPS_Data[1]);

        Pad_string(GPS_Data[2], 2);

        strcpy($GPS_GPGSA.Sat_ID_1, GPS_Data[2]);
        Pad_string(GPS_Data[3], 2);

        strcpy($GPS_GPGSA.Sat_ID_2, GPS_Data[3]);
        Pad_string(GPS_Data[4], 2);

        strcpy($GPS_GPGSA.Sat_ID_3, GPS_Data[4]);
        Pad_string(GPS_Data[5], 2);

        strcpy($GPS_GPGSA.Sat_ID_4, GPS_Data[5]);
        Pad_string(GPS_Data[6], 2);

        strcpy($GPS_GPGSA.Sat_ID_5, GPS_Data[6]);
        Pad_string(GPS_Data[7], 2);

        strcpy($GPS_GPGSA.Sat_ID_6, GPS_Data[7]);

        Pad_string(GPS_Data[8], 2);
        strcpy($GPS_GPGSA.Sat_ID_7, GPS_Data[8]);
        Pad_string(GPS_Data[9], 2);
        strcpy($GPS_GPGSA.Sat_ID_8, GPS_Data[9]);
        strcpy($GPS_GPGSA.Sat_ID_9, GPS_Data[10]);
        strcpy($GPS_GPGSA.Sat_ID_10, GPS_Data[11]);
        strcpy($GPS_GPGSA.Sat_ID_11, GPS_Data[12]);
        strcpy($GPS_GPGSA.Sat_ID_12, GPS_Data[13]);

        $GPS_GPGSA.PDOP = atof(GPS_Data[14]);
        $GPS_GPGSA.HDOP = atof(GPS_Data[15]);
        $GPS_GPGSA.VDOP = atof(GPS_Data[16]);

        strcpy($GPS_GPGSA.checksum, GPS_Data[17]);
        //$GPS_GPGSA = _GPS_GPGSA;

        GPS_Word_Types_Set_Table[2] = 1;

        break;
    }
    case 3: // GPS_GPGSV
    {
        GPS_GPGSV _GPS_GPGSV;

        strcpy(_GPS_GPGSV.MessageID, GPS_Header_Types[3]);

        Pad_string(GPS_Data[0], 1);
        strcpy(_GPS_GPGSV.Messages_Count, GPS_Data[0]);
        Pad_string(GPS_Data[1], 1);
        strcpy(_GPS_GPGSV.Message_number, GPS_Data[1]);
        Pad_string(GPS_Data[2], 2);
        strcpy(_GPS_GPGSV.Satellites_in_view, GPS_Data[2]);
        Pad_string(GPS_Data[3], 2);
        strcpy(_GPS_GPGSV.Sat_ID_1, GPS_Data[3]);
        Pad_string(GPS_Data[4], 2);
        strcpy(_GPS_GPGSV.Elevation_1, GPS_Data[4]);
        Pad_string(GPS_Data[5], 3);
        strcpy(_GPS_GPGSV.Azimuth_1, GPS_Data[5]);
        Pad_string(GPS_Data[6], 2);
        strcpy(_GPS_GPGSV.Signal_to_noise_1, GPS_Data[6]);
        Pad_string(GPS_Data[7], 2);
        strcpy(_GPS_GPGSV.Sat_ID_2, GPS_Data[7]);
        strcpy(_GPS_GPGSV.Elevation_2, GPS_Data[8]);
        strcpy(_GPS_GPGSV.Azimuth_2, GPS_Data[9]);
        Pad_string(GPS_Data[10], 2);
        strcpy(_GPS_GPGSV.Signal_to_noise_2, GPS_Data[10]);
        Pad_string(GPS_Data[11], 2);
        strcpy(_GPS_GPGSV.Sat_ID_3, GPS_Data[11]);
        Pad_string(GPS_Data[12], 2);
        strcpy(_GPS_GPGSV.Elevation_3, GPS_Data[12]);
        Pad_string(GPS_Data[13], 3);
        strcpy(_GPS_GPGSV.Azimuth_3, GPS_Data[13]);
        Pad_string(GPS_Data[14], 2);
        strcpy(_GPS_GPGSV.Signal_to_noise_3, GPS_Data[14]);
        Pad_string(GPS_Data[15], 2);
        strcpy(_GPS_GPGSV.Sat_ID_4, GPS_Data[15]);
        Pad_string(GPS_Data[16], 2);
        strcpy(_GPS_GPGSV.Elevation_4, GPS_Data[16]);
        Pad_string(GPS_Data[17], 3);
        strcpy(_GPS_GPGSV.Azimuth_4, GPS_Data[17]);
        Pad_string(GPS_Data[18], 2);
        strcpy(_GPS_GPGSV.Signal_to_noise_4, GPS_Data[18]);

        // Pad_string(GPS_Data[19], 3);

        strcpy(_GPS_GPGSV.checksum, GPS_Data[19]);

        if (_GPS_GPGSV.Message_number[0] == '1')
        {
            $GPS_GPGSV_1 = _GPS_GPGSV;
            GPS_Word_Types_Set_Table[3] = 1;
        }
        else if (_GPS_GPGSV.Message_number[0] == '2')
        {
            $GPS_GPGSV_2 = _GPS_GPGSV;
            GPS_Word_Types_Set_Table[4] = 1;
        }
        else if (_GPS_GPGSV.Message_number[0] == '3')
        {
            $GPS_GPGSV_3 = _GPS_GPGSV;
            GPS_Word_Types_Set_Table[5] = 1;
        }
        else if (_GPS_GPGSV.Message_number[3] == '4')
        {
            $GPS_GPGSV_4 = _GPS_GPGSV;
            GPS_Word_Types_Set_Table[6] = 1;
        }

        break;
    }
    case 4: // GPS_GPRMC
    {
        strcpy($GPS_GPRMC.MessageID, GPS_Header_Types[4]);

        $GPS_GPRMC.UTC = atof(GPS_Data[0]);
        strcpy($GPS_GPRMC.Status, GPS_Data[1]);
        $GPS_GPRMC.Latitude = atof(GPS_Data[2]);
        strcpy($GPS_GPRMC.Direction_of_latitude, GPS_Data[3]);
        $GPS_GPRMC.Longitude = atof(GPS_Data[4]);
        strcpy($GPS_GPRMC.Direction_of_longitude, GPS_Data[5]);
        $GPS_GPRMC.Speed_knot = atof(GPS_Data[6]);
        $GPS_GPRMC.True_course = atof(GPS_Data[7]);

        Pad_string(GPS_Data[8], 6);

        strcpy($GPS_GPRMC.Date_Stamp, GPS_Data[8]);
        $GPS_GPRMC.Variation_Degrees = atof(GPS_Data[9]);
        strcpy($GPS_GPRMC.Variation_direction, GPS_Data[10]);
        strcpy($GPS_GPRMC.Mode_ind, GPS_Data[11]);

        Pad_string(GPS_Data[12], 3);
        strcpy($GPS_GPRMC.checksum, GPS_Data[12]);

        GPS_Word_Types_Set_Table[7] = 1;

        break;
    }
    case 5: // GPS_GPVTG
    {
        strcpy($GPS_GPVTG.MessageID, GPS_Header_Types[5]);

        $GPS_GPVTG.Track_true = atof(GPS_Data[0]);
        strcpy($GPS_GPVTG.T_Indicator, GPS_Data[1]);
        $GPS_GPVTG.Track_mag = atof(GPS_Data[2]);
        strcpy($GPS_GPVTG.M_Indicator, GPS_Data[3]);
        $GPS_GPVTG.Speed_knot = atof(GPS_Data[4]);
        strcpy($GPS_GPVTG.N_Indicator, GPS_Data[5]);
        $GPS_GPVTG.Speed_Km = atof(GPS_Data[6]);
        strcpy($GPS_GPVTG.K_Indicator, GPS_Data[7]);
        strcpy($GPS_GPVTG.Mode_ind, GPS_Data[8]);

        Pad_string(GPS_Data[9], 3);
        strcpy($GPS_GPVTG.checksum, GPS_Data[9]);

        GPS_Word_Types_Set_Table[8] = 1;

        break;
    }
    case 6: // GPS_GPZDA
    {
        strcpy($GPS_GPZDA.MessageID, GPS_Header_Types[6]);

        $GPS_GPZDA.UTC = atof(GPS_Data[0]);
        Pad_string(GPS_Data[1], 2);
        strcpy($GPS_GPZDA.Day, GPS_Data[1]);
        Pad_string(GPS_Data[2], 2);
        strcpy($GPS_GPZDA.Month, GPS_Data[2]);
        Pad_string(GPS_Data[3], 4);
        strcpy($GPS_GPZDA.Year, GPS_Data[3]);
        strcpy($GPS_GPZDA.Zone_description, GPS_Data[4]);
        strcpy($GPS_GPZDA.Zone_minutes, GPS_Data[5]);
        strcpy($GPS_GPZDA.checksum, GPS_Data[6]);

        GPS_Word_Types_Set_Table[9] = 1;

        break;
    }
    }

    // Memory dealocation section

    for (int i = 0; i < 40; i++)
    {
        free(GPS_Data[i]);
    }
    free(GPS_Data);
    // free(TempString);
}

int GPS_Word_Initialiser(char *string, int BufferSize)
{
    // Detect Header Type
    char *stringCopy = malloc(BufferSize * sizeof(char *));
    memset(stringCopy, 0, BufferSize);
    int _continue = 1;
    int stuckRetry = 1;

    strcpy(stringCopy, string);

    while (_continue == 1)
    {
        int y = strcspn(stringCopy, "$");

        int stringCopyLength = strlen(stringCopy);

        int HeaderIndex = 10;

        char Word_Header[7] = {'\0'};

        strncpy(Word_Header, stringCopy + y, 6);

        for (int x = 0; x < 8; x++)
        {
            if (strcmp(Word_Header, GPS_Header_Types[x]) == 0)
            {
                HeaderIndex = x;
                break;
            }
        }

        if (HeaderIndex != 10)
        {
            GPS_Word_Strip(stringCopy, 100, y, HeaderIndex, BufferSize);
        }

        if (stringCopyLength < 1 || stuckRetry > 99)
        {
            free(stringCopy);
            return (1);
            break;
        }
        stuckRetry++;
    }
    free(stringCopy);
    return (0);
}

char **GPS_Word_Deconstruct(char *string, int length)
{

    char TempStr[100] = {'\0'};

    char **GPS_Temp_Word_Array = malloc(40 * sizeof(char *));

    for (int i = 0; i < 40; i++) // initilise the array
    {
        GPS_Temp_Word_Array[i] = malloc(30 * sizeof(char));
        memset(GPS_Temp_Word_Array[i], 0, 30);
    }

    int TempArrayIndex = 0;
    int Stringlength = strlen(string);

    memset(TempStr, 0, 100);
    strncpy(TempStr, string, (Stringlength - 3)); // Separate checksum and copy string

    for (int x = 0; x < Stringlength; x++)
    {
        int startIndex = strcspn(TempStr, ",");
        int StrLength = strlen(TempStr);

        if (startIndex != strlen(TempStr))
        {

            char NewTempStr[100];
            char WordTemp[30];
            memset(NewTempStr, 0, 100);

            strncpy(NewTempStr, TempStr + startIndex + 1, StrLength);

            int EndIndex = strcspn(NewTempStr, ",");
            memset(WordTemp, 0, 30);
            strncpy(WordTemp, TempStr + startIndex + 1, EndIndex);

            memset(TempStr, 0, 100);
            strcpy(TempStr, NewTempStr);

            if (WordTemp[0] == 0)
            {
                strcpy(WordTemp, "0");
            }
            strcpy(GPS_Temp_Word_Array[TempArrayIndex], WordTemp);
            // GPS_Temp_Word_Array[TempArrayIndex] = WordTemp;
            TempArrayIndex++;
        }
        else
        {
            char ChecksumWord[3];
            memset(ChecksumWord, 0, 3);
            strncpy(ChecksumWord, string + (Stringlength - 3), Stringlength); // Last Checksum word
            strcpy(GPS_Temp_Word_Array[TempArrayIndex], ChecksumWord);

            // GPS_Temp_Word_Array[TempArrayIndex] = ChecksumWord;
            break;
        }
    }
    return GPS_Temp_Word_Array; // Return data array
}

int GPS_Word_Strip(char *GPS_sentence, int Word_Length, int Word_Start_index, int Type, int BufferSize)
{
    char GPS_Word[Word_Length];
    char TempStr[BufferSize];
    char TempChecksumBuffer[BufferSize];
    char Checksum[3];

    memset(TempChecksumBuffer, 0, BufferSize);

    strncpy(GPS_Word, GPS_sentence + Word_Start_index, Word_Length);
    int Word_End_Index = strcspn(GPS_Word, "*");

    if (Word_End_Index != Word_Length)
    {
        memset(GPS_Word, 0, Word_Length);
        strncpy(GPS_Word, GPS_sentence + Word_Start_index, Word_End_Index + 3);
        strncpy(TempStr, GPS_sentence + Word_Start_index + Word_End_Index + 3, BufferSize - Word_End_Index);
        memset(GPS_sentence, 0, BufferSize);

        memcpy(GPS_sentence, TempStr, BufferSize);

        int GPS_Real_Word_Length = strlen(GPS_Word);

        strncpy(TempChecksumBuffer, GPS_Word + 1, GPS_Real_Word_Length - 4);
        strncpy(Checksum, GPS_Word + (GPS_Real_Word_Length - 2), 3);

        if (GPS_Word_Checksum_Validation(TempChecksumBuffer, Checksum) == 1)
        {
            GPS_Data_populate(GPS_Word_Deconstruct(GPS_Word, Word_Length), Type);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}