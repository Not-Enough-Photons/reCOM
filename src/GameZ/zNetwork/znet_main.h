#include "valve/valve_main.h"

class CZNetwork;
class CZOnlineLobby;
class CZNetGame;

static CZNetwork theNetwork;
static CZOnlineLobby theLobby;

void PTT_HeartbeatPrepare();

class CZNetwork
{
public:
	float zNetGetTime();
	void zNetUpdate();
	void zNetRequestObjectPrivateOwnership()
};

class CZNetGame
{
public:
	void ResetScores();
	bool OnSealTeam();
private:
	CValve* mpGameOverValve;
};

class CZNetVoice
{
public:
	void PreTick();
};

class CZOnlineLobby
{
public:
	void Init();
private:
	bool started;
	CValve* onlineStatusValve;
};