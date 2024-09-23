#include <istream>
#include <cstddef>

namespace zar
{
	class CZRdrFile : std::ios::basic_ios
	{
	private:
		float_t m_SoundDistanceClose;
		float_t m_SoundDistanceMed;
		float_t m_SoundDistanceFar;

		// ZAMMO
		char m_InternalName[256];
		char m_DisplayName[256];
		char m_Description[2048];
		int32_t m_ID;
		int32_t m_ImpactDamage;
		int32_t m_Stun;
		int32_t m_Piercing;
		float_t m_Explosion_Damage;
		float_t m_Explosion_Radius;
	};
}