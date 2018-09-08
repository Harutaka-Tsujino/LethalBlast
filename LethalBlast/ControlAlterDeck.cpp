#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"CharactarInfo.h"
#include"ControlAlterDeck.h"

void ControlAlterDeck(SCENE* scene,WordData* pPlayerWordDatas, PlayerDeck* pPlayerDecks, ImagesCustomVertex* pChoiseWordCollisionsVertex,ImagesCustomVertex* pDeckComponentCollisionsVertex,
	ImagesCustomVertex* pSkillInfo,CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices,CustomVertex* pWordDatasBackVertices,
	PLAYERTYPE* playerType, int* pDeckNumToAlter,bool* clickedWord,bool* pChoiceWordData)
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

	switch (*playerType)
	{
	/*case WEAPON_MASTER:

		const float WORD_COLLISION_SCALE_X = (DISPLAY_WIDTH) / 38;
		const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X;

		float listWordPosX = DISPLAY_WIDTH / 2.5f;
		float listWordPosY = DISPLAY_HEIGHT * 0.15f;

		float deckComponentPosX = (DISPLAY_WIDTH) / 76;
		float deckComponentPosY = deckComponentPosX;

		const int WORD_NEW_LINE = 5;

		memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*WEAPON_MASTER_WORD_MAX);
		memset(pDeckComponentCollisionsVertex, 0, sizeof(ImagesCustomVertex)*WEAPON_MASTER_ACTION_LISTS);

		static int wordSlidePosY = 0;
		const int SLIDE_SPEED = 40;

		CustomImageVerticies(pBackgroundVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*(0.65f + 0.175f), DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.175f, 0xFFFFD500);
		CustomImageVerticies(pWordDatasBackVertices, DISPLAY_WIDTH*0.875f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH*0.125f, DISPLAY_HEIGHT / 2.f, 0xFFF5F5F5);

		if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
		{
			if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
			{
				if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ > 0)
				{
					wordSlidePosY += SLIDE_SPEED;
				}

				if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ < 0)
				{
					wordSlidePosY -= SLIDE_SPEED;
				}
			}
		}

		int haveWordNum = 0;

		for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
		{
			if (pPlayerWordDatas[wordDatas].m_have)
			{
				haveWordNum++;
			}
		}

		if (wordSlidePosY > 0)
		{
			wordSlidePosY = 0;
		}

		if (wordSlidePosY < (int)(-WORD_COLLISION_SCALE_X * 2.8 * (haveWordNum / (WORD_NEW_LINE))))
		{
			wordSlidePosY = (int)(-WORD_COLLISION_SCALE_X * 2.8 * (haveWordNum / (WORD_NEW_LINE)));
		}

		haveWordNum = 0;

		for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
		{
			if (pPlayerWordDatas[wordDatas].m_have)
			{
				haveWordNum++;

				CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, listWordPosX, listWordPosY + wordSlidePosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

				listWordPosX += (WORD_COLLISION_SCALE_X * 2.3f);

				if (!((haveWordNum) % (WORD_NEW_LINE)))
				{
					listWordPosX = DISPLAY_WIDTH / 2.5f;
					listWordPosY += (float)(WORD_COLLISION_SCALE_X * 3.f);
				}
			}
		}

		static int deckComponentSlidePosX = 0;

		if (RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
		{
			if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ > 0)
			{
				deckComponentSlidePosX += SLIDE_SPEED;
			}

			if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ < 0)
			{
				deckComponentSlidePosX -= SLIDE_SPEED;
			}
		}

		const int DECK_COMPONENT_NEW_LINE = 20;

		if (deckComponentSlidePosX > 0)
		{
			deckComponentSlidePosX = 0;
		}

		if (deckComponentSlidePosX < (int)(-WORD_COLLISION_SCALE_X * 2 * (DECK_COMPONENT_NEW_LINE - 1)))
		{
			deckComponentSlidePosX = (int)(-WORD_COLLISION_SCALE_X * 2 * (DECK_COMPONENT_NEW_LINE - 1));
		}

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			CustomImageVerticies(pDeckComponentCollisionsVertex[wordDatas].ImageVertex, deckComponentPosX + deckComponentSlidePosX, deckComponentPosY,
				WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

			deckComponentPosX += (float)(WORD_COLLISION_SCALE_X * 2.3);

			if (!((wordDatas + 1) % (DECK_COMPONENT_NEW_LINE)))
			{
				deckComponentPosX = DISPLAY_WIDTH / 2.5f;
				deckComponentPosY += (float)(WORD_COLLISION_SCALE_X * 3.f);
			}
		}

		CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = true;
		}

		if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
		{
			for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
			{
				if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
				{
					if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
					{
						if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
						{
							for (int deckSpace = 0; deckSpace < DECK_WORD_MAX; ++deckSpace)
							{
								if (!pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] && !clickedWord[wordDatas])
								{
									pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] = (WEAPON_MASTER_WORD_LISTS)wordDatas;

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
						clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = false;

						pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas] = VOID_WORD;
					}
				}
			}

			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
			{
				memset(clickedWord, 0, sizeof(bool)*WEAPON_MASTER_WORD_MAX);

				*scene = HOME_SCENE;
			}
		}

		break;*/

	case MAGIC_KNIGHT:

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
		const int SLIDE_SPEED = 40;

		CustomImageVerticies(pBackgroundVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*(0.65f + 0.175f), DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.175f, 0xFFFFD500);
		CustomImageVerticies(pWordDatasBackVertices, DISPLAY_WIDTH*0.875f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH*0.125f, DISPLAY_HEIGHT / 2.f, 0xFFF5F5F5);

		if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
		{
			if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
			{
				if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ > 0)
				{
					wordSlidePosY += SLIDE_SPEED;
				}

				if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ < 0)
				{
					wordSlidePosY -= SLIDE_SPEED;
				}
			}
		}

		int haveWordNum = 0;

		for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
		{
			if (pPlayerWordDatas[wordDatas].m_have)
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
			if (pPlayerWordDatas[wordDatas].m_have)
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
			if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ > 0)
			{
				deckComponentSlidePosX += SLIDE_SPEED;
			}

			if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ < 0)
			{
				deckComponentSlidePosX -= SLIDE_SPEED;
			}
		}

		const int DECK_COMPONENT_NEW_LINE = 20;

		if (deckComponentSlidePosX > 0)
		{
			deckComponentSlidePosX = 0;
		}

		if (deckComponentSlidePosX < (int)(-WORD_COLLISION_SCALE_X * 2 * (DECK_COMPONENT_NEW_LINE - 1)))
		{
			deckComponentSlidePosX = (int)(-WORD_COLLISION_SCALE_X * 2 * (DECK_COMPONENT_NEW_LINE - 1));
		}

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			CustomImageVerticies(pDeckComponentCollisionsVertex[wordDatas].ImageVertex, deckComponentPosX + deckComponentSlidePosX, deckComponentPosY,
				WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

			deckComponentPosX += (float)(WORD_COLLISION_SCALE_X * 2.3);

			if (!((wordDatas + 1) % (DECK_COMPONENT_NEW_LINE)))
			{
				deckComponentPosX = (float)(WORD_COLLISION_SCALE_X*1.3);
				deckComponentPosY += (float)(WORD_COLLISION_SCALE_X * 0.9f);
			}
		}

		static float skillInfoPosY = DISPLAY_HEIGHT / 1.5f;
		const float SKILL_INFO_XSCALE = DISPLAY_WIDTH * 0.25f;
		const float SKILL_INFO_YSCALE = DISPLAY_HEIGHT / 21;

		for (int skill = MPプラス２;skill < SKILL_MAX;++skill)
		{
			CustomImageVerticies(pSkillInfo[skill].ImageVertex, DISPLAY_WIDTH * 0.25, skillInfoPosY, SKILL_INFO_XSCALE, SKILL_INFO_YSCALE);

			skillInfoPosY += SKILL_INFO_YSCALE * 2;
		}

		CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = true;
		}
		
		const int SKILL_COST[SKILL_MAX] = { 0,3,3,3,6,3,4,12 };

		CustomVertex cursol[4];
		const float CURSOL_POSX = DISPLAY_WIDTH * 0.7f;
		const float CURSOL_SCALE = DISPLAY_WIDTH * 0.025f;

		if (g_mouseState.mousePush[RIGHT_CLICK])
		{
			for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
			{
				if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
				{
					if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
					{
						if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
						{
							pChoiceWordData[wordDatas] = true;
						}
					}
				}
			}
		}

		for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
		{
			if (pChoiceWordData[wordDatas] = true)
			{
				CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, DISPLAY_WIDTH*0.85f, DISPLAY_HEIGHT*0.1f, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

				for (int costConfig = 1;costConfig < 3;++costConfig)
				{
					switch (costConfig)
					{
					case 1:
						CustomImageVerticies(cursol, CURSOL_POSX, DISPLAY_HEIGHT*0.7f, CURSOL_SCALE, CURSOL_SCALE);

						if (g_mouseState.mousePush[LEFT_CLICK])
						{
							if (RectToRectCollisionCheak(mouseCursorCollisionVertex, cursol))
							{
								if (pPlayerWordDatas[wordDatas].m_costMax == 3)
								{
									pPlayerWordDatas[wordDatas].m_costMax = 1;
								}

								if (pPlayerWordDatas[wordDatas].m_costMax == 6)
								{
									pPlayerWordDatas[wordDatas].m_costMax = 3;
								}

								if (pPlayerWordDatas[wordDatas].m_costMax == 12)
								{
									pPlayerWordDatas[wordDatas].m_costMax = 6;
								}

							}
						}
						break;

					case 2:
						CustomImageVerticies(cursol, CURSOL_POSX + DISPLAY_WIDTH * 0.1f, DISPLAY_HEIGHT*0.7f, CURSOL_SCALE, CURSOL_SCALE);

						if (g_mouseState.mousePush[LEFT_CLICK])
						{
							if (RectToRectCollisionCheak(mouseCursorCollisionVertex, cursol))
							{
								if (pPlayerWordDatas[wordDatas].m_costMax == 6)
								{
									pPlayerWordDatas[wordDatas].m_costMax = 12;
								}

								if (pPlayerWordDatas[wordDatas].m_costMax == 3)
								{
									pPlayerWordDatas[wordDatas].m_costMax = 6;
								}

								if (pPlayerWordDatas[wordDatas].m_costMax == 1)
								{
									pPlayerWordDatas[wordDatas].m_costMax = 3;
								}

							}
						}
						break;
					}

				}

				int skillSlotSpace = 3;
				const int SKILL_SLOT_MAX = 3;

				for (int skill = MPプラス２;skill < SKILL_MAX;++skill)
				{
					if (g_mouseState.mousePush[LEFT_CLICK])
					{
						if (!RectToRectCollisionCheak(mouseCursorCollisionVertex, pSkillInfo[skill].ImageVertex))
						{
							continue;
						}

						if (pPlayerWordDatas[wordDatas].m_costMax < pPlayerWordDatas[wordDatas].m_currentCost)
						{
							pPlayerWordDatas[wordDatas].m_skillSlot[skillSlotSpace] = 0;
							continue;
						}

						for (int skillSpace = 0;skillSpace < 4;++skillSpace)
						{
							if (pPlayerWordDatas[wordDatas].m_skillSlot[skillSpace] == 0)
							{
								skillSlotSpace = skillSpace;
								pPlayerWordDatas[wordDatas].m_currentCost += pPlayerWordDatas[wordDatas].m_skillSlot[skillSlotSpace];

								break;
							}
						}

						if (skillSlotSpace == SKILL_SLOT_MAX)
						{
							break;
						}

						pPlayerWordDatas->m_skillSlot[skillSlotSpace] = SKILL_COST[skill];

					}
				}
			}
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
								if (!pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] && !clickedWord[wordDatas])
								{
									pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] = (MAGIC_KNIGHT_WORD)wordDatas;

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
						clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = false;

						pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas] = VOID_WORD;
					}
				}
			}

			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
			{
				memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);

				*scene = HOME_SCENE;
			}
		}

		break;

	}
	return;
}
