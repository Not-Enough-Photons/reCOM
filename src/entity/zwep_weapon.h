#pragma once
enum EQUIP_ITEM
{
	ITEM_GLOCK_18,
	ITEM_MARK23,
	ITEM_MARK23_SD,
	ITEM_FIVE_SEVEN,
	ITEM_BERETTA_M9,
	ITEM_SIG226,
	ITEM_DESERT_EAGLE,
	ITEM_HKP9S,
	ITEM_MP5,
	ITEM_MP5_SD,
	ITEM_UZI,
	ITEM_M16,
	ITEM_M4A_CARBINE,
	ITEM_SIG_COMMANDO,
	ITEM_AK47,
	ITEM_AKS74,
	ITEM_M14_GUN,
	ITEM_M4A_CARBINE_203,
	ITEM_JACKHAMMER,
	ITEM_REMINGTON_870,
	ITEM_M60E,
	ITEM_M63A,
	ITEM_BARRET_M82A1,
	ITEM_REMINGTON_700,
	ITEM_M87,
	ITEM_STONER_SR25,
	ITEM_FRAG,
	ITEM_SMOKE,
	ITEM_FLASHBANG,
	ITEM_WILLIE_PETE,
	ITEM_GAS,
	ITEM_HE,
	ITEM_C4,
	ITEM_SATCHEL,
	ITEM_CLAYMORE,
	ITEM_FRAG_2,
	ITEM_ILLUM,
	ITEM_SMOKE_2,
	ITEM_GAS_2,
	ITEM_2X_AMMO
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