#include "zGame/zgame.h"
#include "zUtil/util_main.h"

void process_arguments(int argc, char** argv)
{

}

void game_main(int argc, char** argv)
{
	process_arguments(argc, argv);
	zUtilInit("ftslog.txt");
	COurGame::StartEngine();
	CGame::StartPlay();

	while (true)
	{
		CGame::Tick();
	}
}