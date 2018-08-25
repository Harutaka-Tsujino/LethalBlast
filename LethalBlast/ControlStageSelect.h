#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"
#include"ControlStageSelect.h"

enum STAGE
{
	CAVE_STAGE,
	RUIN_STAGE,
	FOREST_STAGE,
	STAGE_MAX
};

void ControlStageSelect(SCENE* pScene, ImagesCustomVertex* pStageSelectPortals, int* pSelectedStage);

void CalcurateVectByPoints(Vect* dest, double pointOPosX, double pointOPosY, double pointDestPosX, double pointDestPosY);

bool CheckRotatedRectsCollision(CustomVertex* rectA, CustomVertex* rectB);
