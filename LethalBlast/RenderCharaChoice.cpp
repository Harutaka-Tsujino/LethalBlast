#include"RenderCharaChoice.h"

void RenderCharaChoice(SCENE* scene)
{
	static TEXTUREID textureIds[CHARA_CHOICE_TEX_MAX];
	static FONTID fontIds[CHARA_CHOICE_FONT_MAX];

	RenderCharaChoiceInit(textureIds);

	RenderCharaChoiceBackGround(textureIds, fontIds);

	switch (g_playerType)
	{
	case WEAPON_MASTER:

		break;

	case MASIC_KNIGHT:

		break;

	case NECROMAMCERANDSUMMONUR:

		break;
	}

}

void RenderCharaChoiceInit(TEXTUREID* textureIds)
{
	static bool isFirstFrame = true;

	if (isFirstFrame)
	{
		RoadTexture("Texture/CharaChoiceBG.png",&textureIds[CHARA_CHOICE_BACKGROUND]);

		isFirstFrame = false;
	}
}

void RenderCharaChoiceBackGround(TEXTUREID* textureIds, FONTID* fontIds)
{
	CustomVertex CharaChoiceBackGround[4];

	CustomImageVerticies(CharaChoiceBackGround, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);
	DrawImage(CharaChoiceBackGround, textureIds[CHARA_CHOICE_BACKGROUND]);

	SetFont(50.f, 50.f, "MS ゴシック", fontIds, 10.f);

	for (int i = 0;i < 3;i++)
	{
		switch (i)
		{
		case 0:
			WriteText(300.f, 800.f, "ウェポンマスター", DT_CENTER, fontIds[WEAPON_MASTER_FONT]);

			break;

		case 1:
			WriteText(600.f, 800.f, "マジックナイト", DT_CENTER, fontIds[MASIC_KNIGHT_FONT]);

			break;

		case 2:
			WriteText(900.f, 800.f, "ネクロマンサーとサモナー", DT_CENTER, fontIds[NECROMANCER_AND_SUMMONER_FONT]);

			break;
		}
	}

}
