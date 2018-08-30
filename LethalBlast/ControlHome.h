#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlWeaponMasterAction.h"

void ControlHome(SCENE* scene, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	WeaponMasterWordData* pWeaponMAsterWordDatas, WeaponMasterDeck* pWeaponMasterDecks,
	CustomVertex* pDeckAlterPortal, CustomVertex* pModifyWordPortal, CustomVertex* pMainGamePortal, 
	CustomVertex* pCharaChoicePortal, TEXTUREID* wordTexIds, TEXTUREID* weaponMasterWordIds, PLAYERTYPE* playerType,
	bool* initializedTex);

void LoadMagicKnightWordDatas(WordData* pMagicKnightWordDatas);

void LoadDeck(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, const char* deckFilePath, int deckNum);

void LoadWeaponMasterWordDatas(WeaponMasterWordData* pWeaponMasterWordDatas);

void WeaponMasterLoadDeck(WeaponMasterWordData* pWeaponMasterWordDatas, WeaponMasterDeck* pWeaponMasterDeck, const char* deckFilePath, int deckNum);

void LordTextureWeaponMaster(TEXTUREID* pWmFontIds);
