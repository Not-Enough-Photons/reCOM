#pragma once

void zVid_Init();
void zVid_Open();
void zVid_Swap(int buffer);

class CVideo
{
public:
	static void RestoreImage(const char* img);
};