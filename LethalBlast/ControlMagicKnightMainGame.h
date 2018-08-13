#pragma once

//魔法剣士の単語
enum MAGIC_KNIGHT_WORD
{
	VOID_WORD,
#include "Files/Enum/MagicKnightWordEnum.txt"
};

//単語の名前の文字数最大値
#define WORD_NAME_CHAR_MAX 40

//単語のデータ
typedef struct
{
	//名前
	char m_word[WORD_NAME_CHAR_MAX];

	//特殊属性
	ELEMENT_ATTRIBUTE m_element;

	//物理属性
	ATTACK_ATTRIBUTE m_attack;

	//特殊効果ビットフラグ
	unsigned long m_specialAbilities;
}WordData;

//デッキの名前の最大文字数
#define DECK_NAME_CHAR_MAX 40

//デッキに入れることができる単語の最大数
#define DECK_WORD_MAX 40

//デッキのデータ
typedef struct
{
	//デッキの名前
	char m_name[DECK_NAME_CHAR_MAX];

	//デッキを構成している単語の識別子
	int m_wordIds[DECK_WORD_MAX];

	//特殊属性別の合計数
	int m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//物理属性別の合計数
	int m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//構成する単語の数
	int m_wordNum;

	//コスト
	int m_cost;
}MagicKnightDeck;

//単語の手札最大数
#define HAND_WORD_MAX 15

//プレイング時のデッキデータ
typedef struct
{
	//現在のデッキの識別子
	int currentId;

	//手札の単語の識別子
	int handWordId[DECK_WORD_MAX];

	//デッキにある単語の識別子
	int deckWordId[HAND_WORD_MAX];

	//墓地にある単語の識別子
	int discardWordId[DECK_WORD_MAX];
}MagicKnightPlayingDeck;

//必殺技を構成する単語の最大数
#define MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX 5

//魔法剣士の必殺技のデータ
typedef struct
{
	//構成している単語の識別子
	MAGIC_KNIGHT_WORD m_componentWordIds[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX];

	//特殊属性別の合計数
	char m_elemetalTotals[ELEMENT_ATTRIBUTES_MAX];

	//物理属性別の合計数
	char m_AttackTotals[ATTACK_ATTRIBUTES_MAX];

	//特殊効果ビットフラグ
	unsigned long m_specialAbilities;
}MagicKnightAction;
