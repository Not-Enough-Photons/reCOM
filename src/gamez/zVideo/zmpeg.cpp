#include <iostream>

#include "gamez/zVideo/zvid.h"

bool mpegBuffAlloc = false;
bool rgb32Alloc = false;
bool path3tagAlloc = false;
bool demuxBuffAlloc = false;
bool audioBuffAlloc = false;
void* rsrcs = 0;

void CMPEG::Uninit()
{
	// uninitPssAudio();

	if (mpegBuffAlloc)
	{
		free(rsrcs);
	}

	if (rgb32Alloc)
	{

	}

	if (path3tagAlloc)
	{

	}

	if (demuxBuffAlloc)
	{

	}

	if (audioBuffAlloc)
	{

	}

	rsrcs = NULL;
}