#pragma once
namespace zdb
{
	class CZWeaponStance
	{
	public:
		CZWeaponStance();
		~CZWeaponStance();
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
	private:
		const char* m_internalName;
		const char* m_displayName;
		const char* m_description;

		float m_effectiveRange;
		float m_maximumRange;
		float m_muzzleVelocity;
		float m_gravityAcceleration;
		float m_impactRadius;
	};

	class CZFTSWeapon : public CZWeapon
	{
	public:
		CZFTSWeapon() : CZWeapon() { }
		~CZFTSWeapon();
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
}