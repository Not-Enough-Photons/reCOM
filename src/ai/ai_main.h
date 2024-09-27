#pragma once
namespace zdb
{
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