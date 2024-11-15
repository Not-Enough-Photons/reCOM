#pragma once
#include "Apps/FTS/ai_main.h"

#include "gamez/zEntity/ent_main.h"
#include "gamez/zEntity/intersect.h"
#include "gamez/zWeapon/zwep_weapon.h"

enum ZOOMSTATE
{
	SHORT,
	MEDIUM,
	LONG
};

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
	bool CanClimbWall();
	bool CanTraverse(unsigned int moveType);

	void AttemptBombDefuse() const;

	CCharacterType* GetCharacter() const;
	int GetHeadDamage(float headDmgOld, float headDmgNew);
	int GetBodyDamage(float bodyDmgOld, float bodyDmgNew);
	int GetArmDamage(float armDmgOld, float armDmgNew);
	int GetLegDamage(float legDmgOld, float legDmgNew);

	void AdrenalineIncr(float increase);

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
	CBody m_body;

	int m_MaxFollowerDistance;
	int m_MaxFollowerDistanceNext;

	ZOOMSTATE m_zoomstate;
	ZOOMSTATE m_zoomstate_prev;
	ZOOMSTATE m_zoomstate_echo;
	float m_zoomrange;

	int m_onMaterial;
	bool m_didrstep;
	bool m_didlstep;

	float m_bloodriptimer;

	CZSealBody* m_cachedReticuleSeal;
	bool m_useCachedReticuleSeal;
	
	int m_unused;

	bool m_TriggerCount;
	int m_RemoteRoundCount;
	float m_RemoteFireElevation;

	// Throttle
	float pre_thr_l;
	float pre_thr_fb;
	float pre_thr_state;

	float m_prev_thr_x;
	float m_prev_thr_z;

	CPnt3D p0_pos0_w;
	CPnt3D p0_pos1_w;
	float p0_d;
	bool p0_run;

	zdb::DiIntersect pa_di;
	zdb::DiIntersect pa_diIntersect[1]; // ...what?
	CPnt3D pi_diTail;
	int pi_diIntersectHandle[1]; // ...why?
	int pa_diIntersectHandle;

	// Don't know what type goes into the vector, so we'll assume a float for now
	std::vector<float> m_volumetricAltitudes;

	CCharacterType* character;
	CZBodyPart* m_root;
	CZBodyPart* m_lfoot;
	CZBodyPart* m_rfoot;
	CZBodyPart* m_lhand;
	CZBodyPart* m_spinelo;
	CZBodyPart* m_rhand;
	CZBodyPart* m_hips;
	CZBodyPart* m_head;
	CZBodyPart* m_neck;
	CZBodyPart* m_neck;
	CZBodyPart* m_spinehi;
	CZBodyPart* m_lthigh;
	CZBodyPart* m_rthigh;
	CZBodyPart* m_rcalf;
	CZBodyPart* m_rbicep;
	CZBodyPart* m_rforearm;
	CZBodyPart* m_lbicep;
	CZBodyPart* m_lforearm;
	CZBodyPart* m_lscap;
	CZBodyPart* m_rscap;
	CZBodyPart* m_lshoulder_wgt;
	CZBodyPart* m_rshoulder_wgt;
	CZBodyPart* m_lcalf;
	CZBodyPart* m_aimnodes;
	CZBodyPart* m_ltoe;
	CZBodyPart* m_rtoe;
	CZBodyPart* m_weapon;
	CZBodyPart* m_rifle;
	CZBodyPart* m_pistol;
	CZBodyPart* m_grenade;
	CZBodyPart* m_reyeball;
	CZBodyPart* m_leyeball;
	CZBodyPart* m_reyelid;
	CZBodyPart* m_leyelid;

	// std::vector<void> m_deallocList;
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