#pragma once
#include "ai_main.h"
#include "vehicle_main.h"

#include "zNode/node_main.h"
#include "zReader/zrdr_main.h"
#include "zNetwork/znet_main.h"
#include "zSystem/zsys_main.h"
#include "zValve/valve_main.h"
#include "zUI/zui.h"

enum MISSION_STATE
{
	COMPLETE,
	FAILED,
	ABORT,
	TIMEOUT,
	NOFADE
};

class CMission;
class CMissionObjectiveCam;
class CObjAnchor;
class CObjAnchorVec;

static CMission theMission;

class CMission : CSaveModule
{
public:
	CMission() : CSaveModule("CMission", NULL) {}
	~CMission();

	static float nextFrameDelta;
public:
	void Init();

	void Open();
	void PreOpen();
	void Read(_zrdr* reader);
public:
	CZNetGame* netGame;
private:
	MISSION_STATE m_state;

	char* m_database;
	char m_db_string[64];

	float m_timer;
	float m_delay;
	float m_winlosstimer;
	float m_winlossinc;

	bool m_DelayEndMission;
	bool m_FadingToEndMission;
	int m_fade_counter;
	float m_next_fade_time;
	float m_wait_before_falling;

	std::vector<CObjAnchor> m_anchor_extraction;
	// std::vector<CNavPoint> m_navpoints;
	// CObjAnchorVec m_objanchor_vec;
	CMissionObjectiveCam* m_prev_selected_objcam;
	float m_objectives_timer;
	bool m_ignore_objectives;

	bool m_load_ai;
	AI_PARAMS m_ai_params;

	float m_seefarther_binocs;
	float m_seefarther_weapzoom;

	CValve* m_valve_complete;
	CValve* m_valve_failure;
	CValve* m_valve_abort;
	CValve* m_valve_timeout;
	CValve* m_valve_nofade;

	C2DMessage_Q m_messenger;
	C2DMessage_Q m_Subtitles;
	C2DMessage_Q m_ammoMessenger;

	// CLadderList* m_ladders;

	CZNetGame* m_pNetGame;

	bool m_chars_loaded;
	int m_CharLoadSem; // Likely a semaphore

	CVehicleRdr* m_vehicleRdr;
	CRdrFile* m_ordersRdr;
	CRdrFile* m_materialsRdr;
	CRdrFile* m_decalsRdr;
	CRdrFile* m_fontsRdr;
	CRdrFile* m_messagesRdr;
	CRdrFile* m_subtitlesRdr;
	CRdrFile* m_smallmessagesRdr;

	// CSaferStr m_m_strLoadedScrLib;
	// 
	// CMissionCamList m_missioncams;
	// CMissionObjectiveCamList m_objectivecams;

	float m_fighttimer;
	float m_satcheltimer;

	CValve* m_teamValve[32];
	CValve* m_player_valve;

	zdb::CNode* m_sealbombshack;
	zdb::CNode* m_terroristbombshack;

	// E3_TEAMS_ENUM m_e3_team;
};

class CZBombState
{
public:
	static int m_FutureBombState;
};