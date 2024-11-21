#pragma once
#include "gamez/zAnim/anim_main.h"
#include "gamez/zNode/node_main.h"
#include "gamez/zCamera/zcam.h"

class CEntity;
class CCharacterType;
class CharacterDynamics;
class CZSealBody;
class CZBodyPart;

enum DAMAGE_LOCATION
{
	HEAD,
	BODY,
	LARM,
	RARM,
	LLEG,
	RLEG
};

enum SEAL_CONTROL_TYPE
{
	NONE,
	PLAYER,
	AI,
	SQUIRM,
	MISC
};

int recycler_index = 0;
CEntity* ftsPlayer;
CSealAnim* m_sealanim;
CharacterDynamics theCharacterDynamics;

CEntity* ftsGetPlayer();

void SealInitCharacterDynamics();

class CCharacterType
{
public:
	CCharacterType();
};

class CharacterDynamics
{
public:
	void Load(_zrdr* reader);

	float m_gravity;
	float m_DamageToNewtons;
	float m_jumpFactor;
	float m_landFallRate;
	float m_landHardFallRate;
	float m_groundTouchDistance;
	float m_maxSlopeCos;
	float m_stepHeight;
	float m_blastBoostY;
	float m_fallDist[3];
	float m_landSpeed[3];
	float m_standTurnFactor;
	float m_turn_maxRate;
	float m_accelXMin;
	float m_accelXMax;
	float m_accelZMin;
	float m_accelZMax;
	float m_initAimPitch;
	float m_maxAimPitch;
	float m_minAimPitch;
	float m_maxAimYaw;
	float m_proneMaxAimPitch;
	float m_proneMinAimPitch;
	float m_proneMaxAimYaw;
	float m_proneZoomDeltaYaw;
	float m_maxLookPitch;
	float m_minLookPitch;
	float m_maxLookYaw;
	float m_maxEyelookPitch;
	float m_minEyelookPitch;
	float m_maxEyelookYaw;
	float m_maxBlinkRate;
	float m_maxBlinkAngle;
	float m_cosMaxAimPitch;
	float m_cosMinAimPitch;
	float m_cosMaxAimYaw;
	float m_cosMaxEyelookPitch;
	float m_cosMinEyelookPitch;
	float m_cosMaxEyelookYaw;
	float m_maxZoomAimPitch;
	float m_minZoomAimPitch;
	float m_maxZoomAimYaw;
	float m_proneMaxZoomAimPitch;
	float m_proneMinZoomAimPitch;
	float m_proneMaxZoomAimYaw;
	float m_cosMaxZoomAimPitch;
	float m_cosMinZoomAimPitch;
	float m_cosMaxZoomAimYaw;
	float m_cosProneMaxZoomAimPitch;
	float m_cosProneMinZoomAimPitch;
	float m_cosProneMaxZoomAimYaw;
	float m_pitchRate;
	float m_turnThrottleA;
	float m_turnThrottleB;
	float m_pitchThrottleA;
	float m_pitchThrottleB;
	float m_minWaterFactor;
	float m_waterFactorSlope;
	float m_fbStiffness;
	float m_lrStiffness;
	float m_throtExp;
	float m_throtScale;
	float m_cameraRoll;
	float m_zoomFactor;
	float m_zoomRate;
	float m_cameraSideHeight;
	float m_cameraSideDist;
	float m_cameraSidePitch;
	float m_cameraFrontHeight;
	float m_cameraFrontDist;
	float m_cameraFrontPitch;
	float m_cameraBackHeight;
	float m_cameraBackDist;
	float m_cameraBackPitch;
	float m_cameraDownHeight;
	float m_cameraDownDist;
	float m_cameraDownPitch;
	float m_cameraTetherStiffness;
	float m_cameraLookDwell;
	float m_cameraNetPosSmooth;
	float m_cameraReleaseRad;
	float m_cameraPeekDecayRate;
	float m_running_reload_speed;
	float m_running_chgweapon_speed;
	float m_lowHeight;
	float m_medHeight;
	float m_highHeight;
	float m_minStandHeight;
	float m_minJumpHeight;
	cam_wiggle m_cam_wiggle;
	throw_params m_throw_params;
	bool m_loaded;
	std::vector<CCameraParams> m_cam_params;
};

class CEntity
{
public:
	enum TYPE
	{
		type_00,
		type_01,
		type_02,
		type_03
	};

	CEntity(TYPE type, const zdb::CNode& node);
	~CEntity();

	void IncrementAwareCounter();
	void DecrementAwareCounter();

	// Recycler functions
	virtual void OnRecycleEntity();
	CEntity* CreateRecycler;
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

	zdb::CNode& GetNode() const;
	bool IsValid() const;

	void SetController(CEntityCtrl* controller);
protected:
	unsigned int m_id;
	unsigned int m_index;
	unsigned int m_vehicle_index;
	TYPE m_type;

	const char* m_display_name;
	unsigned int m_UnitsSeenBy;

	zdb::CNode* m_node;

	CPnt3D m_velM; // Model-relative velocity
	CPnt3D m_velW; // World-relative velocity
	CPnt3D m_velR; // Angular-relative velocity?
	CQuat m_quat; // Rotation
	CPnt3D m_next_velw; // Model-relative wish velocity
	CQuat m_next_quat; // Next wish rotation
	CMatrix m_next_matrix; // Next wish transformation

	CEntityCtrl* m_control;

	unsigned int m_aware_counter;

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

	virtual void PreTick(float delta);
	virtual void Tick(float delta);
	virtual void PostMortemPreTick(float delta);
	
	virtual void SetThrottle(float throttle, int pad);
	virtual void GetRemoteControl() const;
protected:
	float* throttles;
};

class CftsPlayer : public CEntity
{
public:
	static void RegisterAnimCommands();
};