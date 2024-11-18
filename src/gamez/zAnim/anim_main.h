#pragma once
#include "gamez/zEntity/body.h"
#include "gamez/zNode/node_main.h"
#include "gamez/zMath/zmath_main.h"
#include "gamez/zReader/zrdr_main.h"
#include "gamez/zValve/valve_main.h"
#include "gamez/zSound/zsnd_csnd.h"

class CZAnimMain;

static CZAnimMain ZAnim;

static bool CmdAddNode(zdb::CNode node);
static bool CmdRemoveNode(zdb::CNode node);

enum AnimTypes
{

};

struct REFPT_INFO
{
	CPnt3D m_goal_pos;
	bool m_valid;
	CPnt3D m_goal_norm;
};

struct ANIM_CALLBACK
{
	float m_tfrac;
	void(*m_func)();
	void(*m_userdata)();
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

struct zanim_cmd_val
{
	zanim_cmd_index index;
	unsigned short val;
};

struct zanim_cmd_index
{
	unsigned char cmd;
	unsigned char set;
};

struct _zanim_cmd_hdr
{
	unsigned int data_type;
	bool quad_align;
	bool timeless;
	size_t data_size;
};

struct _zanim_cmd_set
{
	const char* name;
	int count;
	zanim_cmd* cmd_list;
};

struct _zanim_main_params
{
	int m_version;
	float m_gravity;
	bool m_search_external_nodes;
	unsigned int m_unused : 31;
	int m_UserActionAnimIndex;
};

struct _zanim_anim_params
{
	unsigned char m_name_index;
	unsigned char m_root_node_index;

	bool m_paused;
	char m_state;
	char m_activation;
	bool m_network_anim;
	char node_search_scope;

	bool m_auto_copy_anim;
	bool m_auto_add_to_world;
	bool m_create_instance;
	bool m_copy_instance;
	bool m_clone_anim;
	bool m_create_root;

	int m_max_anim_copies;
	int m_unused;

	float m_timer;
	float m_priority;

	int m_damage_seq_offset;
	int m_activation_seq_offset;
	int m_execution_seq_offset;
	int m_cleanup_seq_offset;
};

struct _zanim_si_script
{
	unsigned short script_pathname_index;
	unsigned short script_object_name_index;
	bool spline_interp;
	int total_frame_count;
	int script_data_size;
	char* script_data;
};

struct _zanim_call_anim_ref
{
	unsigned char name_index;
	unsigned char local_name_index;

	bool stop_on_exit;

	CZAnim* base_anim;
	CZAnim* executing_anim;
};

struct _zanim_node_ref
{
	unsigned int parent_index : 8;
	unsigned int name_index : 11;
	unsigned int node_search : 3;

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
	int name_index;
	CValve* valve;
};

struct _zanim_sound
{
	short name_index;
	bool stop_on_exit;
	CSnd* sound_handle;
	CSndInstance* sound_instance;
};

struct _zsequence
{
	int name_index;
	int loop_counter;
	bool paused;
	
	char activation;
	char state;
	char cmd_state;

	int m_IF_NestLevel;

	char* cmd_pc;
	int seq_data_size;

	float seq_timer;
	float cmd_timer;
	float loop_timer;
};

struct ZAnimNetworkPacket
{
	int packet_size;
	unsigned short anim_set_index;
	unsigned short anim_index;
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

	float m_shield;
	float m_armor;
	float m_armor_max;
	float m_health;
	float m_health_max;
};

class CZAnimSet
{
public:
	void GetName();
};

class CZAnimNameTable
{
public:

};

class CZAnimNameIndexTable
{
public:
	void GetName();
};

class CZAnimMain
{
public:
	bool InitCommands();
	void AddCmd(zanim_cmd cmd);
private:
	bool m_IsOpen;
	bool m_IsStarted;
	CZAnimNameTable m_name_table;
	CZAnimSet* m_animset_list;
	int m_animset_count;
	int m_cmdset_count;
	int m_cmdset_index;
	int m_cmdset_index;
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
	float m_exp[41];
	float m_inv_exp[41];
	ZAnimNetworkPacket m_NetworkPacket;
	int m_NetworkPacketMaxSize;
	int m_RunningAnimCount;
	int m_CurrentFrame;
};

static CZAnimMain ZAnim;

class CZBodyAnimBlend
{
public:
	void SetFractionalTime(float time);
private:
	CPnt3D m_dpos;
	float m_quitT;
	CPnt3D m_drot;
	float m_tfrac;
	REFPT_INFO* m_refpt_info;
	CZBodyPart* m_action_node;
	CZBodyPart* m_result_parent;
	char m_flags;
	char m_ctrl;
	char m_state;
	AnimTypes m_animType;
	CActiveAnimList* m_anims;
	ANIM_CALLBACK m_callback;
	// CHoming m_homing;
};

class CSealAnim
{
public:
	CSealAnim();
	~CSealAnim();
};