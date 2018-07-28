#include<windows.h>
#include"DX9Lib.h"
#include"ControlGame.h"
#include"RenderGame.h"
#include"WinMain.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	return CreateWindowAndRepeatToControlAndRender(hInst, "testApp", MainFunction, DISPLAY_WIDTH, DISPLAY_HEIGHT, FALSE);
}

//メッセージループでループさせる関数
void MainFunction(void)
{
	static SCENE scene = GAME_SCENE;

	//シーン分岐
	switch (scene)
	{
	case TITLE_SCENE:

		break;
	case GAME_SCENE:

		ControlGame(&scene);
		RenderGame(&scene);

		break;
	}

	return;
}
