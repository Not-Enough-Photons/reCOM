#pragma once
#include "anim/anim_main.h"

enum OP_TYPE
{
	OP_NONE,
	OP_CMP_EQUAL,
	OP_CMP_NOTEQUAL,
	OP_CMP_GTHAN,
	OP_CMP_LTHAN,
	OP_CMP_GTHANEQ,
	OP_CMP_LTHANEQ,
	OP_EQUAL,
	OP_INCREMENT,
	OP_DECREMENT
};

/// <summary>
/// Determines the pooling type for the valve.
/// <para> ValveType::PERM - Lasts the entire lifetime of the level. Will pool if value reaches threshold. </para>
/// <para> ValveType::TEMP - Loads once then unloads when done. </para>
/// <para> ValveType::PERSIST - Lasts the entire lifetime of the game, and will pool if the value reaches threshold.</para>
/// </summary>
enum VALVE_TYPE
{
	PERM,
	TEMP,
	PERSIST
};

class CValvePool
{
public:
	void Acquire();
};

/// <summary>
/// A class that acts as a "signal" for events to occur in the game.
/// An example is the valve "mission_failure", that when fired, will run callbacks to handle mission failure.
/// </summary>
class CValve
{
public:
	CValve();

	static void RegisterCommands();
	static void Create(const char* name, VALVE_TYPE type);

	static int Init();
	static int Uninit();

	static CValve* GetByName(const char* name);
	static zanim_cmd_hdr* CmdParseCmp(zrdr* reader);
	static bool CmdTickCmp(zanim_cmd_hdr* command, float* delta);

	void Reset();

	void AssignName();
	void SetName(const char* name);
	void FreeName();
	void MakeCallbacks();
	OP_TYPE ParseOperator(const char* op);

	int count;
private:
	const char* m_Name;
	int m_Value;
	VALVE_TYPE m_Type;
};