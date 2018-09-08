#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"

enum ALTER_DECK_TEX
{
	EXIT_ALTER_TEX,
	ALTER_BACK_1_TEX,
	ALTER_BACK_2_TEX,
	ALTER_BACK_3_TEX,
	ALTER_CLICKED_EFFECT_TEX,
	UNDER_ALTER_WORD_BOARD_TEX,
	DECK_ALTER_TAG_TEX,
	CURSOL_TEX,
	WM_ALTER_BACK_1_TEX,
	WM_ALTER_BACK_2_TEX,
	WM_ALTER_BACK_3_TEX,
	ALTER_DECK_TEX_MAX
};

void RenderAlterDeck(ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex, ImagesCustomVertex* pSkillInfo,
	CustomVertex* endDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	TEXTUREID* wordTexIds, WordData* pPlayerWordDatas, PlayerDeck* pPlayerDecks, int* pDeckNumToAlter, bool* clickedWord, bool* pChoiceWordData);
