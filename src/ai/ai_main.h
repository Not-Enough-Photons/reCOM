#pragma once
namespace zdb
{
	enum FireTeam
	{
		FT_UNKNOWN,
		FIRETEAM,
		ABLE,
		BRAVO,
		ESCORTEE,
		FRIENDLY,
		NEUTRAL,
		TURRETS,
		SUPPORT,
		HOSTAGE,
		ENEMIES,
		ALLIES
	};

	enum SealCommand
	{
		CMD_UNKNOWN,
		CMD_ACTION,
		CMD_DEPLOY,
		CMD_FIREATWILL,
		CMD_FOLLOW,
		CMD_HOLDPOS,
		CMD_HOLDFIRE,
		CMD_REGROUP,
		CMD_ESCORT,
		CMD_RUNTO,
		CMD_MOVETO,
		CMD_STEALTHTO,
		CMD_ATTACKTO,
		CMD_LEADTO,
		CMD_COVERTARGET,
		CMD_LASETARGET,
		CMD_BREACH,
		CMD_GETDOWN,
		CMD_PULLOUT,
		CMD_OVERWATCH,
		CMD_SUPPORT,
		CMD_EXTRACT,
		CMD_CLEARAREA,
		CMD_RESTRAIN,
		CMD_REMOVEKILLS,
		CMD_AWAKE,
		CMD_SLEEP,
		CMD_AMBUSH
	};

	class CAiPlanner
	{
	public:
		virtual void Act();
		virtual void Stop();
		virtual float GetPlanCost();
	};

	class CBasicPlanner : public CAiPlanner
	{

	};

	class CStealthPlanner : public CAiPlanner
	{

	};

	class CRestrainedPlanner : public CAiPlanner
	{

	};
}