#include "zgame.h"
#include "util/util_main.h"

void game_main()
{
	zUtilInit("ftslog.txt");
	COurGame::StartEngine();
	CGame::StartPlay();

	while (true)
	{
		CGame::Tick();
	}
}