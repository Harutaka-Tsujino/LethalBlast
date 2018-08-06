#include<windows.h>
#include<time.h>
#include"DX9Lib.h"
#include"ControlGame.h"
#include"RenderGame.h"
#include"WinMain.h"
#include"ControlTitle.h"
#include"RenderTitle.h"
#include"ControlCharaChoice.h"
#include"RenderCharaChoice.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	return CreateWindowAndRepeatToControlAndRender(hInst, "Lethal Blast", MainFunction, DISPLAY_WIDTH, DISPLAY_HEIGHT, FALSE);
}

//メッセージループでループさせる関数
void MainFunction(void)
{
	srand((unsigned int)time(NULL));

	static SCENE scene = TITLE_SCENE;

	//シーン分岐
	switch (scene)
	{
	case TITLE_SCENE:
		TitleContorol(&scene);
		TitleRender(&scene);

		break;

	case CHARA_CHOICE_SCENE:
		ControlCharaChoice(&scene);
		RenderCharaChoice(&scene);

		break;

	case GAME_SCENE:

		ControlGame(&scene);
		RenderGame(&scene);

		break;
	}

	return;
}
