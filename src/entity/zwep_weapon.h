#pragma once
namespace zdb
{
	class CZWeapon
	{

	};

	class CZFTSWeapon : public CZWeapon
	{
	public:
		void Fire();
		void FireProjectile();
		void Reload();
	private:
		// magazines are put into CZAmmo instances, but for now i'll tack it in here
		int m_RemainingAmmo;
		int m_AmmoCount;
	};
}