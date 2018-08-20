#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"RenderHome.h"

void RenderHome(CustomVertex* deckAlterPortal, CustomVertex* modifyWordPortal, CustomVertex* mainGamePortal, CustomVertex* charaChoicePortal)
{
	static int frameCount = -1;

	static TEXTUREID homeTextures[HOME_TEX_MAX];

	if (frameCount == -1)
	{
		RoadTexture("Texture/Home/AlterDeckPortal.png", &homeTextures[ALTER_PORTAL_TEX]);
		RoadTexture("Texture/Home/CharaChoicePortal.png", &homeTextures[CHARA_CHOICE_PORTAL_TEX]);
		RoadTexture("Texture/Home/MainGamePortal.png", &homeTextures[QUEST_PORTAL_TEX]);
		RoadTexture("Texture/Home/ModifyWordPortal.png", &homeTextures[MODIFY_PORTAL_TEX]);

		frameCount = 0;
	}

	DrawImage(deckAlterPortal, homeTextures[ALTER_PORTAL_TEX]);
	DrawImage(modifyWordPortal, homeTextures[MODIFY_PORTAL_TEX]);
	DrawImage(mainGamePortal, homeTextures[QUEST_PORTAL_TEX]);
	DrawImage(charaChoicePortal, homeTextures[CHARA_CHOICE_PORTAL_TEX]);

	return;
}
