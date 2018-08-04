#include<windows.h>
#include"DX9Lib.h"
#include"WinMain.h"
#include"RenderGame.h"
#include"RenderWordListsAndTyping.h"

void RenderGame(SCENE* scene)
{
	static bool isFirstFrame = true;

	//テクスチャのデータをなくさないためstaticをつける
	static TEXTUREID textureIds[TEXTURE_MAX];

	//初回フレーム時に画像の読み込みを行う
	if (isFirstFrame)
	{
		RoadTexture("Texture/BackgroundGame0.png", &textureIds[BACKGROUND_0_TEXTURE]);

		isFirstFrame = false;
	}

	CustomVertex background[4];
	CustomImageVerticies(background, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);

	DrawImage(background, textureIds[BACKGROUND_0_TEXTURE]);

	WordListsAndTypingRender();

	return;
}
