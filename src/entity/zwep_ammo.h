#pragma once
namespace zdb
{
	class CZAmmo
	{
	public:
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
}