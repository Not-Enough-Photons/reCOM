#pragma once
#include "gamez/zAI/zai.h"
#include "gamez/zAnim/zanim.h"
#include "gamez/zNode/znode.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zRender/zrender.h"

struct cam_wiggle;
struct throw_params;

class CEntity;
class CEntityCtrl;
class CCharacterType;
class CharacterDynamics;
class CZSealBody;
class CZBodyPart;
class CModel;
class CCameraParams;

struct HEALTH_PARAMS;

enum class DAMAGE_LOCATION
{
	HEAD,
	BODY,
	LARM,
	RARM,
	LLEG,
	RLEG
};

enum class SEAL_CONTROL_TYPE
{
	CTRL_NONE,
	CTRL_PLAYER,
	CTRL_AI,
	CTRL_SQUIRM,
	CTRL_MISC
};

extern int recycler_index;
extern CSealAnim* m_sealanim;
extern CharacterDynamics theCharacterDynamics;

void SealInitCharacterDynamics();

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

struct start
{
	char m_name[16];
	s32 m_dir;
};

struct startvec
{
	u32 m_count;
	start m_start[4];
};

class CVehicleRdr
{

};

class CVehicleRdrEntry
{
private:
	char m_name[32];
	char m_character[48];
	char m_display_name[32];
	startvec m_start;
	s32 m_teamMask;
	AI_PARAMS m_aiParams;
	u32 m_debug : 1;
	u32 m_disabled : 1;
	u32 m_nofade : 1;
	u32 m_noshoot : 1;
	u32 m_recycle : 1;
	u32 m_nosnooze : 1;
	u32 m_unused : 26;
	s32 m_startIndex;
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

class CEntity
{
public:
	enum TYPE
	{
		ENT_TYPE_UNKNOWN,
		ENT_TYPE_RECYCLE,
		ENT_TYPE_SEAL,
		ENT_TYPE_TURRET
	};

	CEntity(TYPE type, zdb::CNode* node);
public:
	void IncrementAwareCounter();
	void DecrementAwareCounter();

	// Recycler functions
	virtual void OnRecycleEntity();
	CEntity* CreateRecycler();
	void OpenRecycler();

	// Mission callback functions
	virtual void OnMissionStart();
	virtual void OnMissionEnd();

	// Tick virtual functions
	virtual void PreTick() {};
	virtual void PostPreTick() {};
	virtual void PrePostTick() {};
	virtual void Tick() {};
	virtual void PostTick() {};

	void SetDisplayName(const char* displayName);

	virtual void TeleportTo(const CMatrix& mat);

	zdb::CNode* GetNode() const;
	bool IsValid() const;

	void SetController(CEntityCtrl* controller);
public:
	CEntityCtrl* m_control;
	
	u32 m_id;
	u32 m_index;
	u32 m_vehicle_index;

	TYPE m_type;

	const char* m_display_name;
	u32 m_UnitsSeenBy;

	zdb::CNode* m_node;

	CPnt3D m_velM; // Model-relative velocity
	CPnt3D m_velW; // World-relative velocity
	CPnt3D m_velR; // Angular-relative velocity?
	CQuat m_quat; // Rotation
	CPnt3D m_next_velw; // Model-relative wish velocity
	CQuat m_next_quat; // Next wish rotation
	CMatrix m_next_matrix; // Next wish transformation

	u32 m_aware_counter;

	bool m_blink_eyes;
	bool m_drip_blood;
	bool m_animate_footsteps;
	bool m_interpolate_animations;
	bool m_lean_into_turns;
	bool m_do_weapon_recoil;
	bool m_check_player_collision;
	bool m_get_new_altitude;
	bool m_noshoot;
	bool m_update_targetlist;
	bool m_include_in_targetlist;
	bool m_isAlive;

	// CAiMapLoc m_mapLoc;
	// CAiMapLoc m_mapLocValid;
};

class CEntityCtrl
{
public:
	CEntityCtrl();
	~CEntityCtrl();

	virtual void PreTick(f32 delta);
	virtual void Tick(f32 delta);
	virtual void PostMortemPreTick(f32 delta);

	virtual void SetThrottle(f32 throttle, s32 pad);
	virtual void GetRemoteControl() const;

	virtual void OnDeath();
protected:
	CEntity* m_entity;
	f32 m_throttle[3];
};

class CftsPlayer : public CEntity
{
public:
	static void RegisterAnimCommands();
};

class CPickup
{
public:
	void Destroy();
private:
	zdb::CNode* m_node;
	void* m_data;
	u8 m_type;
	bool m_locked;
	bool m_secondary;
	u8 m_unused;
	s16 m_id;
	s16 m_netid;
	bool m_visible_by_units;
};