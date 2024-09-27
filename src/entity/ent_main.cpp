#include "ent_main.h"

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
}