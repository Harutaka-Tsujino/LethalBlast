#include"RenderCharaChoice.h"

void RenderCharaChoice(SCENE* scene, int* cursol)
{
	static TEXTUREID textureIds[CHARA_CHOICE_TEX_MAX];

	RenderCharaChoiceInit(textureIds);

	RenderCharaChoiceBackGround(textureIds, cursol);
}

void RenderCharaChoiceInit(TEXTUREID* textureIds)
{
	static bool isFirstFrame = true;

	//一回だけ入る
	if (isFirstFrame)
	{
		RoadTexture("Texture/CharaChoice/cursol.png", &textureIds[CHARA_CHOICE_CURSOL]);
		RoadTexture("Texture/CharaChoice/MagicKnight.png", &textureIds[CHARA_CHOICE_MAGIC_KNIGHT]);
		RoadTexture("Texture/CharaChoice/WaeponMaster.png", &textureIds[CHARA_CHOICE_WEAPON_MASTER]);

		isFirstFrame = false;
	}
}

void RenderCharaChoiceBackGround(TEXTUREID* textureIds, int* cursol)
{
	CustomVertex CharaChoiceBackGround[4];
	CustomVertex CharaChoiceCharaImage[4];

	//背景の描画
	CustomImageVerticies(CharaChoiceBackGround, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f,GetColor(255,244,12,12));
	DrawImage(CharaChoiceBackGround, NULL);
	
	CustomImageVerticies(CharaChoiceCharaImage, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 2.f);
	DrawImage(CharaChoiceCharaImage, textureIds[CHARA_CHOICE_WEAPON_MASTER]);
	
	CustomImageVerticies(CharaChoiceCharaImage, DISPLAY_WIDTH - (DISPLAY_WIDTH / 4.f), DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT / 2.f);
	DrawImage(CharaChoiceCharaImage, textureIds[CHARA_CHOICE_MAGIC_KNIGHT]);

}
