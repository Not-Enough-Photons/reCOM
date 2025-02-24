#pragma once
#include "gamez/zAnim/zanim.h"
#include "gamez/zNode/znode.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zRender/zrender.h"

struct cam_wiggle;
struct throw_params;

class CEntity;
class CEntityCtrl;
class CCharacterType;
class CTarget;
class CharacterDynamics;
class CZSealBody;
class CZBodyPart;
class CModel;
class CCameraParams;

class CTargetList : public std::vector<CTarget*> {};

struct HEALTH_PARAMS;

enum class DAMAGE_LOCATION
{
	HEAD,
	BODY,
	LARM,
	RARM,
	LLEG,
	RLEG
};

enum class SEAL_CONTROL_TYPE
{
	CTRL_NONE,
	CTRL_PLAYER,
	CTRL_AI,
	CTRL_SQUIRM,
	CTRL_MISC
};

extern CEntity* recycler;
extern u32 recycler_index;
extern CSealAnim* m_sealanim;
extern CharacterDynamics theCharacterDynamics;

struct start
{
	char m_name[16];
	s32 m_dir;
};

struct startvec
{
	u32 m_count;
	start m_start[4];
};

class CEntity
{
public:
	enum TYPE
	{
		ENT_TYPE_UNKNOWN,
		ENT_TYPE_RECYCLE,
		ENT_TYPE_SEAL,
		ENT_TYPE_TURRET
	};

	CEntity(TYPE type, zdb::CNode* node);

	static bool EntityIsValid(CEntity* entity);
	static std::vector<CEntity*>& GetEntityList();
	static void OpenRecycler(u32 index);
	static CEntity* CreateRecycler();
	
	void IncrementAwareCounter();
	void DecrementAwareCounter();

	// Recycler functions
	virtual void OnRecycleEntity() {}
	void OpenRecycler() {}

	// Mission callback functions
	virtual void OnMissionStart() {}
	virtual void OnMissionEnd() {}
	virtual void OnDeath();

	// Tick virtual functions
	virtual void PreTick() {};
	virtual void PostPreTick() {};
	virtual void PrePostTick() {};
	virtual void Tick() {};
	virtual void PostTick() {};

	void JoinTeam(u32 team);
	
	void SetDisplayName(const char* name);

	virtual void TeleportTo(const CMatrix& mat) {}

	u32 GetEntityIndex() const;
	zdb::CNode* GetNode() const;
	bool IsAlive() const;
	bool IsValid() const;

	void SetController(CEntityCtrl* controller);

	static std::vector<CEntity*> m_list;
	
	u32 m_id;
	u32 m_index;
	u32 m_vehicle_index;

	TYPE m_type;

	char* m_display_name;
	u32 m_UnitsSeenBy;

	zdb::CNode* m_node;

	CPnt3D m_velM; // Model-relative velocity
	CPnt3D m_velW; // World-relative velocity
	CPnt3D m_velR; // Angular-relative velocity?
	CQuat m_quat; // Rotation
	CPnt3D m_next_velw; // Model-relative wish velocity
	CQuat m_next_quat; // Next wish rotation
	CMatrix m_next_matrix; // Next wish transformation
	
	CEntityCtrl* m_control;
	
	u32 m_team;
	
	f32 m_max_range_target_sq;
	
	CTargetList m_targets;
	
	u32 m_aware_counter;

	u32 m_blink_eyes : 1;
	u32 m_drip_blood : 1;
	u32 m_animate_footsteps : 1;
	u32 m_interpolate_animations : 1;
	u32 m_lean_into_turns : 1;
	u32 m_do_weapon_recoil : 1;
	u32 m_check_player_collision : 1;
	u32 m_get_new_altitude : 1;
	u32 m_noshoot : 1;
	u32 m_update_targetlist : 1;
	u32 m_include_in_targetlist : 1;
	u32 m_isAlive : 1;

	// CAiMapLoc m_mapLoc;
	// CAiMapLoc m_mapLocValid;
};

class CEntityCtrl
{
public:
	CEntityCtrl();
	~CEntityCtrl();

	virtual void PreTick(f32 delta);
	virtual void Tick(f32 delta);
	virtual void PostMortemPreTick(f32 delta);

	virtual void SetThrottle(f32 throttle, s32 pad);
	virtual void GetRemoteControl() const;

	virtual void OnDeath();

	CEntity* m_entity;
	f32 m_throttle[3];
};

class CftsPlayer : public CEntity
{
public:
	static void RegisterAnimCommands();

	u32 m_is_player_node : 1;
	u32 m_inside : 1;
	u32 m_unused : 30;
};

class CTarget
{
public:
	CEntity* m_ent;
	CPnt3D m_vec;

	f32 m_distSq;
	f32 m_dist;
	f32 m_visibility;
	f32 m_aware;
	s32 m_diHandle;

	u32 m_d_computed : 1;
	u32 m_known : 1;
	u32 m_visible : 1;
	u32 m_hostile : 1;
	u32 m_targeted : 1;
	u32 m_dirty_di : 1;
	u32 m_unused : 26;
};

class CPickup
{
public:
	void Destroy();
private:
	zdb::CNode* m_node;
	void* m_data;
	u8 m_type;
	bool m_locked;
	bool m_secondary;
	u8 m_unused;
	s16 m_id;
	s16 m_netid;
	bool m_visible_by_units;
};