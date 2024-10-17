#pragma once
#include "node/node_main.h"
#include "math/zmath_main.h"

namespace zdb
{
	static int recycler_index = 0;
	static CftsPlayer* ftsPlayer;

	class CEntity
	{
	public:
		CEntity();
		~CEntity();

		void IncrementAwareCounter();
		void DecrementAwareCounter();

		// Recycler functions
		virtual void OnRecycleEntity();
		void OpenRecycler();

		// Mission callback functions
		virtual void OnMissionStart();
		virtual void OnMissionEnd();

		// Tick virtual functions
		virtual void PreTick();
		virtual void PostPreTick();
		virtual void PrePostTick();
		virtual void Tick();
		virtual void PostTick();

		void SetDisplayName(const char* displayName);

		zdb::CNode& GetNode() const;
		bool IsValid() const;

		void SetController(CEntityCtrl* controller);
	private:
		zdb::CNode* m_node;

		float m_x00;
		float m_y00;
		float m_z00;
		float m_x01;
		float m_y01;
		float m_z01;
		float m_x02;
		float m_y02;
		float m_z02;
		float m_x03;
		float m_y03;
		float m_z03;
	};

	class CEntityCtrl
	{
	public:
		virtual void PreTick() = 0;
		virtual void Tick() = 0;
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
	private:
	};

	class CZSealEx : public CNodeEx
	{

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