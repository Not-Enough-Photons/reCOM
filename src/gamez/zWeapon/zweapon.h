#pragma once
#include <list>

#include "gamez/zAnim/zanim.h"
#include "gamez/zEntity/zentity.h"
#include "gamez/zSystem/zsys.h"

class CZProjectile;
class CZProjectileList;
class CZWeapon;
class CZWeaponList;

namespace zwep
{
	extern u32 personMaterialId;
}

enum class ENCUMBRANCE
{
	LIGHTLY_ENCUMBERED,
	MEDIUM_ENCUMBERED,
	HEAVY_ENCUMBERED,
	VERY_HEAVILY_ENCUMBERED,
	NOT_ENCUMBERED,
	NUM_ECUMBTYPES
};

enum class EQUIP_ITEM
{
	EQUIP_NONE,
	EQUIP_PISTOL,
	GLOCK18,
	MARK23,
	MARK23SD,
	FIVE_SEVEN,
	BERETTA,
	P226,
	DESERT_EAGLE,
	HKP9S,
	CHINESE_TYPE_59,
	CROATIAN_HS95,
	DESIGNATOR,
	EQUIP_SMG,
	MP5,
	STEYR_AUG9,
	MP5SD,
	FNP90,
	STEYR_MACHINE_PISTOL,
	SKORPION,
	USI,
	EQUIP_ASSAULT_RIFLE,
	M16A2,
	M16_M203,
	HKG11,
	M4A1_CARBINE,
	AR15,
	SIG551_SWAT,
	SIG552_COMMANDO,
	AK47,
	AKS74,
	M14,
	M4A1_CARBINE_M203,
	M4A1_CARBINE_SILENCED,
	EQUIP_SHOTGUN,
	SPAS12,
	RM3_SUPER_COMBAT,
	JACKHAMMER,
	REMINGTON870,
	EQUIP_MACHINEGUN,
	M60E,
	STONER_M63A,
	MARK46MOD0,
	EQUIP_SNIPER_RIFLE,
	BARRETM82A1,
	REMMINGTON700,
	MCMILLAN,
	DRAGUNOV,
	STONER_SR25_SILENCED,
	STONER_SR25,
	EQUIP_GRENADE,
	GRENADE,
	SMOKE_GRENADE,
	FLASHBANG,
	PHOS_GRENADE,
	TEARGAS_GRENADE,
	HE_GRENADE,
	EQUIP_HEAVYWEAPON,
	M203,
	MULTI_GRENADE_LAUNCHER,
	M79,
	EQUIP_EXPLOSIVE,
	C4,
	SATCHEL_CHARGE,
	CLAYMORE,
	MPBOMB,
	F18_MISSILE,
	EXPLODING_BARREL,
	EQUIP_MELEE,
	TASER,
	EQUIP_LAUNCHED_GRENADE,
	M203_HE,
	M203_IL,
	M203_SMOKE,
	M203_GAS,
	M203_FRAG,
	GL_HE,
	GL_IL,
	GL_SMOKE,
	GL_FRAG,
	EQUIP_EQUIPMENT,
	FLASHLIGHT,
	BINOCULARS,
	RESTRAINTS,
	OLD_NVG_ID,
	OLD_DESIGNATOR,
	KNIFE,
	DETONATOR,
	DOUBLE_AMMO_LOAD,
	EQUIP_ARMOR,
	KEVLAR_ARMOR,
	KEVLAR_INSERT_ARMOR,
	EQUIP_END
};

enum class EQUIP_AMMO
{
	AMMO_NONE,
	A_9X19,
	A_22_RIFLE,
	A_45_ACP,
	A_45_CASELESS,
	A_50_AE,
	A_50_AE_AP,
	A_545X39_SOVIET,
	A_556X45,
	A_762X51,
	A_50_BROWNING,
	A_FRAG_GRENADE,
	A_SMOKE_GRENADE,
	A_TEARGAS_GRENADE,
	A_FLASHBANG,
	A_WP_GRENADE,
	A_SATCHEL_CHARGE,
	A_CLAYMORE,
	A_C4,
	A_MPBOMB,
	A_M203_HE,
	A_M203_IL,
	A_M203_SMOKE,
	A_M203_GAS,
	A_F18_MISSILE,
	A_EXPLODING_BARREL,
	A_HE_GRENADE,
	A_12GAUGE,
	A_M203_FRAG,
	A_GL_FRAG,
	A_GL_IL,
	A_GL_SMOKE,
	A_GL_GAS,
	A_9X19S,
	A_9X19SD,
	A_556X45SD,
	A_762X51SD,
	A_762X39SD,
	A_57X28,
	AMMO_END
};

enum class FIREMODE
{
	SAFETY,
	SINGLE,
	BURST,
	AUTOFIRE,
	SPECIAL_MODE,
	NUM_FIREMODES
};

enum class PROJECTILE_TYPE
{
	NORMAL,
	ONE_FRAME,
	ONE_FRAME_SHOTGUN
};

enum class PROJECTILE_STATE
{
	PROJECTILE_EXPIRED,
	PROJECTILE_FLYOUT,
	PROJECTILE_AT_REST,
	PROJECTILE_TO_BE_DETONATED,
	PROJECTILE_DETONATION_TO_BE_HANDLED,
	PROJECTILE_WAS_DETONATED,
	PROJECTILE_TO_BE_REMOVED
};

enum class GRENADE_STATE
{
	CREATE,
	NEWPOS,
	DETONATE,
	REMOVE
};

class CZAmmo
{
public:
	CZAmmo();
	~CZAmmo();

	void SetInternalName(const char* internalName);
	void SetDisplayName(const char* displayName);
	void SetDescription(const char* description);

	void SetID(int id);
	void SetImpactDamage(float impactDamage);
	void SetHitAnimName(const char* hitAnimName);
	void SetStun(float stun);
	void SetPiercing(float piercing);
	void SetExplosionDamage(float explosionDamage);
	void SetExplosionRadius(float explosionRadius);
	void SetProjectilesFired(int projectilesFired);
	void SetBlowbackFalloff(float blowbackFalloff);
	void SetProximitySquared(float proximity);
	void SetAccelerationFactor(float acceleration);
	void SetIsVolatile(bool volatile);
private:
	const char* m_internalName;
	const char* m_displayName;
	const char* m_description;

	int m_ID;
	float m_impactDamage;
	const char* m_hitAnimName;
	float m_stun;
	float m_piercing;
	float m_explosionDamage;
	float m_explosionRadius;
	int m_projectilesFired;
	float m_blowbackFalloff;
	float m_proximitySquared;
	float m_accelerationFactor;
	bool m_volatile;
};

class CZAmmoList : public std::list<CZAmmo*> {};

class CZWeaponStance
{
public:
	CZWeaponStance();
	~CZWeaponStance();

	void SetReticuleKnock(float knock);
	void SetReticuleKnockReturn(float knockReturn);
	void SetReticuleKnockMax(float knockMax);
	void SetTargetDilateUponFire(float dilation);
	void SetTargetDilateUponMovement(float dilation);
	void SetTargetConstrict(float constriction);
	void SetTargetMin(float min);
	void SetTargetMax(float max);
	void SetSniperDistPPFrameX(float frame);
	void SetSniperDistPPFrameY(float frame);
	void SetSniperDistLimitX(float limit);
	void SetSniperDistLimitY(float limit);
	void SetSniperDecayRate(float decay);
	void SetFireRifleKickRate(float rate);
	void SetFireRifleKickReturnRate(float returnRate);
	void SetFireRifleKickBaseDist(float distance);
	void SetFireRifleKickRandomDist(float randomDistance);
	void SetKnockCount(int knocks);
	void SetKnockEntryStrength(float strength);
	void SetWiggleReport(float wiggleReport);
private:
	f32 m_reticuleKnock;
	f32 m_reticuleKnockReturn;
	f32 m_reticuleKnockMax;
	f32 m_sniperDistPPFrameX;
	f32 m_sniperDistPPFrameY;
	f32 m_sniperDistLimitX;
	f32 m_sniperDistLimitY;
	f32 m_sniperDecayRate;
	f32 m_targetDilateUponFire;
	f32 m_targetDilateUponMovement;
	f32 m_targetDilateUponMovementSqrt;
	f32 m_targetConstrict;
	f32 m_targetMin;
	f32 m_targetMax;
	f32 m_fireRifleKickRate;
	f32 m_fireRifleKickReturnRate;
	f32 m_fireRifleKickBaseDist;
	f32 m_fireRifleKickRandomDist;
	f32 m_wiggleReport;
	s32 m_knockCount;
	f32 m_knockEntryStrength;
};

class CZWeapon
{
public:
	struct AI_PARAMS
	{
		static u32 version;

		u32 m_version : 8;
		u32 m_custom : 1;
		u32 m_hard_min : 1;
		u32 m_unused : 22;
		f32 m_min_range;
		f32 m_max_range;
	};

	CZWeapon();
	~CZWeapon();

	static bool          IsPrimary(EQUIP_ITEM item);
	static bool          IsSecondary(EQUIP_ITEM item);
	static EQUIP_ITEM    GetIDType();
	static EQUIP_ITEM    GetIDType(EQUIP_ITEM id);
	static EQUIP_ITEM    GetWeaponId(const char* name);

	void Open();
	void Close();

	void AddLegalAmmo(CZAmmo* ammo);
	bool AllocateHitAnimMem();
	bool AllocateSpecialMaterialAnimMem();

	bool CreateProjectileList();
	bool CreateWeaponList();

	void DestroyProjectileList();

	void ClearAnims();
	void ClearTimer();

	void Fire(CZProjectile& projectile);
	void Fire(zdb::CNode* firepoint,
		CZWeapon* weapon,
		CZAmmo* ammo,
		const CPnt3D* param_4,
		const CPnt3D* param_5,
		const CPnt3D* param_6,
		zdb::CModel* model,
		CZProjectile* projectile,
		u32 param_9,
		f32 param_10,
		f32 param_11);

	/// -------------------------------------------
	/// GETTERS
	/// -------------------------------------------
	char* GetAssociatedGearName()         const;
	char* GetDecalSetName()               const;
	char* GetDescription()                const;
	char* GetDefaultSpecialAnimName()     const;
	char* GetFireAnimName()               const;
	char* GetHitAnimName()                const;
	char* GetIconTextureName()            const;
	char* GetModelName()                  const;
	char* GetName()                       const;
	char* GetSpecialMaterialAnimName()    const;
	char* GetWeaponName(EQUIP_ITEM id)    const;
	char* GetWeaponUIName(EQUIP_ITEM id)  const;
	char* GetWeaponVUIName(EQUIP_ITEM id) const;

	s32           GetAmmoCapacity()               const;
	s32           GetNumMags()                    const;

	f32           GetEffectiveRange()             const;
	f32           GetImpactRadius()               const;
	f32           GetMaxRange()                   const;
	f32           GetMuzzleVelocity()             const;

	CZAnim* GetDefaultSpecialAnim()         const;
	CZAnim* GetFireAnim()                   const;
	CZAnim* GetHitAnim()                    const;
	CZAnim* GetSpecialMaterialAnim()        const;

	CSnd* GetBulletPassSound()            const;

	CZAmmo* GetDefaultAmmo()                const;

	EQUIP_AMMO    GetDefaultAmmoID()              const;

	ENCUMBRANCE   GetEncumbrance()                const;

	/// -------------------------------------------
	/// SETTERS
	/// -------------------------------------------
	void          SetAssociatedGearName(const char* name);
	void          SetDecalSetName(const char* name);
	void          SetDefaultSpecialAnimName(const char* name);
	void          SetDescription(const char* description);
	void          SetFireAnimName(const char* name);
	void          SetHitAnimName(const char* name);
	void          SetIconTextureName(const char* name);
	void          SetModelName(const char* name);
	void          SetName(const char* name);
	void          SetReloadSoundName(const char* name);
	void          SetSpecialMaterialAnimName(const char* name);

	void          SetAmmoCapacity(s32 capacity);
	void          SetNumMags(s32 mags);

	void          SetEffectiveRange(f32 range);
	void          SetMaxRange(f32 range);
	void          SetImpactRadius(f32 radius);
	void          SetMuzzleVelocity(f32 velocity);
	void          SetSoundRadius(f32 radius);

	void          SetBulletPassSound(CSnd* sound);

	void          SetDefaultSpecialAnim(CZAnim* anim);
	void          SetSpecialMaterialAnim(CZAnim* anim);
	void          SetZoomedFireAnim(CZAnim* anim);
	void          SetFireAnim(CZAnim* anim);
	void          SetHitAnim(CZAnim* anim);

	void          SetEncumbrance(ENCUMBRANCE encumb);

	void          SetHasFireMode(FIREMODE mode);

	/// -------------------------------------------
	/// STATIC MEMBERS
	/// -------------------------------------------
public:
	static bool m_timer_bTimerRegistered;
	static bool m_timer_bTimerCleared;
	static bool m_timer_bIncrTimer;
	static f32 m_timer_pCurval;
	static f32 m_timer_maxval;

	static bool m_allowFireAnimations;
	static bool m_allowImpactAnimations;
	static bool m_allowWeaponIntersection;

	static CZWeaponList m_listWeapons;
	static CZProjectileList m_pProjectileList;

	static CSnd* m_bulletPassSound;
private:
	char* m_name;
	char* m_description;
	char* m_texname;
	char* m_icontexname;
	char* m_associatedgearname;
	char* m_modelname;
	char* m_decalsetname;

	FIREMODE m_maxfiremode;

	s32 m_ammocap;
	s32 m_nummags;

	f32 m_soundradius;
	f32 m_soundradiusSq;

	ENCUMBRANCE m_encumb;

	f32 m_maxrange;
	f32 m_effectiverange;
	f32 m_muzzlevel;
	f32 m_impactradius;
	f32 m_firewait;
	f32 m_reloadtime;
	bool m_reloadAfterShot;

	AI_PARAMS m_ai_params;

	EQUIP_ITEM m_ID;

	CZAnim** m_hitanim;
	CZAnim* m_fireanim;
	CZAnim* m_zoomedfireanim;
	CZAnim* m_defaultspecialanim;
	CZAnim* m_specialmaterialanim;

	CSnd* m_reloadsound;
	char* m_reloadsoundname;

	char* m_hitanimname;
	char* m_fireanimname;
	char* m_defaultspecialanimname;
	char* m_specialmaterialanimname;

	zdb::CTexture* m_texture;
	zdb::CTexHandle* m_icontex;
	// TODO: Implement this type
	// zdb::CZDecalSet m_decalset;

	CZAmmoList m_LegalAmmoList;
	bool m_hasFiremodes[5];
};

class CZFTSWeapon : public CZWeapon
{
public:
	CZFTSWeapon() : CZWeapon() {}
	~CZFTSWeapon();

	void SetAccuracyBurstCountMin(int min);
	void SetAccuracyBurstCountMax(int max);
	void SetAccuracyScalarMin(float min);
	void SetAccuracyScalarMax(float max);
private:
	s32 m_firstZoomLevel;
	s32 m_secondZoomLevel;
	s32 m_thirdZoomLevel;
	bool m_rumbleHighExceeds;
	f32 m_rumbleHighTime;
	bool m_rumbleLowExceeds;
	f32 m_rumbleLowTime;
	f32 m_rumbleLowPower;
	f32 m_accuracyBurstCountMin;
	f32 m_accuracyBurstCountMax;
	f32 m_accuracyScalarMin;
	f32 m_accuracyScalarMax;
	f32 m_normalizedRange;
	s32 m_slotCost;
};

class CZProjectile
{
public:
	void Reset();

	zdb::CNode* GetInstance() const;

	void Detonate();
private:
	u32 m_done : 1;
	u32 m_isfirsthit : 1;
	u32 m_isplayer : 1;
	u32 m_useflyout : 1;
	u32 m_lastHitWasPerson : 1;
	u32 m_lastHitWasVolumetric : 1;
	u32 m_echo : 1;
	u32 m_unused : 25;

	GRENADE_STATE m_grenadestate;
	PROJECTILE_TYPE m_shottype;
	PROJECTILE_STATE m_state;

	CZWeapon* m_weapon;
	CZAmmo* m_ammo;
	
	CPickup* m_pickup;

	zdb::CNode* m_instance;
	zdb::CNode* m_owner;

	zdb::DiIntersect* m_di;
	s32 m_di_handle;

	CZAnim* m_animinstance;

	CPnt3D m_startpos;
	CPnt3D m_framestartpos;
	CPnt3D m_frameendpos;
	CPnt3D m_vel;
	CPnt3D m_lastPlayerHitPos;
	CPnt3D m_lastVolumetricHit;

	f32 m_time;
	f32 m_removaltime;
	f32 m_currange;
	f32 m_heading;
	f32 m_pitch;
	f32 m_roll;

	s32 m_intersecthandle;
	s32 m_shooterID;
	s32 m_object_index;
	s32 m_flyout_idx;
	s32 m_tracer_count;

	bool m_removeASAP;

	s32 m_lastVolumetricMaterial;
};

class CZWeaponList : public std::list<CZWeapon*>
{
public:
	CZWeapon* GetWeaponByIndex(int index) const;
};

class CZProjectileList : public std::list<CZProjectile*> {};

class CAccuracy
{
public:
	f32 FactorX;
	f32 FactorY;
	f32 Factor;
};