#include "fts.h"
#include "gamez/zGame/zgame.h"

void CCinematicState::SetMovie(const char* moviename)
{
	if (m_moviename != NULL)
	{
		free(m_moviename);
	}

	m_moviename = strdup(moviename);
}