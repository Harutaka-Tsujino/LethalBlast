#pragma once
#include"WinMain.h"

//魔法剣士の単語
enum MAGIC_KNIGHT_WORD
{
	VOID_WORD,
	#include "Files/Enum/MagicKnightWordEnum.txt"
};

//単語の文字数の最大値
#define WORD_CHAR_MAX 40

//単語ののデータ
typedef struct
{
	//スペル
	char m_word[WORD_CHAR_MAX];

	//特殊属性
	ELEMENT_ATTRIBUTE m_element;

	//物理属性
	ATTACK_ATTRIBUTE m_attack;

	//特殊効果ビットフラグ
	unsigned long m_specialAbilities;
}WordData;

//単語リスト
typedef struct
{
	//単語リストに配置されている単語の識別番号
	MAGIC_KNIGHT_WORD m_Id;
}WordList;

//魔法剣士の必殺技の単語数の最大値
#define MAGIC_KNIGHT_ACTION_WORDS_MAX 5

//魔法剣士の必殺技のデータ
typedef struct
{
	//タイピングされた文字
	char m_inputWords[WORD_CHAR_MAX * MAGIC_KNIGHT_ACTION_WORDS_MAX];

	//構成している単語の識別番号
	MAGIC_KNIGHT_WORD m_componentWordIds[MAGIC_KNIGHT_ACTION_WORDS_MAX];

	//それぞれの特殊属性の数
	char m_elemetalNum[ELEMENT_ATTRIBUTES_MAX];

	//それぞれの物理属性の数
	char m_AttackNum[ATTACK_ATTRIBUTES_MAX];

	//特殊効果ビットフラグ　
	unsigned long m_specialAbilities;
}MagicKnightAction;

//カタカナの行の数
#define KATAKANA_ROW 5
#define NULL_CHAR 1
#define W_SPACE 5

enum KATAKANA_FIRST_ROW
{
	ファ,
	ヴァ,
	ジャ,
	ワ,
	ア,
	カ,
	サ,
	タ,
	ナ,
	ハ,
	マ,
	ラ,
	ヤ,
	ン,
	パ,
	ガ,
	ザ,
	ダ,
	バ,
	ァ,
	ャ,
	ッ,
	ー,
	KATAKANA_FIRST_ROWS_MAX
};


//カタカナ
typedef struct
{
	//カタカナ一行の文字列
	char katakanaRow[(KATAKANA_ROW + W_SPACE) * MULTI_BYTE + NULL_CHAR];
}Katakana;