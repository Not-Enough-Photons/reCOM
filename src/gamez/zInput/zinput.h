#pragma once
class CInput;
class CPad;
class CKeyboard;

float pad_dt;

enum KEY_STATE
{
	KEY_UP,
	KEY_FALLING,
	KEY_DOWN,
	KEY_RISING
};

void InitKeyreadStuff();

class CInput
{
public:
	// Disallow construction of a purely static class
	CInput() = delete;

	static void Init();
	static void Uninit();
	static void Tick(float delta);
	static CPad* CreatePad(int slot);
	static void DeletePad(int slot);
	static void Flush();
	static int OpenPadIO();
	static void ClosePadIO();
	static bool m_init;

	static CPad** m_pads;
	static CKeyboard* m_keyboard;
};

class CPad
{
public:
	CPad(int port, int slot);
	~CPad();

	void Flush();
	void Tick(float delta);
	bool IsOpen();
private:
	int port;
	int slot;
	int actuator;
	void* alignBuf;

	int open;

	float leftStickVelX;
	float leftStickVelY;
	float rightStickVelX;
	float rightStickVelY;
};

class CKeyboard
{
public:
	CKeyboard();
	~CKeyboard();

	void Tick(float delta);
};