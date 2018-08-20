#pragma once

//魔法剣士の単語
enum MAGIC_KNIGHT_WORD
{
	VOID_WORD,
#include "Files/Enum/MagicKnightWordEnum.txt"
};

//単語の名前の文字数最大値
#define WORD_NAME_CHAR_MAX 40

//修飾時の素材の数
#define MATERIALS_NUM 2

//単語のデータ
typedef struct
{
	//名前
	char m_word[WORD_NAME_CHAR_MAX];

	//特殊属性の識別子
	ELEMENT_ATTRIBUTE m_element;

	//物理属性の識別子
	ATTACK_ATTRIBUTE m_attack;

	//特殊効果ビットフラグ
	unsigned long m_specialAbilities;

	//修飾時の素材
	int m_matterials[MATERIALS_NUM];

	//コスト
	int m_cost;

	//特殊属性の倍率
	int m_elementMultiPlus;

	//所持しているかどうか
	int m_have;
}WordData;

//デッキの名前の最大文字数
#define DECK_NAME_CHAR_MAX 40

//デッキに入れることができる単語の最大数
#define DECK_WORD_MAX 40

//デッキの保存できる最大数
#define MAGIC_KNIGHT_DECKS_MAX 8

//デッキのデータ
typedef struct
{
	//デッキの名前
	char m_name[DECK_NAME_CHAR_MAX];

	//デッキを構成している単語の識別子
	MAGIC_KNIGHT_WORD m_wordIds[DECK_WORD_MAX];

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
#define HAND_WORD_MAX 40

//プレイング時のデッキデータ
typedef struct
{
	//現在のデッキの識別子
	int m_currentId;

	//手札の単語の識別子
	MAGIC_KNIGHT_WORD m_handWordId[DECK_WORD_MAX];

	//デッキにある単語の識別子
	MAGIC_KNIGHT_WORD m_deckWordId[HAND_WORD_MAX];

	//墓地にある単語の識別子
	MAGIC_KNIGHT_WORD m_discardWordId[DECK_WORD_MAX];
}MagicKnightPlayingDeck;

//必殺技を構成する単語の最大数
#define MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX 5

//魔法剣士の必殺技のデータ　八原氏に渡す
typedef struct
{
	//構成している単語の識別子
	MAGIC_KNIGHT_WORD m_componentWordIds[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX];

	//入れた単語が手札の何番目にあったか
	int m_handPos[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX];

	//特殊属性別の合計数
	char m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//物理属性別の合計数
	char m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//特殊効果ビットフラグ
	unsigned long m_specialAbilities;

	//必殺技を放ったか
	bool useAction;
}MagicKnightAction;

void ControlMagicKnightMainGame(WordData* pWordDatas, MagicKnightDeck* pMagicKnightDecks, 
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex);

void LoadMKdeck(SCENE* scene, MagicKnightDeck* pMagicKnightDecks, MagicKnightPlayingDeck* pMagicKnightPlayingDeck);
