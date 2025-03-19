#include "zseal.h"

void CZSealBody::InitLookAnims()
{
    
}

bool CSealCtrlAi::RegisterCommands()
{
	ZAnim.AddCmd("ai::ACTION", CTAction::Parse, NULL, CTAction::Tick, NULL);
	ZAnim.AddCmd("ai::COMM", CTComm::Parse, NULL, CTComm::Tick, NULL);
	ZAnim.AddCmd("ai::DEBUG", CTDebug::Parse, NULL, CTDebug::Tick, NULL);
	ZAnim.AddCmd("ai::DOOR", CTDoor::Parse, CTDoor::Begin, CTDoor::Tick, CTDoor::End);
	ZAnim.AddCmd("ai::EVENT", CTEvent::Parse, CTEvent::Begin, CTEvent::Tick, NULL);
	ZAnim.AddCmd("ai::FIREMODE", CTFireMode::Parse, CTFireMode::Begin, CTFireMode::Tick, NULL);
	ZAnim.AddCmd("ai::FIREWEAPON", CTFireWeapon::Parse, CTFireWeapon::Begin, CTFireWeapon::Tick, NULL);
	ZAnim.AddCmd("ai::GOTO", CTGoto::Parse, CTGoto::Begin, CTGoto::Tick, CTGoto::End);
	ZAnim.AddCmd("ai::HOLD", CTHold::Parse, CTHold::Begin, CTHold::Tick, CTHold::End);
	ZAnim.AddCmd("ai::INSTATE", CTInState::Parse, NULL, CTInState::Tick, NULL);
	ZAnim.AddCmd("ai::INVIEW", CTInView::Parse, NULL, CTInView::Tick, NULL);
	ZAnim.AddCmd("ai::LOOKAT", CTLookAt::Parse, CTLookAt::Begin, CTLookAt::Tick, NULL);
	ZAnim.AddCmd("ai::MACRO", CTMacro::Parse, CTMacro::Begin, CTMacro::Tick, NULL);
	ZAnim.AddCmd("ai::MAP", CTMap::Parse, NULL, CTMap::Tick, NULL);
	ZAnim.AddCmd("ai::MOVE", CTMove::Parse, CTMove::Begin, CTMove::Tick, CTMove::End);
	ZAnim.AddCmd("ai::PAINT", CTPaint::Parse, NULL, CTPaint::Tick, NULL);
	ZAnim.AddCmd("ai::PARAM", CTParam::Parse, NULL, CTParam::Tick, NULL);
	ZAnim.AddCmd("ai::PURSUE", CTPursue::Parse, CTPursue::Begin, CTPursue::Tick, CTPursue::End);
	ZAnim.AddCmd("ai::ANIMATE", CTPlay::Parse, CTPlay::Begin, CTPlay::Tick, CTPlay::End);
	ZAnim.AddCmd("ai::INRANGE", CTRange::Parse, NULL, CTRange::Tick, NULL);
	ZAnim.AddCmd("ai::INREGION", CTRegion::Parse, NULL, CTRegion::Tick, NULL);
	ZAnim.AddCmd("ai::SELECT", CTSelect::Parse, NULL, CTSelect::Tick, NULL);
	ZAnim.AddCmd("ai::SETMODE", CTSetMode::Parse, NULL, CTSetMode::Tick, NULL);
	ZAnim.AddCmd("ai::SETANIMSET", CTSetAnimSet::Parse, NULL, CTSetAnimSet::Tick, NULL);
	ZAnim.AddCmd("ai::SIGNAL", CTSignal::Parse, NULL, CTSignal::Tick, NULL);
	ZAnim.AddCmd("ai::SOUND", CTSound::Parse, CTSound::Begin, CTSound::Tick, CTSound::End);
	ZAnim.AddCmd("ai::STANCE", CTStance::Parse, CTStance::Begin, CTStance::Tick, CTStance::End);
	ZAnim.AddCmd("ai::STATE", CTState::Parse, NULL, CTState::Tick, NULL);
	ZAnim.AddCmd("ai::STOPALL", CTStopAll::Parse, NULL, CTStopAll::Tick, NULL);
	ZAnim.AddCmd("ai::SPECIAL", CTSpecial::Parse, CTSpecial::Begin, CTSpecial::Tick, CTSpecial::End);
	ZAnim.AddCmd("ai::TEAM", CTTeam::Parse, NULL, CTTeam::Tick, NULL);
	ZAnim.AddCmd("ai::VALVE", CTValve::Parse, NULL, CTValve::Tick, NULL);
	ZAnim.AddCmd("ai::WAIT", CTWait::Parse, CTWait::Begin, CTValve::Tick, NULL);

    return true;
}

void CZSealBody::GetMaxZMotion(f32& min, f32& max)
{
	AnimSet* set = m_animset;

	if (m_desiredState == SEAL_STATE::stateClimbLadder)
	{
		min = set->m_aparams.m_ladder_updn;
		max = set->m_aparams.m_ladder_updn;
	}
	else if (m_desiredState == SEAL_STATE::stateProne)
	{
		min = set->m_aparams.m_prone_max_back;
		max = set->m_aparams.m_prone_max_fwd;
	}
	else if (m_desiredState == SEAL_STATE::stateCrouch)
	{
		min = set->m_aparams.m_crouch_max_back;
		max = set->m_aparams.m_crouch_max_fwd;
	}
	else if (m_desiredState == SEAL_STATE::stateStand)
	{
		min = set->m_aparams.m_stand_max_back;
		max = set->m_aparams.m_stand_max_fwd;
	}
	else
	{
		min = 0.0f;
		max = 0.0f;
	}
}