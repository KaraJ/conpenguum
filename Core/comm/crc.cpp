#include "crc.h"

#define POLYNOMIAL    (0x1070U << 3)

BYTE CRC::genCrc8(BYTE inCrc, BYTE inData)
{
	unsigned short  data;

	data = inCrc ^ inData;
	data <<= 8;

	for (size_t i = 0; i < 8; i++ ) 
	{
		if ((data & 0x8000) != 0 )
			data = data ^ POLYNOMIAL;
		data = data << 1;
	}
	return (BYTE) (data >> 8);
}

BYTE CRC::makeCRC(const BYTE* data, size_t size)
{
	BYTE* buff = (BYTE*)malloc(sizeof(BYTE) * (size));

	for (size_t i = 0; i < size; ++i)
		buff[i] = data[i];

	BYTE crc = 0;

	for (size_t i = 0; i < size; ++i)
		crc = genCrc8(crc, buff[i]);
        //Im in ur code fixin ur memory leaks
        free(buff);
	return crc;
}

bool CRC::checkCRC(const BYTE * data, size_t size)
{
	BYTE* buff = (BYTE*)malloc(sizeof(BYTE) * (size));

	for (size_t i = 0; i < size; ++i)
		buff[i] = data[i];

	BYTE crc = 0;

	for (size_t i = 0; i < size; ++i)
		crc = genCrc8(crc, buff[i]);
	free(buff);
	return crc == 0;
}
