class CZNetwork;
class CZOnlineLobby;

static CZNetwork theNetwork;
static CZOnlineLobby theLobby;

void PTT_HeartbeatPrepare();

class CZNetwork
{
public:
	void zNetUpdate();
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