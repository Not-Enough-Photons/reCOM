#pragma once
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

	int Init();
	int Uninit();
	void Reset();

	void AssignName();
	void SetName();
	void FreeName();
	void MakeCallbacks();
private:
	const char* m_Name;
	int m_Value;
	VALVE_TYPE m_Type;
};