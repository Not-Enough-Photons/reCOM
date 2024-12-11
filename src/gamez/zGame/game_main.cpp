#include "zgame.h"

#include "gamez/zUtil/zutil.h"
#include "gamez/zVideo/zvid.h"

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