#include "gamez/zGame/zgame.h"
#include "gamez/zSound/zsnd.h"
#include "gamez/zVideo/zvid.h"

int main(int argc, char** argv)
{
	process_arguments(argc, argv);
	zSysInit();

	if (postinit)
	{
		CSnd::Close();
		zSysPostInit();
		CSnd::UIOpen();
	}

	if (dumpLog)
	{
		COutput::DumpLog("ftslog.txt");
	}

	char* log = NULL;

	if (gopt.doLog != false)
	{
		log = "ftslog.txt";
	}

	zUtilInit(log);

	theGame.StartEngine();
	theGame.StartPlay();

	do
	{
		theGame.Tick(zVid.frameTime);
	} 
	while (true);

	return 0;
}