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
	PAGE_1_TEX,
	PAGE_2_TEX,
	PAGE_3_TEX,
	PAGE_4_TEX,
	PAGE_5_TEX,
	HOME_BACK_1_TEX,
	HOME_BACK_01_TEX,
	HOME_BACK_02_TEX,
	HOME_BACK_03_TEX,
	HOME_BACK_04_TEX,
	HOME_BACK_05_TEX,
	HOME_BACK_06_TEX,
	HOME_TEX_MAX
};

void RenderHome(SCENE* scene,CustomVertex* deckAlterPortal, CustomVertex* modifyWordPortal, CustomVertex* mainGamePortal, CustomVertex* charaChoicePortal, TEXTUREID* wordTexIds);
