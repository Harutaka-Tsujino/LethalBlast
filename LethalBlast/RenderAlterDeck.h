#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void RenderAlterDeck(ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
	CustomVertex* endDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	TEXTUREID* wordTexIds, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, int* pDeckNumToAlter);
