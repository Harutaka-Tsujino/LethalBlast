#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlChoiceDeck()
{
	static bool choseDeck = false;

	if (!choseDeck)
	{
		/*デッキの選択用当たり判定の頂点設定 開始*/
		CustomVertex pChoiseDeckCollisionsVertex[MAGIC_KNIGHT_DECKS_MAX*RECT_VERTEX_NUM];


		/*デッキの選択用当たり判定の頂点設定 終了*/

		return;
	}

	return; 
}

//static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
//static MagicKnightPlayingDeck magicKnightPlayingDeck;
//static MagicKnightAction magicKnightAction;
//CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];
//CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

void ControlMagicKnightMainGame(WordData* pWordDatas ,MagicKnightDeck* pMagicKnightDecks, MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	CustomVertex* pHandWordCollisionsVertex,CustomVertex* pMagicKnightActionCollisionsVertex)
{
	//必殺技を発動している
	if (pMagicKnightAction->useAction)
	{
		return;
	}

	//初期化を行うときのフレームカウント
	const int INIT_FRAME = -1;

	//フレームのカウント
	static int frameCount = INIT_FRAME;

	//初期化を行う
	if (frameCount == INIT_FRAME)
	{
		//構造体の初期化 全て0を代入する
		memset(&pMagicKnightAction,0,sizeof(MagicKnightAction));

		/*プレイ開始時の手札やデッキなどの初期化 開始*/
		MAGIC_KNIGHT_WORD* pWordShuffleBuf = (MAGIC_KNIGHT_WORD*)malloc(sizeof(MAGIC_KNIGHT_WORD)*pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordNum);

		//重複しないようにするためデッキの単語識別子をバッファーに保存する
		for (int deckWordNum = 0; deckWordNum < pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordNum; ++deckWordNum)
		{
			pWordShuffleBuf[deckWordNum] = pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordIds[deckWordNum];
		}

		//デッキの中の単語識別子をシャッフルする
		for (int deckWordNum = 0; deckWordNum < DECK_WORD_MAX; deckWordNum++)
		{
			int unshuffledDeckWordNum = pMagicKnightDecks[pMagicKnightPlayingDeck->m_currentId].m_wordNum - deckWordNum;
			int chosenNum = rand() % (unshuffledDeckWordNum);

			pMagicKnightPlayingDeck->m_deckWordId[deckWordNum] = pWordShuffleBuf[chosenNum];

			//一度選ばれたものは選ばれる範囲から外す
			for (int backShift = chosenNum; backShift < unshuffledDeckWordNum; ++backShift)
			{
				pWordShuffleBuf[backShift] = pWordShuffleBuf[backShift + 1];
			}
		}

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
	CustomImageVerticies(mouseCursorCollisionVertex,g_mouseState.absolutePos.x, g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	//手札
	const int HAND_WORD_COLLISION_WIDTH = DISPLAY_WIDTH / 10;
	const int HAND_WORD_COLLISION_HEIGHT = DISPLAY_HEIGHT / 20;

	for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
	{
		CustomImageVerticies(&pHandWordCollisionsVertex[handWord*RECT_VERTEX_NUM],
			DISPLAY_WIDTH - HAND_WORD_COLLISION_WIDTH * (handWord % 2 + 1), HAND_WORD_COLLISION_HEIGHT*(handWord % 8), 
			HAND_WORD_COLLISION_WIDTH, HAND_WORD_COLLISION_HEIGHT);
	}

	//必殺技
	const int ACTION_COMPONENT_WORD_COLLISION_WIDTH = DISPLAY_WIDTH / 20;
	const int ACTION_COMPONENT_WORD_COLLISION_HEIGHT = DISPLAY_HEIGHT / 40;

	for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
	{
		CustomImageVerticies(&pMagicKnightActionCollisionsVertex[actionComponentWord*RECT_VERTEX_NUM],
			(DISPLAY_WIDTH / 2) + ACTION_COMPONENT_WORD_COLLISION_WIDTH, DISPLAY_HEIGHT - ACTION_COMPONENT_WORD_COLLISION_HEIGHT,
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
				&pHandWordCollisionsVertex[handWord*RECT_VERTEX_NUM]))
			{
				continue;
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
		}

		//必殺技
		for (int actionConponentWord = 0; actionConponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionConponentWord)
		{
			//当たっていなかったら
			if (!RectToRectCollisionCheak(&mouseCursorCollisionVertex[0],
				&pMagicKnightActionCollisionsVertex[actionConponentWord*RECT_VERTEX_NUM]))
			{
				continue;
			}

			//リムーブ
			pMagicKnightAction->m_componentWordIds[actionConponentWord] = (MAGIC_KNIGHT_WORD)NULL;
		}
	}
	/*マウスカーソルとの当たり判定チェック及びその時の処理 終了*/

	//ENTERまたは右クリックで必殺技完成の合図
	if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK])
	{
		/*必殺技が完成したときの処理　開始*/
		for (int actionConponentWord = 0; actionConponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionConponentWord)
		{
			pMagicKnightAction->m_attackTotals[pWordDatas[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_attack] += 1;
			pMagicKnightAction->m_elementTotals[pWordDatas[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_element] += 1;
			pMagicKnightAction->m_specialAbilities |= pWordDatas[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_specialAbilities;
			pMagicKnightAction->useAction = true;
		}
		/*必殺技が完成したときの処理　終了*/
	}
}
