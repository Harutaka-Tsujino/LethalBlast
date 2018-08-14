#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
static MagicKnightPlayingDeck magicKnightPlayingDeck;
static MagicKnightAction magicKnightAction;
CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];
CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

void RenderMagicKnightMainGame(WordData* pWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	CustomVertex* pHandWordCollisionsVertex, CustomVertex* pMagicKnightActionCollisionsVertex)
{
	int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{

		frameCount = 0;
	}

	for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
	{
		DrawImage(&handWordCollisionsVertex[handWord*RECT_VERTEX_NUM], NULL);
	}

	for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
	{
		DrawImage(&pMagicKnightActionCollisionsVertex[actionComponentWord*RECT_VERTEX_NUM], NULL);
	}

	return;
}
