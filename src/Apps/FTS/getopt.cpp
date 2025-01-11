#include "gamez/zAnim/zanim.h"
#include "gamez/zGame/zgame.h"

_options gopt;

void process_arguments(int argc, char** argv)
{
	zSys.cdSounds = false;
	CZAnimMain::m_LoadFromZAR = true;
}