#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlAlterDeck(SCENE* scene, WordData* pMagicKnightWordDatas, ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
	CustomVertex* endDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices, int* pDeckNumToAlter);
