#ifndef CRC32
#define CRC32
#pragma once

#define LittleLong( val )           ( val )

#define CRC32_INIT_VALUE 0xFFFFFFFFUL
#define CRC32_XOR_VALUE  0xFFFFFFFFUL

#define NUM_BYTES 256

typedef unsigned long CRC32_t;

void CRC32_Init( CRC32_t *pulCRC );
void CRC32_ProcessBuffer( CRC32_t *pulCRC , const void *p , int len );
void CRC32_Final( CRC32_t *pulCRC );
CRC32_t	CRC32_GetTableEntry( unsigned int slot );

inline CRC32_t CRC32_ProcessSingleBuffer( const void *p , int len );

#endif;