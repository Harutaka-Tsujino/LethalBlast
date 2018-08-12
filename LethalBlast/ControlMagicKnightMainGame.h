#pragma once

//魔法剣士の単語
enum MAGIC_KNIGHT_WORD
{
	VOID_WORD,
#include "Files/Enum/MagicKnightWordEnum.txt"
};

#define DECK_NAME_MAX 20 
#define DECK_WORD_MAX 40
typedef struct
{
	char m_name[DECK_NAME_MAX];
	int m_wordIds[DECK_WORD_MAX];
	int m_cost;
}MAGIC_KNIGHT_DECK;

typedef struct
{
	int currentDeckId;
	int m_deckList

}MAGIC_KNIGHT_CHOSE_DECK;
