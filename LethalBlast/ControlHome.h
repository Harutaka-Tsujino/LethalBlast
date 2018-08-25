#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlHome(SCENE* scene, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	CustomVertex* deckAlterPortal, CustomVertex* modifyWordPortal, CustomVertex* mainGamePortal, CustomVertex* charaChoicePortal, TEXTUREID* wordTexIds);

void LoadMagicKnightWordDatas(WordData* pMagicKnightWordDatas);

void LoadDeck(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, const char* deckFilePath, int deckNum);
