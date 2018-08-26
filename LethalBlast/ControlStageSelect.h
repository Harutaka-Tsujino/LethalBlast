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

#define FLOOR_MAX 10

typedef struct
{
	int m_enemyId[FLOOR_MAX];
	int m_MKDropId[FLOOR_MAX];
	int m_WMDropId[FLOOR_MAX];
	bool m_clear[FLOOR_MAX];
}STAGE_DATE;

void ControlStageSelect(SCENE* pScene, ImagesCustomVertex* pStageSelectPortals, int* pSelectedStage, CustomVertex* pBackPortal);

void CalcurateVectByPoints(Vect* dest, double pointOPosX, double pointOPosY, double pointDestPosX, double pointDestPosY);

bool CheckRotatedRectsCollision(CustomVertex* rectA, CustomVertex* rectB);
