#include "gamez/zGame/zgame.h"
#include "gamez/zSound/zsnd.h"
#include "gamez/zSystem/zsys.h"
#include "gamez/zVideo/zvid.h"

#include "SDL3/SDL_log.h"

bool LoadWorld(const char* name);
char* SetDatabase(const char* db);

int main(int argc, char** argv)
{
	process_arguments(argc, argv);
	zSysInit();
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

	SetDatabase("ui");
	
	theGame.StartEngine();
	theGame.StartPlay();

	u64 current_t = 0;
	u64 last_t = 0;
	
	while (true)
	{
		current_t = SDL_GetTicks();

		zVid.frameTime = (f32)(current_t - last_t) / 1000.0f;
		
		if (zVid.frameTime >= 0.025f)
		{
			zVid.frameTime = 0.025f;
		}
		
		theGame.Tick(zVid.frameTime);

		last_t = SDL_GetTicks();
	}
	
}