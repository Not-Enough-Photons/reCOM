#pragma once
struct start
{
	char m_name[16];
	int m_dir;
};

struct startvec
{
	unsigned int m_count;
	start m_start[4];
};

class CVehicleRdr
{

};

class CVehicleRdrEntry
{
private:
	char m_name[32];
	char m_character[48];
	char m_display_name[32];
	startvec m_start;
	int m_teamMask;
	AI_PARAMS m_aiParams;
	unsigned int m_debug : 1;
	unsigned int m_disabled : 1;
	unsigned int m_nofade : 1;
	unsigned int m_noshoot : 1;
	unsigned int m_recycle : 1;
	unsigned int m_nosnooze : 1;
	unsigned int m_unused : 26;
	int m_startIndex;
};