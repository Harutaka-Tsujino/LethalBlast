#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlAlterDeck(SCENE* scene,WordData* pMagicKnightWordDatas, ImagesCustomVertex* pChoiseWordCollisionsVertex,ImagesCustomVertex* pDeckComponentCollisionsVertex,
	CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices,CustomVertex* pWordDatasBackVertices,int* pDeckNumToAlter)
{
	//マウス
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	const float WORD_COLLISION_SCALE_X = (DISPLAY_WIDTH*0.75) / 32;
	const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X / 2;

	float listWordPosX = WORD_COLLISION_SCALE_X*2;
	float listWordPosY = WORD_COLLISION_SCALE_X*2;

	float deckComponentPosX = WORD_COLLISION_SCALE_X*2;
	float deckComponentPosY = DISPLAY_HEIGHT * 0.65f+ deckComponentPosX;

	const int WORD_NEW_LINE = 7;
	
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

	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
	{
		if (true/*pMagicKnightWordDatas[wordDatas].m_have*/)
		{
			CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, listWordPosX, listWordPosY + wordSlidePosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);
			
			listWordPosX += (WORD_COLLISION_SCALE_X * 4);

			if (!((wordDatas + 1) % (WORD_NEW_LINE)))
			{
				listWordPosX = WORD_COLLISION_SCALE_X*2;
				listWordPosY += (WORD_COLLISION_SCALE_X * 4);
			}
		}
	}

	static int deckComponentSlidePosX = 0;

	if (RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
	{
		if (g_keyState.keyHold[DIK_COMMA])
		{
			deckComponentSlidePosX -= SLIDE_SPEED;
		}

		if (g_keyState.keyHold[DIK_PERIOD])
		{
			deckComponentSlidePosX += SLIDE_SPEED;
		}
	}

	const int DECK_COMPONENT_NEW_LINE = 20;

	for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
	{
		if (true)
		{
			CustomImageVerticies(pDeckComponentCollisionsVertex[wordDatas].ImageVertex, deckComponentPosX+ deckComponentSlidePosX, deckComponentPosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

			deckComponentPosX += (WORD_COLLISION_SCALE_X * 4);

			if (!((wordDatas+1) % (DECK_COMPONENT_NEW_LINE)))
			{
				deckComponentPosX = WORD_COLLISION_SCALE_X * 2;
				deckComponentPosY += (WORD_COLLISION_SCALE_X * 4);
			}			
		}
	}

	CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);

	if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
		{
			*scene = CHOSE_DECK_TO_BATTLE_SCENE;
		}
	}

	return;
}
