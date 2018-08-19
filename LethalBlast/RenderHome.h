#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

enum HOME_TEX
{
	ALTER_PORTAL_TEX,
	CHARA_CHOICE_PORTAL_TEX,
	MODIFY_PORTAL_TEX,
	QUEST_PORTAL_TEX,
	HOME_TEX_MAX
};

void RenderHome(CustomVertex* deckAlterPortal, CustomVertex* modifyWordPortal, CustomVertex* mainGamePortal, CustomVertex* charaChoicePortal);
