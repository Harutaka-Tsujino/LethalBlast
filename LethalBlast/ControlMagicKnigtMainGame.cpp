#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlStageSelect.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlBattle.h"

//static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
//static MagicKnightPlayingDeck magicKnightPlayingDeck;
//static MagicKnightAction magicKnightAction;
//CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];
//CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

void ControlMagicKnightMainGame(SCENE* scene,WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex, HomingEffect* pHominEffect,
	VSData* battleData,int enemyActionNum,bool* isClear, CustomVertex* resultMask, StageDate* pStageData, EnemyST* pEnemyData,int selectedStage)
{
	//必殺技を発動している
	if (pMagicKnightAction->useAction)
	{
		ZeroMemory(pMagicKnightAction, sizeof(MagicKnightAction));

		bool haveHand = false;

		for (int hand = 0; hand < HAND_WORD_MAX; ++hand)
		{
			if (pMagicKnightPlayingDeck->m_handWordId[hand])
			{
				haveHand = true;
			}

			if (haveHand)
			{
				break;
			}

			else
			{
				if (hand != HAND_WORD_MAX - 1)
				{
					continue;
				}

				int currentDeck = pMagicKnightPlayingDeck->m_currentId;

				for (int word = 0; word < DECK_WORD_MAX; ++word)
				{
					pMagicKnightPlayingDeck->m_handWordId[word] = pMagicKnightDecks[currentDeck].m_wordIds[word];
				}
			}
		}
	}

	//フレームのカウント
	static int frameCount = INIT_FRAME;

	//初期化を行う
	if (frameCount == INIT_FRAME)
	{
		//構造体の初期化 全て0を代入する
		memset(pMagicKnightAction,0,sizeof(MagicKnightAction));

		//VOID_WORDだけ
		memset(pMagicKnightWordDatas, 0, sizeof(WordData));

		/*プレイ開始時の手札やデッキなどの初期化 開始*/
		//MAGIC_KNIGHT_WORD* pWordShuffleBuf = (MAGIC_KNIGHT_WORD*)malloc(sizeof(MAGIC_KNIGHT_WORD)*pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordNum);

		////重複しないようにするためデッキの単語識別子をバッファーに保存する
		//for (int deckWordNum = 0; deckWordNum < pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordNum; ++deckWordNum)
		//{
		//	pWordShuffleBuf[deckWordNum] = pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordIds[deckWordNum];
		//}

		////デッキの中の単語識別子をシャッフルする
		//for (int deckWordNum = 0; deckWordNum < DECK_WORD_MAX; deckWordNum++)
		//{
		//	int unshuffledDeckWordNum = pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordNum - deckWordNum;

		//	if (unshuffledDeckWordNum == 0)
		//	{
		//		break;
		//	}

		//	int chosenNum = rand() % (unshuffledDeckWordNum);

		//	pMagicKnightPlayingDeck->m_deckWordId[deckWordNum] = pWordShuffleBuf[chosenNum];

		//	//一度選ばれたものは選ばれる範囲から外す
		//	for (int backShift = chosenNum; backShift < unshuffledDeckWordNum; ++backShift)
		//	{
		//		pWordShuffleBuf[backShift] = pWordShuffleBuf[backShift + 1];
		//	}
		//}

		////開始のドロー
		//for (int drawNum = 0; drawNum < HAND_WORD_MAX; ++drawNum)
		//{
		//	pMagicKnightPlayingDeck->m_handWordId[drawNum] = pMagicKnightPlayingDeck->m_deckWordId[0];

		//	//ドローされたら残りの単語識別子を手前にずらす
		//	for (int backShift = 0; backShift < HAND_WORD_MAX- drawNum; ++backShift)
		//	{
		//		pMagicKnightPlayingDeck->m_deckWordId[backShift] = pMagicKnightPlayingDeck->m_deckWordId[backShift + 1];
		//	}
		//}
		/*プレイ開始時の手札やデッキなどの初期化 終了*/

		//フレームカウントを0にすることによって後の計算時が簡単に行える

		ZeroMemory(pHominEffect, sizeof(HomingEffect)*SELECT_EFFECT_MAX);
	}

	////////////////////////////////////////////////////////////////////////////エネミーの初期化とか
	static bool initEnemy = true;
	static int currentFloor = 0;
	static int currentEnemyId = pStageData[selectedStage].m_enemyId[currentFloor];

	if (initEnemy)
	{
		ZeroMemory(battleData, sizeof(VSData));

		battleData->m_enemyId = currentEnemyId = pStageData[selectedStage].m_enemyId[currentFloor];
		battleData->m_cTBlank = pEnemyData[currentEnemyId].m_cTBlank;
		battleData->m_cTMax = pEnemyData[currentEnemyId].m_cTNum;

		++currentFloor;
		initEnemy = false;
	}

	/*マウスカーソルとの当たり判定用の頂点設定 開始*/

	//マウスカーソル
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex,(float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	//手札
	const float HAND_WORD_COLLISION_WIDTH = (float)(DISPLAY_WIDTH / 10);
	const float HAND_WORD_COLLISION_HEIGHT = HAND_WORD_COLLISION_WIDTH / 5;
	const float HAND_POS_Y = (float)(DISPLAY_HEIGHT / 2);
	const float CIRCULATE_POS_X = DISPLAY_WIDTH * 1.3f;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static int degree = 0;

	if (!(battleData->m_playerWon || battleData->m_enemyWon))
	{
		if (frameCount < 120)
		{
			for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
			{
				CustomImageVerticies(pHandWordCollisionsVertex[handWord].ImageVertex,
					DISPLAY_WIDTH - 200, HAND_POS_Y,
					HAND_WORD_COLLISION_WIDTH, HAND_WORD_COLLISION_HEIGHT);

				CirculateImageDeg(pHandWordCollisionsVertex[handWord].ImageVertex,
					pHandWordCollisionsVertex[handWord].ImageVertex, (float)(((360 / HAND_WORD_MAX)*(handWord - 3)) + 3 * (-frameCount - 1)), CIRCULATE_POS_X, HAND_POS_Y);
			}
		}

		else
		{
			/*手札のリストをずらす処理 開始*/

			if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ > 0)
			{
				degree -= 9;
			}

			if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ < 0)
			{
				degree += 9;
			}

			if (degree >= 360 || degree <= -360)
			{
				degree = 0;
			}

			for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
			{
				CustomImageVerticies(pHandWordCollisionsVertex[handWord].ImageVertex,
					DISPLAY_WIDTH - 200, HAND_POS_Y,
					HAND_WORD_COLLISION_WIDTH, HAND_WORD_COLLISION_HEIGHT);

				CirculateImageDeg(pHandWordCollisionsVertex[handWord].ImageVertex,
					pHandWordCollisionsVertex[handWord].ImageVertex, (float)(((360 / HAND_WORD_MAX)*(handWord - 3)) + degree), CIRCULATE_POS_X, HAND_POS_Y);
			}
			/*手札のリストをずらす処理 終了*/
		}

		//必殺技
		const float ACTION_COMPONENT_WORD_COLLISION_WIDTH = (float)(DISPLAY_WIDTH / 15);
		const float ACTION_COMPONENT_WORD_COLLISION_HEIGHT = ACTION_COMPONENT_WORD_COLLISION_WIDTH / 4;

		for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
		{
			CustomImageVerticies(pMagicKnightActionCollisionsVertex[actionComponentWord].ImageVertex,
				(DISPLAY_WIDTH*0.17f) + (ACTION_COMPONENT_WORD_COLLISION_WIDTH * 2)*actionComponentWord + 20, DISPLAY_HEIGHT*0.975f - (ACTION_COMPONENT_WORD_COLLISION_HEIGHT * 2),
				ACTION_COMPONENT_WORD_COLLISION_WIDTH, ACTION_COMPONENT_WORD_COLLISION_HEIGHT);
		}
		/*マウスカーソルとの当たり判定用の頂点設定 終了*/

		/*マウスカーソルとの当たり判定チェック及びその時の処理 開始*/

		//手札
		const int ACTION_WORD_FULL = 5;
		int actionWordSpacePlace = ACTION_WORD_FULL;

		if (frameCount >= 120)
		{
			//左クリックされたら
			if (g_mouseState.mousePush[LEFT_CLICK])
			{
				//手札の数だけ調べる
				for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
				{
					//当たっていない
					if (!RectToRectCollisionCheak(&mouseCursorCollisionVertex[0],
						pHandWordCollisionsVertex[handWord].ImageVertex))
					{
						continue;
					}

					//VOID_W0RD
					if (!pMagicKnightPlayingDeck->m_handWordId[handWord])
					{
						break;
					}

					//必殺技のスペースを探す
					for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
					{
						if (pMagicKnightAction->m_componentWordIds[actionComponentWord] == (MAGIC_KNIGHT_WORD)NULL)
						{
							actionWordSpacePlace = actionComponentWord;

							break;
						}
					}

					//スペースがなかったら
					if (actionWordSpacePlace == ACTION_WORD_FULL)
					{
						break;
					}

					for (int effect = 0; effect < SELECT_EFFECT_MAX; ++effect)
					{
						if (!pHominEffect[effect].m_valid)
						{
							float handPosX = pHandWordCollisionsVertex[handWord].ImageVertex[0].m_x + HAND_WORD_COLLISION_WIDTH;
							float handPosY = pHandWordCollisionsVertex[handWord].ImageVertex[0].m_y + HAND_WORD_COLLISION_HEIGHT;

							float actionWordPosX = pMagicKnightActionCollisionsVertex[actionWordSpacePlace].ImageVertex[0].m_x + ACTION_COMPONENT_WORD_COLLISION_WIDTH;
							float actionWordPosY = pMagicKnightActionCollisionsVertex[actionWordSpacePlace].ImageVertex[0].m_y + ACTION_COMPONENT_WORD_COLLISION_HEIGHT;

							CalculateDistanceBetweenTwoPointsXY(&pHominEffect[effect].m_HomingVect, handPosX, handPosY, actionWordPosX, actionWordPosY);

							const float effectScale = DISPLAY_HEIGHT / 50.f;
							CustomImageVerticies(pHominEffect[effect].m_rect, handPosX, handPosY, effectScale, effectScale);

							pHominEffect[effect].m_actionPos = actionWordSpacePlace;

							pHominEffect[effect].m_valid = true;

							break;
						}
					}

					//必殺技に代入
					pMagicKnightAction->m_componentWordIds[actionWordSpacePlace] = pMagicKnightPlayingDeck->m_handWordId[handWord];
					pMagicKnightPlayingDeck->m_handWordId[handWord] = VOID_WORD;

					//手札の位置
					pMagicKnightAction->m_handPos[actionWordSpacePlace] = handWord;
				}

				//必殺技
				for (int actionConponentWord = 0; actionConponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionConponentWord)
				{
					//当たっていなかったら
					if (!RectToRectCollisionCheak(&mouseCursorCollisionVertex[0],
						pMagicKnightActionCollisionsVertex[actionConponentWord].ImageVertex))
					{
						continue;
					}

					if (pMagicKnightAction->m_componentWordIds[actionConponentWord] == (MAGIC_KNIGHT_WORD)NULL)
					{
						break;
					}

					//リムーブ
					pMagicKnightPlayingDeck->m_handWordId[(pMagicKnightAction->m_handPos[actionConponentWord])] = pMagicKnightAction->m_componentWordIds[actionConponentWord];
					pMagicKnightAction->m_componentWordIds[actionConponentWord] = (MAGIC_KNIGHT_WORD)NULL;
					pMagicKnightAction->m_handPos[actionConponentWord] = 0;
				}
			}
		}

		/*マウスカーソルとの当たり判定チェック及びその時の処理 終了*/

		//ENTERまたは右クリックで必殺技完成の合図
		if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK])
		{
			/*必殺技が完成したときの処理　開始*/
			for (int actionConponentWord = 0; actionConponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionConponentWord)
			{
				MAGIC_KNIGHT_WORD magicKnightWord = pMagicKnightAction->m_componentWordIds[actionConponentWord];

				(pMagicKnightAction->m_attackTotals[(pMagicKnightWordDatas[magicKnightWord].m_attack)]) += 1;
				(pMagicKnightAction->m_elementTotals[(pMagicKnightWordDatas[magicKnightWord].m_element)]) += 1;
				(pMagicKnightAction->m_specialAbilities) |= (pMagicKnightWordDatas[magicKnightWord].m_specialAbilities);
				(pMagicKnightAction->useAction) = true;
			}
			/*必殺技が完成したときの処理　終了*/
		}

		const int EFFECT_FRAME = 15;

		for (int effect = 0; effect < SELECT_EFFECT_MAX; ++effect)
		{
			if (pHominEffect[effect].m_valid)
			{
				MoveImage(pHominEffect[effect].m_rect, pHominEffect[effect].m_rect,
					(float)(pHominEffect[effect].m_HomingVect.m_x*(1 / (float)EFFECT_FRAME)),
					(float)(pHominEffect[effect].m_HomingVect.m_y*(1 / (float)EFFECT_FRAME)));

				pHominEffect[effect].m_count++;

				if (pHominEffect[effect].m_count > EFFECT_FRAME)
				{
					pHominEffect[effect].m_count = 0;

					pHominEffect[effect].m_valid = false;
				}
			}
		}

		ControlBattle(pMagicKnightWordDatas, &frameCount, battleData, pMagicKnightAction, pEnemyData[currentEnemyId], enemyActionNum);
	}

	CustomImageVerticies(resultMask, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, GetColor(0, 0, 0, 0));

	if (frameCount < 120)
	{
		frameCount++;
	}

	const int MASK_FRAME_MAX=60;

	if (battleData->m_enemyWon)
	{
		static int effectFrameCount = 0;

		if (effectFrameCount < 600)
		{
			++effectFrameCount;
		}

		else
		{
			static int maskFrameCount = 0;

			GetCustomVerTexColor(resultMask, GetColor(4 * maskFrameCount, 0, 0, 0));

			if (maskFrameCount < MASK_FRAME_MAX)
			{
				++maskFrameCount;
			}

			else
			{
				if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
				{
					frameCount = INIT_FRAME;
					maskFrameCount = 0;
					effectFrameCount = 0;
					*isClear = false;
					initEnemy = true;
					battleData->m_enemyWon = 0;
					currentFloor = 0;
					degree = 0;

					*scene = HOME_SCENE;
				}
			}
		}
	}

	const int STAGE_MAX[STAGE_MAX] = { 4,4,4 };

	if (battleData->m_playerWon)
	{
		static int effectFrameCount = 0;

		if (effectFrameCount < 600)
		{
			++effectFrameCount;
		}

		else
		{
			static int maskFrameCount = 0;

			GetCustomVerTexColor(resultMask, GetColor(4 * maskFrameCount, 0, 0, 0));

			if (maskFrameCount < MASK_FRAME_MAX)
			{
				++maskFrameCount;
			}

			else
			{
				if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
				{
					frameCount = 120;
					maskFrameCount = 0;
					effectFrameCount = 0;
					*isClear = true;
					battleData->m_playerWon = 0;
					initEnemy = true;

					if (currentFloor >= STAGE_MAX[selectedStage])
					{
						degree = 0;
						frameCount = INIT_FRAME;
						*scene = HOME_SCENE;
						currentFloor = 0;
					}
				}
			}
		}
	}

	return;
}

void LoadMKdeck(SCENE* scene, MagicKnightDeck* pMagicKnightDecks, MagicKnightPlayingDeck* pMagicKnightPlayingDeck)
{
	int currentDeck = pMagicKnightPlayingDeck->m_currentId;

	for (int word=0; word < DECK_WORD_MAX; ++word)
	{
		pMagicKnightPlayingDeck->m_handWordId[word] = pMagicKnightDecks[currentDeck].m_wordIds[word];
	}

	*scene = GAME_SCENE;

	return;
}
