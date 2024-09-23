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
	};

	class CMenuState : public CGameState
	{
		void Start();
	};

	class CCinematicState : public CGameState
	{
		void Start();
	};

	class CCoreState : public CGameState
	{
		void Start();
	};

	class CExitState : public CGameState
	{
		void Start();
	};

	class CMPExitState : public CGameState
	{
		void Start();
	};

	class CRebootState : public CGameState
	{
		void Start();
	};

	class CShutdownState : public CGameState
	{
		void Start();
	};
}