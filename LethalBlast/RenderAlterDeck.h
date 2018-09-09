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
	DELETE_TEX,
	SLOT_1,
	SLOT_2,
	SLOT_3,
	SLOT_4,
	SLOT_5,
	SLOT_6,
	SLOT_7,
	WM_ALTER_BACK_1_TEX,
	WM_ALTER_BACK_2_TEX,
	WM_ALTER_BACK_3_TEX,
	ALTER_DECK_TEX_MAX
};

void RenderAlterDeck(ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex, ImagesCustomVertex* pSkillInfo,
	CustomVertex* endDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	TEXTUREID* wordTexIds, WordData* pPlayerWordDatas, Deck* pPlayerDecks, int* pDeckNumToAlter, bool* clickedWord, bool* pChoiceWordData);
