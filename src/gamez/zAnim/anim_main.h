#pragma once
#include "gamez/zEntity/body.h"
#include "gamez/zNode/node_main.h"
#include "gamez/zMath/zmath_main.h"
#include "gamez/zReader/zrdr_main.h"

class CZAnimMain;

static CZAnimMain ZAnim;

static int InitAnimLang();
static int ParseScriptKeywords();
static int ParseAIKeywords();
static int ParseResetBodyKeyword();
static int ParseValveKeywords();
static int ParseCameraKeywords();
static int ParseThirdPersonCamKeyword();
static int ParsePlayerConditionKeywords();
static int ParseWindKeyword();
static int ParseExecuteActionKeyword();
static int ParseDecalRemovalKeyword();
static void ParseScriptKeyword(void* ptr, char* token, int param_3, void(*func), bool(*condition), int param_6);

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

};

struct zanim_cmd_val
{

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

struct _zanim_cmd_params
{
	int m_name_index;
	int m_root_node_index;
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

class CZAnimEx : public CZAnim
{
	void AddAnimEx();
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

typedef _zanim_cmd_hdr* (*rdr_delegate)  (_zrdr*);
typedef void            (*begin_delegate)(_zanim_cmd_hdr*);
typedef bool            (*tick_delegate) (_zanim_cmd_hdr*, float*);
typedef void            (*end_delegate)  (_zanim_cmd_hdr*);

class CZAnimMain
{
public:
	bool InitCommands();
	void AddCmd(const char* name, 
		        rdr_delegate   rdr_delegate, 
		        begin_delegate begin_delegate, 
		        tick_delegate  tick_delegate, 
		        end_delegate   end_delegate);
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