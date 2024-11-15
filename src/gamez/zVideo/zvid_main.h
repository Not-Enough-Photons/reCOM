#pragma once

void zVid_Init();
void zVid_Open();
void zVid_Swap(int buffer);

void uninitPssAudio();

bool doAudio = false;

class CVideo
{
public:
	static void RestoreImage(const char* img);
};

class CMPEG
{
public:
	void Uninit();
};