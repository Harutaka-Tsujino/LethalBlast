#include"ControlTitle.h"

void TitleContorol(SCENE* scene)
{

	//クリックもしくはエンターを押したらゲーム画面に移行する
	if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[LEFT_CLICK])
	{
		*scene = GAME_SCENE;
	}
}