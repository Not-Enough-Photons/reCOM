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
		const char* m_WeaponType;

		// magazines are put into CZAmmo instances, but for now i'll tack it in here
		int m_RemainingAmmo;
		int m_AmmoCount;
	};
}