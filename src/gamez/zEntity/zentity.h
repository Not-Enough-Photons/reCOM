#pragma once
#include "gamez/zAI/zai.h"
#include "gamez/zAnim/zanim.h"
#include "gamez/zNode/znode.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zRender/zrender.h"

struct cam_wiggle;
struct throw_params;

class CEntity;
class CEntityCtrl;
class CCharacterType;
class CharacterDynamics;
class CZSealBody;
class CZBodyPart;
class CModel;
class CCameraParams;

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

extern int recycler_index;
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
public:
	void IncrementAwareCounter();
	void DecrementAwareCounter();

	// Recycler functions
	virtual void OnRecycleEntity() {}
	CEntity* CreateRecycler() { return NULL; }
	void OpenRecycler() {}

	// Mission callback functions
	virtual void OnMissionStart() {}
	virtual void OnMissionEnd() {}

	// Tick virtual functions
	virtual void PreTick() {};
	virtual void PostPreTick() {};
	virtual void PrePostTick() {};
	virtual void Tick() {};
	virtual void PostTick() {};

	void SetDisplayName(const char* displayName);

	virtual void TeleportTo(const CMatrix& mat) {}

	zdb::CNode* GetNode() const;
	bool IsValid() const;

	void SetController(CEntityCtrl* controller);
public:
	CEntityCtrl* m_control;
	
	u32 m_id;
	u32 m_index;
	u32 m_vehicle_index;

	TYPE m_type;

	const char* m_display_name;
	u32 m_UnitsSeenBy;

	zdb::CNode* m_node;

	CPnt3D m_velM; // Model-relative velocity
	CPnt3D m_velW; // World-relative velocity
	CPnt3D m_velR; // Angular-relative velocity?
	CQuat m_quat; // Rotation
	CPnt3D m_next_velw; // Model-relative wish velocity
	CQuat m_next_quat; // Next wish rotation
	CMatrix m_next_matrix; // Next wish transformation

	u32 m_aware_counter;

	bool m_blink_eyes;
	bool m_drip_blood;
	bool m_animate_footsteps;
	bool m_interpolate_animations;
	bool m_lean_into_turns;
	bool m_do_weapon_recoil;
	bool m_check_player_collision;
	bool m_get_new_altitude;
	bool m_noshoot;
	bool m_update_targetlist;
	bool m_include_in_targetlist;
	bool m_isAlive;

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
protected:
	CEntity* m_entity;
	f32 m_throttle[3];
};

class CftsPlayer : public CEntity
{
public:
	static void RegisterAnimCommands();
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