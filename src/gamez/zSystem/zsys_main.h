#pragma once
#include <list>
#include <stdlib.h>
#include <cstring>
#include <cassert>

typedef unsigned long long long128;
typedef bool(*ScheduledTask)(float, void*);

bool postinited = false;

void InitSystemTuners();
void zSysInit();
void zSysPostInit();
void zSysMain();
void zSysReset();
void zSysFifoEnd();
size_t zsys_FullAllocAndFree();

void zVid_Assert(bool condition, unsigned int mask, const char* source, int line);

void* operator new(size_t size);
void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t new_size);
void* memalign(size_t alignment, size_t size);
char* strdup(const char* str1);

_zsys_public zSys;
CTTY theTerminal;

struct _word128
{
	long128 u128;
	float f32[4];
	unsigned long u64[2];
	unsigned int u32[4];
	unsigned short u16[8];
	unsigned char u8[16];
};

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

	void init_page();
	T* acquire(size_t size);
	bool release(T* page);
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
	float m_priority;
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