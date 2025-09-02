#ifndef GPSDATADEFINITIONS_H_INCLUDED
#define GPSDATADEFINITIONS_H_INCLUDED

/*!
 * This header outputs global positioning system fixed data       5 6 7  8
 * \note  Packet layout: $GPGGA,hhmmss.sss,llll.llll,a,yyyyy.yyyy,a,x,xx,xx.x,xxxxx.x,M,xxxx.x,M,xxx.x,xxxx*hh
 */
typedef struct GPGGA
{
    /*!
     * \brief Sentence ID
     * \note 0
     */
    char MessageID[7];

    /*!
     * \brief UTC Time in hhmmss.sss format
     * \note 1
     */
    float UTC;

    /*!
     * \brief Latitude in DDmm.mm format
     * \note 2
     */
    float Latitude;

    /*!
     * \brief Latitude direction: (N for North, S for South)
     * \note 3
     */
    char Direction_of_latitude[2];

    /*!
     * \brief Longitude in DDDmm.mm format
     * \note 4
     */
    float Longitude;

    /*!
     * \brief  Longitude direction: (E = East, W = West)
     * \note 5
     */
    char Direction_of_longitude[2];

    /*!
     * \brief GPS Quality Indicators
     * \note 6
     */
    char GPS_Quality_indicator[2];

    /*!
     * \brief Number of satellites in use
     * \note 7
     */
    char Sat_In_Use[3];

    /*!
     * \brief  Horizontal dilution of precision
     * \note 8
     */
    float HDOP;

    /*!
     * \brief  Antenna altitude above/below mean sea level
     * \note 9
     */
    float Altitude;

    /*!
     * \brief Units of antenna altitude (M = metres)
     * \note 10
     */
    char Altitude_Unit[2];

    /*!
     * \brief Undulation - the relationship between the geoid and the WGS84 ellipsoid
     * \note 11
     */
    float Undulation;

    /*!
     * \brief Units of undulation (M = metres)
     * \note 12
     */
    char Undulation_Units[2];

    /*!
     * \brief Age of correction data (in seconds)
     * \note 13
     */
    float Age;

    /*!
     * \brief Differential base station ID
     * \note 14
     */
    char Reference_ID[5];

    /*!
     * \brief Checksum
     * \note 15
     */
    char checksum[4];
} GPS_GPGGA;

/*!
 * This header outputs geographic position - latitude / longitude
 * \note  Packet layout: $GPGLL,llll.llll,a,lllll.llll,a,nnnnnn.nnn,a,a*hh
 */
typedef struct GPGLL
{
    /*!
     * \brief Sentence ID
     * \note 0
     */
    char MessageID[7];

    /*!
     * \brief Latitude ddmm.mmmm
     * \note 1
     */
    float Latitude;

    /*!
     * \brief N/S Indicator N = North, S = South
     * \note 2
     */
    char Direction_of_latitude[2];

    /*!
     * \brief Longitude dddmm.mmmm
     * \note 3
     */
    float Longitude;

    /*!
     * \brief E/W Indicator E = East, W = West
     * \note 4
     */
    char Direction_of_longitude[2];

    /*!
     * \brief  UTC Time packet in hhmmss.sss format
     * \note 5
     */
    float UTC;

    /*!
     * \brief Status packet 'A' for Valid, 'V' for Invalid
     * \note 6
     */
    char Status[2];

    /*!
     * \brief Positioning system mode indicator
     * \note 8 - Not in use
     */
    char Mode_ind[2];

    /*!
     * \brief Checksum
     * \note 9
     */
    char checksum[5];

} GPS_GPGLL;

/*!
 * This header outputs data about GPS DOP and active satellites
 * \note  Packet layout: $GPGSA,a,n,nn,nn,nn,nn,nn,,,,,,,,n.n,n.n,n.n*hh
 */
typedef struct GPGSA
{
    /*!
     * \brief Sentence ID
     * \note 0
     */
    char MessageID[7];

    /*!
     * \brief A = Automatic 2D/3D  M = Manual, forced to operate in 2D or 3D
     * \note 1
     */
    char Mode_1[2];

    /*!
     * \brief 1 = Fix not available; 2 = 2D; 3 = 3D
     * \note 2
     */
    char Mode_2[2];

    /*!
     * \brief Satellite used on channel 1
     * \note 3
     */
    char Sat_ID_1[3];

    /*!
     * \brief Satellite used on channel 2
     * \note 4
     */
    char Sat_ID_2[3];

    /*!
     * \brief Satellite used on channel 3
     * \note 5
     */
    char Sat_ID_3[3];

    /*!
     * \brief Satellite used on channel 4
     * \note 6
     */
    char Sat_ID_4[3];

    /*!
     * \brief Satellite used on channel 5
     * \note 7
     */
    char Sat_ID_5[3];

    /*!
     * \brief Satellite used on channel 6
     * \note 8
     */
    char Sat_ID_6[3];

    /*!
     * \brief Satellite used on channel 7
     * \note 9
     */
    char Sat_ID_7[3];

    /*!
     * \brief Satellite used on channel 8
     * \note 10
     */
    char Sat_ID_8[3];

    /*!
     * \brief Satellite used on channel 9
     * \note 11
     */
    char Sat_ID_9[3];

    /*!
     * \brief Satellite used on channel 10
     * \note 12
     */
    char Sat_ID_10[3];

    /*!
     * \brief Satellite used on channel 11
     * \note 13
     */
    char Sat_ID_11[3];

    /*!
     * \brief Satellite used on channel 12
     * \note 14
     */
    char Sat_ID_12[3];

    /*!
     * \brief Position dilution of precision
     * \note 15
     */
    float PDOP;

    /*!
     * \brief Horizontal dilution of precision
     * \note 16
     */
    float HDOP;

    /*!
     * \brief Vertical dilution of precision
     * \note 17a
     */
    float VDOP;

    /*!
     * \brief Checksum
     * \note 18
     */
    char checksum[4];

} GPS_GPGSA;

/*!
 * This header outputs data about GPS Satellites in view
 * \note  Packet layout: $GPGSV,n,n,nn,nn,nn,nnn,nn,nn,,,nn,nn,nn,nnn,nn,nn,nn,nnn,*hh
 */
typedef struct GPGSV
{
    /*!
     * \brief Sentence ID
     * \note 0
     */
    char MessageID[7];

    /*!
     * \brief Total number of messages (1-9)
     * \note 1
     */
    char Messages_Count[2];

    /*!
     * \brief Message number (1-9)
     * \note 2
     */
    char Message_number[2];

    /*!
     * \brief Total number of satellites in view
     * \note 3
     */
    char Satellites_in_view[3];

    /*!
     * \brief Satellite PRN number
     * \note 4
     */
    char Sat_ID_1[3];

    /*!
     * \brief Elevation, degrees, 90 maximum
     * \note 5
     */
    char Elevation_1[3];

    /*!
     * \brief Azimuth, degrees True, 000 to 359
     * \note 6
     */
    char Azimuth_1[4];

    /*!
     * \brief SNR (C/No) 00-99 dB
     * \note 7
     */
    char Signal_to_noise_1[3];

    /*!
     * \brief Satellite PRN number
     * \note 8 - not in use
     */
    char Sat_ID_2[3];

    /*!
     * \brief Elevation, degrees, 90 maximum
     * \note 9 - not in use
     */
    char Elevation_2[3];

    /*!
     * \brief Azimuth, degrees True, 000 to 359
     * \note 10 - not in use
     */
    char Azimuth_2[4];

    /*!
     * \brief SNR (C/No) 00-99 dB
     * \note 11
     */
    char Signal_to_noise_2[3];

    /*!
     * \brief Satellite PRN number
     * \note 12
     */
    char Sat_ID_3[3];

    /*!
     * \brief Elevation, degrees, 90 maximum
     * \note 13
     */
    char Elevation_3[3];

    /*!
     * \brief Azimuth, degrees True, 000 to 359
     * \note 14
     */
    char Azimuth_3[4];

    /*!
     * \brief SNR (C/No) 00-99 dB
     * \note 15
     */
    char Signal_to_noise_3[3];

    /*!
     * \brief Satellite PRN number
     * \note 16
     */
    char Sat_ID_4[3];

    /*!
     * \brief Satellite PRN number
     * \note 17
     */
    char Elevation_4[3];

    /*!
     * \brief Azimuth, degrees True, 000 to 359
     * \note 18
     */
    char Azimuth_4[4];

    /*!
     * \brief SNR (C/No) 00-99 dB
     * \note 19 - not in use
     */
    char Signal_to_noise_4[3];

    /*!
     * \brief Checksum
     * \note 20
     */
    char checksum[4];

} GPS_GPGSV;

/*!
 * This header outputs recommended minimum specific
 * GNSS data
 * \details                   0          1 2         3 4          5 6       7      8     9 10 11
 * \note  Packet layout: $GPRMC,hhmmss.sss,a,llll.llll,a,yyyyy.yyyy,a,xxxx.xx,xxx.xx,xxxxxx,,*hh
 * \details              $GPRMC,155939.906,V,0000.0000,0,    0.0000,0,0000.00,000.00,140424,,N00
 */
typedef struct GPRMC
{
    /*!
     * \brief Sentence ID
     * \note 0
     */
    char MessageID[7];

    /*!
     * \brief UTC Time in hhmmss.sss format
     * \note 1
     */
    float UTC;

    /*!
     * \brief Status A = Valid, V = Invalid
     * \note 2
     */
    char Status[2];

    /*!
     * \brief Latitude in DDmm.mm format
     * \note 3
     */
    float Latitude;

    /*!
     * \brief Latitude direction: (N for North, S for South)
     * \note 4
     */
    char Direction_of_latitude[2];

    /*!
     * \brief Longitude in DDDmm.mm format
     * \note 5
     */
    float Longitude;

    /*!
     * \brief  Longitude direction: (E = East, W = West)
     * \note 6
     */
    char Direction_of_longitude[2];

    /*!
     * \brief Speed over ground in knots
     * \note 7
     */
    float Speed_knot;

    /*!
     * \brief Degrees of true course
     * \note 8
     */
    float True_course;

    /*!
     * \brief  Date in dd/mm/yy format
     * \note 9
     */
    char Date_Stamp[7];

    /*!
     * \brief  Magnetic variation, degrees
     * \note 10 - Not in use
     */
    float Variation_Degrees;

    /*!
     * \brief  Magnetic variation direction E/W
     * \note 11 - Not in use
     */
    char Variation_direction[2];

    /*!
     * \brief Positioning system mode indicator
     * \note 12 - Not in use
     */
    char Mode_ind[2];

    /*!
     * \brief Checksum
     * \note 13
     */
    char checksum[4];

} GPS_GPRMC;

/*!
 * This header outputs actual course and speed data relative to the ground, and mode indicator
 * \note   Packet layout: $GPVTG,,a,,a,n.nn,a,n.n,a,a*hh
 */
typedef struct GPVTG
{
    /*!
     * \brief Sentence ID
     * \note 0
     */
    char MessageID[7];

    /*!
     * \brief Track made good, degrees True
     * \note 1 - Not in use
     */
    float Track_true;

    /*!
     * \brief True track indicator
     * \note 2
     */
    char T_Indicator[2];

    /*!
     * \brief Track made good, degrees Magnetic;
     * \note 3 - Not in use
     */
    float Track_mag;

    /*!
     * \brief Magnetic track indicator
     * \note 4
     */
    char M_Indicator[2];

    /*!
     * \brief Speed over ground, knots
     * \note 5
     */
    float Speed_knot;

    /*!
     * \brief Nautical speed indicator (N = Knots)
     * \note 6
     */
    char N_Indicator[2];

    /*!
     * \brief Speed, kilometres/hour
     * \note 7
     */
    float Speed_Km;

    /*!
     * \brief Speed indicator (K = km/hr)
     * \note 8
     */
    char K_Indicator[2];

    /*!
     * \brief Positioning system mode indicator
     * \note 9
     */
    char Mode_ind[2];

    /*!
     * \brief Checksum
     * \note 10
     */
    char checksum[4];

} GPS_GPVTG;

/*!
 * \struct GPS_GPVTG
 * \name GPS_GPVTG
 * This header outputs UTC, day, month, year, and local
 * time zone data
 *
 * \note  Packet layout: $GPZDA,hhmmss.sss,xx,xx,xxxx,,*hh
 */
typedef struct GPZDA
{
    /*!
     * \brief Sentence ID
     * \note 0
     */
    char MessageID[7];

    /*!
     * \brief UTC Time in hhmmss.sss format
     * \note 1
     */
    float UTC;

    /*!
     * \brief Day, 01 to 31
     * \note 2
     */
    char Day[3];

    /*!
     * \brief Month, 01 to 12
     * \note 3
     */
    char Month[3];

    /*!
     * \brief Year
     * \note 4
     */
    char Year[5];

    /*!
     * \brief Local zone description
     * \note 5 - Not in use
     */
    char Zone_description[4];

    /*!
     * \brief Local zone minutes
     * \note 6 - Not in use
     */
    char Zone_minutes[4];

    /*!
     * \brief Checksum
     * \note 7
     */
    char checksum[4];

} GPS_GPZDA;

extern GPS_GPGGA $GPS_GPGGA; // Static GPGGA packet
extern GPS_GPGLL $GPS_GPGLL; // Static GPGLL packet
extern GPS_GPGSA $GPS_GPGSA; // Static GPGSA packet

extern GPS_GPGSV $GPS_GPGSV_1; // First static GPGSV packet
extern GPS_GPGSV $GPS_GPGSV_2; // Second static GPGSV packet
extern GPS_GPGSV $GPS_GPGSV_3; // Third static GPGSV packet
extern GPS_GPGSV $GPS_GPGSV_4; // Fourth static GPGSV packet

extern GPS_GPRMC $GPS_GPRMC; // Static GPRMC packet
extern GPS_GPVTG $GPS_GPVTG; // Static GPVTG packet
extern GPS_GPZDA $GPS_GPZDA; // Static GPZDA packet

/*!
 * \brief Truth table for Gps struct sentances allocated.
 * \note Set 1 for allocated, 0 for un-allocated
 */
extern int GPS_Word_Types_Set_Table[10];

/*!
 * \brief Header types reference registry
 */
static const char *GPS_Header_Types[8] =
    {"$GPGGA", "$GPGLL", "$GPGSA", "$GPGSV", "$GPRMC", "$GPVTG", "$GPZDA", "$PSRF151"};

/*! \brief Convert GPGGA struct to char string
 *  \ingroup GPS_Structs
 *
 * \param GPGGA Accepts GPS_GPGGA struct
 * \return GPGGA struct in one string format
 */
char *GPGGA_to_string(GPS_GPGGA GPGGA);

/*! \brief Convert GPGLL struct to char string
 *  \ingroup GPS_Structs
 *
 * \param GPGLL Accepts GPS_GPGLL struct
 * \return GPGLL struct in one string format
 */
char *GPGLL_to_string(GPS_GPGLL GPGLL);

/*! \brief Convert GPGSA struct to char string
 *  \ingroup GPS_Structs
 *
 * \param GPGSA Accepts GPS_GPGSA struct
 * \return GPGSA struct in one string format
 */
char *GPGSA_to_string(GPS_GPGSA GPGSA);

/*! \brief Convert GPGSV struct to char string
 *  \ingroup GPS_Structs
 *
 * \param GPGSV Accepts GPS_GPGSV struct
 * \return GPGSV struct in one string format
 */
char *GPGSV_to_string(GPS_GPGSV GPGSV);

/*! \brief Convert GPRMC struct to char string
 *  \ingroup GPS_Structs
 *
 * \param GPRMC Accepts GPS_GPRMC struct
 * \return GPRMC struct in one string format
 */
char *GPRMC_to_string(GPS_GPRMC GPRMC);

/*! \brief Convert GPVTG struct to char string
 *  \ingroup GPS_Structs
 *
 * \param GPVTG Accepts GPS_GPVTG struct
 * \return GPVTG struct in one string format
 */
char *GPVTG_to_string(GPS_GPVTG GPVTG);

/*! \brief Convert GPZDA struct to char string
 *  \ingroup GPS_Structs
 *
 *  \param GPZDA Accepts GPS_GPZDA struct
 *  \return GPZDA struct in one string format
 */
char *GPZDA_to_string(GPS_GPZDA GPZDA);

/*! \brief Populate gps structs with data from serial buffer
 *  \ingroup GPS_Functions
 *
 *  \param GPS_Data  Whole GPS sentence in strings array format
 *  \param Type Index number of header used in the sentence
 */
void GPS_Data_populate(char **GPS_Data, int Type);

/*! \brief Takes GPS Sentence from String buffer for processing, and strips it, resulting in buffer being short of that word
 *  \ingroup GPS_Functions
 *
 *  \param GPS_sentence Whole GPS sentence in string format
 *  \param Word_Length String length of the word
 *  \param Word_Start_index Index of the first character of the GPS sentence
 *  \param Type Index number of a word type
 *  \return 1 (True) if data got populated, 0 (False) if not
 */
int GPS_Word_Strip(char *GPS_sentence, int Word_Length, int Word_Start_index, int Type, int BufferSize);

/*! \brief Digest first word out of the string buffer, forward it to the processing chair, then substract it out of the buffer. Takes two parameters
 *  \ingroup GPS_Functions
 *
 *  \param string String buffer
 *  \param length Buffer length
 *  \return 1 (True) if word was processed, 0 (False) if not
 */
int GPS_Word_Initialiser(char *string, int length);

/*! \brief Pad the string with fixed lenght zero's. Takes two parameters
 *  \ingroup GPS_Functions
 *
 *  \param string String buffer to pad
 *  \param length Desired string length.
 */
void Pad_string(char *string, int length);

/*! \brief Decostruct string buffer and return string array
 *  \ingroup GPS_Functions
 *
 *  \param string String buffer to decostruct
 *  \param length Buffer length
 *  \return String array
 */
char **GPS_Word_Deconstruct(char *string, int length);

/*! \brief Compute the checksum using a gps word and check it against checksum fed into the function
 *  \ingroup GPS_Functions
 *
 *  \param string GPS word for checksum validation
 *  \param checksum Checksum string
 *  \return 1 (True) if checksum has matched, 0 (False) if not
 */
int GPS_Word_Checksum_Validation(char *string, char *checksum);


#endif
