#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"

void ControlHome(SCENE* scene, WordData* pMagicKnightWordDatas, Deck* pMagicKnightDecks,
	WordData* pWeaponMAsterWordDatas, Deck* pWeaponMasterDecks,
	CustomVertex* pDeckAlterPortal, CustomVertex* pModifyWordPortal, CustomVertex* pMainGamePortal,
	CustomVertex* pCharaChoicePortal, TEXTUREID* mKWordTex, TEXTUREID* wMWordTex, PLAYERTYPE* playerType,
	bool* initializedTex);

void LoadWordDatas(WordData* pMagicKnightWordDatas, const char *pFilePath, int wordDataMax);

void LoadDeck(WordData* pMagicKnightWordDatas, Deck* pMagicKnightDecks, const char* deckFilePath, int deckNum);

void LordTextureWeaponMaster(TEXTUREID* pWmFontIds);
