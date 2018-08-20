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

	WEAPON_MASTER_ACTION_TEX_MAX,
};

void RenderWeaponMasterAction(WeaponMasterWordData* pWeaponMasterWordData, WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionWords,
	ImagesCustomVertex* pWeaponMasterDeckVerticies, int pPage);

void PageTransitionForWeaponMasterWordLists(ImagesCustomVertex* pWeaponMasterDeckVerticies, int wordLists);
