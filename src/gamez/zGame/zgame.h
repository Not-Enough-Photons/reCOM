#pragma once
#include <deque>
#include <string>

#include "gamez/zReader/zrdr.h"
#include "gamez/zNetwork/znet.h"
#include "gamez/zNode/znode.h"
#include "gamez/zUI/zui.h"

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

static void game_main(int argc, char** argv);
void process_arguments(int argc, char** argv);

class CGame
{
public:
	bool StartEngine();
	void StartPlay();
	void Tick(float delta);
public:
	float m_maxtick;
protected:
	bool m_Active;

	CGameState* m_InitialState;
	CGameState* m_CurrentState;
	CGameState* m_TestVariable;
	CGameState* m_Stack[16];

	int m_MinIdlePeriod;

	unsigned int m_pad;
};

CGame theGame;

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

class CGameState
{
public:
	CGameState();
	~CGameState();
public:
	virtual void PreInit();
	virtual bool Init();
	virtual void PreUnInit();
	virtual void UnInit();

	virtual void Tick();

	virtual void OnPop();
	virtual void OnPush();
public:
	void SetName(const char* name);
protected:
	const char* m_name;
};

class CStateCmdQueue : public std::deque<CGameStateChangeCmd> { };

class CCoreState : public CGameState
{
public:
	CCoreState() : CGameState() { }
	~CCoreState();

	void auxUnload();
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

	void SetMovie(const char* moviename);
	void UnInit();
private:
	bool m_movierunning;
	char* m_moviename;
	int m_savedFrameRate;
	int m_videoSave[2];
	float m_fadeTime;
};

class CExitState : public CGameState
{
private:
	std::string m_libname;
	std::string m_texname;
	zdb::CAssetLib* m_plib;
	void* m_menu;
};

class CMPExitState : public CGameState
{
private:
	std::string m_libname;
	std::string m_texname;
	zdb::CAssetLib* m_plib;
	void* m_menu;
};

class CRebootState : public CGameState
{
};

class CShutdownState : public CGameState
{
};

class CGameStateChangeCmd
{
public:
	static void CreatePool(int size);
};