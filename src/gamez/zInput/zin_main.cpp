#include "gamez/zInput/zinput.h"
#include "gamez/zMath/zmath.h"

const float c_DefaultDelta = 0.03333334f;
const int c_MaxPads = 2;

float pad_dt = 0.0f;

bool CInput::m_init = false;
CPad** CInput::m_pads = NULL;
CKeyboard* CInput::m_keyboard = NULL;

void CInput::Init()
{
	OpenPadIO();
	// TODO:
	// Add replacement IOP function for Windows/Linux
	// InitKeyreadStuff();
	// CInput::m_keyboard = new CKeyboard();
	m_init = true;
}

int CInput::OpenPadIO()
{
	return -1;
}

void CInput::ClosePadIO()
{
	for (int i = 0; i < c_MaxPads; i++)
	{
		DeletePad(i);
	}
}

void CInput::Tick(float delta)
{
	if (m_keyboard != NULL)
	{
		// m_keyboard->Tick(delta);
	}

	for (int pad = 0; pad < c_MaxPads; pad++)
	{
		if (m_pads[pad] != NULL)
		{
			m_pads[pad]->Tick(delta);
		}
	}
}

CPad* CInput::CreatePad(int slot)
{
	CPad* pad;

	if (slot < 2)
	{
		pad = m_pads[slot];

		if (pad == NULL)
		{
			pad = new CPad(slot, 0);
		}

		m_pads[slot] = pad;
		
		if (!pad->IsOpen() && m_pads[slot] != NULL)
		{
			// delete pad;
			m_pads = NULL;
		}
	}
	else
	{
		return NULL;
	}

	return pad;
}

void CInput::DeletePad(int slot)
{
	CPad* pad = m_pads[slot];

	if (slot < 2 && pad != NULL)
	{
		// delete pad;
		m_pads[slot] = NULL;
	}
}

void CInput::Flush()
{
	for (int pad = 0; pad < c_MaxPads; pad++)
	{
		if (m_pads[pad] != NULL)
		{
			m_pads[pad]->Flush();
		}
	}
}

void CInput::Uninit()
{
	ClosePadIO();
	m_init = false;
}

CPad::CPad(int port, int slot)
{
	this->port = port;
	this->slot = slot;

	if (port == 0 || port == 1)
	{

	}
}

void CPad::Flush()
{
	rightStickVelX = 0.0f;
	rightStickVelY = 0.0f;
	leftStickVelX = 0.0f;
	leftStickVelY = 0.0f;
	Tick(c_DefaultDelta);
}

void CPad::Tick(float delta)
{
	pad_dt = delta;
}

bool CPad::IsOpen()
{
	return open != 0;
}