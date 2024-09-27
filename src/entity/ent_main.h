#pragma once
#include "node/node_main.h"
#include "math/zmath_main.h"

namespace zdb
{
	class CEntity
	{
	public:
		CEntity();
	};

	class CZSealBody : CEntity
	{
	public:
		CZSealBody();
		~CZSealBody();

		void SetPosition(float x, float y, float z);
		void SetPosition(zdb::Vector3 position);
		void WritePosition();

		zdb::Vector3 GetPosition() const;
		float GetYaw() const;

		bool AggroLookAt(int param_1, void* param_2, zdb::Vector3 lookPosition);
	private:
		zdb::Vector3 m_Position;
		float m_Yaw;
		zdb::Vector3 m_Scale;

		zdb::Vector3 m_WrittenPosition;
		float m_WrittenYaw;

		CZSealBodyBone* m_SkelRoot;
		CZSealBodyBone* m_Hips;
		CZSealBodyBone* m_SpineLo;
		CZSealBodyBone* m_SpineHi;
		CZSealBodyBone* m_Neck;
		CZSealBodyBone* m_LBicep;
		CZSealBodyBone* m_RBicep;
		CZSealBodyBone* m_LThigh;
		CZSealBodyBone* m_RThigh;
		CZSealBodyBone* m_LCalf;
		CZSealBodyBone* m_RCalf;
		CZSealBodyBone* m_LFoot;
		CZSealBodyBone* m_RFoot;
		CZSealBodyBone* m_LToe;
		CZSealBodyBone* m_RToe;
		CZSealBodyBone* m_LHand;
		CZSealBodyBone* m_RHand;
		CZSealBodyBone* m_LForearm;
		CZSealBodyBone* m_RForearm;
		CZSealBodyBone* m_LSCap;
		CZSealBodyBone* m_RSCap;
		CZSealBodyBone* m_LShoulderWgt;
		CZSealBodyBone* m_RShoulderWgt;
		CZSealBodyBone* m_Head;
		CZSealBodyBone* m_AimNodes;
	};

	class CZSealBodyBone : CNodeEx
	{
	public:
		CZSealBodyBone();
		CZSealBodyBone(const char* name);
	private:
		const char* m_BoneName;
		zdb::Vector3 m_BoneWorldPosition;
		zdb::Vector3 m_BoneLocalPosition;
		zdb::Vector3 m_BoneRotation;
	};

	class CZSealEx : public CNodeEx
	{
	public:
		const char* GetRawCommandType(int command);
		void SetLimbHealth();
		void DamageSeal(float source, float param_2);
		float DamagePlayer(float source, float param_2);
	private:
		float m_Health;
		float m_OldHealth;

		float m_HeadHealth;
		float m_BodyHealth;
		float m_LArmHealth;
		float m_RArmHealth;
		float m_LArmHealth;
		float m_RArmHealth;

		float m_HeadArmor;
		float m_BodyArmor;
		float m_LArmArmor;
		float m_RArmArmor;
		float m_LArmArmor;
		float m_RArmArmor;
	};
}