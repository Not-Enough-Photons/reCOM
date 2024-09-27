#include "ent_main.h"
#include "zwep_weapon.h"

#include "ui/zui_main.h"

namespace zdb
{
	CZSealBody::CZSealBody()
	{
		m_Position = { 0.0f, 0.0f, 0.0f };
		m_Yaw = 0.0f;
		m_WrittenPosition = { 0.0, 0.0, 0.0 };
		m_WrittenYaw = 0.0f;

		m_SkelRoot = new CZSealBodyBone("skel_root");
		m_LFoot = new CZSealBodyBone("lfoot");
		m_RFoot = new CZSealBodyBone("rfoot");
		m_LHand = new CZSealBodyBone("lhand");
		m_LHand = new CZSealBodyBone("rhand");
		m_Hips = new CZSealBodyBone("hips");
		m_Head = new CZSealBodyBone("head");
		m_Neck = new CZSealBodyBone("neck");
		m_SpineHi = new CZSealBodyBone("spinehi");
		m_SpineLo = new CZSealBodyBone("spinelo");
		m_LThigh = new CZSealBodyBone("lthigh");
		m_RThigh = new CZSealBodyBone("rthigh");
		m_LCalf = new CZSealBodyBone("lcalf");
		m_RCalf = new CZSealBodyBone("rcalf");
		m_LBicep = new CZSealBodyBone("lbicep");
		m_RBicep = new CZSealBodyBone("rbicep");
		m_LForearm = new CZSealBodyBone("lforearm");
		m_RForearm = new CZSealBodyBone("rforearm");
		m_LSCap = new CZSealBodyBone("lscap");
		m_RSCap = new CZSealBodyBone("rscap");
		m_LShoulderWgt = new CZSealBodyBone("lshoulder_wgt");
		m_RShoulderWgt = new CZSealBodyBone("rshoulder_wgt");
		m_AimNodes = new CZSealBodyBone("aimnodes");
		m_LToe = new CZSealBodyBone("ltoe");
		m_RToe = new CZSealBodyBone("rtoe");
	}

	CZSealBody::~CZSealBody()
	{

	}

	void CZSealBody::SetPosition(float x, float y, float z)
	{
		m_WrittenPosition.x = x;
		m_WrittenPosition.y = y;
		m_WrittenPosition.z = z;
		WritePosition();
	}

	void CZSealBody::SetPosition(zdb::Vector3 position)
	{
		SetPosition(position.x, position.y, position.z);
	}

	void CZSealBody::WritePosition()
	{
		m_Position.x = m_WrittenPosition.x;
		m_Position.y = m_WrittenPosition.y;
		m_Position.z = m_WrittenPosition.z;
	}

	zdb::Vector3 CZSealBody::GetPosition() const
	{
		return m_Position;
	}

	float CZSealBody::GetYaw() const
	{
		return m_Yaw;
	}

	CZSealBodyBone::CZSealBodyBone()
	{
		m_BoneName = "";
		m_BoneWorldPosition = { 0.0, 0.0, 0.0 };
		m_BoneLocalPosition = { 0.0, 0.0, 0.0 };
		m_BoneRotation = { 0.0, 0.0, 0.0 };
	}

	CZSealBodyBone::CZSealBodyBone(const char* name)
	{
		m_BoneName = name;
		m_BoneWorldPosition = { 0.0, 0.0, 0.0 };
		m_BoneLocalPosition = { 0.0, 0.0, 0.0 };
		m_BoneRotation = { 0.0, 0.0, 0.0 };
	}

	const char* CZSealEx::GetRawCommandType(int command)
	{
		switch (command)
		{
		case 0:
			return "CMD_UNKNOWN";
		case 1:
			return "CMD_ACTION";
		case 2:
			return "CMD_DEPLOY";
		case 3:
			return "CMD_FIREATWILL";
		case 4:
			return "CMD_FOLLOW";
		case 5:
			return "CMD_HOLDPOS";
		case 6:
			return "CMD_HOLDFIRE";
		case 7:
			return "CMD_REGROUP";
		case 8:
			return "CMD_ESCORT";
		case 9:
			return "CMD_RUNTO";
		case 10:
			return "CMD_MOVETO";
		case 11:
			return "CMD_STEALTHTO";
		case 12:
			return "CMD_ATTACKTO";
		case 13:
			return "CMD_LEADTO";
		case 14:
			return "CMD_COVERTARGET";
		case 15:
			return "CMD_LASETARGET";
		case 16:
			return "CMD_BREACH";
		case 17:
			return "CMD_GETDOWN";
		case 18:
			return "CMD_PULLOUT";
		case 19:
			return "CMD_OVERWATCH";
		case 20:
			return "CMD_SUPPORT";
		case 21:
			return "CMD_EXTRACT";
		case 22:
			return "CMD_CLEARAREA";
		case 23:
			return "CMD_RESTRAIN";
		case 24:
			return "CMD_REMOVEKILLS";
		case 25:
			return "CMD_AWAKE";
		case 26:
			return "CMD_SLEEP";
		case 27:
			return "CMD_AMBUSH";
		default:
			return "CMD_UNKNOWN";
		}
	}

	void CZSealEx::SetLimbHealth()
	{

	}

	float CZSealEx::DamagePlayer(float source, float param_2)
	{
		float difference = source - m_OldHealth * ((10.0f - param_2) / 10.0f);

		if (difference <= 0.0f)
		{
			difference = 0.0f;
		}

		float dampenedDamage = m_OldHealth - (source - difference) / 4.0f;
		m_OldHealth = dampenedDamage;

		if (dampenedDamage <= 0.0f)
		{
			m_OldHealth = 0.0f;
		}

		dampenedDamage = m_Health;
		m_Health = dampenedDamage - difference;
		
		if (m_Health <= 0.0f)
		{
			m_Health = 0.0f;
		}

		return m_Health;
	}

	const char* CZFTSWeapon::GetWeaponType(int type) const
	{
		if ((type != -2) && (type != -1))
		{
			if (type == -26)
			{
				return "TURRETED_LAUNCHER";
			}

			if (type == -51)
			{
				return "TURRETED_WEAPON";
			}

			if (type == -55)
			{
				return "ARMOR";
			}

			if (type == -66)
			{
				return "MISC_EQUIP";
			}

			if (type == -71)
			{
				return "LAUNCHED_MISSILE";
			}

			if (type == -85)
			{
				return "LAUNCHED";
			}

			if (type == -105)
			{
				return "EXPLOSIVE";
			}

			if (type == -111)
			{
				return "LAUNCHER";
			}

			if (type == -115)
			{
				return "HEVY_WEAPON";
			}

			if (type == 121)
			{
				return "GRENADE";
			}

			if (type == 101)
			{
				return "SNIPER_RIFLE";
			}

			if (type == 91)
			{
				return "MACHINE_GUN";
			}

			if (type == 81)
			{
				return "SHOTGUN";
			}

			if (type == 51)
			{
				return "ASSLT_RIFLE";
			}

			if (type == 31)
			{
				return "SMG";
			}

			if (type == 4)
			{
				return "PISTOL";
			}
		}

		return "UNKNOWN";
	}

	void CZFTSWeapon::Fire()
	{
		// TODO: the rest of this fire function
		// for now implement the things i know so far
		int claymores = 0;
		if (claymores < 4)
		{

		}
		else
		{
			zdb::CZUI::SendUIMessage(0, (char*)0x583ad0, "Max Claymores Placed (4)", nullptr, 0, 0);
		}
	}
}