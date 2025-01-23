#pragma once
#include <deque>

#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"

class CHUD;

class CSnd;

namespace zdb
{
	class CAssetLib;
	
	class CWorld;
}

class CGameState
{
public:
	virtual void PreInit() = 0;
	virtual bool Init() = 0;
	virtual void PreUnInit() = 0;
	virtual void UnInit() = 0;

	virtual void Tick(f32 dT) = 0;

	virtual void OnPop() = 0;
	virtual void OnPush() = 0;
public:
	void SetName(const char* name);
protected:
	char* m_name;
};

class CCoreState : public CGameState
{
public:
	CCoreState();

	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}
protected:
	f32 m_agl;
	f32 m_posScale;
	bool m_showingTB;

	CMatrix objMtx1;
	CMatrix objMtx2;

	zdb::CWorld* m_world;

	u32 skyColor[3];

	s32 m_LoadThreadId;
	bool m_loading;
	bool m_loadstarted;
	CHUD* m_hud;
	s32 m_skip_swap;
};

class CMenuState : public CGameState
{
public:
	CMenuState();
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}

	void DrawForeplane();
private:
	void* m_menu;
	s32 m_skip;
	s32 m_skip_swap;

	CSaferStr TtySoundString;
	CSaferStr BackSoundString;

	CSnd* SelectionSound;

	char m_DefaultMenu[64];

	s32 m_iopregh;
};

class CLoadState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}
private:
	void* m_menu;
	void* m_e3config;

	bool m_fadeup;
	bool m_fadedown;

	f32 m_time_elapsed;
	s32 m_tick_alarm_id;

	bool m_voiceover_started;
	bool m_waiting_for_x;
	bool m_abort;
};

class CCinematicState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}

	void SetMovie(const char* moviename);
private:
	bool m_movierunning;
	char* m_moviename;
	s32 m_savedFrameRate;
	s32 m_videoSave[2];
	f32 m_fadeTime;
};

class CExitState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}
private:
	std::string m_libname;
	std::string m_texname;
	zdb::CAssetLib* m_plib;
	void* m_menu;
};

class CMPExitState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}
private:
	std::string m_libname;
	std::string m_texname;
	zdb::CAssetLib* m_plib;
	void* m_menu;
};

class CRebootState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}
};

class CShutdownState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}
};

class CTestState : public CGameState
{
public:
	CTestState();
	
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(f32 dT);

	void OnPop() {}
	void OnPush() {}

	void TestLoadReaders();
private:
	bool m_bTestLoadReaders;
};

class CGameStateChangeCmd
{
	friend class CGame;
public:
	static void CreatePool(s32 size);
private:
	bool m_active;
	u32 m_type;
	CGameState* m_toState;
	u32 m_toStateIdx;
};

class CStateCmdQueue : public std::deque<CGameStateChangeCmd*> {};