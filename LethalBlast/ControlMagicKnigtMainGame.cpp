#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlMagicKnightMainGame.h"

void ControlMagicKnightMainGame()
{
	const int MAGIC_KNIGHT_DECKS_MAX = 15;
	static MAGIC_KNIGHT_DECK magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];

	//現在選択されている単語(列挙子)のデッキをシャッフルして格納する
	static int wordDeck[DECK_WORD_MAX];

	const int FIRST_FRAME = -1;
	static int frameCount = FIRST_FRAME;

	if (frameCount == FIRST_FRAME)
	{
		frameCount = 0;

		memset(magicKnightDecks, 0, sizeof(int)*DECK_WORD_MAX);
		memset(wordDeck, 0, sizeof(int)*DECK_WORD_MAX);

		for (int deckNum = 0; deckNum < DECK_WORD_MAX; deckNum++)
		{
			wordDeck[deckNum] = magicKnightDecks[].m_wordIds[]
		}
	}
}
