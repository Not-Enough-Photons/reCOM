#include "seal.h"

#include "gamez/zAnim/anim_main.h"

bool CSealCtrlAi::RegisterCommands()
{
	unsigned int ai_cmdid = 0;

	ai_cmdid = ZAnim.AddCmd("ai::ACTION", CTAction::Parse, NULL, CTAction::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::COMM", CTComm::Parse, NULL, CTComm::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::DEBUG", CTDebug::Parse, NULL, CTDebug::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::DOOR", CTDoor::Parse, CTDoor::Begin, CTDoor::Tick, CTDoor::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::EVENT", CTEvent::Parse, CTEvent::Begin, CTEvent::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::FIREMODE", CTFireMode::Parse, CTFireMode::Begin, CTFireMode::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::FIREWEAPON", CTFireWeapon::Parse, CTFireWeapon::Begin, CTFireWeapon::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::GOTO", CTGoto::Parse, CTGoto::Begin, CTGoto::Tick, CTGoto::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::HOLD", CTHold::Parse, CTHold::Begin, CTHold::Tick, CTHold::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::INSTATE", CTInState::Parse, NULL, CTInState::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::INVIEW", CTInView::Parse, NULL, CTInView::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::LOOKAT", CTLookAt::Parse, CTLookAt::Begin, CTLookAt::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::MACRO", CTMacro::Parse, CTMacro::Begin, CTMacro::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::MAP", CTMap::Parse, NULL, CTMap::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::MOVE", CTMove::Parse, CTMove::Begin, CTMove::Tick, CTMove::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::PAINT", CTPaint::Parse, NULL, CTPaint::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::PARAM", CTParam::Parse, NULL, CTParam::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::PURSUE", CTPursue::Parse, CTPursue::Begin, CTPursue::Tick, CTPursue::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::ANIMATE", CTPlay::Parse, CTPlay::Begin, CTPlay::Tick, CTPlay::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::INRANGE", CTRange::Parse, NULL, CTRange::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::INREGION", CTRegion::Parse, NULL, CTRegion::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::SELECT", CTSelect::Parse, NULL, CTSelect::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::SETMODE", CTSetMode::Parse, NULL, CTSetMode::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::SETANIMSET", CTSetAnimSet::Parse, NULL, CTSetAnimSet::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::SIGNAL", CTSignal::Parse, NULL, CTSignal::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::SOUND", CTSound::Parse, CTSound::Begin, CTSound::Tick, CTSound::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::STANCE", CTStance::Parse, CTStance::Begin, CTStance::Tick, CTStance::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::STATE", CTState::Parse, NULL, CTState::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::STOPALL", CTStopAll::Parse, NULL, CTStopAll::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::SPECIAL", CTSpecial::Parse, CTSpecial::Begin, CTSpecial::Tick, CTSpecial::End) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::TEAM", CTTeam::Parse, NULL, CTTeam::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::VALVE", CTValve::Parse, NULL, CTValve::Tick, NULL) & 0xffff;
	ai_cmdid = ZAnim.AddCmd("ai::WAIT", CTWait::Parse, CTWait::Begin, CTValve::Tick, NULL) & 0xffff;

	return true;
}