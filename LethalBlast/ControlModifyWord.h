#pragma once
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlModify(SCENE* scene, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	ImagesCustomVertex* pChoiseWordCollisionsVertex, CustomVertex* pWordDatasBackVertices, CustomVertex* pEndModifyVertices, CustomVertex* pBackgroundVertices,
	int* modifyWordBox, ImagesCustomVertex* modifyBoxVertices, CustomVertex* decideModify, bool* clickedWord);
