#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"

enum SKILL_COST
{
	VOID_SKILL,

	MP_PLUS_2,

	REDUSE_DAMEGE_25PAR,

	HEAL_HP_25PAR,

	NEXT_TURN_DAMEGE_1p3,

	ATTACK_1p1,

	PURSUIT_25PAR,

	CURRENT_1p4_NEXT_0p8,

	SKILL_COST_MAX,
};

void ControlAlterDeck(SCENE* scene, WordData* pPlayerWordDatas, Deck* pPlayerDecks, ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
	ImagesCustomVertex* pSkillInfo, CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	PLAYERTYPE* playerType, int* pDeckNumToAlter, bool* clickedWord, bool* pChoiceWordData);
