#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"CharactarInfo.h"
#include"ControlAlterDeck.h"

void ControlAlterDeck(SCENE* scene,WordData* pPlayerWordDatas, Deck* pPlayerDecks, ImagesCustomVertex* pChoiseWordCollisionsVertex,ImagesCustomVertex* pDeckComponentCollisionsVertex,
	ImagesCustomVertex* pSkillInfo,CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices,CustomVertex* pWordDatasBackVertices,
	PLAYERTYPE* playerType, int* pDeckNumToAlter,bool* clickedWord,bool* pChoiceWordData)
{	
	//マウス
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	switch (*playerType)
	{
	case WEAPON_MASTER:
	{
		static int frameCount = INIT_FRAME;

		if (frameCount == INIT_FRAME)
		{
			memset(clickedWord, 0, sizeof(bool)*WEAPON_MASTER_WORD_MAX);
			ZeroMemory(pChoiceWordData, sizeof(bool)*WEAPON_MASTER_WORD_MAX);

			for (int word = SPACE_WORD;word < WEAPON_MASTER_WORD_MAX;++word)
			{
				pPlayerWordDatas[word].m_costMax = 1;
				pPlayerWordDatas[word].m_have = 1;

				for (int skill = 0;skill < SKILL_SLOT_MAX;++skill)
				{
					pPlayerWordDatas[word].m_skillSlot[skill] = 0;
				}
			}

			pPlayerWordDatas[SPACE_WORD].m_have = 0;
			pPlayerWordDatas[SPACE_WORD].m_costMax = 0;
			pPlayerDecks[(*pDeckNumToAlter)].m_costMax = 120;

			frameCount = 0;
		}

		const float WORD_COLLISION_SCALE_X = (DISPLAY_WIDTH) / 30;
		const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X;

		float listWordPosX = (float)(WORD_COLLISION_SCALE_X * 2);
		float listWordPosY = WORD_COLLISION_SCALE_X * 4;

		const int WORD_NEW_LINE = 5;

		memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*WEAPON_MASTER_WORD_MAX);

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

		if (wordSlidePosY < (int)(-WORD_COLLISION_SCALE_X * 2.5 * (haveWordNum / (WORD_NEW_LINE))))
		{
			wordSlidePosY = (int)(-WORD_COLLISION_SCALE_X * 2.5 * (haveWordNum / (WORD_NEW_LINE)));
		}

		haveWordNum = 0;

		for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
		{
			if (pPlayerWordDatas[wordDatas].m_have)
			{
				haveWordNum++;

				CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, listWordPosX, listWordPosY + wordSlidePosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);

				listWordPosX += (WORD_COLLISION_SCALE_X * 4.f);

				if (!((haveWordNum) % (WORD_NEW_LINE)))
				{
					listWordPosX = (float)(WORD_COLLISION_SCALE_X * 2);
					listWordPosY += (float)(WORD_COLLISION_SCALE_X*2.5);
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
		const float DECK_WORD_COLLISION_SCALE = (DISPLAY_WIDTH) / 55;
		float deckComponentPosX = (float)(DECK_WORD_COLLISION_SCALE * 2);
		float deckComponentPosY = DISPLAY_HEIGHT * 0.765f;

		if (deckComponentSlidePosX > 0)
		{
			deckComponentSlidePosX = 0;
		}

		if (deckComponentSlidePosX < (int)(-DECK_WORD_COLLISION_SCALE * 3 * (DECK_COMPONENT_NEW_LINE - 1)))
		{
			deckComponentSlidePosX = (int)(-DECK_WORD_COLLISION_SCALE * 3 * (DECK_COMPONENT_NEW_LINE - 1));
		}

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			CustomImageVerticies(pDeckComponentCollisionsVertex[wordDatas].ImageVertex, deckComponentPosX + deckComponentSlidePosX, deckComponentPosY,
				DECK_WORD_COLLISION_SCALE, DECK_WORD_COLLISION_SCALE);

			deckComponentPosX += (float)(WORD_COLLISION_SCALE_X * 2.3);

			if (!((wordDatas + 1) % (DECK_COMPONENT_NEW_LINE)))
			{
				deckComponentPosX = (float)(DECK_WORD_COLLISION_SCALE * 2);
				deckComponentPosY += (float)(DECK_WORD_COLLISION_SCALE*2.3f);
			}
		}

		ZeroMemory(pSkillInfo, sizeof(ImagesCustomVertex)*SKILL_COST_MAX);

		float skillInfoPosY = (float)(DISPLAY_HEIGHT * 0.28f);
		const float SKILL_INFO_XSCALE = (float)(DISPLAY_WIDTH * 0.125f);
		const float SKILL_INFO_YSCALE = (float)(DISPLAY_HEIGHT * 0.047f);

		for (int skill = VOID_SKILL;skill < SKILL_COST_MAX;++skill)
		{
			CustomImageVerticies(pSkillInfo[skill].ImageVertex, DISPLAY_WIDTH * 0.85f, skillInfoPosY, SKILL_INFO_XSCALE, SKILL_INFO_YSCALE);

			skillInfoPosY += SKILL_INFO_YSCALE * 1.5f;
		}

		CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas])] = true;
		}

		const int SKILL_COST[SKILL_MAX] = { 0,3,3,3,6,3,4,12 };
		static int ChoiceWordDataBuff = 0;

		CustomVertex cursol[4];
		const float CURSOL_POSX = DISPLAY_WIDTH * 0.8f;
		const float CURSOL_SCALE = DISPLAY_WIDTH * 0.01f;

		CustomVertex initVertex[4];
		CustomImageVerticies(initVertex, DISPLAY_WIDTH*0.8f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.035f, DISPLAY_HEIGHT*0.025f);

		if (g_mouseState.mousePush[RIGHT_CLICK])
		{
			for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
			{
				if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
				{
					if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
					{
						if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
						{
							pChoiceWordData[wordDatas] = true;

							if (pChoiceWordData[wordDatas] == true)
							{
								pChoiceWordData[ChoiceWordDataBuff] = false;
							}

							ChoiceWordDataBuff = wordDatas;
						}
					}
				}
			}
		}

		for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
		{
			if (pChoiceWordData[wordDatas] == true)
			{
				for (int costConfig = 1;costConfig < 3;++costConfig)
				{
					switch (costConfig)
					{
					case 1:
						CustomImageVerticies(cursol, CURSOL_POSX, DISPLAY_HEIGHT*0.2f, CURSOL_SCALE, CURSOL_SCALE);

						if (g_mouseState.mousePush[LEFT_CLICK])
						{
							if (RectToRectCollisionCheak(mouseCursorCollisionVertex, cursol))
							{
								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax -= (pPlayerWordDatas[wordDatas].m_costMax);

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

								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax += pPlayerWordDatas[wordDatas].m_costMax;

							}
						}
						break;

					case 2:
						CustomImageVerticies(cursol, CURSOL_POSX + DISPLAY_WIDTH * 0.12f, DISPLAY_HEIGHT*0.2f, CURSOL_SCALE, CURSOL_SCALE);

						if (g_mouseState.mousePush[LEFT_CLICK])
						{
							if (RectToRectCollisionCheak(mouseCursorCollisionVertex, cursol))
							{
								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax -= (pPlayerWordDatas[wordDatas].m_costMax);

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

								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax += pPlayerWordDatas[wordDatas].m_costMax;

							}
						}
						break;
					}

				}

				int skillSlotSpace = SKILL_SLOT_MAX;

				for (int skill = MP_PLUS_2;skill < SKILL_COST_MAX;++skill)
				{
					if (g_mouseState.mousePush[LEFT_CLICK])
					{
						if (!RectToRectCollisionCheak(mouseCursorCollisionVertex, pSkillInfo[skill].ImageVertex))
						{
							continue;
						}

						if (pPlayerWordDatas[wordDatas].m_costMax < pPlayerWordDatas[wordDatas].m_currentCost + SKILL_COST[skill])
						{
							continue;
						}

						for (int skillSpace = 0;skillSpace < 4;++skillSpace)
						{
							if (pPlayerWordDatas[wordDatas].m_skillSlot[skillSpace] == VOID_SKILL)
							{
								skillSlotSpace = skillSpace;

								pPlayerWordDatas[wordDatas].m_currentCost += SKILL_COST[skill];

								pPlayerWordDatas[wordDatas].m_skillSlot[skillSlotSpace] = skill;

								skillSlotSpace = SKILL_SLOT_MAX;

								break;
							}
						}

						if (skillSlotSpace == SKILL_SLOT_MAX)
						{
							break;
						}


					}
				}
			}
		}

		if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
		{
			for (int wordDatas = SPACE_WORD; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
			{
				if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
				{
					if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
					{
						if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
						{
							for (int deckSpace = 0; deckSpace < DECK_WORD_MAX; ++deckSpace)
							{
								if (!pPlayerDecks[(*pDeckNumToAlter)].m_wordId[deckSpace] && !clickedWord[wordDatas])
								{
									pPlayerDecks[(*pDeckNumToAlter)].m_wordId[deckSpace] = (MAGIC_KNIGHT_WORD)wordDatas;

									if (pPlayerDecks[(*pDeckNumToAlter)].m_wordNum < 40)
									{
										clickedWord[wordDatas] = true;
										pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax += pPlayerWordDatas[wordDatas].m_costMax;
										pPlayerDecks[(*pDeckNumToAlter)].m_wordNum += 1;
									}
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
						if (pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas] == SPACE_WORD)
						{
							break;
						}

						clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas])] = false;

						pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax -= pPlayerWordDatas[pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas]].m_costMax;

						pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas] = SPACE_WORD;

						pPlayerDecks[(*pDeckNumToAlter)].m_wordNum -= 1;
					}
				}
			}

			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, initVertex))
			{
				for (int word = SPACE_WORD;word < WEAPON_MASTER_WORD_MAX;++word)
				{
					if (pChoiceWordData[word] == true)
					{
						pPlayerWordDatas[word].m_costMax = 1;
						pPlayerWordDatas[word].m_currentCost = 0;

						for (int skill = 0;skill < SKILL_SLOT_MAX;++skill)
						{
							pPlayerWordDatas[word].m_skillSlot[skill] = VOID_SKILL;
						}
					}
				}
				pPlayerWordDatas[VOID_WORD].m_costMax = 0;
			}

			CalcDeckCost(pPlayerWordDatas, &pPlayerDecks[(*pDeckNumToAlter)]);

			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
			{
				if (pPlayerDecks[(*pDeckNumToAlter)].m_costMax >= pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax)
				{
					if (pPlayerDecks[(*pDeckNumToAlter)].m_wordNum == 40)
					{
						memset(clickedWord, 0, sizeof(bool)*WEAPON_MASTER_WORD_MAX);
						ZeroMemory(pChoiceWordData, sizeof(bool)*WEAPON_MASTER_WORD_MAX);

						isSuccess = soundsManager.Stop(_T("Alterbgm"));
						isSuccess = soundsManager.Start(_T("Homebgm"));

						*scene = HOME_SCENE;
					}
				}
			}
		}

		break;
	}
	

	case MAGIC_KNIGHT:
	{
		static int frameCount = INIT_FRAME;

		if (frameCount == INIT_FRAME)
		{
			memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
			ZeroMemory(pChoiceWordData, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);

			for (int word = VOID_WORD;word < MAGIC_KNIGHT_WORD_MAX;++word)
			{
				pPlayerWordDatas[word].m_costMax = 1;
				pPlayerWordDatas[word].m_have = 1;

				for (int skill = 0;skill < SKILL_SLOT_MAX;++skill)
				{
					pPlayerWordDatas[word].m_skillSlot[skill] = 0;
				}
			}

			pPlayerWordDatas[VOID_WORD].m_have = 0;
			pPlayerWordDatas[VOID_WORD].m_costMax = 0;
			pPlayerDecks[(*pDeckNumToAlter)].m_costMax = 120;

			isSuccess = soundsManager.AddFile("Audio/BGM/antoinettenoniwa.mp3", _T("Alterbgm"));
			isSuccess = soundsManager.Start(_T("Alterbgm"), true);

			frameCount = 0;
		}

		const float WORD_COLLISION_SCALE_X = (DISPLAY_WIDTH) / 14;
		const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X / 5;

		float listWordPosX = (float)(WORD_COLLISION_SCALE_X * 1.3);
		float listWordPosY = WORD_COLLISION_SCALE_X;

		float deckComponentPosX = (float)(WORD_COLLISION_SCALE_X * 1.3);
		float deckComponentPosY = DISPLAY_HEIGHT * 0.765f;

		const int WORD_NEW_LINE = 4;

		memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*MAGIC_KNIGHT_WORD_MAX);

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

		ZeroMemory(pSkillInfo, sizeof(ImagesCustomVertex)*SKILL_COST_MAX);

		float skillInfoPosY = (float)(DISPLAY_HEIGHT * 0.28f);
		const float SKILL_INFO_XSCALE = (float)(DISPLAY_WIDTH * 0.125f);
		const float SKILL_INFO_YSCALE = (float)(DISPLAY_HEIGHT * 0.047f);

		for (int skill = VOID_SKILL;skill < SKILL_COST_MAX;++skill)
		{
			CustomImageVerticies(pSkillInfo[skill].ImageVertex, DISPLAY_WIDTH * 0.85f, skillInfoPosY, SKILL_INFO_XSCALE, SKILL_INFO_YSCALE);

			skillInfoPosY += SKILL_INFO_YSCALE * 1.5f;
		}

		CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);

		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
		{
			clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas])] = true;
		}

		const int SKILL_COST[SKILL_MAX] = { 0,3,3,3,6,3,4,12 };
		static int ChoiceWordDataBuff = 0;

		CustomVertex cursol[4];
		const float CURSOL_POSX = DISPLAY_WIDTH * 0.8f;
		const float CURSOL_SCALE = DISPLAY_WIDTH * 0.01f;

		CustomVertex initVertex[4];
		CustomImageVerticies(initVertex, DISPLAY_WIDTH*0.8f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.035f, DISPLAY_HEIGHT*0.025f);

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

							if (pChoiceWordData[wordDatas] == true)
							{
								pChoiceWordData[ChoiceWordDataBuff] = false;
							}

							ChoiceWordDataBuff = wordDatas;
						}
					}
				}
			}
		}

		for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
		{
			if (pChoiceWordData[wordDatas] == true)
			{
				for (int costConfig = 1;costConfig < 3;++costConfig)
				{
					switch (costConfig)
					{
					case 1:
						CustomImageVerticies(cursol, CURSOL_POSX, DISPLAY_HEIGHT*0.2f, CURSOL_SCALE, CURSOL_SCALE);

						if (g_mouseState.mousePush[LEFT_CLICK])
						{
							if (RectToRectCollisionCheak(mouseCursorCollisionVertex, cursol))
							{
								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax -= (pPlayerWordDatas[wordDatas].m_costMax);

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

								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax += pPlayerWordDatas[wordDatas].m_costMax;

							}
						}
						break;

					case 2:
						CustomImageVerticies(cursol, CURSOL_POSX + DISPLAY_WIDTH * 0.12f, DISPLAY_HEIGHT*0.2f, CURSOL_SCALE, CURSOL_SCALE);

						if (g_mouseState.mousePush[LEFT_CLICK])
						{
							if (RectToRectCollisionCheak(mouseCursorCollisionVertex, cursol))
							{
								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax -= (pPlayerWordDatas[wordDatas].m_costMax);

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

								pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax += pPlayerWordDatas[wordDatas].m_costMax;

							}
						}
						break;
					}
				}

				int skillSlotSpace = SKILL_SLOT_MAX;

				for (int skill = MP_PLUS_2;skill < SKILL_COST_MAX;++skill)
				{
					if (g_mouseState.mousePush[LEFT_CLICK])
					{
						if (!RectToRectCollisionCheak(mouseCursorCollisionVertex, pSkillInfo[skill].ImageVertex))
						{
							continue;
						}

						if (pPlayerWordDatas[wordDatas].m_costMax < pPlayerWordDatas[wordDatas].m_currentCost + SKILL_COST[skill])
						{
							continue;
						}

						for (int skillSpace = 0;skillSpace < 4;++skillSpace)
						{
							if (pPlayerWordDatas[wordDatas].m_skillSlot[skillSpace] == VOID_SKILL)
							{
								skillSlotSpace = skillSpace;

								pPlayerWordDatas[wordDatas].m_currentCost += SKILL_COST[skill];

								pPlayerWordDatas[wordDatas].m_skillSlot[skillSlotSpace] = skill;

								skillSlotSpace = SKILL_SLOT_MAX;

								break;
							}
						}

						if (skillSlotSpace == SKILL_SLOT_MAX)
						{
							break;
						}
					}
				}
			}
		}

		if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
		{
			for (int wordDatas = VOID_WORD; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
			{
				if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
				{
					if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
					{
						if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
						{
							for (int deckSpace = 0; deckSpace < DECK_WORD_MAX; ++deckSpace)
							{
								if (!pPlayerDecks[(*pDeckNumToAlter)].m_wordId[deckSpace] && !clickedWord[wordDatas])
								{
									pPlayerDecks[(*pDeckNumToAlter)].m_wordId[deckSpace] = (MAGIC_KNIGHT_WORD)wordDatas;

									if (pPlayerDecks[(*pDeckNumToAlter)].m_wordNum < 40)
									{
										clickedWord[wordDatas] = true;
										pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax += pPlayerWordDatas[wordDatas].m_costMax;
										pPlayerDecks[(*pDeckNumToAlter)].m_wordNum += 1;
									}
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
						if (pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas] == VOID_WORD)
						{
							break;
						}

						clickedWord[(pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas])] = false;

						pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax -= pPlayerWordDatas[pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas]].m_costMax;

						pPlayerDecks[(*pDeckNumToAlter)].m_wordId[wordDatas] = VOID_WORD;

						pPlayerDecks[(*pDeckNumToAlter)].m_wordNum -= 1;
					}
				}
			}

			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, initVertex))
			{
				for (int word = VOID_WORD;word < MAGIC_KNIGHT_WORD_MAX;++word)
				{
					if (pChoiceWordData[word] == true)
					{
						pPlayerWordDatas[word].m_costMax = 1;
						pPlayerWordDatas[word].m_currentCost = 0;

						for (int skill = 0;skill < SKILL_SLOT_MAX;++skill)
						{
							pPlayerWordDatas[word].m_skillSlot[skill] = VOID_SKILL;
						}
					}
				}
				pPlayerWordDatas[VOID_WORD].m_costMax = 0;
			}

			CalcDeckCost(pPlayerWordDatas, &pPlayerDecks[(*pDeckNumToAlter)]);

			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
			{
				if (pPlayerDecks[(*pDeckNumToAlter)].m_costMax >= pPlayerDecks[(*pDeckNumToAlter)].m_currentCostMax)
				{
					if (pPlayerDecks[(*pDeckNumToAlter)].m_wordNum == 40)
					{
						memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
						ZeroMemory(pChoiceWordData, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);

						isSuccess = soundsManager.Stop(_T("Alterbgm"));
						isSuccess = soundsManager.Start(_T("Homebgm"));

						*scene = HOME_SCENE;
					}
				}
			}
		}
		break;
	}
	}

	return;
}

void CalcDeckCost(WordData* pPlayerWordDatas, Deck* pPlayerDecks)
{
	pPlayerDecks->m_currentCostMax = 0;

	for (int deckWord = 0;deckWord < DECK_WORD_MAX;++deckWord)
	{
		pPlayerDecks->m_currentCostMax += pPlayerWordDatas[pPlayerDecks->m_wordId[deckWord]].m_costMax;
	}
}
