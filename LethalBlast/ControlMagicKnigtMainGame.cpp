#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

//static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
//static MagicKnightPlayingDeck magicKnightPlayingDeck;
//static MagicKnightAction magicKnightAction;
//CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];
//CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

void ControlMagicKnightMainGame(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, 
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex)
{
	//必殺技を発動している
	if (pMagicKnightAction->useAction)
	{
		return;
	}

	//フレームのカウント
	static int frameCount = INIT_FRAME;

	//初期化を行う
	if (frameCount == INIT_FRAME)
	{
		//構造体の初期化 全て0を代入する
		memset(pMagicKnightAction,0,sizeof(MagicKnightAction));
		memset(pMagicKnightWordDatas, 0, sizeof(WordData));

		/*プレイ開始時の手札やデッキなどの初期化 開始*/
		MAGIC_KNIGHT_WORD* pWordShuffleBuf = (MAGIC_KNIGHT_WORD*)malloc(sizeof(MAGIC_KNIGHT_WORD)*pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordNum);

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

		//開始のドロー
		for (int drawNum = 0; drawNum < HAND_WORD_MAX; ++drawNum)
		{
			pMagicKnightPlayingDeck->m_handWordId[drawNum] = pMagicKnightPlayingDeck->m_deckWordId[0];

			//ドローされたら残りの単語識別子を手前にずらす
			for (int backShift = 0; backShift < HAND_WORD_MAX- drawNum; ++backShift)
			{
				pMagicKnightPlayingDeck->m_deckWordId[backShift] = pMagicKnightPlayingDeck->m_deckWordId[backShift + 1];
			}
		}
		/*プレイ開始時の手札やデッキなどの初期化 終了*/

		//フレームカウントを0にすることによって後の計算時が簡単に行える
		frameCount = 0;
	}

	/*マウスカーソルとの当たり判定用の頂点設定 開始*/

	//マウスカーソル
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex,(float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	//手札
	const float HAND_WORD_COLLISION_WIDTH = (float)(DISPLAY_WIDTH / 20);
	const float HAND_WORD_COLLISION_HEIGHT = HAND_WORD_COLLISION_WIDTH / 2;
	const float HAND_POS_Y = (float)(DISPLAY_HEIGHT / 2);
	const float CIRCULATE_POS_X = DISPLAY_WIDTH * 1.3f;

	/*手札のリストをずらす処理 開始*/
	static int degree = 0;

	if (g_keyState.keyHold[DIK_COMMA])
	{
		degree-=2;
	}

	if (g_keyState.keyHold[DIK_PERIOD])
	{
		degree+=2;
	}

	if (degree == 360 || degree == -360)
	{
		degree = 0;
	}

	for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
	{
		CustomImageVerticies(pHandWordCollisionsVertex[handWord].ImageVertex,
			DISPLAY_WIDTH-200, HAND_POS_Y,
			HAND_WORD_COLLISION_WIDTH, HAND_WORD_COLLISION_HEIGHT);

		CirculateImageDeg(pHandWordCollisionsVertex[handWord].ImageVertex,
			pHandWordCollisionsVertex[handWord].ImageVertex, (float)(((360 / HAND_WORD_MAX)*handWord)+ degree), CIRCULATE_POS_X, HAND_POS_Y);
	}
	/*手札のリストをずらす処理 終了*/

	//必殺技
	const float ACTION_COMPONENT_WORD_COLLISION_WIDTH = (float)(DISPLAY_WIDTH / 20);
	const float ACTION_COMPONENT_WORD_COLLISION_HEIGHT = ACTION_COMPONENT_WORD_COLLISION_WIDTH / 2;

	for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
	{
		CustomImageVerticies(pMagicKnightActionCollisionsVertex[actionComponentWord].ImageVertex,
			(DISPLAY_WIDTH / 3) + (ACTION_COMPONENT_WORD_COLLISION_WIDTH*2)*actionComponentWord, DISPLAY_HEIGHT - (ACTION_COMPONENT_WORD_COLLISION_HEIGHT*2),
			ACTION_COMPONENT_WORD_COLLISION_WIDTH, ACTION_COMPONENT_WORD_COLLISION_HEIGHT);
	}
	/*マウスカーソルとの当たり判定用の頂点設定 終了*/

	/*マウスカーソルとの当たり判定チェック及びその時の処理 開始*/

	//手札
	const int ACTION_WORD_FULL = 5;
	int actionWordSpacePlace = ACTION_WORD_FULL;

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
			for (int actionComponentWord = 0; MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
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
				continue;
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

	return;
}

void LoadMKdeck(SCENE* scene, MagicKnightDeck* pMagicKnightDecks, MagicKnightPlayingDeck* pMagicKnightPlayingDeck)
{
	int currentDeck = pMagicKnightPlayingDeck->m_currentId;

	for (int word=0; word < DECK_WORD_MAX; ++word)
	{
		pMagicKnightPlayingDeck->m_deckWordId[word] = pMagicKnightDecks[currentDeck].m_wordIds[word];
	}

	*scene = GAME_SCENE;

	return;
}
