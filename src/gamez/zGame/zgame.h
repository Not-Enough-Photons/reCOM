#pragma once
#include <deque>
#include <string>

#include "gamez/zReader/zrdr.h"
#include "gamez/zNode/znode.h"

class CGame;
class CGameStateChangeCmd;

class CHUD;

class CSnd;

class CZAnimZAR;

enum MENU_STATE
{
	stateNone,
	stateWeaponSel,
	stateOrders,
	statePauseTestMenu,
	stateFullScreenMapMenu,
	stateFullScreenMapAnim,
	stateLast
};

enum GAME_NAME
{
	nameUnknown,
	nameFTS,
	nameAP
};

void process_arguments(int argc, char** argv);

extern CGame theGame;
extern std::vector<CGameStateChangeCmd*> m_pool;

struct _options
{
	bool doHud;
	bool doStatusLine;
	bool doStatusLineSmall;
	bool doFPS;
	bool doAssetReport;
	bool loadAi;
	bool enableAi;
	bool doDyn;
	bool doWep;
	bool doConsole;
	bool doIntersections;
	bool doAltitudes;
	bool LoadZAnimFromZAR;
	bool doShadow;
	bool noDie;
	bool noSee;
	bool noEnemy;
	bool noAlpha;
	bool noBravo;
	bool infiniteAmmo;
	bool noObjectives;
	bool doLog;
	bool doTaskReport;
	bool doRenderReport;
	bool dumpLog;
	bool doRadar;
	bool doEntityReport;
};

extern _options gopt;

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

class CGame
{
public:
	CGame();
public:
	bool StartEngine();
	void StartPlay();
	bool Tick(f32 dT);
	CGameState* Switch(CGameState* state, u32 index);
public:
	f32 m_maxtick;
protected:
	bool m_Active;

	CGameState* m_InitialState;
	CGameState* m_TestVariable;
	CGameState* m_Stack[16];
	u32 m_CurrentState;

	s32 m_MinIdlePeriod;

	CStateCmdQueue m_StateChangeQueue;

	u32 m_pad;
};

class COurGame : public CGame
{
public:
	static bool StartEngine();
protected:
	CMenuState m_menuState;
	CLoadState m_loadState;
	CCoreState m_coreState;
	CExitState m_exitState;
	CMPExitState m_MPexitState;
	CCinematicState m_cinematicSubState;
};

class CGameMenu
{
public:
	void DrawForeplane();
public:
	zdb::CNode m_nodeTop;

	CZAnimZAR* animfile;

	zdb::CNode* m_pBackplaneNode;
	zdb::CNode* m_pForeplaneNode;
};