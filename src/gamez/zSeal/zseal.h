#pragma once
#include "Apps/FTS/hud.h"

#include "gamez/zAI/zai.h"
#include "gamez/zAnim/zanim.h"
#include "gamez/zBody/zbody.h"
#include "gamez/zEntity/zentity.h"
#include "gamez/zPhysics/zphysics.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zUI/zui.h"
#include "gamez/zWeapon/zweapon.h"

/// -------------------------------------------
/// FORWARD DECLARATIONS
/// -------------------------------------------
class CZSealBody;
class CSealCtrl;
class CAppCamera;

class CCharacterGear;

enum class PLAYER_CAM_STATE;

/// -------------------------------------------
/// ENUMS
/// -------------------------------------------
enum class ZOOMSTATE
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

enum class TRIGGER
{
	TRIGGER_UP,
	TRIGGER_DOWN,
	TRIGGER_FALLING,
	TRIGGER_RISING,
	TRIGGER_FINISH
};

enum class SEAL_STATE
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

enum class SEAL_PEEK
{
	PEEK_LEFT,
	PEEK_UP,
	PEEK_RIGHT,
	PEEK_NONE
};

enum class SEAL_STANCE
{
	STANCE_NONE,
	STANCE_STAND,
	STANCE_CROUCH,
	STANCE_PRONE,
	STANCE_IDLE,
	STANCE_MAX
};

enum class SEAL_ITEM
{
	itemNone,
	itemRifle,
	itemPistol,
	itemThrowable,
	itemDone
};

enum class SEAL_HANDLE
{
	H_UNKNOWN,
	H_HUTCHINS,
	H_BAILEY,
	H_DIMONE
};

enum class SEAL_DEATH_TYPE
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

enum class AiSig
{
	AISIG_UNKNOWN,
	AISIG_ANIMCOMPLETE,
	AISIG_BEGINCRITICAL,
	AISIG_ENDCRITICAL,
	AISIG_SUSPEND,
	AISIG_RELEASE
};

namespace sealai
{
	const char* get_aiseq(AI_SEQUENCE sequence);

	AI_MODE get_mode(const char* name);

	const char* get_stance(SEAL_STANCE stance);
	SEAL_STANCE get_stance(const char* name);

	AI_STATE get_state(const char* name);
	const char* get_state(AI_STATE state);
}

// TODO: Unknown type in std::vector
class CObjAnims : public std::vector<void*> {};

extern f32 noTurnThreshold;
extern f32 fineTuneThreshold;
extern f32 throttleFudge;

class CFire : CSequence {};
class CLookItem : CSequence {};
class CLook : CSequence {};
class CBlink : CSequence {};
class CTurnInPlace : CSequence {};
class CCrouchedRun : CSequence {};

class CZKit
{
public:
	// CZKit();

	void SetItemByIndex(s32 index, CZWeapon* weapon);
	void SetWeaponInfoChanged();
	void NVG_Enabled(bool enable);

	void* GetIcon(s32 index) const;
	f32 GetFireDelay() const;
	CZWeapon* GetCurItem() const;
	s32 GetNumItems() const;
	f32 GetCurZoom() const;

	void SetBody(const CZSealBody& body);
private:
	u32 m_first : 1;
	u32 m_reticuletypeChanged : 1;
	u32 m_weaponinfoChanged : 1;
	u32 m_retblocked : 1;
	u32 m_nvg_enabled : 1;
	u32 m_binocs_enabled : 1;
	u32 m_lase_echo : 1;
	u32 m_lase_deploy_echo : 1;
	u32 m_lensfx_enable : 1;
	u32 m_waiting_to_fire : 1;
	u32 m_waiting_to_raise : 1;
	u32 m_changeToRifle : 1;
	u32 m_requested_item : 1;
	u32 m_current_requested_ammo : 1;
	u32 m_heartbeat_enabled : 1;
	u32 m_unused : 17;

	f32 m_retposx;
	f32 m_retposy;
	f32 m_retoffsetx;
	f32 m_retoffsety;

	f32 m_sniper_posx;
	f32 m_sniper_posy;
	f32 m_sniper_prev_posx;
	f32 m_sniper_prev_posy;

	f32 m_firerifle_kick_baseline;
	f32 m_firerifle_kick_movedist;
	f32 m_firerifle_kick_accum;
	s32 m_firerifle_kick_state;

	u32 m_heartbeat_state;
	f32 m_heartbeat_accum;
	f32 m_chill_parabola;

	s32 m_curitemreticule;
	
	f32 m_screenoffset_x;
	f32 m_screenoffset_y;

	f32 m_lase_timer;
	CZAnim* m_lase_anim;
	// name* m_lase_mapname // TODO: Create the name struct. I don't know why they named it that.

	u32 m_itemstate[30];
	CZFTSWeapon* m_item[30];
	CZAmmo* m_ammo[30];
	s32 m_reloads[30][10];
	s32 m_currentmag[30];
	s32 m_firemode[30];
	CCharacterGear* m_associatedgear[30];
	u8 m_iteminuse[30];

	s32 m_cur_zoom;
	s32 m_restore_zoom;
	s32 m_burst_count;
	s32 m_fire_delay;
	s32 m_selected_item;
	s32 m_last_selected;
	s32 m_num_items;
	
	CZSealBody* m_body;
	
	std::vector<u8> m_items_avail;

	zdb::CNode* m_detonator_model;
	zdb::CNode* m_flashlight_model;
	zdb::CTexture* m_detonator_icon;

	f32 m_retsize;
	f32 m_prev_retsize;
	f32 m_prev_factor;
	f32 m_prev_axis_a;
	f32 m_prev_axis_b;
	f32 m_retblockedsize;
	f32 m_retblockedX;
	f32 m_retblockedY;
	f32 m_retsizegoal;
	f32 m_retmax;
	f32 m_retmin;

	s32 m_tracercount;
	f32 m_firetime;
	
	// zdb::CLightMap* m_lightMap; // TODO: Create the CLightMap class
	CSnd* m_rldsnd;
	CSnd* m_clicksnd;
	CSnd* m_lasersnd_start;
	CSnd* m_lasersnd_fin;

	f32 m_pickupRequestWait;
};

class CSealStats
{
public:
	s32 m_headshots;
	s32 m_headhits;
	s32 m_hits;
	s32 m_shots;
	s32 m_kills;
	s32 m_washit;
	s32 m_deaths;
	s32 m_hostages;
	s32 m_bases_blown;
	s32 m_hostages_rescued;
	f32 m_hit_percent;
	s32 m_num_times_seen;
	s32 m_num_stealthkills;
	s32 m_num_restrained;
	s32 m_num_grenades_used;
	s32 m_num_cqb_used;
	s32 m_primary_rounds_fired;
	s32 m_secondary_rounds_fired;
	s16 m_sMvpScore;
	s32 m_iRoundsWon;
	s32 m_iRoundsTied;
};

class CSealEx : public zdb::CNodeEx
{
public:
	void OnWeaponHit(CNode* node, zdb::IntersectStruct* intersection, CZProjectile* projectile);

	CZSealBody* m_seal;
};

class CZSealBody : public CEntity, public CBody
{
	// Tomb Of The Unknown Functions
	friend class CCharacterGear;
public:
	/// -------------------------------------------
	/// CREATION/DELETION
	/// -------------------------------------------

	CZSealBody(zdb::CNode* node, CCharacterType* chartype);

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

	void PreTick(f32 delta);
	void PostPreTick(f32 delta);
	void Tick(f32 delta);
	void PrePostTick(f32 delta);
	void PostTick(f32 delta);
	void PostMortemPreTick(f32 delta);

	void OnMissionStart() {}
	void OnMissionEnd() {}
	void OnWeaponHit(zdb::IntersectStruct* intersection, CZProjectile* projectile);
	void OnDeath();
	void OnRecycleEntity() {}

	/// -------------------------------------------
	/// HEALTH
	/// -------------------------------------------

	f32 SetHealth(f32 health);
	void SetArmor(f32 armor, DAMAGE_LOCATION location);

	int GetHeadDamage(f32 headDmgOld, f32 headDmgNew);
	int GetBodyDamage(f32 bodyDmgOld, f32 bodyDmgNew);
	int GetArmDamage(f32 armDmgOld, f32 armDmgNew);
	int GetLegDamage(f32 legDmgOld, f32 legDmgNew);

	bool DamageHead(f32 damage, f32 damageMax);
	bool DamageBody(f32 damage, f32 damageMax);
	bool DamageLArm(f32 damage, f32 damageMax);
	bool DamageRArm(f32 damage, f32 damageMax);
	bool DamageLLeg(f32 damage, f32 damageMax);
	bool DamageRLeg(f32 damage, f32 damageMax);

	bool DamageHead(CZProjectile* projectile);
	bool DamageBody(CZProjectile* projectile);
	bool DamageLArm(CZProjectile* projectile);
	bool DamageRArm(CZProjectile* projectile);
	bool DamageLLeg(CZProjectile* projectile);
	bool DamageRLeg(CZProjectile* projectile);

	void AdrenalineIncr(f32 increase);

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
	bool CanPickupNetItem(u16 hostIdx, u16 pickupIdx, u16* idxPtr, u8 type) const;
	bool CanPitch() const;
	bool CanProneAim() const;
	bool CanTraverse(zdb::CDI::CDIType type) const;
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

	void HandleBloodDrip(f32 delta);
	void HandleBombDefuse() {}
	void HandleDamage(CZProjectile* projectile);
	void HandleDamageExplosive(CZBodyPart* part, DAMAGE_LOCATION location);
	void HandleDamageNonExplosive(CZBodyPart* part, DAMAGE_LOCATION location);
	s32 HandleFallingDamage(f32 impactForce); // TODO: Figure out what this function returns
	void HandleFootfallSound(CPnt3D* position);
	void HandleGrenadeExplosion();
	void HandleKiller(s32 killerIndex);
	void HandleLanding(f32 impactForce);
	void HandlePickupAck(s32 param_1, u16 pickupIdx, void* pickupAck); // TODO: Figure out wtf the AckUnion type is
	void HandlePickupAmmoInstance(void* pickup); // TODO: Create the CPickup type
	void HandlePickupEquip(void* pickup); // TODO: Create the CPickup type
	void HandlePickupMPBomb(void* pickup); // TODO: Create the CPickup type
	void HandleSealStep();
	void HandleSliding(f32 delta);
	void HandleSmokeAndGas(zdb::IntersectStruct* intersection, const void* material, const CPnt3D* position); // TODO: Create the CMaterialEx type
	void HandleStunDamage(u8 stunType, f32 damage, const CPnt3D* position); // TODO: Create the STUN_TYPE enum
	void HandleStunFromHit(EQUIP_ITEM itemType, const CPnt3D* position);
	void HandleStunRecovery(u8 stunType); // TODO: Create the STUN_TYPE enum
	void HandleWater(zdb::IntersectStruct* intersection, const void* material, const CPnt3D* position); // TODO: Create the CMaterialEx type
	void HandleWeaponEvent(CZProjectile* projectile, u32 eventIdx, void* eventData);
	bool HandleWeaponIntersect();
	void HandleWeaponInterp();

	void TeleportTo(const CMatrix& mat) {}

	void AttemptBombDefuse() const;

	CCharacterType* GetCharacter() const;

	f32 GetFormationHeading(f32 heading) const;
	void UpdateFollowParams(f32 heading);
	void HandleKiller(const CZSealBody& killer);

	CZBodyPart* GetRootPart() const;
public:
	static CSealAnim* m_sealanim;
	static CRdrFile* m_motionRdrFile;
private:
	s32 m_MaxFollowerDistance;
	s32 m_MaxFollowerDistanceNext;

	ZOOMSTATE m_zoomstate;
	ZOOMSTATE m_zoomstate_prev;
	bool m_zoomstate_echo;

	f32 m_zoomrange;

	s32 m_onMaterial;

	bool m_didrstep;
	bool m_didlstep;

	f32 m_blooddriptimer;

	CZSealBody* m_cachedReticuleSeal;
	u32 m_useCachedReticuleSeal : 1;
	u32 m_unused : 31;

	bool m_TriggerCount;
	s32 m_RemoteRoundCount;
	f32 m_RemoteFireElevation;

	// Throttle
	f32 pre_thr_l;
	f32 pre_thr_fb;
	f32 pre_thr_strafe;

	f32 m_prev_thr_x;
	f32 m_prev_thr_z;

	CPnt3D p0_pos0_w;
	CPnt3D p0_pos1_w;
	f32 p0_d;
	bool p0_run;

	zdb::DiIntersect pa_di;
	zdb::DiIntersect pi_diIntersect[1];
	CPnt3D pi_diTail;
	s32 pi_diIntersectHandle[1];
	s32 pa_diIntersectHandle;
	
	std::vector<zdb::IntersectStruct*> m_volumetricAltitudes;

	CZBodyPart* m_root;
	CZBodyPart* m_lfoot;
	CZBodyPart* m_rfoot;
	CZBodyPart* m_lhand;
	CZBodyPart* m_spinelo;
	CZBodyPart* m_rhand;
	CZBodyPart* m_hips;
	CZBodyPart* m_head;
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

	f32 m_recoilParam;

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
	s32 m_formation_clock;

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

	u32 m_action_available_mask;
	u32 m_action_selection_mask;
	bool m_action_display_on;
	u32 m_action_command;

	f32 m_wep_upT;
	f32 m_wep_waitT;
	f32 m_wep_downT;
	f32 m_wep_sumT;

	s32 chordStart;
	s32 numChords;

	u32 m_QueryCharacterAltitude : 1;
	u8 m_threatdir[4];
	f32 m_threatscale[8];
	f32 m_threatangle[8];

	bool m_doCZSealBodyPostTick;

	CPnt3D dpos;
	f32 m_my;
	CPnt3D next_posw;

	bool m_anim_handled;
	u32 m_weapon_state;

	SEAL_ITEM m_item;

	CZProjectile* m_detonation_countdown;

	std::vector<CPnt3D*> m_refpoints;

	f32 m_mass;
	f32 m_waterdepth;
	CPnt3D m_footL;
	f32 m_twist_back;
	CPnt3D m_footR;
	f32 m_local_drot;
	f32 m_dT;
	f32 m_alt;
	f32 m_skel_y_w;

	f32 m_health;
	SEAL_DEATH_TYPE m_deathType;
	f32 m_time_of_death;
	s32 m_killer_index;
	s32 m_killer_weapon_index;
	s32 m_lastkiller_id;

	s32 m_ClientIndex;
	s32 m_vote_tally;
	bool m_new_stats;
	bool m_voted_against;
	bool m_local_voted_against;
	bool m_advance_camera;
	bool m_retreat_camera;
	bool m_needs_respawn;
	bool m_stunned;
	bool m_left_game;

	u32 m_full_update_time;

	f32 m_movespeedmod;
	f32 m_encumbmod;
	f32 m_damagemod;
	f32 m_retmods;
	f32 m_stunval[7];

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
	f32 m_armor[6];

	bool m_neworder;

	CZProjectile* m_lastprojectile;
	CZProjectile* m_tempprojectile;
	s32 m_projectileinserecthandle;
	zdb::DiIntersect m_projectiledi;
	u32 m_lastregion;

	u32 m_HudUpdateViewCone : 1;
	u32 m_hudwashit : 1;
	u32 m_aim_point_valid : 1;
	u32 m_invincible : 1;
	u32 m_invisible : 1;
	u32 m_infiniteammo : 1;
	u32 m_doPostTick : 1;
	u32 m_restrainable : 1;
	u32 m_restrained : 1;
	u32 m_order_flag : 1;
	u32 m_limp : 1;
	u32 m_isinsmoke : 1;
	u32 m_isingas : 1;
	u32 m_respawning : 1;
	u32 m_joined_unit : 1;
	u32 m_send_detail : 1;
	u32 m_snake_path : 1;
	u32 m_action_climb : 1;
	u32 m_action_jump : 1;
	u32 m_is_moving : 1;
	u32 m_is_turning : 1;
	u32 m_airborne : 1;
	u32 m_jumped : 1;
	u32 m_inwater : 1;
	u32 m_stancechanged : 1;
	u32 m_have_aim_norm : 1;
	u32 m_was_turning : 1;
	u32 m_aimpt_attainable : 1;
	u32 m_firept_attainable : 1;
	u32 m_used_vel_y : 1;
	u32 m_echo_pickup : 1;
	u32 m_animate_me : 1;
	u32 m_do_drop_weapons : 1;
	u32 m_fix_skel_y : 1;
	u32 m_inside : 1;
	u32 m_prev_have_aim_norm : 1;
	u32 m_am_stunned : 1;
	u32 m_iszooming : 1;
	u32 m_unused_bits : 26;

	CQuat m_fwdlook;
	f32 m_zoomval;
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

	s16 m_throttleQuadrant;
	s16 m_prev_throttleQuadrant;
	f32 m_descent;
	f32 m_slide_descent;
	CPnt3D m_ground_normal;
	CPnt3D m_inAirHorizVel;
	f32 m_nextJumpTimer;
	f32 m_jumpTimer;
	f32 m_jumpImpulse;

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
	s16 m_last_foot;
	s16 m_fixed_foot;

	f32 m_TimeSpentDead;
	s32 m_NumDeathAnimsPlayed;
};

class CSealUnit
{
public:
	static bool TickAll(f32 dT, void* buf);
};

class CSealCtrl : CEntityCtrl
{
	friend class CAppCamera;
public:
	CSealCtrl() : CEntityCtrl() {}
	~CSealCtrl();

	virtual bool AllowCommand(CZSealBody* seal, FT_COMMAND command, void* buffer);
	virtual bool CanDefuseBomb(CNodeAction* action) const;
	virtual bool CanPlaceBomb(CNodeAction* action) const;
	virtual bool CanPerformAction(CNodeAction* action) const;
	virtual void ClearGoal(GOAL_TYPE type);
	virtual void ClearLook(AI_LOOK look);
	virtual bool ComputeTurnThrottle(const CPnt3D& velWorld, const CPnt3D& velLocal, f32& throttle);
	// virtual float ComputeVisibility(zdb::DiIntersection* intersection, CTarget* target);

	virtual bool IsAi() const;
	virtual bool IsPlayer() const;
	virtual bool IsRemote() const;

	bool CreateAiEvent(CAiEvent::EVENT event, f32 expiration, f32 radius, bool flag, CPnt3D* position, s32 dummy);
public:
	u32 m_padid;
private:
	f32 m_look_timer;
	Rfloat m_look_rate;
	AI_LOOK m_look_mode;
	LOOK_DATA_TYPE m_look_type;
	CPnt3D m_look_data;
	CPnt3D m_look_data_mdir;
	CPnt3D m_look_bias;
	u32 m_look_flags;

	Rfloat m_scan_angle;
	CAiTimer m_scan_timer;
	f32 m_scan_limits;

	f32 m_fov;
	f32 m_fovtan;
	f32 m_fovcos;

	CAiCone m_view_cone;
	CAiDecay m_visrange;
	CAiDecay m_aware;

	u32 m_targetSum;
	CAiDecay m_targetThreat;
	CSealUnit m_unit;

	u32 m_ai_net_state;
	TRIGGER m_trigger;
	f32 m_trigger_power;
	s32 m_throwwait;
	f32 m_buttonreading[10];
	s32 m_firstreading;
	s32 m_lastreading;

	f32 m_zoomlevel;
	f32 m_zoomincrement;
	f32 m_aimPitch;
	f32 m_aimYaw;
	f32 m_highrumbletime;
	f32 m_rumbletime;
	f32 m_rumblestr;

	s32 m_HudDoPickup;
	s32 m_curpickup_ID;
	s32 m_curpickup_secondary_ID;

	zdb::CNode* m_bomb_defusal_node;
	zdb::CNode* m_mpbomb_node;
	f32 m_mpbomb_timer;

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

	u32 m_unused : 16;

	CPnt3D m_goal_dir;
	CPnt3D m_goal_pos;
	CPnt3D m_fudge_velR;
	CPnt3D m_fudge_velM;
	CPnt3D m_fudge_velW;

	GOAL_TYPE m_goal_type;
	f32 m_goal_pos_tolerance;
	CAiTimer m_goal_timer;

	f32 m_speed;

	f32 m_event_time[15];
	CPnt3D m_remote_goal_pos;
	CQuat m_remote_goal_quat;

	PLAYER_CAM_STATE m_camState;
	MENU_STATE m_menustate;

	f32 m_hotswapL1;
	f32 m_hotswapL2;

	CAiTimer m_wep_state;

	f32 m_bombpickuptimer;
	f32 m_weapon_pickup_timer;
};

class CSealCtrlAi : CSealCtrl
{
public:
	static bool RegisterCommands();
};

class CSealCtrlSquirm : CSealCtrl
{

};

class CTAction
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTComm
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTDebug
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTDoor
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTEvent
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTFireMode
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTFireWeapon
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTGoto
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTHold
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTInState
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTInView
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTLookAt
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTMacro
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTMap
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTMove
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTPaint
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTParam
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTPlay
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void Create(int count, unsigned int*, f32, f32);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTPursue
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTRange
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTRegion
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTSelect
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTSetAnimSet
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTSetMode
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTSignal
{
public:
	static AiSig GetSignalByName(const char* signal);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTSound
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTSpecial
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTStance
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static void End(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTState
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTStopAll
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTTeam
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTValve
{
public:
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};

class CTWait
{
public:
	static void Begin(_zanim_cmd_hdr* header);
	static _zanim_cmd_hdr* Parse(_zrdr* reader);
	static bool Tick(_zanim_cmd_hdr* header, f32* delta);
};