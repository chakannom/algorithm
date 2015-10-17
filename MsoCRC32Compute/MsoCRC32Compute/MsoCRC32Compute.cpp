/**************************************************************************
MsoCRC32Compute Algorithm by (MS-OSHARED - v20140204)

2.4.3 MsoCrc32Compute
  The purpose of this algorithm is to calculate a cyclic redundancy check(CRC)
 checksum. Given a data stream, this function computes a 32-bit checksum using
 the polynomial x^32+x^7+x^5+x^3+x2+x+1. The algorithm uses big-endian bit
 ordering in a byte (most significant bit first). Normal representation for
 a polynomial is xAF.

2.4.3.1 Caching Algorithm
  The caching algorithm is run once and its purpose is to initiate Cache - an
  array of 256 integers.
 ---------------------------------------------------------------------------
	SUBROUTINE InitCrcCache()
		IF Called once
			RETURN
		END IF
		FOR each Index from 0 to 255
			SET Value to Index
			SHIFT Value left by 24 bits
			FOR Bit from 0 to 7
				IF highest (32st) bit of Value is set
					SHIFT Value left by 1 bit
					Bitwise exclusive-OR Value with xAF
				ELSE
					SHIFT Value left by 1 bit
				END IF
			END FOR
			AND Value with 0xFFFF
			SET Cache[Index] to Value
		END LOOP
	END SUBROUTINE
 ---------------------------------------------------------------------------

2.4.3.2 CRC Computation
  Given a stream (1) of data, or an array of bytes, this function computes a
 32-bit checksum. The caller specifies the initial value of the checksum 
 (CrcValue). Note that the caller can split the stream (1) of data into substrams
 and call this subroutine for each of the substrams, passing in the result of
 the CRC computation from the previous substream as CrcValue.
 ---------------------------------------------------------------------------
	SUBROUTINE CRC(CrcValue, Array)
		CALL InitCrcCache()
		FOR each Byte from Array
			SET Index to CrcValue
			SHIFT Index right 24 bits
			Bitwise exclusive-OR Index with Byte
			SHIFT CrcValue left 8 bits
			Bitwise exclusive-OR CrcValue with Cache[Index]
		END LOOP
		RETURN CrcValue
	END SUBROUTINE
 ---------------------------------------------------------------------------

 * Array's value is the data portion of the XF records. It doesn't contain the record's type and size.
**************************************************************************/


#include <stdio.h>
#include <malloc.h>

typedef unsigned char      BYTE;    // Byte is a char (size: 1)
typedef unsigned short int WORD16;  // 16-bit word is a short int (size: 2)
typedef unsigned int       WORD32;  // 32-bit word is an int (size: 4)

#define POLYNOMIAL 0xAF      // Standard CRC-32 ppolynomial
#define INITIAL 0xFFFF

static WORD32 cache[256];

void InitCrcCache();
WORD32 CRC(WORD32 crcValue, BYTE *array, WORD32 arraySize);

void main()
{
	InitCrcCache();

	for (int i=0; i<256; i++) {
		printf("%03d=%lx, ", i, cache[i]);
		if(i%7 == 0) printf("\n");
	}

	printf("\n\n");


	WORD32 crc, check;

	BYTE in_frame[20];
	BYTE out_frame[20];

	in_frame[0] = 0x55;
	in_frame[1] = 0xA1;
	in_frame[2] = 0x12;
	in_frame[3] = 0x34;
	in_frame[4] = 0x43;
	in_frame[5] = 0xAF;

	crc = CRC(0, in_frame, 4);
	printf("------- CRC-32 TEST ------\n");
	printf("%lX", crc);


	out_frame[0] = in_frame[0];
	out_frame[1] = in_frame[1];
	out_frame[2] = in_frame[2];
	out_frame[3] = in_frame[3];
	out_frame[4] = in_frame[4];
	out_frame[5] = in_frame[5];
	out_frame[4] = (crc & 0xFF000000) >> 24;
	out_frame[5] = (crc & 0x00FF0000) >> 16;
	out_frame[6] = (crc & 0x0000FF00) >> 8;
	out_frame[7] = (crc & 0x000000FF);
	check = CRC(0, out_frame, 8);
	printf("\nReceiver CRC check = %lX\n", check);
}

void InitCrcCache()
{
	register WORD32 index, bit;
	register WORD32 value;
	for (index=0; index<256; index++) {
		value = index << 24;
		for (bit=0; bit<8; bit++) {
			if (value & 0x80000000) {
				value = (value << 1) ^ POLYNOMIAL;
			} else {
				value = (value << 1);
			}
		}
		cache[index] = value & INITIAL;
	}
}

WORD32 CRC(WORD32 crcValue, BYTE *array, WORD32 arraySize)
{
	register WORD32 index, j;
	for (j=0; j<arraySize; j++) {
		index = (crcValue >> 24) ^ *array++;
		crcValue = (crcValue << 8) ^ cache[index];
	}
	return crcValue;
}