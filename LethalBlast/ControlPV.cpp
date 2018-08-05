#include"DX9Lib.h"
#include"WinMain.h"

void ControlPV(SCENE* scene)
{
	static bool firstFrame = true;

	//前のシーンでの入力を受け継がないようにする
	if (firstFrame)
	{
		firstFrame = false;

		return;
	}

	//クリックもしくはエンターを押したらゲーム画面に移行する
	if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[LEFT_CLICK])
	{
		*scene = TITLE_SCENE;
	}

	return;
}
