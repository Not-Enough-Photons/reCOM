#pragma once
#include "gamez/zMath/zmath_main.h"

void zVid_Init();
void zVid_Uninit();
void zVid_Open();
void zVid_Swap(int buffer);
void zVid_FrameRestore();
void zVid_ClearColor(unsigned int* bit);
void zVid_Sync0();
void zVid_ZTestOn();
void zVid_ZTestOff();
void zVid_ZTestOnWriteSet(bool set);

void zvid_MpegReset();
void zvid_SetVideoMode(_zvid_mode mode);

void uninitPssAudio();

bool doAudio = false;

enum _zvid_mode
{
	NTSC,
	PAL
};

class _zvid_public
{
public:
	unsigned int wideFrameFlag;

	bool showTextureBuffer;
	bool showTextureBufferFormat;

	long frameNumber;
	unsigned int frameRate;
	float frameTime;
	float runTime;
	float procTime;

	float aspect[2];
	void* displayBuf;
	void* renderBuf;
	unsigned int renderWidth;
	unsigned int renderHeight;
	float minZ;
	float maxZ;

	unsigned int textureBaseAddr;
	unsigned int textureEndAddr;

	_zvid_mode videoMode;
	_zvid_mode vidMode;

	float hblnkRate;

	bool doMpeg224;

	bool pcrtcDo;
	IPNT2D pcrtcOffset;

	long ztest_on;
	long ztest_off;

	long dmaFrameRestore;
};

_zvid_public zVid;

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