#include <list>

#include <rsa/rsadef.h>

#include "gamez/zValve/zvalve.h"
#include "gamez/zUI/zui.h"

class CZNetwork;
class CZOnlineLobby;
class CZNetGame;

extern CZNetwork theNetwork;
extern CZOnlineLobby theLobby;

enum MP_MINOR_GAME_STATE
{
	MP_MINOR_UNKNOWN,
	MP_MINOR_NOTREADY,
	MP_MINOR_READY
};

enum MP_MAJOR_GAME_STATE
{
	MP_MAJOR_UNKNOWN,
	MP_MAJOR_MENUS,
	MP_MAJOR_LOADING,
	MP_MAJOR_INPLAY,
	MP_MAJOR_ROUNDOVER,
	MP_MAJOR_NEWROUND,
	MP_MAJOR_GAMEOVER,
	MP_MAJOR_PLAY,
	MP_MAJOR_GAMELOBBY,
	MP_MAJOR_GHOST
};

enum MP_GAME_TYPE
{
	MP_GAME_UNKNOWN,
	MP_GAME_DEFUSE,
	MP_GAME_DEMOLITION,
	MP_GAME_ESCORT,
	MP_GAME_EXTRACT,
	MP_GAME_JAILBREAK,
	MP_GAME_DEATHMATCH,
	MP_GAME_FOOTBOMB
};

enum MP_NET_READY
{
	NET_READY_UNKNOWN,
	NET_READY_WAITING,
	NET_READY_PLAY,
	NET_READY_MENUS
};

enum MP_CONNECTION
{
	USB_MODEM,
	USB_ETHERNET,
	NA_MODEM,
	NA_ETHERNET
};

enum LOBBY_STATE
{
	ROOT_LOBBY_STATE,
	CONNECT_SUCCESS,
	CONNECT_ERROR,
	ACCOUNT_REGISTRATION,
	USER_REGISTRATION,
	SCREENNAME_REGISTRATION,
	REGISTRATION_FAILURE,
	ACCOUNT_LOGIN,
	USER_LOGIN,
	SCREENNAME_LOGIN,
	LOGIN_FAILURE,
	LOBBY_ACTIVE,
	SESSION_BEGIN,
	CREATE_NEW_GAME,
	CREATE_FAILURE,
	JOIN_GAME,
	LOBBY_SERVER_CONNECT,
	READY_TO_CONNECT,
	END_SESSION,
	JOIN_ROOM,
	CREATE_ROOM,
	RETRIEVE_CLAN_INFO,
	MAX_LOBBY_STATES
};

enum class LOBBY_STATE_FLAG
{
	REGISTER,
	ENTRY,
	TICK,
	EXIT,
	UNREGISTER
};

void PTT_HeartbeatPrepare();

class CZNetwork
{
public:
	enum class EVENT
	{
		ONSTART,
		ONEXIT,
		ONACTIVATE,
		ONMPEGEND,
		MP_JOIN_ROOM,
		MP_PLAYER_NOT_FOUND,
		MP_SUCCESS,
		MP_CREATE_CLAN_SUCCESS,
		MP_CREATE_CLAN_FAILURE,
		MP_DISBAND_CLAN_SUCCESS,
		MP_DISBAND_CLAN_FAILURE,
		MP_MEDIUS_ERROR,
		MP_MEDIUS_HAS_INVITES,
		ON_STATE_POP,
		ON_SKB_APPLY,
		ON_SKB_CLOSE,
		ON_LOAD_COMPLETE,
		ON_CLIENT_CONNECT,
		ON_FORCE_NEW_DB,
		ON_LADDER_REFRESH,
		ON_TTY_DONE,
		MP_MEDIUS_JOIN_GAME_FAILURE,
		MP_MEDIUS_READY_TO_CONNECT,
		MP_PLAYER_ALREADY_MEMBER,
		MP_VERSION_NUMBER_ERROR,
		MP_LEADERSHIP_TRANSFER_SUCCESS,
		MEMCARD_ERROR,
		MP_MEDIUS_BECAME_LEADER,
		ON_SKB_CANCEL,
		NETCNF_ERROR,
		MP_MEDIUS_JOIN_ROOM_FAILURE,
		MP_PLAYER_IS_LEADER,
		MP_CLAN_DISBANDED
	};
public:
	float zNetGetTime();
	void zNetUpdate();
	void zNetRequestObjectPrivateOwnership();
public:
	s32 m_SealIndex;
	s32 m_TerrIndex;

	bool m_bSessionMaster;
	bool m_bNetwork;
	bool m_bConnected;
	bool m_bJoined;
	bool m_menu_skip;
	bool m_network_init;
	bool m_monitor_ok;

	s8 m_ServerIP[32];
	s8 m_ServerPort[32];
	s8 m_MediusIP[64];
	s8 m_MediusPort[32];
	s8 m_MyInternalIP[16];

	s32 m_WorldID;
	s32 m_ClientIndex;
	s32 m_NetObjectCount;
	s32 m_DataStreamCount;
	s32 m_GameConnectionIndex;
	s32 m_LobbyConnectionIndex;
	s32 m_sessionmaster_index;
	s32 m_net_time;
	s32 m_local_time;

	bool m_bMediusEnabled;
	bool m_bNetCnfRequired;

	s8 m_ObjectFieldUpdate[4096];
	void* m_ObjectUpdateCallbackList[16];
	void* m_ObjectPostUpdateCallbackList[16];

	MP_CONNECTION m_connection_type;

	char m_charName[31];
	char m_charType[31];

	s8 m_BuildTimeStamp[64];
	
	s8 m_SessionKey[17];
	s8 m_AccessKey[17];
	RSA_KEY m_PubKey;

	std::list<s8> m_message_list;
	std::list<s8> m_fix_list;
};

class CNetClock
{
	friend class CZNetGame;
private:
	u32 m_max_game_time;
	u32 m_save_max_game_time;
	u32 m_initial_read;
	u32 m_time_in_round;
	u32 m_game_time;
	u32 m_total_time;
	s32 m_rtime_delta;
	bool m_initial_read_set;
	bool m_clock_running;
};

class CZNetGame
{
public:
	CValve* m_pMaxRoundCountValve;
	CValve* m_pHalfRoundCountValve;
	CValve* m_pRoundCountValve;
	CValve* m_pGameOverValve;
	CValve* m_pPlayerTeamValve;
	CValve* m_pBombStatusValve;
	CValve* m_pBombOwnerValve;
	CValve* m_pMajorGameStateValve;
	CValve* m_pMinorGameStateValve;
	CValve* m_pJoinGameValve;
	CValve* m_pLateJoinerValve;
	CValve* m_p45SecondClockValve;
	CValve* m_pXSecondClockValve;
	CValve* m_HostagesKilledBySealsValve;
	CValve* m_HostagesKilledByTurdsValve;
	CValve* m_pPenaltyValve;
	CValve* m_pPlayerJoinCountValve;
	CValve* m_pPlayerReadyCountValve;
	CValve* m_pMPPersistentValve;
	CValve* m_pMPProgTimer1Valve;

	CUIVariable* m_uiv_SealList;
	CUIVariable* m_uiv_TerrList;
	CUIVariable* m_uiv_NoneList;
	CUIVariable* m_uiv_ChatList;

	PNT2D m_static_radio_loc;
	PNT2D m_dynamic_radio_loc;

	s32 m_persona_object_index;
	s32 m_game_object_index;
	s32 m_world_id;
	s32 m_max_round_count;
	s32 m_net_ready_count;
	s32 m_last_penalty;
	s32 m_gate_clock;

	u32 m_countdown;
	u32 m_net_team;

	bool m_was_late_joiner;
	bool m_ready_to_play;
	bool m_persona_created;
	bool m_bdown;
	bool m_ghost_ok;
	bool m_am_a_ghost;
	bool m_game_over;
	bool m_bomb_clock_started;
	bool m_bomb_created;
	bool m_bomb_owned;
	bool m_ten_second_launch;

	CNetClock m_clock;

	CValve* m_pTimerValve;
	CValve* m_pDebugValve;
	CZAnim* m_pTimerAnim;

	CPnt3D m_new_bomb_pos;
	bool m_use_bomb_pos;

	MP_GAME_TYPE m_game_type;
	MP_NET_READY m_net_start_flag;
	MP_MAJOR_GAME_STATE m_mp_major_game_state;
	MP_MAJOR_GAME_STATE m_my_major_game_state;
	MP_MINOR_GAME_STATE m_mp_minor_game_state;

	f32 m_pos_smooth;

	s32 m_mpe3_round_count;
	s32 m_mpe3_round_winner;
	s32 m_mpe3_score00;
	s32 m_mpe3_score08;
	s32 m_e3_index;
};

class CZNetVoice
{
public:
	void PreTick();
};

class CZOnlineLobby
{
public:
	void Init();
private:
	bool started;
	CValve* onlineStatusValve;
};