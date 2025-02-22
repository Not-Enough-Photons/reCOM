#include "gamez/zGame/zgame.h"
#include "gamez/zSound/zsnd.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zVideo/zvid.h"

#include "SDL3/SDL_log.h"

bool LoadWorld(const char* name);

int main(int argc, char** argv)
{
	process_arguments(argc, argv);
	zSysInit();

	return 0;
	
	zSysPostInit();
	
	SDL_Log("%s selected for GameZ.", gamez_GamePath);

	if (dumpLog)
	{
		COutput::DumpLog("ftslog.txt");
	}

	char* log = NULL;

	if (gopt.doLog)
	{
		log = "ftslog.txt";
	}

	zUtilInit(log);

	theGame.StartEngine();
	theGame.StartPlay();

	while (true)
	{
		theGame.Tick(zVid.frameTime);
	}
}