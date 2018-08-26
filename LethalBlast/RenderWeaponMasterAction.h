#pragma once
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlWeaponMasterAction.h"

#define WORD_LISTS_DISPLAY_WIDTH
#define WORD_LISTS_DISPLAY_HEIGHT

enum WEAPON_MASTER_ACTION_TEX
{
	WEAPON_MASTER_PAGE_CURSOL_TEX,

	WEAPON_MASTER_FONT_TEX,

	WEAPON_MASTER_FRAME_TEX,

	LIST_BG_TEX,

	WEAPON_MASTER_ACTION_TEX_MAX,
};

enum WEAPON_MASTER_ACTION_FONT
{
	PAGE_FONT,

	PAGE_FONT_MAX,

	FONT_MAX,
};

void RenderWeaponMasterAction(ImagesCustomVertex* pWeaponMasterDeckVerticies, ImagesCustomVertex* pWeaponMasterAction,
	WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas, int pPage, TEXTUREID* pWmFontIds);
