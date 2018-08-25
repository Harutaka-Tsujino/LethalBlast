#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"RenderModifyWord.h"

void RenderModify(WordData* pMagicKnightWordDatas,ImagesCustomVertex* pChoiseWordCollisionsVertex,
	CustomVertex* pWordDatasBackVertices, CustomVertex* pEndModifyVertices, CustomVertex* pBackgroundVertices,
	int* modifyWordBox, ImagesCustomVertex* modifyBoxVertices, CustomVertex* decideModify, TEXTUREID* wordTexIds, bool* clickedWord)
{
	static TEXTUREID modifyTexId[MODIFY_TEX_MAX];

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("Texture/AlterDeck/EndAlterDeck.png",&modifyTexId[END_MODIFY_TEX]);
		RoadTexture("Texture/AlterDeck/EndAlterDeck.png", &modifyTexId[DECIDE_MODIFY_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground1.png", &modifyTexId[MODIFY_BACK_1_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground2.png", &modifyTexId[MODIFY_BACK_2_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground3.png", &modifyTexId[MODIFY_BACK_3_TEX]);
		RoadTexture("Texture/AlterDeck/RedFrame.png", &modifyTexId[MODIFY_CLICKED_EFFECT_TEX]);
		RoadTexture("Texture/AlterDeck/UnderAlterWordBoard.png", &modifyTexId[UNDER_MODIFY_WORD_BOARD_TEX]);

		frameCount = 0;
	}

	CustomVertex modifyBackVertices[4];
	CustomImageVerticies(modifyBackVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);

	DrawImage(modifyBackVertices, modifyTexId[MODIFY_BACK_1_TEX]);

	for (int word = 0; word < MAGIC_KNIGHT_WORD_MAX; ++word)
	{
		DrawImage(pChoiseWordCollisionsVertex[word].ImageVertex, modifyTexId[UNDER_MODIFY_WORD_BOARD_TEX]);
		DrawImage(pChoiseWordCollisionsVertex[word].ImageVertex, wordTexIds[word]);

		if (clickedWord[word])
		{
			DrawImage(pChoiseWordCollisionsVertex[word].ImageVertex, modifyTexId[MODIFY_CLICKED_EFFECT_TEX]);
		}
	}

	DrawImage(modifyBackVertices, modifyTexId[MODIFY_BACK_2_TEX]);

	for (int word = 0; word < 2; ++word)
	{
		DrawImage(modifyBoxVertices[word].ImageVertex, modifyTexId[UNDER_MODIFY_WORD_BOARD_TEX]);

		if (modifyWordBox[word])
		{
			DrawImage(modifyBoxVertices[word].ImageVertex, wordTexIds[modifyWordBox[word]]);
		}
	}

	DrawImage(modifyBackVertices, modifyTexId[MODIFY_BACK_3_TEX]);

	DrawImage(decideModify, modifyTexId[DECIDE_MODIFY_TEX]);

	DrawImage(pEndModifyVertices, modifyTexId[END_MODIFY_TEX]);

	return;
}
