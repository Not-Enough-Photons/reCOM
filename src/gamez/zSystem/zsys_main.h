#pragma once
#include <stdlib.h>
#include <cstring>
#include <cassert>

void InitSystemTuners();
void zSysMain();
void zSysReset();

size_t zsys_FullAllocAndFree();

void zAllocateAssert(bool condition, const char* sourceFile, int line);
void* zAllocateAlign(size_t alignment, size_t size, const char* sourceFile, int line);
void* zAllocateArray(int size, int count, const char* sourceFile, int line);
void* zAllocateString(const char* str, const char* sourceFile, int line);
void* zReAllocate(void* ptr, size_t size, const char* sourceFile, int line);
void* zAllocate(size_t size, const char* sourceFile, int line);
void* zAllocateInst(void* instance, const char* sourceFile, int line);

_zsys_public zSys;

struct four
{
	four* next;
};

struct twelve
{
	twelve* next;
	unsigned int dummy[2];
};

template<typename T>
class _zmalloc
{
public:
	_zmalloc(size_t count);
	~_zmalloc();
private:
	T* m_page;
	T* m_head;
	T* m_tail;

	unsigned int m_bytes;
	unsigned int m_size;
	unsigned int m_count;
	unsigned int m_peak;
	unsigned int m_overflow;
};

class _zsys_public
{
public:
	void* DmaToVif0;
	void* DmaToVif1;
	void* DmaToGif;
	void* DmaFromSPR;

	long sprPacketEnd[2];

	int sprPx;

	bool isT10K;
	bool isCdBoot;
	bool cdSounds;
	bool memIrxLoaded;

	unsigned int timerTicksPerSecond;
	float timerScale;
};

class CSched_Manager
{
public:
	static void Clear(const char* sched);
};

class CSaveManager
{

};

class CSaveModule
{
public:
	CSaveModule(const char* module, CSaveManager* mcSaveManager);
	~CSaveModule();
public:
};