#include"ControlWeaponMasterAction.h"

void ControlWeaponMasterAction(WeaponMasterWordData* pWeaponMasterWordData, WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas,
	ImagesCustomVertex* pWeaponMasterDeckVerticies, ImagesCustomVertex* pWeaponMasterAction, int *pPage)
{

	//必殺技が発動中ならこの後の処理を行わない
	if (pWeaponMasterActionDatas->m_useAction)
	{
		return;
	}

	const float MOUSE_SCALE = 0.5;

	CustomVertex mouseState[RECT_VERTEX_NUM];
	CustomVertex pageTransition[4];
	CustomImageVerticies(mouseState, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_SCALE, MOUSE_SCALE);

	//ページ遷移用のカーソルの設定
	for (int rectForPageTransition = 0;rectForPageTransition < 2;rectForPageTransition++)
	{
		switch (rectForPageTransition)
		{
		case 0:
			CustomImageVerticies(pageTransition, DISPLAY_WIDTH - (DISPLAY_WIDTH / 5.f), DISPLAY_HEIGHT / 1.4f, DISPLAY_WIDTH / 75.f, DISPLAY_WIDTH / 75.f);

			if (RectToRectCollisionCheak(mouseState, pageTransition))
			{
				if (g_mouseState.mousePush[LEFT_CLICK])
				{
					if (*pPage == 2)
					{
						*pPage = 1;
					}

					if (*pPage == 3)
					{
						*pPage = 2;
					}

					if (*pPage == 4)
					{
						*pPage = 3;
					}
				}
				
			}

			break;

		case 1:
			CustomImageVerticies(pageTransition, DISPLAY_WIDTH - (DISPLAY_WIDTH / 15.f), DISPLAY_HEIGHT / 1.4f, DISPLAY_WIDTH / 75.f, DISPLAY_WIDTH / 75.f);

			if (RectToRectCollisionCheak(mouseState, pageTransition))
			{
				if (g_mouseState.mousePush[LEFT_CLICK])
				{
					if (*pPage == 3)
					{
						(*pPage) = 4;
					}

					if (*pPage == 2)
					{
						(*pPage) = 3;
					}

					if (*pPage == 1)
					{
						(*pPage) = 2;
					}
				}
			}
			

			break;
		}
	}


	//当たり判定用のCustomVertexの設定
	switch (*pPage)
	{
	case 1:

		for (int wordLists = 0;wordLists < 10;wordLists++)
		{
			WeaponMasterWordListsPageTransition(pWeaponMasterDeckVerticies, wordLists);
			if (g_mouseState.mousePush[LEFT_CLICK])
			{
				//当たっていない
				if (!RectToRectCollisionCheak(mouseState, pWeaponMasterDeckVerticies[wordLists].ImageVertex))
				{
					continue;
				}

				//SPACE_WORD
				if (!pWeaponMasterDeck->m_wordIds[wordLists])
				{
					break;
				}

				const int WEAPON_MASTER_ACTION_WORDS_FULL = 10;
				int weaponMasterActionWordSpace = 10;

				//スペースを探す
				for (int toTakeAction = 0;toTakeAction < WEAPON_MASTER_ACTION_LISTS;++toTakeAction)
				{
					if (pWeaponMasterActionDatas->m_componentWordIds[toTakeAction] == (WEAPON_MASTER_WORD_LISTS)NULL)
					{
						weaponMasterActionWordSpace = toTakeAction;

						break;
					}
				}

				//スペースがなかったら
				if (weaponMasterActionWordSpace == WEAPON_MASTER_ACTION_WORDS_FULL)
				{
					break;
				}

				//必殺技を代入
				pWeaponMasterActionDatas->m_componentWordIds[weaponMasterActionWordSpace] = pWeaponMasterDeck->m_wordIds[wordLists];
				pWeaponMasterDeck->m_wordIds[wordLists] = SPACE_WORD;

				//手札の位置
				pWeaponMasterActionDatas->m_handPos[weaponMasterActionWordSpace] = wordLists;

				//必殺技
				for (int actionConponentWord = 0; actionConponentWord < WEAPON_MASTER_ACTION_LISTS; ++actionConponentWord)
				{
					//当たっていなかったら
					if (!RectToRectCollisionCheak(mouseState, pWeaponMasterAction[actionConponentWord].ImageVertex))
					{
						continue;
					}

					if (pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord] == (WEAPON_MASTER_WORD_LISTS)NULL)
					{
						break;
					}

					//リムーブ
					pWeaponMasterDeck->m_wordIds[(pWeaponMasterActionDatas->m_handPos[actionConponentWord])] = pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord];
					pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord] = (WEAPON_MASTER_WORD_LISTS)NULL;
					pWeaponMasterActionDatas->m_handPos[actionConponentWord] = 0;
				}

			}
		}

		WeaponMasterInputInfoToAction(pWeaponMasterDeck, pWeaponMasterActionDatas, pWeaponMasterAction, mouseState);

		break;

	case 2:

		for (int wordLists = 10;wordLists < 20;wordLists++)
		{
			WeaponMasterWordListsPageTransition(pWeaponMasterDeckVerticies, wordLists);
			if (g_mouseState.mousePush[LEFT_CLICK])
			{
				//当たっていない
				if (!RectToRectCollisionCheak(mouseState, pWeaponMasterDeckVerticies[wordLists].ImageVertex))
				{
					continue;
				}

				//SPACE_WORD
				if (!pWeaponMasterDeck->m_wordIds[wordLists])
				{
					break;
				}

				const int WEAPON_MASTER_ACTION_WORDS_FULL = 10;
				int weaponMasterActionWordSpace = 10;

				//スペースを探す
				for (int toTakeAction = 0;toTakeAction < WEAPON_MASTER_ACTION_LISTS;++toTakeAction)
				{
					if (pWeaponMasterActionDatas->m_componentWordIds[toTakeAction] == (WEAPON_MASTER_WORD_LISTS)NULL)
					{
						weaponMasterActionWordSpace = toTakeAction;

						break;
					}
				}

				//スペースがなかったら
				if (weaponMasterActionWordSpace == WEAPON_MASTER_ACTION_WORDS_FULL)
				{
					break;
				}

				//必殺技を代入
				pWeaponMasterActionDatas->m_componentWordIds[weaponMasterActionWordSpace] = pWeaponMasterDeck->m_wordIds[wordLists];
				pWeaponMasterDeck->m_wordIds[wordLists] = SPACE_WORD;

				//手札の位置
				pWeaponMasterActionDatas->m_handPos[weaponMasterActionWordSpace] = wordLists;

				//必殺技
				for (int actionConponentWord = 0; actionConponentWord < WEAPON_MASTER_ACTION_LISTS; ++actionConponentWord)
				{
					//当たっていなかったら
					if (!RectToRectCollisionCheak(mouseState, pWeaponMasterAction[actionConponentWord].ImageVertex))
					{
						continue;
					}

					if (pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord] == (WEAPON_MASTER_WORD_LISTS)NULL)
					{
						break;
					}

					//リムーブ
					pWeaponMasterDeck->m_wordIds[(pWeaponMasterActionDatas->m_handPos[actionConponentWord])] = pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord];
					pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord] = (WEAPON_MASTER_WORD_LISTS)NULL;
					pWeaponMasterActionDatas->m_handPos[actionConponentWord] = 0;
				}

			}
		}

		WeaponMasterInputInfoToAction(pWeaponMasterDeck, pWeaponMasterActionDatas, pWeaponMasterAction, mouseState);

		break;

	case 3:

		for (int wordLists = 20;wordLists < 30;wordLists++)
		{
			WeaponMasterWordListsPageTransition(pWeaponMasterDeckVerticies, wordLists);
			if (g_mouseState.mousePush[LEFT_CLICK])
			{
				//当たっていない
				if (!RectToRectCollisionCheak(mouseState, pWeaponMasterDeckVerticies[wordLists].ImageVertex))
				{
					continue;
				}

				//SPACE_WORD
				if (!pWeaponMasterDeck->m_wordIds[wordLists])
				{
					break;
				}

				const int WEAPON_MASTER_ACTION_WORDS_FULL = 10;
				int weaponMasterActionWordSpace = 10;

				//スペースを探す
				for (int toTakeAction = 0;toTakeAction < WEAPON_MASTER_ACTION_LISTS;++toTakeAction)
				{
					if (pWeaponMasterActionDatas->m_componentWordIds[toTakeAction] == (WEAPON_MASTER_WORD_LISTS)NULL)
					{
						weaponMasterActionWordSpace = toTakeAction;

						break;
					}
				}

				//スペースがなかったら
				if (weaponMasterActionWordSpace == WEAPON_MASTER_ACTION_WORDS_FULL)
				{
					break;
				}

				//必殺技を代入
				pWeaponMasterActionDatas->m_componentWordIds[weaponMasterActionWordSpace] = pWeaponMasterDeck->m_wordIds[wordLists];
				pWeaponMasterDeck->m_wordIds[wordLists] = SPACE_WORD;

				//手札の位置
				pWeaponMasterActionDatas->m_handPos[weaponMasterActionWordSpace] = wordLists;

			}
		}

		WeaponMasterInputInfoToAction(pWeaponMasterDeck, pWeaponMasterActionDatas, pWeaponMasterAction, mouseState);

		break;

	case 4:

		for (int wordLists = 30;wordLists < 40;wordLists++)
		{
			WeaponMasterWordListsPageTransition(pWeaponMasterDeckVerticies, wordLists);
			if (g_mouseState.mousePush[LEFT_CLICK])
			{
				//当たっていない
				if (!RectToRectCollisionCheak(mouseState, pWeaponMasterDeckVerticies[wordLists].ImageVertex))
				{
					continue;
				}

				//SPACE_WORD
				if (!pWeaponMasterDeck->m_wordIds[wordLists])
				{
					break;
				}

				const int WEAPON_MASTER_ACTION_WORDS_FULL = 10;
				int weaponMasterActionWordSpace = 10;

				//スペースを探す
				for (int toTakeAction = 0;toTakeAction < WEAPON_MASTER_ACTION_LISTS;++toTakeAction)
				{
					if (pWeaponMasterActionDatas->m_componentWordIds[toTakeAction] == (WEAPON_MASTER_WORD_LISTS)NULL)
					{
						weaponMasterActionWordSpace = toTakeAction;

						break;
					}
				}

				//スペースがなかったら
				if (weaponMasterActionWordSpace == WEAPON_MASTER_ACTION_WORDS_FULL)
				{
					break;
				}

				//必殺技を代入
				pWeaponMasterActionDatas->m_componentWordIds[weaponMasterActionWordSpace] = pWeaponMasterDeck->m_wordIds[wordLists];
				pWeaponMasterDeck->m_wordIds[wordLists] = SPACE_WORD;

				//手札の位置
				pWeaponMasterActionDatas->m_handPos[weaponMasterActionWordSpace] = wordLists;

			}
		}

		WeaponMasterInputInfoToAction(pWeaponMasterDeck, pWeaponMasterActionDatas, pWeaponMasterAction, mouseState);

		break;
	}

	if (g_mouseState.mousePush[RIGHT_CLICK] || g_keyState.keyPush[DIK_RETURN])
	{
		/*必殺技が完成したときの処理　開始*/
		for (int actionConponentWord = 0; actionConponentWord < WEAPON_MASTER_ACTION_LISTS; ++actionConponentWord)
		{
			WEAPON_MASTER_WORD_LISTS WeaponMasterWord = pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord];

			(pWeaponMasterActionDatas->m_attackTotals[(pWeaponMasterWordData[WeaponMasterWord].m_attack)]) += 1;
			(pWeaponMasterActionDatas->m_elementTotals[(pWeaponMasterWordData[WeaponMasterWord].m_element)]) += 1;
			(pWeaponMasterActionDatas->m_specialAbilities) |= (pWeaponMasterWordData[WeaponMasterWord].m_specialAbilities);
			(pWeaponMasterActionDatas->m_useAction) = true;
		}
		/*必殺技が完成したときの処理　終了*/
	}
	const float ACTION_COMPONENT_WORD_COLLISION_WIDTH = (float)(DISPLAY_WIDTH / 30);
	const float ACTION_COMPONENT_WORD_COLLISION_HEIGHT = ACTION_COMPONENT_WORD_COLLISION_WIDTH;

	//アクションの文字の頂点座標設定
	for (int actionComponentWord = 0;actionComponentWord < WEAPON_MASTER_ACTION_LISTS;++actionComponentWord)
	{
		CustomImageVerticies(pWeaponMasterAction[actionComponentWord].ImageVertex,
			(DISPLAY_WIDTH / 5) + (ACTION_COMPONENT_WORD_COLLISION_WIDTH * 2)*actionComponentWord, DISPLAY_HEIGHT - (ACTION_COMPONENT_WORD_COLLISION_HEIGHT * 2),
			ACTION_COMPONENT_WORD_COLLISION_WIDTH, ACTION_COMPONENT_WORD_COLLISION_HEIGHT);
	}

}

void WeaponMasterWordListsPageTransition(ImagesCustomVertex* pWeaponMasterDeckVerticies,int wordLists)
{
	const float WEAPON_MASTER_WORD_LIST_LEFT_POS = DISPLAY_WIDTH - (DISPLAY_WIDTH / 5.5f);
	const float WEAPON_MASTER_WORD_LIST_RIGHT_POS = DISPLAY_WIDTH - (DISPLAY_WIDTH / 11.f);
	const float WEAPON_MASTER_WORD_LIST_POSY = DISPLAY_HEIGHT / 10.f;
	const float WEAPON_MASTER_WORD_LIST_SCALE = DISPLAY_WIDTH / 55.f;

	switch (wordLists)
	{
	case 0:
	case 10:
	case 20:
	case 30:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_LEFT_POS, WEAPON_MASTER_WORD_LIST_POSY, WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 1:
	case 11:
	case 21:
	case 31:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_RIGHT_POS, WEAPON_MASTER_WORD_LIST_POSY, WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 2:
	case 12:
	case 22:
	case 32:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_LEFT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 4), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 3:
	case 13:
	case 23:
	case 33:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_RIGHT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 4), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 4:
	case 14:
	case 24:
	case 34:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_LEFT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 8), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 5:
	case 15:
	case 25:
	case 35:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_RIGHT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 8), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 6:
	case 16:
	case 26:
	case 36:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_LEFT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 12), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 7:
	case 17:
	case 27:
	case 37:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_RIGHT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 12), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 8:
	case 18:
	case 28:
	case 38:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_LEFT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 16), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	case 9:
	case 19:
	case 29:
	case 39:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, WEAPON_MASTER_WORD_LIST_RIGHT_POS, WEAPON_MASTER_WORD_LIST_POSY + (WEAPON_MASTER_WORD_LIST_SCALE * 16), WEAPON_MASTER_WORD_LIST_SCALE, WEAPON_MASTER_WORD_LIST_SCALE);
		break;

	}
}

void WeaponMasterInputInfoToAction(WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas, ImagesCustomVertex* pWeaponMasterAction, CustomVertex* mouseState)
{
	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		//必殺技
		for (int actionConponentWord = 0; actionConponentWord < WEAPON_MASTER_ACTION_LISTS; ++actionConponentWord)
		{
			//当たっていなかったら
			if (!RectToRectCollisionCheak(mouseState, pWeaponMasterAction[actionConponentWord].ImageVertex))
			{
				continue;
			}

			if (pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord] == (WEAPON_MASTER_WORD_LISTS)NULL)
			{
				break;
			}

			//リムーブ
			pWeaponMasterDeck->m_wordIds[(pWeaponMasterActionDatas->m_handPos[actionConponentWord])] = pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord];
			pWeaponMasterActionDatas->m_componentWordIds[actionConponentWord] = (WEAPON_MASTER_WORD_LISTS)NULL;
			pWeaponMasterActionDatas->m_handPos[actionConponentWord] = 0;
		}
	}
}
