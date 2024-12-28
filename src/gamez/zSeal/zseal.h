#pragma once
#include "gamez/zAI/zai.h"
#include "gamez/zAnim/zanim.h"
#include "gamez/zEntity/body.h"
#include "gamez/zEntity/zentity.h"
#include "gamez/zEntity/intersect.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zUI/zui.h"
#include "gamez/zWeapon/zwep_weapon.h"
#include "gamez/zWeapon/zwep_ammo.h"

enum ZOOMSTATE
{
	ZOOMSTATE_UNKNOWN,
	ZOOMSTATE_3RDPERSON,
	ZOOMSTATE_1STPERSON,
	ZOOMSTATE_NVG,
	ZOOMSTATE_BINOCS,
	ZOOMSTATE_WEAPONDEF1,
	ZOOMSTATE_WEAPONDEF2,
	ZOOMSTATE_WEAPONDEF3,
	ZOOMSTATE_WEAPONDEF4,
	ZOOMSTATE_WEAPONDEF5,
	ZOOMSTATE_WEAPONDEF6,
	ZOOMSTATE_WEAPONDEF7,
	ZOOMSTATE_WEAPONDEF8,
	NUM_ZOOMSTATES
};

enum TRIGGER
{
	TRIGGER_UP,
	TRIGGER_DOWN,
	TRIGGER_FALLING,
	TRIGGER_RISING,
	TRIGGER_FINISH
};

enum SEAL_STATE
{
	stateStand,
	stateCrouch,
	stateProne,
	statePeek,
	stateHang,
	stateClimbLadder,
	stateInAir,
	stateIdle,
	stateDead,
	stateCarrying,
	stateCarried,
	stateDone
};

enum SEAL_PEEK
{
	PEEK_LEFT,
	PEEK_UP,
	PEEK_RIGHT,
	PEEK_NONE
};

enum SEAL_STANCE
{
	STANCE_NONE,
	STANCE_STAND,
	STANCE_CROUCH,
	STANCE_PRONE,
	STANCE_IDLE,
	STANCE_MAX
};

enum SEAL_ITEM
{
	itemNone,
	itemRifle,
	itemPistol,
	itemThrowable,
	itemDone
};

enum SEAL_HANDLE
{
	H_UNKNOWN,
	H_HUTCHINS,
	H_BAILEY,
	H_DIMONE
};

enum SEAL_DEATH_TYPE
{
	DEATH_NONE,
	DEATH_KNIFE_KILL,
	DEATH_CQB,
	DEATH_HEADSHOT,
	DEATH_GRENADE,
	DEATH_BULLET,
	DEATH_GHOST,
	DEATH_FALLING,
	DEATH_MAX
};

enum ENCUMBERANCE
{
	LIGHTLY_ENCUMBERED,
	MEDIUM_ENCUMBERED,
	HEAVY_ENCUMBERED,
	VERY_HEAVILY_ENCUMBERED,
	NOT_ENCUMBERED,
	NUM_ECUMBTYPES
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

/// -------------------------------------------
/// FORWARD DECLARATIONS
/// -------------------------------------------

// TODO: Unknown type in std::vector
class CObjAnims : public std::vector<void*> {};

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

class CFire : CSequence {};
class CLookItem : CSequence {};
class CLook : CSequence {};
class CBlink : CSequence {};
class CTurnInPlace : CSequence {};
class CCrouchedRun : CSequence {};

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
	BITFIELD_UINT(m_first, 1);
	BITFIELD_UINT(m_reticuletypeChanged, 1);
	BITFIELD_UINT(m_weaponinfoChanged, 1);
	BITFIELD_UINT(m_retblocked, 1);
	BITFIELD_UINT(m_nvg_enabled, 1);
	BITFIELD_UINT(m_binocs_enabled, 1);
	BITFIELD_UINT(m_lase_echo, 1);
	BITFIELD_UINT(m_lase_deploy_echo, 1);
	BITFIELD_UINT(m_lensfx_enable, 1);
	BITFIELD_UINT(m_waiting_to_fire, 1);
	BITFIELD_UINT(m_waiting_to_raise, 1);
	BITFIELD_UINT(m_changeToRifle, 1);
	BITFIELD_UINT(m_requested_item, 1);
	BITFIELD_UINT(m_current_requested_ammo, 1);
	BITFIELD_UINT(m_heartbeat_enabled, 1);
	BITFIELD_UINT(m_unused, 17);

	float m_retposx;
	float m_retposy;
	float m_retoffsetx;
	float m_retoffsety;

	float m_sniper_posx;
	float m_sniper_posy;
	float m_sniper_prev_posx;
	float m_sniper_prev_posy;

	float m_firerifle_kick_baseline;
	float m_firerifle_kick_movedist;
	float m_firerifle_kick_accum;
	int m_firerifle_kick_state;

	unsigned int m_heartbeat_state;
	float m_heartbeat_accum;
	float m_chill_parabola;

	int m_curitemreticule;
	
	float m_screenoffset_x;
	float m_screenoffset_y;

	float m_lase_timer;
	CZAnim* m_lase_anim;
	// name* m_lase_mapname // TODO: Create the name struct. I don't know why they named it that.

	unsigned int m_itemstate[30];
	CZFTSWeapon* m_item[30];
	CZAmmo* m_ammo[30];
	int m_reloads[30][10];
	int m_currentmag[30];
	int m_firemode[30];
	CCharacterGear* m_associatedgear[30];
	unsigned char m_iteminuse[30];

	int m_cur_zoom;
	int m_restore_zoom;
	int m_burst_count;
	int m_fire_delay;
	int m_selected_item;
	int m_last_selected;
	int m_num_items;
	
	CZSealBody* m_body;
	
	std::vector<unsigned char> m_items_avail;

	zdb::CNode* m_detonator_model;
	zdb::CNode* m_flashlight_model;
	zdb::CTexture* m_detonator_icon;

	float m_retsize;
	float m_prev_retsize;
	float m_prev_factor;
	float m_prev_axis_a;
	float m_prev_axis_b;
	float m_retblockedsize;
	float m_retblockedX;
	float m_retblockedY;
	float m_retsizegoal;
	float m_retmax;
	float m_retmin;

	int m_tracercount;
	float m_firetime;
	
	// zdb::CLightMap* m_lightMap; // TODO: Create the CLightMap class
	CSnd* m_rldsnd;
	CSnd* m_clicksnd;
	CSnd* m_lasersnd_start;
	CSnd* m_lasersnd_fin;

	float m_pickupRequestWait;
};

class CZSealBody : public CEntity, CBody
{
	// Tomb Of The Unknown Functions
	friend class CCharacterGear;
public:
	/// -------------------------------------------
	/// CREATION/DELETION
	/// -------------------------------------------

	CZSealBody(const zdb::CNode& node, const CCharacterType& character) : CEntity(CEntity::type_02, node) {}
	~CZSealBody();

	static CCharacterType* PreCreateSeal(CCharacterType* charType, const char* name, zdb::CNode** nodes);
	static CZSealBody* Create(CCharacterType* charType, const char* name, CSealCtrl* controller);
	static void PostCreateSeal(CZSealBody* seal, CSealCtrl* controller);
	static bool ReCreate(CZSealBody* seal, const CCharacterType* charType);

	void Destroy();
	bool DestroyAimAnims();
	void DeleteCameraEffectsNode();

	/// -------------------------------------------
	/// INITIALIZATION
	/// -------------------------------------------

	void InitDatabaseHandles();
	void InitDecalHandles();
	void InitHandSignals();
	void InitLookAnims();
	CRdrFile* InitMotionRdrFile();

	void SetupGear();
	void SetupEyes();

	void SetupDefaultArmor();
	void SetupKevlarArmor();
	void SetupKevlarInsertArmor();

	/// -------------------------------------------
	/// EVENTS
	/// -------------------------------------------

	void PreTick(float delta);
	void PostPreTick(float delta);
	void Tick(float delta);
	void PrePostTick(float delta);
	void PostTick(float delta);
	void PostMortemPreTick(float delta);

	void OnMissionStart();
	void OnMissionEnd();
	void OnWeaponHit();
	void OnDeath();
	void OnRecycleEntity();

	/// -------------------------------------------
	/// HEALTH
	/// -------------------------------------------

	float SetHealth(float health);
	void SetArmor(float armor, DAMAGE_LOCATION location);

	int GetHeadDamage(float headDmgOld, float headDmgNew);
	int GetBodyDamage(float bodyDmgOld, float bodyDmgNew);
	int GetArmDamage(float armDmgOld, float armDmgNew);
	int GetLegDamage(float legDmgOld, float legDmgNew);

	bool DamageHead(float damage, float damageMax);
	bool DamageBody(float damage, float damageMax);
	bool DamageLArm(float damage, float damageMax);
	bool DamageRArm(float damage, float damageMax);
	bool DamageLLeg(float damage, float damageMax);
	bool DamageRLeg(float damage, float damageMax);

	bool DamageHead(CZProjectile* projectile);
	bool DamageBody(CZProjectile* projectile);
	bool DamageLArm(CZProjectile* projectile);
	bool DamageRArm(CZProjectile* projectile);
	bool DamageLLeg(CZProjectile* projectile);
	bool DamageRLeg(CZProjectile* projectile);

	void AdrenalineIncr(float increase);

	void SetupDefaultArmor();
	void SetupKevlarArmor();
	void SetupKevlarInsertArmor();

	/// -------------------------------------------
	/// STATE CONDITIONS
	/// -------------------------------------------

	bool CanAttainAim(CPnt3D& point) const;
	bool CanChangeItem() const;
	bool CanClimbLadder() const;
	bool CanClimbWall() const;
	bool CanCrouch() const;
	bool CanFire() const;
	bool CanHeadLook() const;
	bool CanInterrupt() const;
	bool CanPickupNetItem(unsigned short hostIdx, unsigned short pickupIdx, unsigned short* idxPtr, unsigned char type) const;
	bool CanPitch() const;
	bool CanProneAim() const;
	bool CanTraverse(CDIType type) const;
	bool CanTurn() const;
	bool CanUseBodyCarry(CZSealBody* seal) const;
	bool CanUseCQB(CZSealBody* seal) const;
	bool CanUseKnife(CZSealBody* seal) const;
	bool CanUseRestraint(CZSealBody* seal) const;
	bool CanZoom() const;

	/// -------------------------------------------
	/// BEHAVIOR HANDLING
	/// (Damage, world interactions, etc.)
	/// -------------------------------------------

	void HandleBloodDrip(float delta);
	void HandleBombDefuse() {}
	void HandleDamage(CZProjectile* projectile);
	void HandleDamageExplosive(CZBodyPart* part, DAMAGE_LOCATION location);
	void HandleDamageNonExplosive(CZBodyPart* part, DAMAGE_LOCATION location);
	int HandleFallingDamage(float impactForce); // TODO: Figure out what this function returns
	void HandleFootfallSound(CPnt3D* position);
	void HandleGrenadeExplosion();
	void HandleKiller(int killerIndex);
	void HandleLanding(float impactForce);
	void HandlePickupAck(int param_1, unsigned short pickupIdx, void* pickupAck); // TODO: Figure out wtf the AckUnion type is
	void HandlePickupAmmoInstance(void* pickup); // TODO: Create the CPickup type
	void HandlePickupEquip(void* pickup); // TODO: Create the CPickup type
	void HandlePickupMPBomb(void* pickup); // TODO: Create the CPickup type
	void HandleSealStep();
	void HandleSliding(float delta);
	void HandleSmokeAndGas(zdb::IntersectStruct* intersection, const void* material, const CPnt3D* position); // TODO: Create the CMaterialEx type
	void HandleStunDamage(char stunType, float damage, const CPnt3D* position); // TODO: Create the STUN_TYPE enum
	void HandleStunFromHit(char itemType, const CPnt3D* position); // TODO: Create the EQUIP_ITEM enum
	void HandleStunRecovery(char stunType); // TODO: Create the STUN_TYPE enum
	void HandleWater(zdb::IntersectStruct* intersection, const void* material, const CPnt3D* position); // TODO: Create the CMaterialEx type
	void HandleWeaponEvent(CZProjectile* projectile, unsigned int eventIdx, void* eventData);
	bool HandleWeaponIntersect();
	void HandleWeaponInterp();

	void TeleportTo(const CMatrix& mat);

	void AttemptBombDefuse() const;

	CCharacterType* GetCharacter() const;

	float GetFormationHeading(float heading) const;
	void UpdateFollowParams(float heading);
	void HandleKiller(const CZSealBody& killer);

	CZBodyPart* GetRootPart() const;
public:
	static CSealAnim* m_sealanim;
	static CRdrFile* m_motionRdrFile;
private:
	int m_MaxFollowerDistance;
	int m_MaxFollowerDistanceNext;

	ZOOMSTATE m_zoomstate;
	ZOOMSTATE m_zoomstate_prev;
	bool m_zoomstate_echo;

	float m_zoomrange;

	int m_onMaterial;

	bool m_didrstep;
	bool m_didlstep;

	float m_blooddriptimer;

	CZSealBody* m_cachedReticuleSeal;
	BITFIELD_INT(m_useCachedReticuleSeal, 1);
	BITFIELD_INT(m_unused, 31);

	bool m_TriggerCount;
	int m_RemoteRoundCount;
	float m_RemoteFireElevation;

	// Throttle
	float pre_thr_l;
	float pre_thr_fb;
	float pre_thr_strafe;

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

	std::vector<void*> m_deallocList;

	CCharacterGear* m_rifle_as_gear;
	CCharacterGear* m_pistol_as_gear;

	SEAL_STATE m_desiredState;
	SEAL_PEEK m_desiredPeek;

	float m_recoilParam;

	CObjAnims m_obj_anims;
	void* m_select; // TODO: Unknown void* type

	zdb::IntersectStruct m_last_altitude;
	zdb::IntersectStruct m_last_reticule;
	zdb::IntersectStruct m_last_reticule_action;

	CAiEvent* m_aiEvent;
	CAiPath m_snakePath;

	CPnt3D m_look_dir;
	CPnt3D m_formation_dir;
	CPnt3D m_saved_formation_dir;

	CAiMapLoc m_last_valid_maploc;
	CPnt3D m_last_valid_CPnt;
	int m_formation_clock;

	bool m_follow_params_are_current;
	bool m_saved_formation_dir_is_valid;

	AnimSet* m_animset;
	AnimSet* m_default_animset;
	AnimType m_CurrentBlendAnimType;
	
	CCharacterType* m_charType;
	
	CSealStats m_mp_stats;
	CSealStats m_stats;
	CAccuracy m_accuracy;
	CZKit m_kit;
	CSealEx m_sealEx;

	CAppCamera* m_camera;
	CZSealBody* m_carry;
	CAiDecay* m_adrenaline;

	CNodeAction* m_prev_nodeaction;

	CCompassAnchor* m_mpbomb_anchor;
	CCompassAnchor* m_mpbase_anchor;
	CCompassAnchor* m_hostage_anchor;

	unsigned int m_action_available_mask;
	unsigned int m_action_selection_mask;
	bool m_action_display_on;
	unsigned int m_action_command;

	float m_wep_upT;
	float m_wep_waitT;
	float m_wep_downT;
	float m_wep_sumT;

	int chordStart;
	int numChords;

	unsigned int m_QueryCharacterAltitude : 1;
	unsigned char m_threatdir[4];
	float m_threatscale[8];
	float m_threatangle[8];

	bool m_doCZSealBodyPostTick;

	CPnt3D dpos;
	float m_my;
	CPnt3D next_posw;

	bool m_anim_handled;
	unsigned int m_weapon_state;

	SEAL_ITEM m_item;

	CZProjectile* m_detonation_countdown;

	std::vector<CPnt3D*> m_refpoints;

	float m_mass;
	float m_waterdepth;
	CPnt3D m_footL;
	float m_twist_back;
	CPnt3D m_footR;
	float m_local_drot;
	float m_dT;
	float m_alt;
	float m_skel_y_w;

	float m_health;
	SEAL_DEATH_TYPE m_deathType;
	float m_time_of_death;
	int m_killer_index;
	int m_killer_weapon_index;
	int m_lastkiller_id;

	int m_ClientIndex;
	int m_vote_tally;
	bool m_new_stats;
	bool m_voted_against;
	bool m_local_voted_against;
	bool m_advance_camera;
	bool m_retreat_camera;
	bool m_needs_respawn;
	bool m_stunned;
	bool m_left_game;

	unsigned int m_full_update_time;

	float m_movespeedmod;
	float m_encumbmod;
	float m_damagemod;
	float m_retmods;
	float m_stunval[7];

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
	float m_armor[6];

	bool m_neworder;

	CZProjectile* m_lastprojectile;
	CZProjectile* m_tempprojectile;
	int m_projectileinserecthandle;
	zdb::DiIntersect m_projectiledi;
	unsigned int m_lastregion;

	BITFIELD_UINT(m_HudUpdateViewCone, 1);
	BITFIELD_UINT(m_hudwashit, 1);
	BITFIELD_UINT(m_aim_point_valid, 1);
	BITFIELD_UINT(m_invincible, 1);
	BITFIELD_UINT(m_invisible, 1);
	BITFIELD_UINT(m_infiniteammo, 1);
	BITFIELD_UINT(m_doPostTick, 1);
	BITFIELD_UINT(m_restrainable, 1);
	BITFIELD_UINT(m_restrained, 1);
	BITFIELD_UINT(m_order_flag, 1);
	BITFIELD_UINT(m_limp, 1);
	BITFIELD_UINT(m_isinsmoke, 1);
	BITFIELD_UINT(m_isingas, 1);
	BITFIELD_UINT(m_respawning, 1);
	BITFIELD_UINT(m_joined_unit, 1);
	BITFIELD_UINT(m_send_detail, 1);
	BITFIELD_UINT(m_snake_path, 1);
	BITFIELD_UINT(m_action_climb, 1);
	BITFIELD_UINT(m_action_jump, 1);
	BITFIELD_UINT(m_is_moving, 1);
	BITFIELD_UINT(m_is_turning, 1);
	BITFIELD_UINT(m_airborne, 1);
	BITFIELD_UINT(m_jumped, 1);
	BITFIELD_UINT(m_inwater, 1);
	BITFIELD_UINT(m_stancechanged, 1);
	BITFIELD_UINT(m_have_aim_norm, 1);
	BITFIELD_UINT(m_was_turning, 1);
	BITFIELD_UINT(m_aimpt_attainable, 1);
	BITFIELD_UINT(m_firept_attainable, 1);
	BITFIELD_UINT(m_used_vel_y, 1);
	BITFIELD_UINT(m_echo_pickup, 1);
	BITFIELD_UINT(m_animate_me, 1);
	BITFIELD_UINT(m_do_drop_weapons, 1);
	BITFIELD_UINT(m_fix_skel_y, 1);
	BITFIELD_UINT(m_inside, 1);
	BITFIELD_UINT(m_prev_have_aim_norm, 1);
	BITFIELD_UINT(m_am_stunned, 1);
	BITFIELD_UINT(m_iszooming, 1);
	BITFIELD_UINT(m_unused_bits, 26);

	CQuat m_fwdlook;
	float m_zoomval;
	zdb::CHit* m_fwdhit;

	std::vector<CZWeapon*> m_weapons;
	zdb::IntersectStruct* m_wephit;

	CFire* m_fire;
	CLookItem* m_lookitem;
	CLook* m_look;
	CLook* m_eyelook;
	CBlink* m_blink;
	CTurnInPlace* m_turnip;
	CCrouchedRun* m_crouch;

	AnimType idlehack;

	short m_throttleQuadrant;
	short m_prev_throttleQuadrant;
	float m_descent;
	float m_slide_descent;
	CPnt3D m_ground_normal;
	CPnt3D m_inAirHorizVel;
	float m_nextJumpTimer;
	float m_jumpTimer;
	float m_jumpImpulse;

	CZAnim* m_belowwateranim;
	CZAnim* m_inwateranim;
	zdb::CNode m_wateranimnode;

	CPnt3D m_aim_dir;
	CPnt3D m_aim_goal;
	CPnt3D m_aim_point;
	CPnt3D m_reticle_pt;
	CPnt3D m_aim_norm;
	CPnt3D m_prev_aim_point;
	CPnt3D m_prev_aim_norm;
	CPnt3D m_prev_reticle_pt;
	CPnt3D m_curr_aimpos;
	zdb::CNode* m_curr_aimpt;
	CPnt3D m_curr_firepos;
	zdb::CNode* m_curr_firept;

	CPnt3D m_skel_root;
	short m_last_foot;
	short m_fixed_foot;

	float m_TimeSpentDead;
	int m_NumDeathAnimsPlayed;
};

class CSealEx : public zdb::CNodeEx
{
public:
	virtual void OnAction(CNode* node, void* action);
	virtual void OnCopy(CNode* node, CNode* other);
	virtual void OnDelete(CNode* node);
	virtual void OnDoubleClick(CNode* node);
	virtual void OnMove(CNode* node);
	virtual void OnSelect(CNode* node, bool selected);
	virtual void* OnWeaponHit(CNode* node, zdb::IntersectStruct* intersection, CZProjectile* projectile);
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
	CSealCtrl() : CEntityCtrl() {}
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