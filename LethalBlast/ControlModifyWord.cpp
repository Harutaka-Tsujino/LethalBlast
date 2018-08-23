#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlModify(SCENE* scene, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	ImagesCustomVertex* pChoiseWordCollisionsVertex, CustomVertex* pWordDatasBackVertices, CustomVertex* pEndModifyVertices, CustomVertex* pBackgroundVertices,
	int* modifyWordBox, ImagesCustomVertex* modifyBoxVertices,CustomVertex* decideModify,bool* clickedWord)
{
	static int frameCount = -1;

	if (frameCount == -1)
	{
		memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
		ZeroMemory(modifyWordBox, sizeof(int) * MATERIALS_NUM);

		frameCount = 0;
	}

	for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
	{
		CustomImageVerticies(modifyBoxVertices[modifyBox].ImageVertex, DISPLAY_WIDTH / 15.f + ((DISPLAY_WIDTH / 5.f)*(modifyBox)),
			DISPLAY_HEIGHT -DISPLAY_HEIGHT / 8.f, DISPLAY_WIDTH / 20.f, DISPLAY_WIDTH / 40.f);
	}

	CustomImageVerticies(decideModify, DISPLAY_WIDTH*0.65f, DISPLAY_HEIGHT-DISPLAY_HEIGHT / 8.f, DISPLAY_WIDTH / 20.f, DISPLAY_WIDTH / 40.f);

	//マウス
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	const float WORD_COLLISION_SCALE_X = DISPLAY_WIDTH / 32;
	const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X / 2;

	float listWordPosX = WORD_COLLISION_SCALE_X * 2;
	float listWordPosY = WORD_COLLISION_SCALE_X * 2;

	const int WORD_NEW_LINE = 7;

	memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*MAGIC_KNIGHT_WORD_MAX);

	static int wordSlidePosY = 0;
	const int SLIDE_SPEED = 13;

	CustomImageVerticies(pWordDatasBackVertices, DISPLAY_WIDTH*0.875f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH*0.125f, DISPLAY_HEIGHT / 2.f, 0xFFF5F5F5);

	CustomImageVerticies(pBackgroundVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*(0.65f + 0.175f), DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.175f, 0xFFFFD500);

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

	if (wordSlidePosY > 0)
	{
		wordSlidePosY = 0;
	}

	if (wordSlidePosY < (int)(-WORD_COLLISION_SCALE_X * 4 * (MAGIC_KNIGHT_WORD_MAX / (WORD_NEW_LINE - 1))))
	{
		wordSlidePosY = (int)(-WORD_COLLISION_SCALE_X * 4 * (MAGIC_KNIGHT_WORD_MAX / (WORD_NEW_LINE - 1)));
	}

	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
	{
		if (pMagicKnightWordDatas[wordDatas].m_have)
		{
			CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, listWordPosX, listWordPosY + wordSlidePosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

			listWordPosX += (WORD_COLLISION_SCALE_X * 4);

			if (!((wordDatas + 1) % (WORD_NEW_LINE)))
			{
				listWordPosX = WORD_COLLISION_SCALE_X * 2;
				listWordPosY += (WORD_COLLISION_SCALE_X * 4);
			}
		}
	}

	CustomImageVerticies(pEndModifyVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);

	if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
	{
		for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
		{
			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
			{
				if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
				{
					for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
					{
						if (modifyWordBox[modifyBox] == 0)
						{
							if (modifyBox == 1 && modifyWordBox[0] == wordDatas)
							{
								break;
							}

							if (modifyBox == 0 && modifyWordBox[1] == wordDatas)
							{
								break;
							}

							modifyWordBox[modifyBox] = wordDatas;

							clickedWord[wordDatas] = true;

							break;
						}
					}
				}
			}
		}

		for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
		{
			if (RectToRectCollisionCheak(modifyBoxVertices[modifyBox].ImageVertex, mouseCursorCollisionVertex))
			{
				clickedWord[modifyWordBox[modifyBox]] = false;

				modifyWordBox[modifyBox] = 0;
			}
		}

		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, decideModify))
		{
			for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
			{
				if (!modifyWordBox[modifyBox])
				{
					return;
				}
			}

			for (int word = VOID_WORD + 1; word < MAGIC_KNIGHT_WORD_MAX; ++word)
			{
				if (pMagicKnightWordDatas[word].m_matterials[0] == modifyWordBox[0])
				{
					if (pMagicKnightWordDatas[word].m_matterials[1] == modifyWordBox[1])
					{
						pMagicKnightWordDatas[word].m_have = true;

						break;
					}
				}

				if (pMagicKnightWordDatas[word].m_matterials[0] == modifyWordBox[1])
				{
					if (pMagicKnightWordDatas[word].m_matterials[1] == modifyWordBox[0])
					{
						pMagicKnightWordDatas[word].m_have = true;

						break;
					}
				}
			}
		}

		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndModifyVertices))
		{
			memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
			memset(modifyWordBox, 0, sizeof(int)*MATERIALS_NUM);

			*scene = HOME_SCENE;
		}
	}

	return;
}
