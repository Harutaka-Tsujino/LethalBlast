﻿#include"ControlCharaChoice.h"

void ControlCharaChoice(SCENE* scene, int* cursol)
{
	//カーソル移動処理
	if (g_keyState.keyPush[DIK_LEFT])
	{
		if (*cursol == 2)
		{
			*cursol = 1;
		}

		if (*cursol == 3)
		{
			*cursol = 2;
		}
	}

	if (g_keyState.keyPush[DIK_RIGHT])
	{
		if (*cursol == 2)
		{
			*cursol = 3;
		}

		if (*cursol == 1)
		{
			*cursol = 2;
		}
	}

	//カーソルがあるところでエンターが押されたらゲーム画面へ移行
	for (int i = 1;i < 4;i++)
	{
		if (*cursol == i)
		{
			if (g_keyState.keyPush[DIK_RETURN])
			{
				*scene = GAME_SCENE;
			}
		}
	}

}
