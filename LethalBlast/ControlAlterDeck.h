#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"

enum SKILL_COST
{
	VOID_SKILL,

	MPプラス２,

	被ダメ２５％カット,

	２５％回復,

	次の与ダメ１．３倍,

	与ダメ１．１倍,

	追撃２５％,

	今１．４倍次０．８倍,

	SKILL_MAX,
};

void ControlAlterDeck(SCENE* scene, WordData* pPlayerWordDatas, PlayerDeck* pPlayerDecks, ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
	ImagesCustomVertex* pSkillInfo, CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	PLAYERTYPE* playerType, int* pDeckNumToAlter, bool* clickedWord, bool* pChoiceWordData);
