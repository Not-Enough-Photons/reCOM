#pragma once
#include <list>
#include <stdlib.h>
#include <cstring>
#include <cassert>

/// -------------------------------------------
/// PRIMITIVE TYPES
/// -------------------------------------------

typedef uint8_t    u8;  // unsigned char
typedef uint16_t   u16; // unsigned short
typedef uint32_t   u32; // unsigned int
typedef uint64_t   u64; // unsigned long
typedef int8_t     s8;  // char
typedef int16_t    s16; // short
typedef int32_t    s32; // int
typedef int64_t    s64; // long
typedef float_t    f32; // float

/// -------------------------------------------
/// USEFUL MACROS
/// -------------------------------------------

#define BITFIELD_INT(x, cnt) int x : cnt
#define BITFIELD_UINT(x, cnt) unsigned int x : cnt

typedef unsigned long long long128;
typedef bool(*ScheduledTask)(float, void*);

void InitSystemTuners();
void zSysInit();
void zSysPostInit();
void zSysMain();
void zSysReset();
void zSysFifoEnd();
size_t zsys_FullAllocAndFree();

void zVid_Assert(bool condition, unsigned int mask, const char* source, int line);

void* operator new(size_t size);
void* __malloc(size_t size);
void* __calloc(size_t num, size_t size);
void* __realloc(void* ptr, size_t new_size);
void* __memalign(size_t alignment, size_t size);
char* __strdup(const char* str);
void __free(void* block);

struct _zsys_public;
class CTTY;

extern size_t _HeapSize;

extern _zsys_public zSys;
extern CTTY theTerminal;

struct _word128
{
	long128 u128;
	f32 f32[4];
	u64 u64[2];
	u32 u32[4];
	u16 u16[8];
	u8 u8[16];
};

struct four
{
	four* next;
};

struct twelve
{
	twelve* next;
	u32 dummy[2];
};

template<typename T>
class _zmalloc
{
public:
	_zmalloc(size_t count);
	~_zmalloc();

	void init_page();
	T* acquire(size_t size);
	bool release(T* page);
private:
	T* m_page;
	T* m_head;
	T* m_tail;

	u32 m_bytes;
	u32 m_size;
	u32 m_count;
	u32 m_peak;
	u32 m_overflow;
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

class CSched_Manager : public std::list<ScheduledTask>
{
public:
	CSched_Manager();
	~CSched_Manager();
public:
	void AddTask(const char* name, ScheduledTask task, float delta, void* buf);
	ScheduledTask GetTask(int index);
	bool RemoveTask(void* buf, bool child);
	bool RemoveTask(const char* taskName, bool child);

	void Clear();
	void ClearFreeList(bool emptyList);

	bool Tick(float delta);
private:
	bool m_inTick;
	f32 m_priority;
	std::list<ScheduledTask> m_FreeList;
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

class CTTY
{
public:
	void Print(char* buffer, size_t size);
	void Render();
};