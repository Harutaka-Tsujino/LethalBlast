#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"RenderAlterDeck.h"

void RenderAlterDeck(ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
	CustomVertex* endDeckAlterVertices,CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	TEXTUREID* wordTexIds, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, int* pDeckNumToAlter, bool* clickedWord)
{
	static TEXTUREID collisionTestTexId;
	static TEXTUREID alterDeckTexId[ALTER_DECK_TEX_MAX];

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("Texture/TestRect.png", &collisionTestTexId);
		RoadTexture("Texture/AlterDeck/EndAlterDeck.png", &alterDeckTexId[EXIT_ALTER_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground1.png", &alterDeckTexId[ALTER_BACK_1_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground2.png", &alterDeckTexId[ALTER_BACK_2_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground3.png", &alterDeckTexId[ALTER_BACK_3_TEX]);
		RoadTexture("Texture/AlterDeck/RedFrame.png", &alterDeckTexId[ALTER_CLICKED_EFFECT_TEX]);

		frameCount = 0;
	}

	CustomVertex alterBackVertices[4];
	CustomImageVerticies(alterBackVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);
	
	DrawImage(alterBackVertices, alterDeckTexId[ALTER_BACK_1_TEX]);
	
	for (int wordNum = 0; wordNum < MAGIC_KNIGHT_WORD_MAX; ++wordNum)
	{
		DrawImage(pChoiseWordCollisionsVertex[wordNum].ImageVertex, wordTexIds[wordNum]);

		if (clickedWord[wordNum])
		{
			DrawImage(pChoiseWordCollisionsVertex[wordNum].ImageVertex, alterDeckTexId[ALTER_CLICKED_EFFECT_TEX]);
		}
	}
	
	DrawImage(alterBackVertices, alterDeckTexId[ALTER_BACK_2_TEX]);

	for (int deckNum = 0; deckNum < DECK_WORD_MAX; ++deckNum)
	{
		DrawImage(pDeckComponentCollisionsVertex[deckNum].ImageVertex, wordTexIds[(pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[deckNum])]);
	}

	DrawImage(alterBackVertices, alterDeckTexId[ALTER_BACK_3_TEX]);

	DrawImage(endDeckAlterVertices, alterDeckTexId[EXIT_ALTER_TEX]);


	return;
}
