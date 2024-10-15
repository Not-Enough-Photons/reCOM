#include <iostream>
#include <fstream>
#include "system\zsys_main.h"

void* LoadZAR()
{
	const char* path = "C:/Users/Adam/Desktop/ZWEAPON.ZAR";
	std::ifstream stream(path, std::ios_base::binary);

	stream.seekg(0, stream.end);
	int length = stream.tellg();
	stream.seekg(0, stream.beg);

	char* buf = new char[length];
	stream.read(buf, length);
	stream.close();

	return &buf;
}

int main()
{
	void* zar = LoadZAR();

	delete[] zar;
	return 0;
}