#pragma once
namespace zdb
{
	class CZWeapon
	{
	public:
		virtual void Fire();
		virtual void Reload();
	};

	class CZFTSWeapon : public CZWeapon
	{
	public:
		const char* GetWeaponType(int type) const;

		void Fire();
		void FireProjectile();
		void Reload();
	private:
		const char* m_InternalName;
		const char* m_DisplayName;
		const char* m_Description;

		const char* m_WeaponType;
		
		// magazines are put into CZAmmo instances, but for now i'll tack it in here
		int m_RemainingAmmo;
		int m_AmmoCount;
		int m_NumMags;

		float m_MuzzleVelocity;
		float m_AccScalarMin;
		float m_AccScalarMax;
		float m_GravityAcceleration;

		const char* m_ModelName;
		const char* m_FireAnimName;
		const char* m_HitAnimName;

		float m_Encumberance;

		bool m_BurstMode;
		bool m_SingleMode;
		bool m_AutoMode;

		float m_Timer1;
		float m_Timer2;

		float m_RecoilPct;

		float m_MaximumRange;
		float m_EffectiveRange;

		int m_SlotCost;

		bool m_HasBackblast;
	};
}