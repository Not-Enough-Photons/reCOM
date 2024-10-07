#pragma once
#include "ai/ai_main.h";

namespace zdb
{
	enum TextColor
	{
		WHITE,
		YELLOW,
		BLUE,
		ORANGE,
		RED,
		PURPLE
	};

	enum TextAlignment
	{
		LEFT,
		CENTER,
		RIGHT
	};

	class C2D
	{

	};

	class C2DPoly : public C2D
	{
	public:
		C2DPoly();
	};

	class C2DBitmap : public C2D
	{
	public:
		C2DBitmap();
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
		static void SendUIMessage(int count, int* ptr, const char* message, TextColor color, TextAlignment alignment);
	};
}