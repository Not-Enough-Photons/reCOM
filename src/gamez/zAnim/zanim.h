#pragma once
#include <string>

// #include "gamez/zEntity/body.h"
#include "gamez/zNode/znode.h"
#include "gamez/zMath/zmath.h"
#include "gamez/zReader/zrdr.h"
#include "gamez/zValve/zvalve.h"
#include "gamez/zSound/zsnd.h"

class CZAnim;
class CZAnimMain;
class CBlendable;
class CAnimsByFP;

namespace zar
{
	class CZAR;
}

extern CZAnimMain ZAnim;

static bool CmdAddNode(zdb::CNode node);
static bool CmdRemoveNode(zdb::CNode node);

enum class AnimType
{
	animTypeUndefined,
	animTypeRef,
	animTypeStand,
	animTypeSneak,
	animTypeSkitter,
	animTypeRun,
	animTypeSneakBack,
	animTypeSkitterBack,
	animTypeDie,
	animTypeJumpLaunch,
	animTypeJumpFall,
	animTypeJumpLand,
	animTypeJumpLandHard,
	animTypeStrafeRight,
	animTypeStrafeLeft,
	animTypeStrafeRightFast,
	animTypeStrafeLeftFast,
	animTypeStep,
	animTypeStand2Crouch,
	animTypeCrouch,
	animTypeCrouch2Prone,
	animTypeCrouchWalk,
	animTypeCrouchStep,
	animTypeCrouchStrafeR,
	animTypeCrouchStrafeRFast,
	animTypeCrouchWalkBack,
	animTypeStand2Prone,
	animTypeProne,
	animTypeProneCrawl,
	animTypeProneTurn,
	animTypePeekL,
	animTypePeekR,
	animTypeCrouchPeekL,
	animTypeCrouchPeekR,
	animTypeStand2PeekU,
	animtypeCrouch2PeekU,
	animTypeStand2Hang,
	animTypeHang,
	animTypeHang2Climb,
	animTypeHandJumpDown,
	animTypeLedge2HangBw,
	animTypeHopdownBw,
	animTypeFalling,
	animTypeLandSoft,
	animTypeLandHanging,
	animTypeClimbCrate,
	animTypeHopdownForward,
	animTypeStand2Ladder,
	animTypeClimbLadder,
	animTypeClimbOffLadder,
	animTypeFallForward01,
	animTypeGetupForward,
	animTypeThrowGrenade,
	animTypeUnderhandToss,
	animTypeFlinchRArm,
	animTypeFlinchRLeg,
	animTypeRLimp,
	animTypeRifle2Pistol,
	animTypeCrouchRifle2Pistol,
	animTypeProneRifle2Pistol,
	animTypeStand2Binocular,
	animTypeCrouch2Binocular,
	animTypeProne2Binocular,
	animTypeRestraintsApply,
	animTypeRestraintsReceive,
	animTypePutOnGround,
	animTypePutOnWall,
	animTypeOpenDoor,
	animTypeGetFromGround,
	animTypeGetFromSurface,
	animTypeRunR,
	animTypeRunL,
	animType_OnWall,
	animType_OnWallSmoke,
	animType_Stand2OnWall,
	animType_StandStretch,
	animType_Slouch,
	animType_SlouchSmoke,
	animTypeStab,
	animTypeStab_P,
	animTypeStabbed,
	animTypeCQB,
	animTypeCQB_P,
	animTypeCQBVictimFallBackwards,
	animTypeCQBVictimFallForwards,
	animTypeHeadLooks,
	animTypeHeadLooksProne,
	animTypeStand_P,
	animTypeCrouch_P,
	animTypeProne_P,
	animTypeHang_P,
	animTypeClimbLadder_P,
	animTypeSneak_P,
	animTypeSkitter_P,
	animTypeRun_P,
	animTypeSneakBack_P,
	animTypeSkitterBack_P,
	animTypeDie_P,
	animTypeStrafeRight_P,
	animTypeStrafeLeft_P,
	animTypeStrafeRightFast_P,
	animTypeStrafeLeftFast_P,
	animTypeStep_P,
	animTypeStand2Crouch_P,
	animTypeCrouch2Prone_P,
	animTypeCrouchWalk_P,
	animTypeCrouchStep_P,
	animTypeCrouchStrafeR_P,
	animTypeCrouchWalkBack_P,
	animTypeProneCrawl_P,
	animTypePeekL_P,
	animTypePeekR_P,
	animTypeCrouchPeekL_P,
	animTypeCrouchPeekR_P,
	animTypeStand2PeekU_P,
	animTypeCrouch2PeekU_P,
	animTypeStand2Hang_P,
	animTypeHang2Climb_P,
	animTypeHangJumpDown_P,
	animTypeLedge2HangBw_P,
	animTypeHopdownBw_P,
	animTypeFalling_P,
	animTypeLandSoft_P,
	animTypeLandHanging_P,
	animTypeClimbCrate_P,
	animTypeHopdownForward_P,
	animTypeStand2Ladder_P,
	animTypeClimbOffLadder_P,
	animTypeFallForward01_P,
	animTypeGetupForward01_P,
	animTypeRLimp_P,
	animTypeThrowGrenade_P,
	animTypeUnderhandToss_P,
	animTypeStand2Binocular_P,
	animTypeCrouch2Binocular_P,
	animTypeProne2Binocular_P,
	animTypeRestraintsApply_P,
	animTypePutOnGround_P,
	animTypePutOnWall_P,
	animTypeOpenDoor_P,
	animTypeGetFromGround_P,
	animTypeGetFromSurface_P,
	animTypeRunR_P,
	animTypeRunL_P
};

struct REFPT_INFO
{
	CPnt3D m_goal_pos;
	bool m_valid;
	CPnt3D m_goal_norm;
};

struct ANIM_CALLBACK
{
	f32 m_tfrac;
	void(*m_func)();
	void(*m_userdata)();
};

struct ANIMSET_PARAMS
{
	f32 m_stand_max_fwd;
	f32 m_stand_max_back;
	f32 m_stand_max_rt;
	f32 m_stand_max_left;

	f32 m_crouch_max_fwd;
	f32 m_crouch_max_back;
	f32 m_crouch_max_rt;
	f32 m_crouch_max_left;

	f32 m_prone_max_fwd;
	f32 m_prone_max_back;
	f32 m_prone_max_rt;
	f32 m_prone_max_left;

	f32 m_ladder_updn;
};

struct ANIMTYPE_GROUP
{
	AnimType m_rifle_type;
	AnimType m_pistol_type;
	AnimType m_rifle_fp_type;
	AnimType m_pistol_fp_type;
};

struct BLENDABLE_ANIM
{
	f32 m_trans0;
	f32 m_trans1;
	AnimType m_animtype;
};


struct zanim_cmd_index
{
	u8 cmd;
	u8 set;
};

struct zanim_cmd_val
{
	zanim_cmd_index index;
	u16 val;
};

struct zanim_cmd
{
	const char* name;
	zanim_cmd_val cmd_val;
	void*(*parser)();
	void*(*begin)();
	void*(*tick)();
	void*(*end)();
};

struct _zanim_cmd_hdr
{
	u32 data_type : 16;
	u32 quad_align : 1;
	u32 timeless : 1;
	u32 data_size : 14;
};

struct _zanim_cmd_set
{
	char* name;
	s32 count;
	zanim_cmd* cmd_list;
};

struct _zanim_main_params
{
	s32 m_version;
	f32 m_gravity;
	u32 m_search_external_nodes : 1;
	u32 m_unused : 31;
	s32 m_UserActionAnimIndex;
};

struct _zanim_anim_params
{
	u8 m_name_index;
	u8 m_root_node_index;

	bool m_paused;
	s8 m_state;
	s8 m_activation;
	bool m_network_anim;
	s8 node_search_scope;

	bool m_auto_copy_anim;
	bool m_auto_add_to_world;
	bool m_create_instance;
	bool m_copy_instance;
	bool m_clone_anim;
	bool m_create_root;

	s32 m_max_anim_copies;
	s32 m_unused;

	f32 m_timer;
	f32 m_priority;

	s32 m_damage_seq_offset;
	s32 m_activation_seq_offset;
	s32 m_execution_seq_offset;
	s32 m_cleanup_seq_offset;
};

struct _zanim_si_script
{
	u16 script_pathname_index;
	u16 script_object_name_index;
	bool spline_interp;
	s32 total_frame_count;
	s32 script_data_size;
	char* script_data;
};

struct _zanim_call_anim_ref
{
	u8 name_index;
	u8 local_name_index;

	bool stop_on_exit;

	CZAnim* base_anim;
	CZAnim* executing_anim;
};

struct _zanim_node_ref
{
	u32 parent_index : 8;
	u32 name_index : 11;
	u32 node_search : 3;

	bool is_light;
	bool created_here;
	bool stop_on_exit;
	bool on_world_lightlist;
	bool save_translation;
	bool save_rotation;
	bool save_active;
	bool save_parent;
	bool is_local_light;
	bool set_inactive;

	zdb::CNode* node_ptr;
};

struct _zanim_valve_ref
{
	s32 name_index;
	CValve* valve;
};

struct _zanim_sound
{
	s16 name_index;
	bool stop_on_exit;
	CSnd* sound_handle;
	CSndInstance* sound_instance;
};

struct _zsequence
{
	s32 name_index;
	s32 loop_counter;
	bool paused;
	
	s8 activation;
	s8 state;
	s8 cmd_state;

	s32 m_IF_NestLevel;

	s8* cmd_pc;
	s32 seq_data_size;

	f32 seq_timer;
	f32 cmd_timer;
	f32 loop_timer;
};

struct ZAnimNetworkPacket
{
	s32 packet_size;
	u16 anim_set_index;
	u16 anim_index;
};

struct AnimSet
{
	ANIMSET_PARAMS m_aparams;

	bool m_ready;
	std::string m_name;

	std::vector<u32> m_animIDs;
	std::vector<AnimType> m_basetypes;
	std::vector<CZAnim> m_included;

	CAnimsByFP* m_animgps;

	CBlendable* m_move_anims;
	CBlendable* m_moveback_anims;
	CBlendable* m_strafeL_anims;
	CBlendable* m_strafeR_anims;
	CBlendable* m_crouchmove_anims;
	CBlendable* m_crouchmoveback_anims;
	CBlendable* m_crouchstrafeL_anims;
	CBlendable* m_crouchstrafeR_anims;
};

struct SequenceData
{
	f32 m_fraction;
	CPnt4D m_data;
};

class Sequence : std::vector<SequenceData*> {};

struct Props
{
	s32 m_refCount;

	Sequence m_textureSeq;
	Sequence m_colorSeq;
	Sequence m_scaleSeq;

	zdb::CModel* m_model;
	f32 m_friction;
	CPnt4D m_accelW;
	f32 m_windFactor;
	f32 m_priority;
	f32 m_nearFade1;
	f32 m_nearFade2;
	f32 m_farFade1;
	f32 m_farFade2;
	f32 m_invNearFade;
	f32 m_invFarFade;
	f32 m_visualDensity;
	bool m_checkFade;
};

class CAnimsByFP
{
private:
	ANIMTYPE_GROUP m_animgroups;
};

class CBlendable
{
	BLENDABLE_ANIM m_blendable[4];
};

class CActiveAnimList
{

};

class CZAnim
{
public:
	void AddNewNodeRef();
	void OnWeaponHitInit();
	void GetNode();
};

class CZAnimEx : public zdb::CNodeEx
{
public:
	void AddAnimEx();
private:
	CZAnim* m_anim;

	zdb::CNode* m_nodeEx;
	zdb::CNode* m_root_node;

	f32 m_shield;
	f32 m_armor;
	f32 m_armor_max;
	f32 m_health;
	f32 m_health_max;
};

class CZAnimSet
{
public:
	void GetName();
};

class CZAnimZAR : public zar::CZAR {};

class CZAnimNameTable
{
public:

};

class CZAnimNameIndexTable
{
public:
	void GetName();
};

class CZAnimMain : public _zanim_main_params
{
public:
	bool SplitName(const char* name, char** splitname);
	
	bool InitCommands();
	u32 AddCmd(const char* name, _zanim_cmd_hdr*(*parser)(_zrdr*), void(*begin)(_zanim_cmd_hdr*), bool(*tick)(_zanim_cmd_hdr*, f32*), void(*end)(_zanim_cmd_hdr*));
public:
	static bool m_LoadFromZAR;
private:
	bool m_IsOpen;
	bool m_IsStarted;

	CZAnimNameTable m_name_table;
	CZAnimSet* m_animset_list;

	s32 m_animset_count;
	s32 m_cmdset_count;
	s32 m_cmdset_index;
	s32 m_cmdlist_index;

	_zanim_cmd_set* m_cmdset_list;

	CZAnimSet* m_CurAnimSet;
	CZAnim* m_CurAnim;
	_zsequence* m_CurSeq;
	bool m_anim_complete;

	bool m_debug;

	CZAnim* m_UserActionAnim;

	// LOD m_Lod;
	void(*m_network_activation_callback)();
	void(*m_block_activation_callback)();

	_zanim_cmd_hdr m_cmd_if;
	_zanim_cmd_hdr m_cmd_elseif;
	_zanim_cmd_hdr m_cmd_else;
	_zanim_cmd_hdr m_cmd_endif;
	_zanim_cmd_hdr m_cmd_endwhile;
	_zanim_cmd_hdr m_cmd_ExprOperator;

	f32 m_exp[41];
	f32 m_inv_exp[41];

	ZAnimNetworkPacket m_NetworkPacket;
	s32 m_NetworkPacketMaxSize;

	s32 m_RunningAnimCount;
	s32 m_CurrentFrame;
};

class CActiveAnimPool
{

};

static CZAnimMain ZAnim;

class CZBodyAnimBlend
{
public:
	void SetFractionalTime(f32 time);
private:
	CPnt3D m_dpos;
	float m_quitT;
	CPnt3D m_drot;
	float m_tfrac;

	REFPT_INFO* m_refpt_info;

	// CZBodyPart* m_action_node;
	// CZBodyPart* m_result_parent;

	char m_flags;
	char m_ctrl;
	char m_state;

	AnimType m_animType;

	CActiveAnimList* m_anims;
	ANIM_CALLBACK m_callback;
	// CHoming m_homing;
};

class CZSIObject
{
private:
	f32* m_positionData;
	CQuat* m_rotations;
	u32 m_inUse : 1;
	u32 m_constPos : 1;
	u32 m_constRot : 1;
	u32 m_padding : 21;
	u32 m_body_part_id : 8;
	char* m_pName;
};

class CZSIScript
{
	friend class CZSIScriptCommon;
protected:
	s32 m_isLoaded : 1;
	s32 m_looped : 1;
	f32 m_tf;
	f32 m_tScale;
	f32 m_multiplier;
	CZSIScriptCommon* m_pCommon;
};

class CZSIScriptCommon
{
	friend class CZSIObject;
private:
	char* m_name;
	s16 m_nFrames;
	s16 m_nObjects;
	CZSIObject* m_pObjects;
	s16 m_refCount;
	s16 m_objects_ready;
	f32 m_distance;
	f32 m_thr_scale;
	f32 m_blendtime;
	f32 m_terrnorm0;
	f32 m_terrnorm1;
	f32 m_fire_val;
	f32 m_interrupt_val;
	std::vector<CZSIObject*> m_objects_for_body;
};

class CSealAnim
{
public:
	CSealAnim();
	~CSealAnim();
};

class CSequence
{
private:
	f32 m_upT;
	f32 m_holdT;
	f32 m_downT;
	f32 m_currT;
};