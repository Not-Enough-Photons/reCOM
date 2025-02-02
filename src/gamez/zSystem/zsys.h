#pragma once
#include <list>
#include <stdlib.h>
#include <cstring>
#include <cassert>
#include <string>

/// -------------------------------------------
/// ENDIAN CONVERISONS
/// -------------------------------------------
#define U16_BE(x) ((u8*)x)[1] << 0 | ((unsigned)((u8*)x)[0] << 8)
#define U32_BE(x) ((u8*)x)[3] << 0 | ((u8*)x)[2] << 8 | ((u8*)x)[1] << 16 | (unsigned)((u8*)x)[0] << 24;
#define F32_BE(x) ((u8*)x)[3] << 0 | ((u8*)x)[2] << 8 | ((u8*)x)[1] << 16 | ((u8*)x)[0] << 24;

/// -------------------------------------------
/// ALLOCATION MACROS
/// -------------------------------------------
#define zmalloc(size) __malloc(size, __FILE__, __LINE__)
#define zcalloc(num, size) __calloc(num, size, __FILE__, __LINE__)
#define zrealloc(ptr, new_size) __realloc(ptr, new_size, __FILE__, __LINE__)
#define zmemalign(alignment, size) __memalign(alignment, size, __FILE__, __LINE__)
#define zstrdup(str) __strdup(str, __FILE__, __LINE__)
#define zfree(block) __free(block, __FILE__, __LINE__)

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
typedef float      f32; // float
typedef double     f64;

/// -------------------------------------------
/// USEFUL MACROS
/// -------------------------------------------

#define BITFIELD_INT(x, cnt) int x : cnt
#define BITFIELD_UINT(x, cnt) unsigned int x : cnt

class _zsys_public;

class CTTY;
class CSched_Manager;

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
void* __malloc(size_t size, const char* file, int line);
void* __calloc(size_t num, size_t size, const char* file, int line);
void* __realloc(void* ptr, size_t new_size, const char* file, int line);
void* __memalign(size_t alignment, size_t size, const char* file, int line);
char* __strdup(const char* str, const char* file, int line);
void __free(void* block, const char* file, int line);

extern CSched_Manager zTaskScheduler;
extern size_t _HeapSize;
extern _zsys_public zSys;
extern CTTY theTerminal;
extern bool postinit;
extern bool postinited;

union _word128
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

	s64 sprPacketEnd[2];

	s32 sprPx;

	bool isT10K;
	bool isCdBoot;
	bool cdSounds;
	bool memIrxLoaded;

	u32 timerTicksPerSecond;
	f32 timerScale;
};

class CSched_Manager : public std::list<ScheduledTask>
{
public:
	void AddTask(const char* name, bool(*task)(f32, void*), f32 delta, void* buf);
	ScheduledTask GetTask(s32 index);
	bool RemoveTask(void* buf, bool child);
	bool RemoveTask(const char* taskName, bool child);

	void Clear();
	void ClearFreeList(bool emptyList);

	bool Tick(f32 delta);
private:
	bool m_inTick;
	f32 m_priority;
	std::list<ScheduledTask> m_FreeList;
};

class CSaferStr : public std::basic_string<const char*>
{
public:
	CSaferStr& operator=(const char* str)
	{
		if (str == NULL)
		{
			replace(0, -1, 0);
		}
		else
		{
			size_t len = strlen(str);
			assign(len, str);
		}

		return *this;
	}
};

class CSaveManager
{

};

class CSaveModule
{
public:
	CSaveModule(const char* module, CSaveManager* mcSaveManager) {}
public:
};

class CTTY
{
public:
	enum class ZLOG_LEVEL
	{
		LVL_INFO,
		LVL_WARN,
		LVL_ERROR,
		LVL_CRITICAL
	};
	
	void Print(char* buffer, size_t size);
	void Render();
private:
	char m_buffer[1024];
};

class CConsole
{
public:
	void Tick(f32 dT);
};