﻿#include"ControlCharaChoice.h"

#define MOUSE_SCALE 0.5f

void ControlCharaChoice(SCENE* scene, int* cursol,int* playerType)
{
	CustomVertex MouseObj[4], ObjA[4], ObjB[4], ObjC[4];
	CustomImageVerticies(MouseObj, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_SCALE, MOUSE_SCALE);
	CustomImageVerticies(ObjA, WEPON_MASTER_CHOICE_TEXT_WIDTH, 600.f, WEPON_MASTER_CHOICE_TEXT_WIDTH, 20.f);
	CustomImageVerticies(ObjB, WEPON_MASTER_CHOICE_TEXT_WIDTH*3, 600.f, WEPON_MASTER_CHOICE_TEXT_WIDTH, 20.f);
	CustomImageVerticies(ObjC, WEPON_MASTER_CHOICE_TEXT_WIDTH*5, 600.f, WEPON_MASTER_CHOICE_TEXT_WIDTH, 20.f);

	if (RectToRectCollisionCheak(MouseObj,ObjA))
	{
		*cursol = 1;
		*playerType = WEAPON_MASTER;
	}

	if (RectToRectCollisionCheak(MouseObj, ObjB))
	{
		*cursol = 2;
		*playerType = MAGIC_KNIGHT;
	}
	
	if (RectToRectCollisionCheak(MouseObj, ObjC))
	{
		*cursol = 3;
		*playerType = NECROMAMCERANDSUMMONUR;
	}

	//カーソル移動処理
	if (g_keyState.keyPush[DIK_LEFT])
	{
		if (*cursol == 2)
		{
			*cursol = 1;
			*playerType = WEAPON_MASTER;
		}

		if (*cursol == 3)
		{
			*cursol = 2;
			*playerType = MAGIC_KNIGHT;
		}
	}

	if (g_keyState.keyPush[DIK_RIGHT])
	{
		if (*cursol == 2)
		{
			*cursol = 3;
			*playerType = NECROMAMCERANDSUMMONUR;
		}

		if (*cursol == 1)
		{
			*cursol = 2;
			*playerType = MAGIC_KNIGHT;
		}
	}

	//カーソルがあるところでエンターが押されたらゲーム画面へ移行
	for (int i = 1;i < 4;i++)
	{
		if (*cursol == i)
		{
			if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[LEFT_CLICK])
			{
				*scene = GAME_SCENE;
			}
		}
	}

}

bool RectToRectCollisionCheak(CustomVertex* pObjA,CustomVertex* pObjB)
{
	if ((pObjA[0].m_x <= pObjB[0].m_x && pObjB[0].m_x <= pObjA[1].m_x) ||
		(pObjA[0].m_x <= pObjB[1].m_x && pObjB[1].m_x <= pObjA[1].m_x))
	{

		if ((pObjA[0].m_y <= pObjB[0].m_y && pObjB[0].m_y <= pObjA[3].m_y) ||
			(pObjA[0].m_y <= pObjB[3].m_y && pObjB[3].m_y <= pObjA[3].m_y))
		{
			return true;
		}
	}

	return false;
}