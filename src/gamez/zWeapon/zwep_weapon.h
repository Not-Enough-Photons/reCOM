#pragma once
#include <list>

#include "gamez/zAnim/zanim.h"

class CZProjectile;
class CZProjectileList;

enum EQUIP_ITEM
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

enum EQUIP_AMMO
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

enum FIRE_MODE
{
	SAFETY,
	SINGLE,
	BURST,
	AUTOFIRE,
	SPECIAL_MODE,
	NUM_FIREMODES
};

enum PROJECTILE_TYPE
{
	NORMAL,
	ONE_FRAME,
	ONE_FRAME_SHOTGUN
};

enum PROJECTILE_STATE
{
	PROJECTILE_EXPIRED,
	PROJECTILE_FLYOUT,
	PROJECTILE_AT_REST,
	PROJECTILE_TO_BE_DETONATED,
	PROJECTILE_DETONATION_TO_BE_HANDLED,
	PROJECTILE_WAS_DETONATED,
	PROJECTILE_TO_BE_REMOVED
};

enum GRENADE_STATE
{
	CREATE,
	NEWPOS,
	DETONATE,
	REMOVE
};

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
	float m_reticuleKnock;
	float m_reticuleKnockReturn;
	float m_reticuleKnockMax;
	float m_sniperDistPPFrameX;
	float m_sniperDistPPFrameY;
	float m_sniperDistLimitX;
	float m_sniperDistLimitY;
	float m_sniperDecayRate;
	float m_targetDilateUponFire;
	float m_targetDilateUponMovement;
	float m_targetDilateUponMovementSqrt;
	float m_targetConstrict;
	float m_targetMin;
	float m_targetMax;
	float m_fireRifleKickRate;
	float m_fireRifleKickReturnRate;
	float m_fireRifleKickBaseDist;
	float m_fireRifleKickRandomDist;
	float m_wiggleReport;
	int m_knockCount;
	float m_knockEntryStrength;
};

class CZWeapon
{
public:
	CZWeapon();
	~CZWeapon();

	static bool m_allowFireAnimations;
	static bool m_allowImpactAnimations;
	static bool m_allowWeaponIntersection;
	static CZWeaponList m_listWeapons;
	static CZProjectileList m_pProjectileList;

	void Init();
	void PreTick();
	void PostTick();

	const char* GetInternalName() const;
	const char* GetDisplayName() const;
	const char* GetDescription() const;

	float GetSoundRadius() const;
	float GetSoundRadiusSqrt() const;
	float GetEffectiveRange() const;
	float GetMaximumRange() const;
	float GetMuzzleVelocity() const;
	float GetGravityAcceleration() const;
	float GetImpactRadius() const;

	void SetInternalName(const char* internalName);
	void SetDisplayName(const char* displayName);
	void SetDescription(const char* description);

	EQUIP_ITEM itemType;
private:
	const char* m_internalName;
	const char* m_displayName;
	const char* m_description;

	float m_soundRadius;
	float m_soundRadiusSqrt;
	float m_effectiveRange;
	float m_maximumRange;
	float m_muzzleVelocity;
	float m_gravityAcceleration;
	float m_impactRadius;
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
	int m_firstZoomLevel;
	int m_secondZoomLevel;
	int m_thirdZoomLevel;
	bool m_rumbleHighExceeds;
	float m_rumbleHighTime;
	bool m_rumbleLowExceeds;
	float m_rumbleLowTime;
	float m_rumbleLowPower;
	float m_accuracyBurstCountMin;
	float m_accuracyBurstCountMax;
	float m_accuracyScalarMin;
	float m_accuracyScalarMax;
	float m_normalizedRange;
	int m_slotCost;
};

class CZProjectile
{
public:
	float ResolveDamage(float target, float source, float* currentDamage, float* newDamage);
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
	float FactorX;
	float FactorY;
	float Factor;
};