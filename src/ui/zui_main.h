#pragma once
#include "ai/ai_main.h";

namespace zdb
{
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
		static void InitializeCommandEntry(zdb::SealCommand command);
		static const char* GetTeamName(zdb::FireTeam team);
		static const char* GetRawCommandType(zdb::SealCommand command);
		static const char* GetCommandDisplayName(zdb::SealCommand command);
		static const char* GetProperRegroupDisplay(zdb::SealCommand command);
		static const char* GetCommandDescription(zdb::SealCommand command);
		static void SendUIMessage(float param_1, const char* message, char* messagePtr, void* param_4, void* param_5, int param_6);
	};
}