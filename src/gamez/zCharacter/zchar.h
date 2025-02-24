﻿#include "gamez/zCamera/zcam.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zRender/zrender.h"
#include "gamez/zSystem/zsys.h"

struct AnimSet;

class CSnd;

class CVehicleRdrEntry;

namespace zdb
{
	class CModel;
}

struct cam_wiggle
{
	f32 amplitude;
	f32 duration;
	f32 rate;
};

struct throw_params
{
	f32 m_abort_threshold;
	f32 max_distance_stand;
	f32 max_distance_crouch;
	f32 toss_power_threshold;
	f32 toss_aim_threshold;
};

struct HEALTH_PARAMS
{
	void Parse(_zrdr* reader);

	f32 m_head_health;
	f32 m_head_healthMax;
	f32 m_body_health;
	f32 m_body_healthMax;
	f32 m_larm_health;
	f32 m_larm_healthMax;
	f32 m_rarm_health;
	f32 m_rarm_healthMax;
	f32 m_lleg_health;
	f32 m_lleg_healthMax;
	f32 m_rleg_health;
	f32 m_rleg_healthMax;
	f32 m_armor_head;
	f32 m_armor_body;
	f32 m_armor_rarm;
	f32 m_armor_larm;
	f32 m_armor_rleg;
	f32 m_armor_lleg;
};

class CCharacterGear
{
private:
	s32 m_ref_count;
	s32 m_partid;
	u32 m_gearid;
	char* m_name;
	char* m_model_file;
	zdb::CModel* m_model;
	CPnt3D m_offset;
	CPnt3D m_rotation;
};

class CCharacterWeap
{
private:

};

class CCharacterType
{
public:
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
		CVehicleRdrEntry* m_veh;
	};
	
	CCharacterType();

	static bool Open(const char* path);
private:
	char* m_name;

	s32 m_ref_count;

	char* m_model_file;
	char* m_model_name;
	u32 m_parentID;

	CSaferStr m_arrSoundNames[66];

	CSnd* m_sounds[66];

	LODVec m_LODs;

	std::vector<AnimSet*> m_anim_sets;

	char* m_texture_asset;
	zdb::CModel* m_model;

	std::list<CCharacterGear*> m_gear;
	std::vector<CCharacterWeap*> m_weapons;

	s32 m_strength;
	s32 m_recovery_factor;
	s32 m_controller_id;

	bool m_istemporary;

	AI_PARAMS m_aiParams;
	HEALTH_PARAMS m_healthParams;
};

class CharacterDynamics
{
public:
	void Load(_zrdr* reader);

	f32 m_gravity = 98.1f;
	f32 m_DamageToNewtons = 235.0f;
	f32 m_jumpFactor = 1.0f;
	f32 m_landFallRate = 0.0f;
	f32 m_landHardFallRate = 90.0f;
	f32 m_groundTouchDistance = 3.0f;
	f32 m_maxSlopeCos = 0.64278f;
	f32 m_stepHeight = 4.0f;
	f32 m_blastBoostY = 1.0f;
	f32 m_fallDist[3];
	f32 m_landSpeed[3];
	f32 m_standTurnFactor = 1.0f;
	f32 m_turn_maxRate = 2.0f;
	f32 m_accelXMin = 2.0f;
	f32 m_accelXMax = 5.0f;
	f32 m_accelZMin = 2.0f;
	f32 m_accelZMax = 5.0f;
	f32 m_initAimPitch = -0.159f;
	f32 m_maxAimPitch = 1.483f;
	f32 m_minAimPitch = -1.483f;
	f32 m_maxAimYaw = 1.483f;
	f32 m_proneMaxAimPitch = 0.349f;
	f32 m_proneMinAimPitch = -0.349f;
	f32 m_proneMaxAimYaw = 0.785f;
	f32 m_proneZoomDeltaYaw = 0.349f;
	f32 m_maxLookPitch = 1.55f;
	f32 m_minLookPitch = -1.55f;
	f32 m_maxLookYaw = 1.55f;
	f32 m_maxEyelookPitch = 0.139f;
	f32 m_minEyelookPitch = -0.139f;
	f32 m_maxEyelookYaw;
	f32 m_maxBlinkRate;
	f32 m_maxBlinkAngle;
	f32 m_cosMaxAimPitch;
	f32 m_cosMinAimPitch;
	f32 m_cosMaxAimYaw;
	f32 m_cosProneMaxAimPitch;
	f32 m_cosProneMinAimPitch;
	f32 m_cosProneMaxAimYaw;
	f32 m_cosMaxLookPitch;
	f32 m_cosMinLookPitch;
	f32 m_cosMaxLookYaw;
	f32 m_cosMaxEyelookPitch;
	f32 m_cosMinEyelookPitch;
	f32 m_cosMaxEyelookYaw;
	f32 m_maxZoomAimPitch;
	f32 m_minZoomAimPitch;
	f32 m_maxZoomAimYaw;
	f32 m_proneMaxZoomAimPitch;
	f32 m_proneMinZoomAimPitch;
	f32 m_proneMaxZoomAimYaw;
	f32 m_cosMaxZoomAimPitch;
	f32 m_cosMinZoomAimPitch;
	f32 m_cosMaxZoomAimYaw;
	f32 m_cosProneMaxZoomAimPitch;
	f32 m_cosProneMinZoomAimPitch;
	f32 m_cosProneMaxZoomAimYaw;
	f32 m_pitchRate;
	f32 m_turnThrottleA;
	f32 m_turnThrottleB;
	f32 m_pitchThrottleA;
	f32 m_pitchThrottleB;
	f32 m_minWaterFactor;
	f32 m_waterFactorSlope;
	f32 m_fbStiffness;
	f32 m_lrStiffness;
	f32 m_throtExp;
	f32 m_throtScale;
	f32 m_cameraRoll;
	f32 m_zoomFactor;
	f32 m_zoomRate;
	f32 m_cameraSideHeight;
	f32 m_cameraSideDist;
	f32 m_cameraSidePitch;
	f32 m_cameraFrontHeight;
	f32 m_cameraFrontDist;
	f32 m_cameraFrontPitch;
	f32 m_cameraBackHeight;
	f32 m_cameraBackDist;
	f32 m_cameraBackPitch;
	f32 m_cameraDownHeight;
	f32 m_cameraDownDist;
	f32 m_cameraDownPitch;
	f32 m_cameraTetherStiffness;
	f32 m_cameraLookDwell;
	f32 m_cameraNetPosSmooth;
	f32 m_cameraReleaseRad;
	f32 m_cameraPeekDecayRate;
	f32 m_running_reload_speed;
	f32 m_running_chgweapon_speed;
	f32 m_lowHeight;
	f32 m_medHeight;
	f32 m_highHeight;
	f32 m_minStandHeight;
	f32 m_minJumpHeight;
	cam_wiggle m_cam_wiggle;
	throw_params m_throw_params;
	bool m_loaded = false;
	std::vector<CCameraParams> m_cam_params;
};