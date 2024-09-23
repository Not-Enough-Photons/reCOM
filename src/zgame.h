#pragma once
namespace zdb
{
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