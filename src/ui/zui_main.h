#pragma once
namespace zdb
{
	enum CommandDescType
	{
		DESC_BASE,
		DESC_THROW_ITEM,
		DESC_FIRE_AT_WILL,
		DESC_FOLLOW,
		DESC_HOLD_POSITION,
		DESC_HOLD_FIRE,
		DESC_REGROUP,
		DESC_HOSTAGE_FOLLOW,
		DESC_RUN_TO,
		DESC_MOVE_TO,
		DESC_STEALTH_TO,
		DESC_ATTACK_TO,
		DESC_ESCORT_TO,
		DESC_COVER_TARGET,
		DESC_LASER,
		DESC_BREACH,
		DESC_GET_DOWN,
		DESC_PULL_OUT,
		DESC_OVERWATCH,
		DESC_EXTRACT_HOSTAGE,
		DESC_REMOVE_KILLS
	};

	class C2D
	{

	};

	class CPlainBmp : public C2D
	{

	};

	class C2DMessageString : public C2D
	{

	};

	class CZUI
	{
	public:
		static const char* GetCommandDescription(CommandDescType desc);
		static void SendUIMessage(float param_1, const char* message, char* messagePtr, void* param_4, void* param_5, int param_6);
	};
}