#pragma once
#include "anim/anim_main.h"
#include "node/node_main.h"

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

	bool loadedCD;

	float gravity;
	float newtonDamage;
	float jumpFactor;
	float landFallRate;
	float landHardFallRate;
	float groundTouchDistance;
	float maxSlope;
	float stepHeight;
	float fallDamageLimit;
	float fallDamageHeavy;
	float fallDamageDeath;
	float waterFactorSlope;
	float minWaterFactor;
	float fbAccel;
	float lrAccel;
	float throttleExp;
	float standTurnFactor;
	float turnMaxRate;
	float initAimPitch;
	float maxAimPitch;
	float minAimPitch;
	float maxAimYaw;
	float proneMinAimPitch;
	float proneMaxAimPitch;
	float proneMaxAimYaw;
	float proneZoomDeltaYaw;
	float maxLookPitch;
	float maxLookYaw;
	float maxEyeLookPitch;
	float minEyeLookPitch;
	float maxEyeLookYaw;
	float maxBlinkRate;
	float maxBlinkAngle;
	float pitchRate;
	float turnThrottleA;
	float turnThrottleB;
	float pitchThrottleA;
	float pitchThrottleB;
	float cameraRoll;
	float cameraWiggleAmplitude;
	float cameraWiggleDuration;
	float cameraWiggleRate;
	float zoomFactor;
	float zoomRate;
	float minRunningReloadSpeed;
	float minRunChangeWeaponSpeed;
	float lowClimbHeight;
	float medClimbHeight;
	float highClimbHeight;
	float minStandHeight;
	float minJumpHeight;
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
private:
	zdb::CNode* m_node;

	float m_x00;
	float m_y00;
	float m_z00;
	float m_x01;
	float m_y01;
	float m_z01;
	float m_x02;
	float m_y02;
	float m_z02;
	float m_x03;
	float m_y03;
	float m_z03;
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