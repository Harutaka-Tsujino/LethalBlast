#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void RenderChoiceDeck(ImagesCustomVertex* pChoiseDeckCollisionsVertex, MagicKnightDeck* pMagicKnightDecks)
{
	static TEXTUREID collisionTestTexId;

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/TestRect.png", &collisionTestTexId);

		frameCount = 0;
	}

	for (int deckNum = 0; deckNum < MAGIC_KNIGHT_DECKS_MAX; ++deckNum)
	{
		DrawImage(pChoiseDeckCollisionsVertex[deckNum].ImageVertex,collisionTestTexId);
	}

	return;
}
