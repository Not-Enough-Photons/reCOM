#pragma once
#include "Apps/FTS/ai_main.h"

#include "gamez/zEntity/ent_main.h"
#include "gamez/zEntity/intersect.h"
#include "gamez/zMath/zmath_main.h"
#include "gamez/zWeapon/zwep_weapon.h"

enum ZOOMSTATE
{
	SHORT,
	MEDIUM,
	LONG
};

enum TRIGGER
{
	type_00,
	type_01
};

enum PLAYER_CAM_STATE
{
	type_00,
	type_01
};

enum MENU_STATE
{
	type_00,
	type_01
};

enum AiSig
{
	AISIG_UNKNOWN,
	AISIG_ANIMCOMPLETE,
	AISIG_BEGINCRITICAL,
	AISIG_ENDCRITICAL,
	AISIG_SUSPEND,
	AISIG_RELEASE
};

float noTurnThreshold = 0.0f;
float fineTuneThreshold = 0.0f;
float throttleFudge = 0.0f;
bool init = false;

struct HEALTH_PARAMS
{
	void Parse(_zrdr* reader);

	float m_head_health;
	float m_head_healthMax;
	float m_body_health;
	float m_body_healthMax;
	float m_larm_health;
	float m_larm_healthMax;
	float m_rarm_health;
	float m_rarm_healthMax;
	float m_lleg_health;
	float m_lleg_healthMax;
	float m_rleg_health;
	float m_rleg_healthMax;
	float m_armor_head;
	float m_armor_body;
	float m_armor_rarm;
	float m_armor_larm;
	float m_armor_rleg;
	float m_armor_lleg;
};

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

class CZSealBody : public CEntity, CBody
{
	// Tomb Of The Unknown Functions
public:
	CZSealBody(const zdb::CNode& node, const CCharacterType& character) : CEntity(CEntity::type_02, node) {}
	~CZSealBody();

	static CZSealBody* Create(long param_1, int param_2, int param_3);

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
public:
	static CSealAnim* m_sealanim;

	CSealCtrl* m_control;
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

class CSealUnit
{

};

class CSealStats
{
public:
	int m_headshots;
	int m_headhits;
	int m_hits;
	int m_shots;
	int m_kills;
	int m_washit;
	int m_deaths;
	int m_hostages;
	int m_bases_blown;
	int m_hostages_rescued;
	float m_hit_percent;
	int m_num_times_seen;
	int m_num_stealthkills;
	int m_num_restrained;
	int m_num_grenades_used;
	int m_num_cqb_used;
	int m_primary_rounds_fired;
	int m_secondary_rounds_fired;
	short m_sMvpScore;
	int m_iRoundsWon;
	int m_iRoundsTied;
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

	virtual bool IsAi() const;
	virtual bool IsPlayer() const;
	virtual bool IsRemote() const;

	bool CreateAiEvent(CAiEvent::EVENT event, float expiration, float radius, bool flag, CPnt3D* position, int dummy);
public:
	unsigned int m_padid;
private:
	float m_look_timer;
	Rfloat m_look_rate;
	AI_LOOK m_look_mode;
	LOOK_DATA_TYPE m_look_type;
	CPnt3D m_look_data;
	CPnt3D m_look_data_mdir;
	CPnt3D m_look_bias;
	unsigned int m_look_flags;

	Rfloat m_scan_angle;
	CAiTimer m_scan_timer;
	float m_scan_limits;

	float m_fov;
	float m_fovtan;
	float m_fovcos;

	CAiCone m_view_cone;
	CAiDecay m_visrange;
	CAiDecay m_aware;

	unsigned int m_targetSum;
	CAiDecay m_targetThreat;	
	CSealUnit m_unit;

	unsigned int m_ai_net_state;
	TRIGGER m_trigger;
	float m_trigger_power;
	int m_throwwait;
	float m_buttonreading[10];
	int m_firstreading;
	int m_lastreading;

	float m_zoomlevel;
	float m_zoomincrement;
	float m_aimPitch;
	float m_aimYaw;
	float m_highrumbletime;
	float m_rumbletime;
	float m_rumblestr;

	int m_HudDoPickup;
	int m_curpickup_ID;
	int m_curpickup_secondary_ID;

	zdb::CNode* m_bomb_defusal_node;
	zdb::CNode* m_mpbomb_node;
	float m_mpbomb_timer;

	CZSealBody* m_victimbody;
	CZSealBody* m_corpsebody;

	bool m_goal_pos_valid;
	bool m_goal_dir_valid;
	bool m_wasthrowing;
	bool m_HudUpdateWeapon;
	bool m_HudUpdateViewCone;
	bool m_throwing;
	bool m_justthrew;
	bool m_update_zoom;
	bool m_zoomin;
	bool m_zoomout;
	bool m_input_enabled;
	bool m_mpbomb_bTimerAvailable;
	bool m_mpbomb_bTimerEngaged;
	bool m_has_respawned;
	bool m_do_aimap_collide;

	unsigned int m_unused : 16;

	CPnt3D m_goal_dir;
	CPnt3D m_goal_pos;
	CPnt3D m_fudge_velR;
	CPnt3D m_fudge_velM;
	CPnt3D m_fudge_velW;

	GOAL_TYPE m_goal_type;
	float m_goal_pos_tolerance;
	CAiTimer m_goal_timer;

	float m_speed;

	float m_event_time[15];
	CPnt3D m_remote_goal_pos;
	CQuat m_remote_goal_quat;

	PLAYER_CAM_STATE m_camState;
	MENU_STATE m_menustate;
	
	float m_hotswapL1;
	float m_hotswapL2;

	CAiTimer m_wep_state;

	float m_bombpickuptimer;
	float m_weapon_pickup_timer;
};

class CSealCtrlAi : CSealCtrl
{
public:
	static bool RegisterCommands();
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

class CTAction
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTComm
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTDebug
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTDoor
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTEvent
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTFireMode
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTFireWeapon
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTGoto
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTHold
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTInState
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTInView
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTLookAt
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTMacro
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTMap
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTMove
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTPaint
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTParam
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTPlay
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void Create(int count, unsigned int*, float, float);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTPursue
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTRange
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTRegion
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTSelect
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTSetAnimSet
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTSetMode
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTSignal
{
public:
	static AiSig GetSignalByName(const char* signal);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTSound
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTSpecial
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTStance
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTState
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTStopAll
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTTeam
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTValve
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};

class CTWait
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, float* delta);
};