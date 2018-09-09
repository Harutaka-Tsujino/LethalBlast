#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"
#include"ControlStageSelect.h"
#include"RenderStageSelect.h"

void RenderStageSelect(ImagesCustomVertex* pStageSelectPortals, CustomVertex* pBackPortal)
{
	static int frameCount = INIT_FRAME;
	//static TEXTUREID stageSelectTexIds[STAGE_SELECT_TEX_MAX];

	static TEXTUREID StageTextureIds[STAGE_MAX];
	static TEXTUREID homeTextures;
	if (frameCount == INIT_FRAME)
	{
		RoadTexture("Texture/StagePortal/Forest.png", &StageTextureIds[�X]);
		RoadTexture("Texture/StagePortal/mainBG.png", &StageTextureIds[���]);
		RoadTexture("Texture/StagePortal/CrystalCave.png", &StageTextureIds[���A]);
		RoadTexture("Texture/Home/CharaChoicePortal.png", &homeTextures);

		frameCount = 0;
	}

	DrawImage(pStageSelectPortals[���].ImageVertex, StageTextureIds[���]);
	DrawImage(pStageSelectPortals[�X].ImageVertex, StageTextureIds[�X]);
	DrawImage(pStageSelectPortals[���A].ImageVertex, StageTextureIds[���A]);
	DrawImage(pBackPortal, homeTextures);

	return;
}
