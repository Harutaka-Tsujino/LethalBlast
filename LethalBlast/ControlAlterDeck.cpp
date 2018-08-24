#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlAlterDeck(SCENE* scene,WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, ImagesCustomVertex* pChoiseWordCollisionsVertex,ImagesCustomVertex* pDeckComponentCollisionsVertex,
	CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices,CustomVertex* pWordDatasBackVertices,int* pDeckNumToAlter,bool* clickedWord)
{
	static int frameCount = -1;

	if (frameCount == -1)
	{
		memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);

		frameCount = 0;
	}

	//マウス
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	const float WORD_COLLISION_SCALE_X = (DISPLAY_WIDTH) / 14;
	const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X / 5;

	float listWordPosX = (float)(WORD_COLLISION_SCALE_X*1.3);
	float listWordPosY = WORD_COLLISION_SCALE_X;

	float deckComponentPosX = (float)(WORD_COLLISION_SCALE_X * 1.3);
	float deckComponentPosY = DISPLAY_HEIGHT * 0.765f;

	const int WORD_NEW_LINE = 4;
	
	memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*MAGIC_KNIGHT_WORD_MAX);
	memset(pDeckComponentCollisionsVertex, 0, sizeof(ImagesCustomVertex)*MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX);

	static int wordSlidePosY = 0;
	const int SLIDE_SPEED = 13;

	CustomImageVerticies(pBackgroundVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*(0.65f + 0.175f), DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.175f, 0xFFFFD500);
	CustomImageVerticies(pWordDatasBackVertices, DISPLAY_WIDTH*0.875f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH*0.125f, DISPLAY_HEIGHT / 2.f, 0xFFF5F5F5);

	if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
	{
		if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
		{
			if (g_keyState.keyHold[DIK_COMMA])
			{
				wordSlidePosY += SLIDE_SPEED;
			}

			if (g_keyState.keyHold[DIK_PERIOD])
			{
				wordSlidePosY -= SLIDE_SPEED;
			}
		}
	}

	int haveWordNum = 0;

	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
	{
		if (pMagicKnightWordDatas[wordDatas].m_have)
		{
			haveWordNum++;
		}
	}

	if (wordSlidePosY > 0)
	{
		wordSlidePosY = 0;
	}

	if (wordSlidePosY < (int)(-WORD_COLLISION_SCALE_X * 1.2 * (haveWordNum / (WORD_NEW_LINE))))
	{
		wordSlidePosY = (int)(-WORD_COLLISION_SCALE_X * 1.2 * (haveWordNum / (WORD_NEW_LINE)));
	}

	haveWordNum = 0;

	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
	{
		if (pMagicKnightWordDatas[wordDatas].m_have)
		{
			haveWordNum++;

			CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, listWordPosX, listWordPosY + wordSlidePosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);
			
			listWordPosX += (WORD_COLLISION_SCALE_X * 2.3f);

			if (!((haveWordNum) % (WORD_NEW_LINE)))
			{
				listWordPosX = (float)(WORD_COLLISION_SCALE_X*1.3);
				listWordPosY += (float)(WORD_COLLISION_SCALE_X*1.2);
			}
		}
	}

	static int deckComponentSlidePosX = 0;

	if (RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
	{
		if (g_keyState.keyHold[DIK_COMMA])
		{
			deckComponentSlidePosX += SLIDE_SPEED;
		}

		if (g_keyState.keyHold[DIK_PERIOD])
		{
			deckComponentSlidePosX -= SLIDE_SPEED;
		}
	}

	const int DECK_COMPONENT_NEW_LINE = 20;

	if (deckComponentSlidePosX > 0)
	{
		deckComponentSlidePosX = 0;
	}

	if (deckComponentSlidePosX <(int)(-WORD_COLLISION_SCALE_X*4*(DECK_COMPONENT_NEW_LINE-1)))
	{
		deckComponentSlidePosX = (int)(-WORD_COLLISION_SCALE_X * 4 * (DECK_COMPONENT_NEW_LINE-1));
	}

	for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
	{
		CustomImageVerticies(pDeckComponentCollisionsVertex[wordDatas].ImageVertex, deckComponentPosX + deckComponentSlidePosX, deckComponentPosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

		deckComponentPosX += (float)(WORD_COLLISION_SCALE_X * 2.3);

		if (!((wordDatas + 1) % (DECK_COMPONENT_NEW_LINE)))
		{
			deckComponentPosX = (float)(WORD_COLLISION_SCALE_X*1.3);
			deckComponentPosY += (float)(WORD_COLLISION_SCALE_X * 0.9f);
		}
	}

	CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);

	for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
	{
		clickedWord[(pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = true;
	}

	if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
	{
		for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
		{
			if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
			{
				if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
				{
					if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
					{
						for (int deckSpace = 0; deckSpace < DECK_WORD_MAX; ++deckSpace)
						{
							if (!pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] && !clickedWord[wordDatas])
							{
								pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] = (MAGIC_KNIGHT_WORD)wordDatas;

								clickedWord[wordDatas] = true;
							}
						}
					}
				}
			}
		}

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
			{
				if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pDeckComponentCollisionsVertex[wordDatas].ImageVertex))
				{
					clickedWord[(pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = false;

					pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas] = VOID_WORD;
				}
			}
		}

		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
		{
			memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);

			*scene = HOME_SCENE;
		}
	}

	return;
}
