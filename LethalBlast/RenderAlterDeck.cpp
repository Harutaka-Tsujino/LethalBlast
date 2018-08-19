#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void RenderAlterDeck(ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
	CustomVertex* endDeckAlterVertices,CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	TEXTUREID* wordTexIds, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, int* pDeckNumToAlter)
{
	static TEXTUREID collisionTestTexId;
	static TEXTUREID alterDeckTexId;

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("Texture/TestRect.png", &collisionTestTexId);
		RoadTexture("Texture/AlterDeck/EndAlterDeck.png", &alterDeckTexId);

		frameCount = 0;
	}

	for (int deckNum = 0; deckNum < MAGIC_KNIGHT_DECKS_MAX; ++deckNum)
	{
		DrawImage(pChoiseWordCollisionsVertex[deckNum].ImageVertex, wordTexIds[deckNum]);
	}
	
	DrawImage(pBackgroundVertices, NULL);

	for (int deckNum = 0; deckNum < DECK_WORD_MAX; ++deckNum)
	{
		DrawImage(pDeckComponentCollisionsVertex[deckNum].ImageVertex, wordTexIds[(pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[deckNum])]);
	}

	DrawImage(pWordDatasBackVertices, NULL);

	DrawImage(endDeckAlterVertices, alterDeckTexId);

	return;
}
