#pragma once

#include "gamez/zAI/zai.h"
#include "gamez/zEntity/zentity.h"
#include "gamez/zNode/znode.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zValve/zvalve.h"
#include "gamez/zUI/zui.h"

class CMission;
class CMissionObjectiveCam;
class CObjAnchor;
class CObjAnchorVec;

class CZNetGame;

extern CMission theMission;
extern CZSealBody* ftsPlayer;

CZSealBody* ftsGetPlayer();
void ftsSetPlayer(CZSealBody* player);

bool ftsGetSquirm();
void ftsSetSquirm(bool squirm);

void ftsNetworkGameInit();
void ftsNetworkGameUninit();
void ftsNetworkPlayerInit();
void ftsNetworkSealInit();

s32 FilterMissionFolder(const char* prefix, const char* infix, const char* postfix, char* output);

class Headset
{
public:
	static void ftsDeleteHeadset() {}
	static void* ftsGetHeadset() { return NULL; }
};

enum MISSION_STATE
{
	MISSION_UNLOADED,
	MISSION_RUNNING,
	MISSION_SUCCESS,
	MISSION_FAILURE,
	MISSION_ABORTED,
	MISSION_TIMEOUT
};

class CMission : CSaveModule
{
	struct AI_PARAMS
	{
		f32 weather_factor;
		FT_COMMAND fireteam_command;
		f32 recycle_range;
		f32 recycle_time;
		f32 respawn_time;
		f32 respawn_fade;
		f32 respawn_range;
		f32 player_grid_spacing;
		s32 player_grid_count;
	};

public:
	CMission() : CSaveModule("CMission", NULL) {}

	static f32 nextFrameDelta;
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

	f32 m_timer;
	f32 m_delay;
	f32 m_winlosstimer;
	f32 m_winlossinc;

	bool m_DelayEndMission;
	bool m_FadingToEndMission;
	s32 m_fade_counter;
	f32 m_next_fade_time;
	f32 m_wait_before_falling;

	std::vector<CObjAnchor*> m_anchor_extraction;
	// std::vector<CNavPoint> m_navpoints;
	// CObjAnchorVec m_objanchor_vec;
	CMissionObjectiveCam* m_prev_selected_objcam;
	f32 m_objectives_timer;
	bool m_ignore_objectives;

	bool m_load_ai;
	AI_PARAMS m_ai_params;

	f32 m_seefarther_binocs;
	f32 m_seefarther_weapzoom;

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
	s32 m_CharLoadSem; // Likely a semaphore

	CVehicleRdr* m_vehicleRdr;
	CRdrFile* m_ordersRdr;
	CRdrFile* m_materialsRdr;
	CRdrFile* m_decalsRdr;
	CRdrFile* m_fontsRdr;
	CRdrFile* m_messagesRdr;
	CRdrFile* m_subtitlesRdr;
	CRdrFile* m_smallmessagesRdr;

	CSaferStr m_m_strLoadedScrLib;
	// 
	// CMissionCamList m_missioncams;
	// CMissionObjectiveCamList m_objectivecams;

	f32 m_fighttimer;
	f32 m_satcheltimer;

	CValve* m_teamValve[32];
	CValve* m_player_valve;

	zdb::CNode* m_sealbombshack;
	zdb::CNode* m_terroristbombshack;

	// E3_TEAMS_ENUM m_e3_team;
};

class CMissionCam
{
private:
	char* m_identifier;
	char* m_name;
	char* m_description[3];

	CZAnim* m_anim;
	CSnd* m_music;
};

class CZBombState
{
public:
	static s32 m_FutureBombState;
};