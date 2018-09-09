#define _CRT_SECURE_NO_WARNINGS
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"
#include"ControlStageSelect.h"

void ControlStageSelect(SCENE* pScene, ImagesCustomVertex* pStageSelectPortals, int* pSelectedStage,CustomVertex* pBackPortal)
{
	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		frameCount = 0;
	}

	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	const int MOVE_PORTAL_FRAME = 25;

	ZeroMemory(pStageSelectPortals, sizeof(ImagesCustomVertex)*STAGE_MAX);

	if (frameCount >= MOVE_PORTAL_FRAME / 3 * 1)
	{
		CustomImageVerticies(pStageSelectPortals[ì¥åA].ImageVertex, (DISPLAY_WIDTH / 6.f) * 1,
			(DISPLAY_HEIGHT / 2.f),
			DISPLAY_WIDTH / 6.f, DISPLAY_HEIGHT / 2.f/*, GetColor(255, 18, 18, 18)*/);
	}

	if (frameCount >= MOVE_PORTAL_FRAME / 3 * 2)
	{
		CustomImageVerticies(pStageSelectPortals[à‚ê’].ImageVertex, (DISPLAY_WIDTH / 6.f) * 3 ,
			(DISPLAY_HEIGHT / 2.f),
			DISPLAY_WIDTH / 6.f, DISPLAY_HEIGHT / 2.f/*, 0xFFEA0D0D*/);
	}

	if (frameCount >= MOVE_PORTAL_FRAME / 3 * 3)
	{
		CustomImageVerticies(pStageSelectPortals[êX].ImageVertex, (DISPLAY_WIDTH / 6.f) * 5 ,
			(DISPLAY_HEIGHT / 2.f),
			DISPLAY_WIDTH / 6.f, DISPLAY_HEIGHT / 2.f/*, GetColor(255, 18, 18, 18)*/);
	}

	/*for (int stage = 0; stage < STAGE_MAX; ++stage)
	{
		RotateImageDeg(pStageSelectPortals[stage].ImageVertex, pStageSelectPortals[stage].ImageVertex, (float)(-15 + 30 * stage)*(2 - frameCount / (float)MOVE_PORTAL_FRAME));
	}*/

	if (frameCount < MOVE_PORTAL_FRAME)
	{
		frameCount++;
	}

	if (!g_mouseState.mousePush[LEFT_CLICK])
	{
		return;
	}

	if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pBackPortal))
	{
		*pScene = HOME_SCENE;

		frameCount = 0;

		return;
	}

	static bool initCave = false;

	if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[ì¥åA].ImageVertex))
	{
		*pSelectedStage = ì¥åA;
		*pScene = CHOSE_DECK_TO_BATTLE_SCENE;

		if (!initCave)
		{
			/*InitStageData(&pStageData[ì¥åA], "Files/Stage/ForestStage.csv", FORSEST_FLOOR_MAX);
			InitEnemyData(pEnemyData);*/

			initCave = true;
		}

		frameCount = 0;

		return;
	}

	static bool initForest = false;

	if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[êX].ImageVertex))
	{
		*pSelectedStage = êX;
		*pScene = CHOSE_DECK_TO_BATTLE_SCENE;

		if (!initForest)
		{
			/*InitStageData(&pStageData[êX], "Files/Stage/ForestStage.csv", FORSEST_FLOOR_MAX);
			InitEnemyData(pEnemyData)*/;

			initForest = true;
		}

		frameCount = 0;

		return;
	}

	static bool initRuin = false;

	if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[à‚ê’].ImageVertex))
	{
		*pSelectedStage = à‚ê’;
		*pScene = CHOSE_DECK_TO_BATTLE_SCENE;

		if (!initRuin)
		{
			/*InitStageData(&pStageData[à‚ê’], "Files/Stage/ForestStage.csv", FORSEST_FLOOR_MAX);
			InitEnemyData(pEnemyData);*/

			initForest = true;
		}

		frameCount = 0;

		return;
	}

	return;
}

bool CheckRotatedRectsCollision(CustomVertex* rectA, CustomVertex* rectB)
{
	Vect rectAVect;
	Vect rectBVect;

	for (int rectAVertex = 0; rectAVertex < RECT_VERTEX_NUM; ++rectAVertex)
	{
		bool includeRectAVertex[RECT_VERTEX_NUM] = { 0,0,0,0 };

		for (int rectBVertex = 0; rectBVertex < RECT_VERTEX_NUM; ++rectBVertex)
		{
			CalcurateVectByPoints(&rectAVect, rectB[rectBVertex].m_x, rectB[rectBVertex].m_y,
				rectA[rectAVertex].m_x, rectA[rectAVertex].m_y);

			CalcurateVectByPoints(&rectBVect, rectB[rectBVertex].m_x, rectB[rectBVertex].m_y,
				rectB[(rectBVertex + 1) % RECT_VERTEX_NUM].m_x,rectB[(rectBVertex + 1) % RECT_VERTEX_NUM].m_y);

			if (Cross(rectBVect, rectAVect) >= 0)
			{
				includeRectAVertex[rectBVertex] = true;
			}
		}

		for (int vertex = 0; vertex < RECT_VERTEX_NUM; ++vertex)
		{
			if (includeRectAVertex[vertex] == true)
			{
				if (vertex == RECT_VERTEX_NUM - 1)
				{
					return true;
				}
			}

			else
			{
				break;
			}
		}
	}

	for (int rectBVertex = 0; rectBVertex < RECT_VERTEX_NUM; ++rectBVertex)
	{
		bool includeRectBVertex[RECT_VERTEX_NUM] = { 0,0,0,0 };

		for (int rectAVertex = 0; rectAVertex < RECT_VERTEX_NUM; ++rectAVertex)
		{
			CalcurateVectByPoints(&rectBVect, rectA[rectAVertex].m_x, rectA[rectAVertex].m_y, 
				rectB[rectBVertex].m_x, rectB[rectBVertex].m_y);

			CalcurateVectByPoints(&rectAVect, rectA[rectAVertex].m_x, rectA[rectAVertex].m_y, 
				rectA[(rectAVertex + 1) % RECT_VERTEX_NUM].m_x,rectA[(rectAVertex + 1) % RECT_VERTEX_NUM].m_y);

			if (Cross(rectAVect, rectBVect) >= 0)
			{
				includeRectBVertex[rectAVertex] = true;
			}
		}

		for (int vertex = 0; vertex < RECT_VERTEX_NUM; ++vertex)
		{
			if (includeRectBVertex[vertex] == true)
			{
				if (vertex == RECT_VERTEX_NUM - 1)
				{
					return true;
				}
			}

			else
			{
				break;
			}
		}
	}

	return false;
}

void CalcurateVectByPoints(Vect* dest, double pointOPosX, double pointOPosY, double pointDestPosX, double pointDestPosY)
{
	dest->m_x = pointDestPosX - pointOPosX;
	dest->m_y = pointDestPosY - pointOPosY;

	return;
}

//void InitStageData(StageDate* pStageData, const char* filePath, int floorMax)
//{
//	FILE* pForesF;
//
//	pForesF = fopen(filePath, "r");
//
//	for (int floor = 0; floor < floorMax; ++floor)
//	{
//		fscanf(pForesF, "%d,", &pStageData->m_enemyId[floor]);
//
//		for (int drop = 0; drop < FLOOR_DROP_MAX; ++drop)
//		{
//			fscanf(pForesF, "%d,", &pStageData->m_dropWord[floor].m_mKDropId[drop]);
//		}
//
//		for (int drop = 0; drop < FLOOR_DROP_MAX; ++drop)
//		{
//			fscanf(pForesF, "%d,", &pStageData->m_dropWord[floor].m_wMDropId[drop]);
//		}
//
//		fscanf(pForesF, "%d,", &pStageData->m_clear[floor].m_mKClear);
//		fscanf(pForesF, "%d,", &pStageData->m_clear[floor].m_wMClear);
//	}
//
//	fclose(pForesF);
//
//	return;
//}
//
//void InitEnemyData(EnemyST* pEnemyData)
//{
//	FILE* pEnemySTF;
//
//	pEnemySTF= fopen("Files/EnemyStates/EnemyState.csv", "r");
//	
//	for (int enemy = VOID_ENEMY+1; enemy < ENEMY_MAX; ++enemy)
//	{
//		fscanf(pEnemySTF, "%[^,],%d,%d,", pEnemyData[enemy].m_name,
//			&pEnemyData[enemy].m_cTBlank, &pEnemyData[enemy].m_cTNum);
//
//		fseek(pEnemySTF, sizeof(char), SEEK_CUR);
//
//		for (int action = 0; action < ENEMY_ACTION_MAX; ++action)
//		{
//			fscanf(pEnemySTF, " %[^,],%u,", pEnemyData[enemy].m_enemyAction[action].m_name,
//				&pEnemyData[enemy].m_enemyAction[action].m_ActionDamage);
//
//			for (int element = 0; element < ELEMENT_ATTRIBUTES_MAX - 1; ++element)
//			{
//				fscanf(pEnemySTF, "%d,", &pEnemyData[enemy].m_enemyAction[action].m_ActionElements[element]);
//			}
//
//			for (int attack = 0; attack < ATTACK_ATTRIBUTES_MAX - 1; ++attack)
//			{
//				fscanf(pEnemySTF, "%d,", &pEnemyData[enemy].m_enemyAction[action].m_ActionAttacks[attack]);
//			}
//		}
//	}
//
//	fclose(pEnemySTF);
//
//	return;
//}