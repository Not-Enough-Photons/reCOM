#include "zseal.h"

_zanim_cmd_hdr* CTAction::Parse(_zrdr* reader)
{
	// Look inside the "action" tag to find a string value
	/*
	* action 
	(
		state (YOUR_STATE_HERE)
		auto_return (true)
	)
	*/
	const char* action = zrdr_findstring(reader, "action");
	unsigned int state = zrdr_finduint(reader, "state", &state, 1);
	bool auto_return = zrdr_findbool(reader, "auto_return", &auto_return);

	if (action != NULL)
	{

	}

	return NULL;
}

bool CTAction::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTComm::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTComm::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTDebug::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTDebug::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTDoor::Begin(_zanim_cmd_hdr* header)
{

}

void CTDoor::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTDoor::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTDoor::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTEvent::Begin(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTEvent::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTEvent::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTFireMode::Begin(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTFireMode::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTFireMode::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTFireWeapon::Begin(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTFireWeapon::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTFireWeapon::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTGoto::Begin(_zanim_cmd_hdr* header)
{

}

void CTGoto::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTGoto::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTGoto::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTHold::Begin(_zanim_cmd_hdr* header)
{

}

void CTHold::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTHold::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTHold::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTInState::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTInState::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTInView::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTInView::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTLookAt::Begin(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTLookAt::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTLookAt::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTMacro::Begin(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTMacro::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTMacro::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTMap::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTMap::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTMove::Begin(_zanim_cmd_hdr* header)
{

}

void CTMove::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTMove::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTMove::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTPaint::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTPaint::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTParam::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTParam::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTPlay::Begin(_zanim_cmd_hdr* header)
{

}

void CTPlay::Create(int count, unsigned int* param_2, float param_3, float param_4)
{

}

void CTPlay::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTPlay::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTPlay::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTPursue::Begin(_zanim_cmd_hdr* header)
{

}

void CTPursue::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTPursue::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTPursue::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTRange::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTRange::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTRegion::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTRegion::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTSelect::Begin(_zanim_cmd_hdr* header)
{

}

void CTSelect::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTSelect::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTSelect::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTSetAnimSet::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTSetAnimSet::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTSetMode::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTSetMode::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

AiSig CTSignal::GetSignalByName(const char* signal)
{
	return AiSig::AISIG_UNKNOWN;
}

_zanim_cmd_hdr* CTSignal::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTSignal::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTSound::Begin(_zanim_cmd_hdr* header)
{

}

void CTSound::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTSound::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTSound::Tick(_zanim_cmd_hdr* header, float* delta)
{
	return false;
}

void CTSpecial::Begin(_zanim_cmd_hdr* header)
{

}

void CTSpecial::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTSpecial::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTSpecial::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTStance::Begin(_zanim_cmd_hdr* header)
{

}

void CTStance::End(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTStance::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTStance::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTState::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTState::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTStopAll::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTStopAll::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTTeam::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTTeam::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

_zanim_cmd_hdr* CTValve::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTValve::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}

void CTWait::Begin(_zanim_cmd_hdr* header)
{

}

_zanim_cmd_hdr* CTWait::Parse(_zrdr* reader)
{
	return NULL;
}

bool CTWait::Tick(_zanim_cmd_hdr* header, float* dT)
{
	return false;
}