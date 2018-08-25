#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"
#include"ControlStageSelect.h"

void ControlStageSelect(SCENE* pScene, ImagesCustomVertex* pStageSelectPortals, int* pSelectedStage)
{
	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		frameCount = 0;
	}

	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	for (int stage = 0; stage < STAGE_MAX; ++stage)
	{
		CustomImageVerticies(pStageSelectPortals[stage].ImageVertex, (DISPLAY_WIDTH / 2.f)*(stage), DISPLAY_HEIGHT / 2.f,
		DISPLAY_WIDTH/6.f, DISPLAY_WIDTH*2.f, GetColor(255, 80* stage, 155, 255));

		RotateImageDeg(pStageSelectPortals[stage].ImageVertex, pStageSelectPortals[stage].ImageVertex,45);
	}

	for (int stage = 0; stage < STAGE_MAX; ++stage)
	{

		if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[stage].ImageVertex))
		{
			pStageSelectPortals[stage].ImageVertex->m_color = 0xFFFFFFFF;
		}

		if (!g_mouseState.mousePush[LEFT_CLICK])
		{
			break;
		}

		if (CheckRotatedRectsCollision(mouseCursorCollisionVertex, pStageSelectPortals[stage].ImageVertex))
		{
			*pSelectedStage = stage;
			*pScene = GAME_SCENE;
		}
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
