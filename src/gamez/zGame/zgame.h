#pragma once
#include <deque>
#include <string>

#include "gamez/zFTS/fts_state.h"

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