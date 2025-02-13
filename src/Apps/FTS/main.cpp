#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>

#include "gamez/zGame/zgame.h"
#include "gamez/zSound/zsnd.h"
#include "gamez/zVideo/zvid.h"
#include "imgui/imgui_impl_sdlrenderer3.h"

bool LoadWorld(const char* name);

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

	while (true)
	{
		theGame.Tick(zVid.frameTime);
	}
}