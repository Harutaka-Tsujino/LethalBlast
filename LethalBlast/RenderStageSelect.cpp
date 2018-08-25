#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"
#include"ControlStageSelect.h"
#include"RenderStageSelect.h"

void RenderStageSelect(ImagesCustomVertex* pStageSelectPortals)
{
	static int frameCount = INIT_FRAME;
	//static TEXTUREID stageSelectTexIds[STAGE_SELECT_TEX_MAX];

	if (frameCount == INIT_FRAME)
	{
		frameCount = 0;
	}

	for (int stage = 0; stage < STAGE_MAX; ++stage)
	{
		DrawImage(pStageSelectPortals[stage].ImageVertex, NULL);
	}

	return;
}
