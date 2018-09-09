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
		RoadTexture("Texture/StagePortal/Forest.png", &StageTextureIds[êX]);
		RoadTexture("Texture/StagePortal/mainBG.png", &StageTextureIds[à‚ê’]);
		RoadTexture("Texture/StagePortal/CrystalCave.png", &StageTextureIds[ì¥åA]);
		RoadTexture("Texture/Home/CharaChoicePortal.png", &homeTextures);

		frameCount = 0;
	}

	DrawImage(pStageSelectPortals[à‚ê’].ImageVertex, StageTextureIds[à‚ê’]);
	DrawImage(pStageSelectPortals[êX].ImageVertex, StageTextureIds[êX]);
	DrawImage(pStageSelectPortals[ì¥åA].ImageVertex, StageTextureIds[ì¥åA]);
	DrawImage(pBackPortal, homeTextures);

	return;
}
