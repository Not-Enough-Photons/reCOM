#include "zGame/zgame.h"
#include "zUtil/util_main.h"
#include "zVideo/zvid_main.h"

void process_arguments(int argc, char** argv)
{

}

void game_main(int argc, char** argv)
{
	process_arguments(argc, argv);

	zUtilInit("ftslog.txt");

	theGame.StartEngine();
	theGame.StartPlay();

	while (true)
	{
		theGame.Tick(zVid.frameTime);
	}
}