#include<windows.h>
#include<time.h>
#include"DX9Lib.h"
#include"ControlGame.h"
#include"RenderGame.h"
#include"WinMain.h"
#include"ControlTitle.h"
#include"RenderTitle.h"
#include"ControlPV.h"
#include"RenderPV.h"
#include"ControlCharaChoice.h"
#include"RenderCharaChoice.h"
#include"ControlWordListsAndTyping.h"
#include"RenderWordListsAndTyping.h"

int g_playerType;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	return CreateWindowAndRepeatToControlAndRender(hInst, "Lethal Blast", MainFunction, DISPLAY_WIDTH, DISPLAY_HEIGHT, FALSE);
}

//メッセージループでループさせる関数
void MainFunction(void)
{
	srand((unsigned int)time(NULL));

	static SCENE scene = (SCENE)0;

	static TEXTUREID textureIds[ALL_TEX_MAX];
	static FONTID fontIds[ALL_FONT_MAX];

	static WordData magicKnigtWords[MAGIC_KNIGHT_WORD_MAX];
	static WordList magicKnightWordLists[5];
	static MagicKnightAction magicKnightAction;
	static WordCandidate wordCandidates[5];

	//シーン分岐
	switch (scene)
	{
	case PV_SCENE:

		ControlPV(&scene);
		RenderPV(&scene);

		break;

	case TITLE_SCENE:

		TitleContorol(&scene);
		TitleRender(&scene);

		break;

	case CHARA_CHOICE_SCENE:

		ControlCharaChoice(&scene);
		RenderCharaChoice (&scene);

		break;

	case GAME_SCENE:

		ControlGame(&scene);
		RenderGame(&scene);
		ControlTyping(magicKnigtWords, magicKnightWordLists, &magicKnightAction, wordCandidates);
		RenderMasicKnightWordLists(fontIds, magicKnigtWords, magicKnightWordLists, &magicKnightAction, wordCandidates);

		break;
	}

	return;
}
