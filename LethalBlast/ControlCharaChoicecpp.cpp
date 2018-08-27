#include"ControlCharaChoice.h"

#define MOUSE_SCALE 0.5f

void ControlCharaChoice(SCENE* scene, int* cursol, PLAYERTYPE* playerType)
{
	//フォントの矩形の作成
	CustomVertex MouseObj[4], ObjA[4], ObjB[4];
	CustomImageVerticies(MouseObj, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_SCALE, MOUSE_SCALE);
	CustomImageVerticies(ObjA, WEPON_MASTER_CHOICE_TEXT_WIDTH, 600.f, WEPON_MASTER_CHOICE_TEXT_WIDTH, 20.f);
	CustomImageVerticies(ObjB, WEPON_MASTER_CHOICE_TEXT_WIDTH*3, 600.f, WEPON_MASTER_CHOICE_TEXT_WIDTH, 20.f);

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		frameCount = 0;
	}

	//マウスの当たり判定でカーソルを動かす
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

	//カーソル移動処理
	if (g_keyState.keyPush[DIK_LEFT])
	{
		*cursol = 1;
		*playerType = WEAPON_MASTER;
	}

	if (g_keyState.keyPush[DIK_RIGHT])
	{
		*cursol = 2;
		*playerType = MAGIC_KNIGHT;
	}

	//カーソルがあるところでエンターが押されたらゲーム画面へ移行
	for (int i = 1;i < 3;i++)
	{
		if (*cursol == i)
		{
			if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[LEFT_CLICK])
			{
				*scene = LOAD_TO_HOME_SCENE;
			}
		}
	}

}

bool RectToRectCollisionCheak(CustomVertex* pObjA,CustomVertex* pObjB)
{
	//四角形の当たり判定
	if ((pObjA[0].m_x <= pObjB[0].m_x && pObjB[0].m_x <= pObjA[1].m_x) ||
		(pObjA[0].m_x <= pObjB[1].m_x && pObjB[1].m_x <= pObjA[1].m_x)||
		(pObjB[0].m_x <= pObjA[0].m_x && pObjA[1].m_x <= pObjB[1].m_x))
	{
		if ((pObjA[0].m_y <= pObjB[0].m_y && pObjB[0].m_y <= pObjA[3].m_y) ||
			(pObjA[0].m_y <= pObjB[3].m_y && pObjB[3].m_y <= pObjA[3].m_y)||
			(pObjB[0].m_y <= pObjA[0].m_y && pObjA[3].m_y <= pObjB[3].m_y))
		{
			return true;
		}
	}

	return false;
}
