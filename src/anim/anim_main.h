#pragma once
#include "math/zmath_main.h"
#include "node/node_main.h"

static int InitAnimScriptKeywords();
static void ParseAnimCodeKeyword(void* ptr, char* token, int param_3, void(*func), bool(*condition), int param_6);

static bool CmdAddNode(zdb::CNode node);
static bool CmdRemoveNode(zdb::CNode node);