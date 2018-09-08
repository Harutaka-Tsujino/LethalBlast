#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void RenderChoiceDeck(ImagesCustomVertex* pChoiseDeckCollisionsVertex)
{
	static TEXTUREID deckTexIds[MAGIC_KNIGHT_DECKS_MAX+1];

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/DeckChoice/Deck0.jpg", &deckTexIds[0]);
		RoadTexture("texture/DeckChoice/Deck1.jpg", &deckTexIds[1]);
		RoadTexture("texture/DeckChoice/Deck2.jpg", &deckTexIds[2]);
		RoadTexture("texture/DeckChoice/Deck3.jpg", &deckTexIds[3]);
		RoadTexture("texture/DeckChoice/Deck4.jpg", &deckTexIds[4]);
		RoadTexture("texture/DeckChoice/Deck5.jpg", &deckTexIds[5]);
		RoadTexture("texture/DeckChoice/Deck6.jpg", &deckTexIds[6]);
		RoadTexture("texture/DeckChoice/Deck7.jpg", &deckTexIds[7]);
		RoadTexture("texture/DeckChoice/ChoiceDeckBack.png", &deckTexIds[8]);

		frameCount = 0;
	}

	CustomVertex back[RECT_VERTEX_NUM];

	CustomImageVerticies(back, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f);

	DrawImage(back, deckTexIds[8]);

	for (int deckNum = 0; deckNum < MAGIC_KNIGHT_DECKS_MAX; ++deckNum)
	{
		DrawImage(pChoiseDeckCollisionsVertex[deckNum].ImageVertex, deckTexIds[deckNum]);
	}

	return;
}
