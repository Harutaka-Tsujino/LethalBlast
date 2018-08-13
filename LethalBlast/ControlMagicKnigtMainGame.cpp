#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

void ControlMagicKnightMainGame()
{
	//デッキの保存できる最大数
	const int MAGIC_KNIGHT_DECKS_MAX = 15;
	static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];

	MagicKnightPlayingDeck magicKnightPlayingDeck;

	MagicKnightAction magicKnightAction;

	//初期化を行うときのフレームカウント
	const int INIT_FRAME = -1;

	//フレームのカウント
	static int frameCount = INIT_FRAME;

	//初期化を行う
	if (frameCount == INIT_FRAME)
	{
		//フレームカウントを0にすることによって後の計算時が簡単に行える
		frameCount = 0;

		//構造体の初期化 全て0を代入する
		memset(magicKnightDecks, 0, sizeof(MagicKnightDeck));
		memset(&magicKnightPlayingDeck, 0, sizeof(MagicKnightPlayingDeck));
		memset(&magicKnightAction,0,sizeof(MagicKnightAction));

		//デッキの読み込み あとで書く

		//デッキを選ばせる あとで書く

		/*プレイ開始時の手札やデッキなどの初期化 開始*/
		int* pWordShuffleBuf = (int*)malloc(sizeof(int)*magicKnightDecks[magicKnightPlayingDeck.currentId].m_wordNum);

		//重複しないようにするためデッキの単語識別子をバッファーに保存する
		for (int deckWordNum = 0; deckWordNum < magicKnightDecks[magicKnightPlayingDeck.currentId].m_wordNum; ++deckWordNum)
		{
			pWordShuffleBuf[deckWordNum] = magicKnightDecks[magicKnightPlayingDeck.currentId].m_wordIds[deckWordNum];
		}

		//デッキの中の単語識別子をシャッフルする
		for (int deckWordNum = 0; deckWordNum < DECK_WORD_MAX; deckWordNum++)
		{
			int unshuffledDeckWordNum = magicKnightDecks[magicKnightPlayingDeck.currentId].m_wordNum - deckWordNum;
			int chosenNum = rand() % (unshuffledDeckWordNum);

			magicKnightPlayingDeck.deckWordId[deckWordNum] =pWordShuffleBuf[chosenNum];

			//一度選ばれたものは選ばれる範囲から外す
			for (int backShift = chosenNum; backShift < unshuffledDeckWordNum; ++backShift)
			{
				pWordShuffleBuf[backShift] = pWordShuffleBuf[backShift + 1];
			}
		}

		//開始のドロー
		for (int drawNum = 0; drawNum < HAND_WORD_MAX; ++drawNum)
		{
			magicKnightPlayingDeck.handWordId[drawNum] = magicKnightPlayingDeck.deckWordId[0];

			//ドローされたら残りの単語識別子を手前にずらす
			for (int backShift = 0; backShift < HAND_WORD_MAX- drawNum; ++backShift)
			{
				magicKnightPlayingDeck.deckWordId[backShift] = magicKnightPlayingDeck.deckWordId[backShift + 1];
			}
		}
		/*プレイ開始時の手札やデッキなどの初期化 終了*/
	}

	/*カーソルとの当たり判定用の頂点設定 開始*/
	//手札
	const int RECT_VERTEX_NUM = 4;
	CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];

	const int HAND_WORD_COLLISION_WIDTH = DISPLAY_WIDTH / 10;
	const int HAND_WORD_COLLISION_HEIGHT = DISPLAY_HEIGHT / 20;
	for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
	{
		CustomImageVerticies(&handWordCollisionsVertex[handWord*RECT_VERTEX_NUM],
			DISPLAY_WIDTH - HAND_WORD_COLLISION_WIDTH * (handWord % 2 + 1), HAND_WORD_COLLISION_HEIGHT*(handWord % 8), 
			HAND_WORD_COLLISION_WIDTH, HAND_WORD_COLLISION_HEIGHT);
	}

	//必殺技
	CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

	const int ACTION_COMPONENT_WORD_COLLISION_WIDTH = DISPLAY_WIDTH / 20;
	const int ACTION_COMPONENT_WORD_COLLISION_HEIGHT = DISPLAY_HEIGHT / 40;
	for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
	{
		CustomImageVerticies(&magicKnightActionCollisionsVertex[actionComponentWord*RECT_VERTEX_NUM],
			(DISPLAY_WIDTH / 2) + ACTION_COMPONENT_WORD_COLLISION_WIDTH, DISPLAY_HEIGHT - ACTION_COMPONENT_WORD_COLLISION_HEIGHT,
			ACTION_COMPONENT_WORD_COLLISION_WIDTH, ACTION_COMPONENT_WORD_COLLISION_HEIGHT);
	}
	/*カーソルとの当たり判定用の頂点設定 終了*/


}
