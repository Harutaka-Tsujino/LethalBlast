#include"RenderTitle.h"
#include<windows.h>

void TitleRender(SCENE *scene)
{
	static TEXTUREID textureIds[TITLE_TEX_MAX];
	static FONTID fontIds[TITLE_FONT_MAX];

	TitleRenderInit(textureIds);

	CustomVertex TitleBackGround[4];

	CustomImageVerticies(TitleBackGround, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);
	DrawImage(TitleBackGround, textureIds[TITLE_BG_TEX]);

	TitleRogoCanFadeIn(textureIds);

	PressEnterFont(fontIds);
}

void TitleRenderInit(TEXTUREID* textureIds)
{
	static bool isFirstFrame = true;

	//一回だけ読み込む
	if (isFirstFrame)
	{
		RoadTexture("Texture/Title/TitleBackground.png", &textureIds[TITLE_BG_TEX]);
		RoadTexture("Texture/Title/TitleRogo.png", &textureIds[TITLE_ROGO_TEX]);

		isFirstFrame = false;
	}
}

void TitleRogoCanFadeIn(TEXTUREID* textureIds)
{
	CustomVertex TitleRogo[4];

	//タイトルロゴのｘ、y座標
	float TetleRogoPosX = DISPLAY_WIDTH / 2.f;
	float TetleRogoPosY = DISPLAY_HEIGHT / 2.5f;

	//アルファ値を変えるためのカウント
	static int alphaCount = 0;

	//透明度の変数
	static unsigned char alpha = 0;
	
	//ここからフェードイン処理
	alphaCount++;

	if (alphaCount <= 75)
	{
		alpha += 255 / 75;
	}
	//ここまでフェードイン処理

	CustomImageVerticies(TitleRogo, TetleRogoPosX, TetleRogoPosY, 600.f, 600.f, GetColor(alpha, 0xFF, 0xFF, 0xFF));
	DrawImage(TitleRogo, textureIds[TITLE_ROGO_TEX]);
}

void PressEnterFont(FONTID* fontIds)
{
	static int alphaCount = -1;

	if (alphaCount == -1)
	{ 
		SetFont(50, 50, "MS ゴシック", fontIds, 20);

		alphaCount = 0;
	}

	//透明度の変数
	static int alpha = 0;

	//ここから点滅処理
	if (alphaCount < 51)
	{
		alpha += 5;	//透明度を上げていく
	}

	else
	{
		alpha -= 5;	//透明度を下げていく
	}

	//カウントが以上になったら初期化する
	if (alpha == 0)
	{
		alphaCount = 0;
	}

	else
	{
		alphaCount++;
	}

	//ここまで点滅処理

	WriteText(DISPLAY_WIDTH / 2, 600, "Press Enter", DT_CENTER, fontIds[PRESS_ENTER_FONT], GetColor((UCHAR)alpha, 0xFF, 0xFF, 0xFF));

	return;
}