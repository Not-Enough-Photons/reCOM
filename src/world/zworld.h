#pragma once
namespace zdb
{
	class CWorld
	{
	public:
		void GetTexHandle();
	};

	class CWind
	{
	public:
		static void RegisterAnimCommands();
		void CmdParseWind();
	};
}