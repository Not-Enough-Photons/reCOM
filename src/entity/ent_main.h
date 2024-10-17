#pragma once
#include "node/node_main.h"
#include "math/zmath_main.h"

namespace zdb
{
	static CftsPlayer* ftsPlayer;

	class CEntity
	{
	public:
		CEntity();
	};

	/// <summary>
	/// Base FTS player class. FTS stands for "Fireteam Seal."
	/// </summary>
	class CftsPlayer
	{
	public:
		/// <summary>
		/// Gets the static player instance.
		/// </summary>
		/// <returns></returns>
		static CftsPlayer* ftsGetPlayer()
		{
			return ftsPlayer;
		}

		static void RegisterAnimCommands();
	};

	class CZSealBody : CEntity
	{
	public:
		CZSealBody();
		~CZSealBody();

		// Tomb Of The Unknown Functions
		static CZSealBody* Create(long param_1, int param_2, int param_3);

		int* FUN_002e4d60(zdb::Vector3* param_2, long param_3);

		float SetHealth(float health);
		void OnDeath(void* ftsPlayer);

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
		float m_LLegHealth;
		float m_RLegHealth;

		float m_HeadArmor;
		float m_BodyArmor;
		float m_LArmArmor;
		float m_RArmArmor;
		float m_LLegArmor;
		float m_RLegArmor;
	};

	class CSealCtrl
	{

	};

	class CSealCtrlAi : public CSealCtrl
	{
	public:
		static void RegisterCommands();
	};
}