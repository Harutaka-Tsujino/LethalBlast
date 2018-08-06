#include"RenderCharaChoice.h"

void RenderCharaChoice(SCENE* scene, int* cursol)
{
	static TEXTUREID textureIds[CHARA_CHOICE_TEX_MAX];
	static FONTID fontIds[CHARA_CHOICE_FONT_MAX];

	RenderCharaChoiceInit(textureIds,fontIds);

	RenderCharaChoiceBackGround(textureIds, fontIds, cursol);
}

void RenderCharaChoiceInit(TEXTUREID* textureIds, FONTID* fontIds)
{
	static bool isFirstFrame = true;

	//一回だけ入る
	if (isFirstFrame)
	{
		RoadTexture("Texture/CharaChoice/CharaChoiceBackGround.png",&textureIds[CHARA_CHOICE_BACKGROUND]);
		RoadTexture("Texture/CharaChoice/cursol.png", &textureIds[CHARA_CHOICE_CURSOL]);
		RoadTexture("Texture/CharaChoice/NecromancerAndSummonur.png", &textureIds[CHARA_CHOICE_NECROMANCER_AND_SUMMONER]);

		SetFont(20.f, 40.f, "MS ゴシック", fontIds, 10.f);

		isFirstFrame = false;
	}
}

void RenderCharaChoiceBackGround(TEXTUREID* textureIds, FONTID* fontIds, int* cursol)
{
	CustomVertex CharaChoiceBackGround[4];
	CustomVertex CharaChoiceCursol[4];
	CustomVertex CharaChoiceCharaImage[4];

	//背景の描画
	CustomImageVerticies(CharaChoiceBackGround, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);
	DrawImage(CharaChoiceBackGround, textureIds[CHARA_CHOICE_BACKGROUND]);

	//キャラ選択のためのフォント
	for (int i = 0;i < 3;i++)
	{
		switch (i)
		{
		case 0:
			WriteText(300.f, 900.f, "ウェポンマスター", DT_CENTER, fontIds[0]);

			break;

		case 1:
			WriteText(800.f, 900.f, "マジックナイト", DT_CENTER, fontIds[0]);

			break;

		case 2:
			WriteText(1400.f, 900.f, "ネクロマンサーとサモナー", DT_CENTER, fontIds[0]);

			break;
		}
	}

	//カーソルが合ったとき立ち絵などを描画する
	if (*cursol == 1)
	{
		CustomImageVerticies(CharaChoiceCursol, 100.f, 900.f, 25.f, 25.f);
		DrawImage(CharaChoiceCursol, textureIds[CHARA_CHOICE_CURSOL]);

		CustomImageVerticies(CharaChoiceCharaImage, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 3.f, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 3.f);
		DrawImage(CharaChoiceCharaImage, textureIds[CHARA_CHOICE_WEAPON_MASTER]);
	}

	if (*cursol == 2)
	{
		CustomImageVerticies(CharaChoiceCursol, 630.f, 900.f, 25.f, 25.f);
		DrawImage(CharaChoiceCursol, textureIds[CHARA_CHOICE_CURSOL]);

		CustomImageVerticies(CharaChoiceCharaImage, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 3.f, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 3.f);
		DrawImage(CharaChoiceCharaImage, textureIds[CHARA_CHOICE_MAGIC_KNIGHT]);
	}

	if (*cursol == 3)
	{
		CustomImageVerticies(CharaChoiceCursol, 1100.f, 900.f, 25.f, 25.f);
		DrawImage(CharaChoiceCursol, textureIds[CHARA_CHOICE_CURSOL]);

		CustomImageVerticies(CharaChoiceCharaImage, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 3.f, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 3.f);
		DrawImage(CharaChoiceCharaImage, textureIds[CHARA_CHOICE_NECROMANCER_AND_SUMMONER]);
	}

}

