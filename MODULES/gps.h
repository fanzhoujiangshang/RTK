#ifndef _GPS_H_
#define _GPS_H_
#endif

extern u8 GPS_ReceiveBuffer[256];
extern u8 GPS_RecDataIndex;
extern u8 GPS_RecDataIndex_Old;
extern void init_UBLOX(void);
extern void GPS_Handle(void);

typedef struct
{
	double m_UTC_Position;
	double m_Latitude;
	double m_Longitude;
	int32_t m_PositionFixIndicator;
	int32_t m_SatellitesUsed;
}GPS_RawData;
typedef struct
{
	u8 m_UTC_Hour;
	u8 m_UTC_Mins;
	u8 m_UTC_Secs;
	double m_Latitude_degree;
	double m_Longitude_degree;
}GPS_Data;









