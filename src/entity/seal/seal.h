#pragma once
#include "ai/ai_main.h"
#include "entity/ent_main.h"
#include "entity/weapon/zwep_weapon.h"

float noTurnThreshold = 0.0f;
float fineTuneThreshold = 0.0f;
float throttleFudge = 0.0f;
bool init = false;

class CZKit
{
public:
	CZKit();
	~CZKit();

	void SetItemByIndex(int index, CZWeapon* weapon);
	void SetWeaponInfoChanged();
	void NVG_Enabled(bool enable);

	void* GetIcon(int index) const;
	float GetFireDelay() const;
	CZWeapon* GetCurItem() const;
	int GetNumItems() const;
	float GetCurZoom() const;

	void SetBody(const CZSealBody& body);
private:
	CZSealBody* seal;
	int curWeaponIdx;
	CZWeapon** arsenal;
	int numItems;
};

class CZSealBody : CEntity
{
	// Tomb Of The Unknown Functions
public:
	CZSealBody(const zdb::CNode& node, const CCharacterType& character) : CEntity(CEntity::type_02, node) {}
	~CZSealBody();

	static CZSealBody* Create(long param_1, int param_2, int param_3);

	CEntity* baseEntity;
	CEntity* entity;

	void Destroy();
	bool DestroyAimAnims();

	void OnDeath();

	void TeleportTo(const CMatrix& mat);

	CCharacterType* GetCharacter() const;
	int GetHeadDamage(float headDmgOld, float headDmgNew);
	int GetBodyDamage(float bodyDmgOld, float bodyDmgNew);
	int GetArmDamage(float armDmgOld, float armDmgNew);
	int GetLegDamage(float legDmgOld, float legDmgNew);

	float SetHealth(float health);
	void SetArmor(float armor, DAMAGE_LOCATION location);
	void SetupDefaultArmor();
	void SetupKevlarArmor();
	void SetupKevlarInsertArmor();

	float GetFormationHeading(float heading) const;
	void UpdateFollowParams(float heading);
	void HandleKiller(const CZSealBody& killer);

	CZBodyPart* GetRootPart() const;
private:
	float health;
	bool dead;

	float velX;
	float velY;

	float armorHead;
	float armorBody;
	float armorLArm;
	float armorRArm;
	float armorLLeg;
	float armorRLeg;

	bool hasFollower;

	CCharacterType* character;
	CZBodyPart* skel_root;
	CZBodyPart* lfoot;
	CZBodyPart* rfoot;
	CZBodyPart* lhand;
	CZBodyPart* spinelo;
	CZBodyPart* rhand;
	CZBodyPart* hips;
	CZBodyPart* head;
	CZBodyPart* neck;
	CZBodyPart* neck;
	CZBodyPart* spinehi;
	CZBodyPart* lthigh;
	CZBodyPart* rthigh;
	CZBodyPart* rcalf;
	CZBodyPart* rbicep;
	CZBodyPart* rforearm;
	CZBodyPart* lbicep;
	CZBodyPart* lforearm;
	CZBodyPart* lscap;
	CZBodyPart* rscap;
	CZBodyPart* lshoulder_wgt;
	CZBodyPart* rshoulder_wgt;
	CZBodyPart* lcalf;
	CZBodyPart* aimnodes;
	CZBodyPart* ltoe;
	CZBodyPart* rtoe;
};

class CZSealEx : public zdb::CNodeEx
{

};

class CSealCtrl : CEntityCtrl
{
public:
	CSealCtrl() : CEntityCtrl() { }
	~CSealCtrl();

	virtual bool AllowCommand(CZSealBody* seal, FT_COMMAND command, void* buffer);
	virtual bool CanDefuseBomb(CNodeAction* action) const;
	virtual bool CanPlaceBomb(CNodeAction* action) const;
	virtual bool CanPerformAction(CNodeAction* action) const;
	virtual void ClearGoal(GOAL_TYPE type);
	virtual void ClearLook(AI_LOOK look);
	virtual bool ComputeTurnThrottle(const CPnt3D& velWorld, const CPnt3D& velLocal, float& throttle);
	// virtual float ComputeVisibility(zdb::DiIntersection* intersection, CTarget* target);
	bool CreateAiEvent(CAiEvent::EVENT event, float expiration, float radius, bool flag, CPnt3D* position, int dummy);
private:
	float* timerMap;
	CZSealBody* body;
};

class CSealCtrlAi : CSealCtrl
{

};

class CSealCtrlSquirm : CSealCtrl
{

};

class CAiState
{
public:
	CAiState();
	~CAiState();

	static CAiState* Create(AI_STATE state);

	virtual void Tick();
	virtual void OnSignal();
	virtual bool CanPursue(CSealCtrlAi* controller);

	void Reset(AI_STATE state);
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