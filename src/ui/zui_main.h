#pragma once
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
		void SendUIMessage(float time, const char* message, char* messagePtr, void* param_4, void* param_5, int param_6);
	};
}