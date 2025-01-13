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
	for (int i = 0; i < 2; i++)
	{
		DeletePad(i);
	}
}

void CInput::Tick(f32 delta)
{
	if (m_keyboard != NULL)
	{
		// m_keyboard->Tick(delta);
	}

	for (s32 pad = 0; pad < 2; pad++)
	{
		if (m_pads[pad] != NULL)
		{
			m_pads[pad]->Tick(delta);
		}
	}
}

CPad* CInput::CreatePad(s32 slot)
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

void CInput::DeletePad(s32 slot)
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
	for (s32 pad = 0; pad < c_MaxPads; pad++)
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

CPad::CPad(s32 port, s32 slot)
{
	if (port == 0 || port == 1)
	{

	}
}

void CPad::Flush()
{
	Tick(c_DefaultDelta);
}

void CPad::Tick(f32 delta)
{
	pad_dt = delta;
}

bool CPad::IsOpen()
{
	return m_open != 0;
}