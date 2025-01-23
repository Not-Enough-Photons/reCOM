#pragma once
#include <vector>

#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"

class CAiMap;
class CAiAStar;
class CAiPlanner;
class CAiPathStats;
class CAiMapLoc;

class CEntity;

class CSealCtrlAi;

enum ASTAR_STATUS
{
	ASTAR_STATUS_UNKNOWN,
	ASTAR_SUCCESS,
	ASTAR_FAILURE_NOPATH,
	ASTAR_FAILURE_MANYTICKS,
	ASTAR_FAILURE_TOOLONG,
	ASTAR_FAILURE_NONEOPEN,
	ASTAR_FAILURE_OUTOFTIME,
	ASTAR_FAILURE_UNKNOWN
};

enum TYPE
{
	LINEAR,
	EXPONENTIAL
};

enum PATH_TYPE
{
	PATH_DEFAULT,
	PATH_BASIC,
	PATH_STEALTH,
	PATH_RESTRAINED
};

enum PATH_STATE
{
	UNKNOWN,
	INQUEUE,
	PLANNING,
	ABORT,
	COMPLETE,
	FAILED
};

enum FIRETEAM
{
	FT_MP_PLAYER,
	FT_FIRETEAM,
	FT_ALPHA,
	FT_BRAVO,
	FT_USER,
	FT_RESERVED,
	FT_ESCORTEE,
	FT_MP_RADIO,
	FT_MP_SOP,
	FT_NEUTRAL,
	FT_TURRETS,
	FT_HOSTAGE,
	FT_SUPPORT,
	FT_ENEMIES,
	FT_ALLIES,
	FT_ALL
};

enum FT_COMMAND
{
	CMD_UNKNOWN,
	CMD_ACTION,
	CMD_DEPLOY,
	CMD_FIREATWILL,
	CMD_FOLLOW,
	CMD_HOLDPOS,
	CMD_HOLDFIRE,
	CMD_REGROUP,
	CMD_REMOVEKILLS,
	CMD_AMBUSH,
	CMD_RESTRAIN,
	CMD_GETDOWN,
	CMD_ESCORT,
	CMD_GOTONODE,
	CMD_STEALTHTO,
	CMD_RUNTO,
	CMD_LEADTO,
	CMD_ATTACKTO,
	CMD_BREACHBANGCLEAR,
	CMD_BREACHFRAGCLEAR,
	CMD_BREACHNONECLEAR,
	CMD_BOMB,
	CMD_EXTRACT,
	CMD_COVERTARGET,
	CMD_LASETARGET,
	CMD_CLEARAREA,
	CMD_AWARE,
	CMD_AWAKE,
	CMD_RADIO_CHANNEL_ZERO,
	CMD_RADIO_CHANNEL,ONE,
	CMD_RADIO_CHANNEL_TWO,
	CMD_RADIO_CHANNEL_THREE,
	CMD_RADIO_CHANNEL_ONOFF,
	CMD_VOTE_ON,
	CMD_VOTE_OFF,
	CMD_GRENADE_THROWN,
	CMD_ENEMY_DEAD,
	CMD_FRIEND_DEAD,
	CMD_UNDER_FIRE,
	CMD_GOT_ONE,
	CMD_ESCORTEE_FOLLOWING,
	CMD_PLAYER_HAS_KILLED,
	CMD_COVER_ME,
	CMD_DEFUSE,
	CMD_PROTECT,
	CMD_POINT,
	CMD_SOP1,
	CMD_SOP2,
	CMD_SOP3,
	CMD_SOP4,
	CMD_SOP5,
	CMD_SOP6,
	CMD_SOP7,
	CMD_TAUNT1,
	CMD_TAUNT2,
	CMD_TAUNT3,
	CMD_TAUNT4,
	CMD_TAUNT5,
	CMD_TAUNT6,
	CMD_TAUNT7,
	CMD_SEALS_WINNING,
	CMD_TERRORISTS_WINNING,
	CMD_HOSTAGE_KILLED,
	CMD_BOMB_PLANTED,
	CMD_TARGET_DESTROYED,
	CMD_BOMB_DEFUSED,
	CMD_MAX
};

enum AI_MODE
{
	AIM_SLEEP,
	AIM_IDLE,
	AIM_HOLD,
	AIM_PATH,
	AIM_CREEP,
	AIM_SLIDE,
	AIM_FOLLOW,
	AIM_MAX
};

enum AI_LOOK
{
	AIL_ALL,
	AIL_NORMAL,
	AIL_TURNING,
	AIL_CURIOUS,
	AIL_EVENT,
	AIL_CORPSE,
	AIL_TASK,
	AIL_FRANTIC,
	AIL_TARGET,
	AIL_BUDDY,
	AIL_DEPLOY
};

enum LOOK_DATA_TYPE
{
	LOOK_GARBAGE,
	LOOK_POSW,
	LOOK_DIRW,
	LOOK_DIRR
};

enum AI_STATE
{
	STATE_UNKNOWN,
	STATE_SCRIPT,
	STATE_HOLD,
	STATE_AVOID,
	STATE_DEPLOY,
	STATE_LASING,
	STATE_SURRENDER,
	STATE_RESTRAINED,
	STATE_GOTO,
	STATE_FOLLOW,
	STATE_BREACH,
	STATE_ACTION,
	STATE_PURSUE,
	STATE_ANIMATE,
	STATE_CQB,
	STATE_FLEE,
	STATE_PATHRECO,
	STATE_RESCUED,
	STATE_SUSPENDED,
	STATE_SHOTAT,
	STATE_RELOAD,
	STATE_NOAMMO,
	STATE_PICKUP,
	STATE_HOSTAGE,
	STATE_CORPSE,
	STATE_EVENT,
	STATE_TARGETING,
	STATE_GRENADE,
	STATE_STUNNED,
	STATE_RUSH
};

enum AI_SEQUENCE
{
	AIS_AWARE0,
	AIS_AWARE1,
	AIS_AWARE2,
	AIS_AWARE3,
	AIS_AWAREX
};

enum GOAL_TYPE
{
	GOAL_NONE,
	GOAL_SCAN,
	GOAL_LOOK,
	GOAL_MOVE,
	GOAL_SHOOT,
	GOAL_AVOID,
	GOAL_RECOVER
};

struct AI_PARAMS
{
	u32 mask;
	f32 accuracy;
	f32 courage;
	f32 surrender;
	f32 stealth;
	f32 training;
	f32 visual_sens;
	f32 visual_range;
	f32 visual_fov;
	f32 aware_decay;
	f32 thip_range;
	u32 respawn;
	f32 target_delay;
	f32 target_discipline;
	// CVehicleRdrEntry* m_veh;
};

class CAiEvent
{
public:
	enum EVENT
	{
		AIE_NONE,
		AIE_UNKNOWN,
		AIE_GENERIC,
		AIE_POINT,
		AIE_ENTITY,
		AIE_VOICE,
		AIE_WEPHIT,
		AIE_CORPSE,
		AIE_DOOR,
		AIE_WEPFIRE,
		AIE_EXPLOSION,
		AIE_SURRENDER,
		AIE_GETDOWN,
		AIE_HELPATTACK,
		AIE_ALARM,
		AIE_LIGHTSOFF,
		AIE_MAX
	};

	static CAiEvent* Create(CAiEvent* other);
	static CAiEvent* Acquire();

	static f32 GetEventRate(EVENT event);

	s32 aiBitMask;
	f32 expiration;
	f32 soundRadiusSqr;
	CPnt3D* source;
	CEntity* originator;
	s32 dummy;
};

class CAiMapVec : std::vector<CAiMap> { };
class CAiMapLocVec : std::vector<CAiMapLoc> { };
class points : std::vector<CPnt3D> { };

class CAiMap
{

};

class CAiMapLoc
{
	u32 m_mapid : 6;
	u32 m_x : 13;
	u32 m_y : 13;
};

class CAiPathStats
{
public:
	f32 nodes_searched;
	f32 nodes_added;
	f32 nodes_removed;
	f32 nodes_visited;
	f32 nodes_left;

	f32 path_length;
	f32 path_cost;

	f32 m_ticks;
	f32 m_time;
	CAiMapLoc m_current;
	CAiMapLocVec m_visited;
};

class CAiPath
{
public:
	CAiAStar* m_astar;
	CAiPlanner* m_planner;

	bool m_custom;

	PATH_TYPE m_type;
	f32 m_type_bias;

	CAiPath* m_template;
	void* m_overlay;

	s32 m_flags;
	s32 m_app_flags;
	s32 m_legcount;
	s32 m_planleg;
	s32 m_curleg;

	CAiMapLocVec m_waypts;
	CAiMapVec m_maps;
	CAiPathStats m_stats;

	PATH_STATE m_state;
	ASTAR_STATUS m_status;

	f32 m_length;
	s32 m_tolerance;
	s32 m_search_limit;
	s32 m_snake_len;

	points m_points;
	s32 m_pathId;
};

class CAiAStar
{

};

class CAiState
{
public:
	enum class SIGNAL
	{
		AISIG_UNKNOWN,
		AISIG_BEGINCRITICAL,
		AISIG_ENDCRITICAL,
		AISIG_SUSPEND,
		AISIG_RELEASE,
		AISIG_ANIMCOMPLETE
	};

	static CAiState* Create(AI_STATE state);

	virtual bool Tick(f32 dT, CSealCtrlAi* controller) { return true; }
	virtual void OnSignal(SIGNAL signal, CSealCtrlAi* controller) { }

	virtual bool CanAttack() const { return true; }
	virtual bool CanPursue(CSealCtrlAi* controller) const { return true; }
	virtual bool CanPushAiState(AI_STATE state, CSealCtrlAi* controller) { return true; }
	virtual bool CanScan() const { return true; }
	virtual bool CanSwitchAiState(AI_STATE state, CSealCtrlAi* controller) { return true; }

	void Reset(AI_STATE state);
protected:
	u32 m_bitfield;
	AI_STATE m_state;
	s32 m_field1_0x4;
	s32 m_field2_0x8;
	s32 m_field8_0x14;
};

class CAiSScript : public CAiState
{
public:
	bool CanPursue(CSealCtrlAi* controller);
};

class CAiSHold : public CAiState
{

};

class CAiSAvoid : public CAiState
{

};

class CAiSDeploy : public CAiState
{

};

class CAiSSurrender : public CAiState
{

};

class CAiSRestrained : public CAiState
{

};

class CAiSUseVehicle : public CAiState
{

};

class CAiSGoto : public CAiState
{

};

class CAiSFollow : public CAiState
{

};

class CAiSBreach : public CAiState
{

};

class CAiSAction : public CAiState
{

};

class CAiSPursue : public CAiState
{

};

class CAiSAnimate : public CAiState
{

};

class CAiSCQBAttack : public CAiState
{

};

class CAiSFlee : public CAiState
{

};

class CAiSPathRecover : public CAiState
{

};

class CAiSRescued : public CAiState
{

};

class CAiSSuspended : public CAiState
{

};

class CAiSShotAt : public CAiState
{

};

class CAiSNoAmmo : public CAiState
{

};

class CAiSHostage : public CAiState
{

};

class CAiSPlan : public CAiState
{

};

class CAiSEvent : public CAiState
{

};

class CAiSTarget : public CAiState
{

};

class CAiSGrenade : public CAiState
{

};

class CAiSStunResponse : public CAiState
{

};

class CAiSRush : public CAiState
{

};

class CAiPlanner
{

};

class CBasicPlanner : public CAiPlanner
{

};

class CStealthPlanner : public CAiPlanner
{

};

class CRestrainedPlanner : public CAiPlanner
{

};

class CAiDecay
{
	f32 m_value;
	f32 m_goal;
	TYPE m_type;
};

class CAiParams
{

};

class CAiTimer
{
public:
	const f32 infinite = 0xBF800000;
private:
	Rfloat m_period;
	f32 m_timer;
};

class CAiCone
{
	f32 m_dot;
	CPnt3D m_vec;
	f32 m_height;
	f32 m_radius;
	f32 m_point_radius;
	f32 m_inv_height;
	CPnt3D m_cone_pos;
	CPnt3D m_cone_dir;
};

class CAiVismap
{

};