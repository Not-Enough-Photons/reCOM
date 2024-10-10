#pragma once
namespace zdb
{
	static void FUN_004b0dc0(long param_1, long param_2);
	static bool FUN_004f8940(int param_1);
	static void ZGameMain();

	class CGame
	{
	public:
		CGame();
	};

	class COurGame : public CGame
	{
	public:
		void InitializeTextChat();
		void Unk001(void* param_1, int param_2);
	};

	class CGameState
	{
	public:
		virtual void Start();
		virtual void Exit();
	};

	class CMenuState : public CGameState
	{
		void Start();
		void Exit();
	};

	class CCinematicState : public CGameState
	{
		void Start();
		void Exit();
	};

	class CCoreState : public CGameState
	{
		void Start();
		void Exit();
	};

	class CExitState : public CGameState
	{
		void Start();
		void Exit();
	};

	class CMPExitState : public CGameState
	{
		void Start();
		void Exit();
	};

	class CRebootState : public CGameState
	{
		void Start();
		void Exit();
	};

	class CShutdownState : public CGameState
	{
		void Start();
		void Exit();
	};
}