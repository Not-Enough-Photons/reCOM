#include <iostream>
#include "reader/zrdr_parse.h"

int main()
{
	char* fileBuf = "run/WEAPONS.ZAR";
	char* readBuf = new char[16];

	zdb::FlipBytes(fileBuf, readBuf, 8);

	std::cout << readBuf << std::endl;

	return 0;
}