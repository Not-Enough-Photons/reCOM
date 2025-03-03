#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "gamez/zMath/zmath.h"

class _zvid_public;

class CValve;
class CWindow;
class CRdrIO;

enum _zvid_mode
{
	ZVID_MODE_NTSC,
	ZVID_MODE_PAL,
	ZVID_MODE_DTV480P,
	ZVID_MODE_NUM
};

void zVid_Init(_zvid_mode mode);
void zVid_Uninit();
void zVid_CreateWindow();
void zVid_Open();
void zVid_Swap(bool doSwap);
void zVid_FrameRestore();
void zVid_ClearColor(f32 red, f32 green, f32 blue);
void zVid_Sync0();
void zVid_ZTestOn();
void zVid_ZTestOff();
void zVid_ZTestOnWriteSet(bool set);

void zvid_MpegReset();
void zvid_SetVideoMode(_zvid_mode mode);

void uninitPssAudio();

extern bool doAudio;
extern _zvid_public zVid;
extern CWindow* theWindow;

extern CValve* lodLevel;

class _zvid_public
{
public:
	u32 wideFrameFlag;

	bool showTextureBuffer;
	bool showTextureBufferFormat;

	s64 frameNumber;
	u32 frameRate;
	f32 frameTime;
	f32 runTime;
	f32 procTime;

	f32 aspect[2];
	void* displayBuf;
	void* renderBuf;
	u32 renderWidth;
	u32 renderHeight;
	f32 minZ;
	f32 maxZ;

	u32 textureBaseAddr;
	u32 textureEndAddr;

	_zvid_mode videoMode;
	_zvid_mode vidMode;

	f32 hblnkRate;

	bool doMpeg224;

	bool pcrtcDo;
	IPNT2D pcrtcOffset;

	s64 ztest_on;
	s64 ztest_off;

	s64 dmaFrameRestore;
};

class CWindow
{
public:
	CWindow();
	CWindow(CRdrIO* reader);
	CWindow(const char* name, u32 width, u32 height);
	
	SDL_Window* GetWindow() const;
	SDL_Renderer* GetRenderer() const;

	f32 GetWidth() const { return m_width; }
	f32 GetHeight() const { return m_height; }
private:
	char* m_name;
	u32 m_width;
	u32 m_height;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};

class CVideo
{
public:
	static void Clear(u8 r, u8 g, u8 b, u8 a) { }
	static void RestoreImage(const char* img, bool raw = false);
};

class CMPEG
{
public:
	void Uninit();
};