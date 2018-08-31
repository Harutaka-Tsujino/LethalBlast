#pragma once


enum STAGE
{
	CAVE_STAGE,
	RUIN_STAGE,
	FOREST_STAGE,
	STAGE_MAX
};

#define FLOOR_MAX 10
#define FLOOR_DROP_MAX 5

typedef struct
{
	int m_mKDropId[FLOOR_DROP_MAX];
	int m_wMDropId[FLOOR_DROP_MAX];
}DropWord;

typedef struct
{
	bool m_mKClear;
	bool m_wMClear;
}Clear;

typedef struct
{
	int m_enemyId[FLOOR_MAX];
	DropWord m_dropWord[FLOOR_MAX];
	Clear m_clear[FLOOR_MAX];
}StageDate;

#define FORSEST_FLOOR_MAX 4

#include"ControlBattle.h"

void ControlStageSelect(SCENE* pScene, ImagesCustomVertex* pStageSelectPortals, int* pSelectedStage, CustomVertex* pBackPortal, StageDate* pStageData, EnemyST* pEnemyData);

void CalcurateVectByPoints(Vect* dest, double pointOPosX, double pointOPosY, double pointDestPosX, double pointDestPosY);

bool CheckRotatedRectsCollision(CustomVertex* rectA, CustomVertex* rectB);

void InitStageData(StageDate* pStageData, const char* filePath, int floorMax);

void InitEnemyData(EnemyST* pEnemyData);
