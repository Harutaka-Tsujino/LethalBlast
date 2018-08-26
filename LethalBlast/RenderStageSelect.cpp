#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"
#include"ControlStageSelect.h"
#include"RenderStageSelect.h"

void RenderStageSelect(ImagesCustomVertex* pStageSelectPortals, CustomVertex* pBackPortal)
{
	static int frameCount = INIT_FRAME;
	//static TEXTUREID stageSelectTexIds[STAGE_SELECT_TEX_MAX];

	if (frameCount == INIT_FRAME)
	{
		frameCount = 0;
	}

	DrawImage(pStageSelectPortals[RUIN_STAGE].ImageVertex, NULL);
	DrawImage(pStageSelectPortals[FOREST_STAGE].ImageVertex, NULL);
	DrawImage(pStageSelectPortals[CAVE_STAGE].ImageVertex, NULL);
	DrawImage(pBackPortal, NULL);

	return;
}
