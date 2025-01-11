#pragma once
#include <deque>
#include <string>

#include "gamez/zReader/zrdr.h"
// #include "gamez/zNetwork/znet.h"
#include "gamez/zNode/znode.h"

class CGame;
class CGameStateChangeCmd;

class CHUD;

class CSnd;

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

void game_main(int argc, char** argv);
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

	virtual void Tick(float dT) = 0;

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

	void Tick(float dT);

	void OnPop() {}
	void OnPush() {}
protected:
	float m_agl;
	float m_posScale;
	bool m_showingTB;

	CMatrix objMtx1;
	CMatrix objMtx2;

	zdb::CWorld* m_world;

	unsigned int skyColor[3];

	int m_LoadThreadId;
	bool m_loading;
	bool m_loadstarted;
	CHUD* m_hud;
	int m_skip_swap;
};

class CMenuState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(float dT);

	void OnPop() {}
	void OnPush() {}
private:
	void* m_menu;
	int m_skip;
	int m_skip_swap;

	// CSaferStr TtySoundString;
	// CSaferStr BackSoundString;

	CSnd* SelectionSound;

	char m_DefaultMenu[64];

	int m_iopregh;
};

class CLoadState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(float dT);

	void OnPop() {}
	void OnPush() {}
private:
	void* m_menu;
	void* m_e3config;

	bool m_fadeup;
	bool m_fadedown;

	float m_time_elapsed;
	int m_tick_alarm_id;

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

	void Tick(float dT);

	void OnPop() {}
	void OnPush() {}

	void SetMovie(const char* moviename);
private:
	bool m_movierunning;
	char* m_moviename;
	int m_savedFrameRate;
	int m_videoSave[2];
	float m_fadeTime;
};

class CExitState : public CGameState
{
public:
	void PreInit() {}
	bool Init();
	void PreUnInit() {}
	void UnInit() {}

	void Tick(float dT);

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

	void Tick(float dT);

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

	void Tick(float dT);

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

	void Tick(float dT);

	void OnPop() {}
	void OnPush() {}
};

class CGameStateChangeCmd
{
	friend class CGame;
public:
	static void CreatePool(int size);
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