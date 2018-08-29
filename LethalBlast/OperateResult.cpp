#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlStageSelect.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlBattle.h"
#include"OperateResult.h"

void OperateResultScene(SCENE* scene, bool isClear)
{
	static int frameCount = INIT_FRAME;
	static TEXTUREID ResultTexIds[RESULT_TEX_MAX];

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("Texture/Result/GameOver.png", &ResultTexIds[GAME_OVER_TEX]);
		RoadTexture("Texture/Result/StageClear.png", &ResultTexIds[STAGE_CLEAR_TEX]);

		frameCount = 0;
	}

	CustomVertex back[RECT_VERTEX_NUM];
	CustomImageVerticies(back, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);


	if (isClear)
	{
		DrawImage(back, ResultTexIds[STAGE_CLEAR_TEX]);
	}

	else
	{
		DrawImage(back, ResultTexIds[GAME_OVER_TEX]);
	}

	if (g_mouseState.mousePush[LEFT_CLICK]||g_keyState.keyPush[DIK_RETURN])
	{
		*scene = HOME_SCENE;
	}

	return;
}
