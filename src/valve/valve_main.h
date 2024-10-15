#pragma once
enum ValveType
{
	PERM,
	TEMP,
	PERSIST
};

/// <summary>
/// A class that acts as a "signal" for events to occur in the game.
/// An example is the valve "mission_failure", that when fired, will run callbacks to handle mission failure.
/// </summary>
class CValve
{
private:
	const char* m_Name;
	int m_Value;
	ValveType m_Type;
};