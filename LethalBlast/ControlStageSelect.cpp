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

	const int MOVE_PORTAL_FRAME = 15;

	CustomImageVerticies(pStageSelectPortals[CAVE_STAGE].ImageVertex, (DISPLAY_WIDTH / 6.f) * 0, (DISPLAY_HEIGHT / 2.f)*(2 - frameCount / (float)MOVE_PORTAL_FRAME),
		DISPLAY_WIDTH / 3.f, DISPLAY_WIDTH*2.f, GetColor(255, 18, 18, 18));

	CustomImageVerticies(pStageSelectPortals[RUIN_STAGE].ImageVertex, (DISPLAY_WIDTH / 6.f) * 3, (DISPLAY_HEIGHT / 2.f)*(2 - frameCount / (float)MOVE_PORTAL_FRAME),
		DISPLAY_WIDTH*1.f, DISPLAY_WIDTH*2.f, 0xFFEA0D0D);

	CustomImageVerticies(pStageSelectPortals[FOREST_STAGE].ImageVertex, (DISPLAY_WIDTH / 6.f) * 7.05, (DISPLAY_HEIGHT / 2.f)*(2 - frameCount / (float)MOVE_PORTAL_FRAME),
		DISPLAY_WIDTH / 3.f, DISPLAY_WIDTH*2.f, GetColor(255, 18, 18, 18));

	for (int stage = 0; stage < STAGE_MAX; ++stage)
	{
		RotateImageDeg(pStageSelectPortals[stage].ImageVertex, pStageSelectPortals[stage].ImageVertex, (float)(-15 + 30 * stage)*(2 - frameCount / (float)MOVE_PORTAL_FRAME));
	}

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

	if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[CAVE_STAGE].ImageVertex))
	{
		*pSelectedStage = CAVE_STAGE;
		*pScene = CHOSE_DECK_TO_BATTLE_SCENE;

		frameCount = 0;

		return;
	}

	if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[FOREST_STAGE].ImageVertex))
	{
		*pSelectedStage = FOREST_STAGE;
		*pScene = CHOSE_DECK_TO_BATTLE_SCENE;

		frameCount = 0;

		return;
	}

	if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[RUIN_STAGE].ImageVertex))
	{
		*pSelectedStage = RUIN_STAGE;
		*pScene = CHOSE_DECK_TO_BATTLE_SCENE;

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
