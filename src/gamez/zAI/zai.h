#pragma once
#include "vehicle_main.h"

#include "gamez/zEntity/zentity.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zSeal/zseal.h"

typedef unsigned char TYPE;
typedef unsigned char PATH_TYPE;
typedef unsigned char PATH_STATE;
typedef unsigned char ASTAR_STATUS;

enum FIRE_TEAM
{
	FT_UNKNOWN,
	FIRETEAM,
	ABLE,
	BRAVO,
	ESCORTEE,
	FRIENDLY,
	NEUTRAL,
	TURRETS,
	SUPPORT,
	HOSTAGE,
	ENEMIES,
	ALLIES
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
	CMD_ESCORT,
	CMD_RUNTO,
	CMD_MOVETO,
	CMD_STEALTHTO,
	CMD_ATTACKTO,
	CMD_LEADTO,
	CMD_COVERTARGET,
	CMD_LASETARGET,
	CMD_BREACH,
	CMD_GETDOWN,
	CMD_PULLOUT,
	CMD_OVERWATCH,
	CMD_SUPPORT,
	CMD_EXTRACT,
	CMD_CLEARAREA,
	CMD_RESTRAIN,
	CMD_REMOVEKILLS,
	CMD_AWAKE,
	CMD_SLEEP,
	CMD_AMBUSH
};

enum AI_LOOK
{
	type_00,
	type_01,
	type_02,
	type_03
};

enum LOOK_DATA_TYPE
{
	type_00,
	type_01,
	type_02,
	type_03,
	type_04,
	type_05,
	type_06,
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

enum GOAL_TYPE
{
	type_00,
	type_01,
	type_02,
	type_03,
	type_04
};

struct AI_PARAMS
{
	unsigned int mask;
	float accuracy;
	float courage;
	float surrender;
	float stealth;
	float training;
	float visual_sens;
	float visual_range;
	float visual_fov;
	float aware_decay;
	float thip_range;
	unsigned int respawn;
	float target_delay;
	float target_discipline;
	CVehicleRdrEntry* m_veh;
};

namespace sealai
{
	const char* get_state(AI_STATE state);
}

class CAiEvent
{
public:
	enum EVENT
	{
		type_00,
		type_01,
		type_02,
		type_03,
		type_04,
		type_05,
		type_06,
		type_07,
		type_08,
		type_09,
		type_10,
		type_11,
		type_12,
		type_13,
		type_14,
	};

	static CAiEvent* Create(CAiEvent* other);
	static CAiEvent* Acquire();

	static float GetEventRate(EVENT event);

	int aiBitMask;
	float expiration;
	float soundRadiusSqr;
	CPnt3D* source;
	CEntity* originator;
	int dummy;
};

class CAiMapVec : std::vector<CAiMap> { };
class CAiMapLocVec : std::vector<CAiMapLoc> { };
class points : std::vector<CPnt3D> { };

class CAiMap
{

};

class CAiPath
{
private:
	CAiAStar* m_astar;
	CAiPlanner* m_planner;

	bool m_custom;

	PATH_TYPE m_type;
	float m_type_bias;

	CAiPath* m_template;
	void* m_overlay;

	unsigned int m_flags;
	unsigned int m_app_flags;
	unsigned int m_legcount;
	unsigned int m_planleg;
	unsigned int m_curleg;

	CAiMapLocVec m_waypts;
	CAiMapVec m_maps;
	CAiPathStats m_stats;

	PATH_STATE m_state;
	ASTAR_STATUS m_status;

	float m_length;
	unsigned int m_tolerance;
	unsigned int m_search_limit;
	unsigned int m_snake_len;

	points m_points;
	unsigned int m_pathId;
};

class CAiPathStats
{
public:
	int nodes_searched;
	int nodes_added;
	int nodes_removed;
	int nodes_visited;
	int nodes_left;

	int path_length;
	int path_cost;

	int m_ticks;
	float m_time;
	CAiMapLoc m_current;
	CAiMapLocVec m_visited;
};

class CAiAStar
{

};

class CAiPlanner
{

};

class CAiDecay
{
	float m_value;
	float m_goal;
	TYPE m_type;
};

class CAiParams
{

};

class CAiTimer
{
public:
	const float infinite = 0xBF800000;
private:
	Rfloat m_period;
	float m_timer;
};

class CAiCone
{
	float m_dot;
	CPnt3D m_vec;
	float m_height;
	float m_radius;
	float m_point_radius;
	float m_inv_height;
	CPnt3D m_cone_pos;
	CPnt3D m_cone_dir;
};

class CAiVismap
{

};

class CAiMapLoc
{
	unsigned int m_mapid : 6;
	unsigned int m_x : 13;
	unsigned int m_y : 13;
};