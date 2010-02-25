#ifndef CRC_H
#define CRC_H

#include "../globals.h"
#include <sys/types.h>
#include <stdlib.h>

class CRC
{
public:
	static BYTE makeCRC(const BYTE* data, size_t size);
	static bool checkCRC(const BYTE * data, size_t size);
private:
	static BYTE genCrc8(BYTE inCrc, BYTE inData);
};

#endif
