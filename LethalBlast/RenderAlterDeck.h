#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

enum ALTER_DECK_TEX
{
	EXIT_ALTER_TEX,
	ALTER_BACK_1_TEX,
	ALTER_BACK_2_TEX,
	ALTER_BACK_3_TEX,
	ALTER_CLICKED_EFFECT_TEX,
	UNDER_ALTER_WORD_BOARD_TEX,
	DECK_ALTER_TAG_TEX,
	ALTER_DECK_TEX_MAX
};

void RenderAlterDeck(ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
	CustomVertex* endDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	TEXTUREID* wordTexIds, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, int* pDeckNumToAlter, bool* clickedWord);
