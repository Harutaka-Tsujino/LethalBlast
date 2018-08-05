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

//マジックナイトのリスト数
#define MAGIC_KNIGHT_WORD_LISTS_MAX 5

//単語リスト
typedef struct
{
	//単語リストに配置されている単語の識別番号
	MAGIC_KNIGHT_WORD m_Id;
}WordList;

//魔法剣士の必殺技の単語数の最大値
#define MAGIC_KNIGHT_ACTION_WORDS_MAX 5

//入力する単語
typedef struct
{
	//タイピングする1単語
	char m_word[WORD_CHAR_MAX];
}InputWord;

//魔法剣士の必殺技のデータ
typedef struct
{
	//タイピングされた文字
	InputWord m_inputWords[MAGIC_KNIGHT_ACTION_WORDS_MAX];

	//構成している単語の識別番号
	MAGIC_KNIGHT_WORD m_componentWordIds[MAGIC_KNIGHT_ACTION_WORDS_MAX];

	//それぞれの特殊属性の数
	char m_elemetalNum[ELEMENT_ATTRIBUTES_MAX];

	//それぞれの物理属性の数
	char m_AttackNum[ATTACK_ATTRIBUTES_MAX];

	//特殊効果ビットフラグ　
	unsigned long m_specialAbilities;
}MagicKnightAction;

enum KATAKANA
{
	ア,イ,ウ,エ,オ,
	カ,キ,ク,ケ,コ,
	サ,シ,ス,セ,ソ,
	タ,チ,ツ,テ,ト,
	ナ,ニ,ヌ,ネ,ノ,
	ハ,ヒ,フ,ヘ,ホ,
	ヴァ,ヴィ,ヴ,ヴェ,ヴォ,
	ファ,フィ,/*フ*/フェ,フォ,
	マ,ミ,ム,メ,モ,
	ヤ,/*イ*/ユ,イェ,ヨ,
	ラ,リ,ル,レ,ロ,
	ワ,ウィ,/*ウ*/ウェ,ヲ,
	ン,

	ガ,ギ,グ,ゲ,ゴ,
	ザ,ジ,ズ,ゼ,ゾ,
	ダ,ヂ,ヅ,デ,ド,
	バ,ビ,ブ,ベ,ボ,

	パ,ピ,プ,ペ,ポ,


	キャ,キィ,キュ,キェ,キョ,
	シャ,シィ,シュ,シェ,ショ,
	チャ,チィ,チュ,チェ,チョ,
	ニャ,ニィ,ニュ,ニェ,ニョ,
	ヒャ,ヒィ,ヒュ,ヒェ,ヒョ,
	ミャ,ミィ,ミュ,ミェ,ミョ,
	リャ,リィ,リュ,リェ,リョ,

	ギャ,ギィ,ギュ,ギェ,ギョ,
	ジャ,/*ジ*/ジュ,ジェ,ジョ,
	/*ジャ*/ジィ,/*ジュ*//*ジェ*//*ジョ*/
	ヂャ,ヂィ,ヂュ,ヂェ,ヂョ,
	ビャ,ビィ,ビュ,ビェ,ビョ,

	ピャ,ピィ,ピュ,ピェ,ピョ,

	ァ,ィ,ゥ,ェ,ォ,
	ャ,/*ィ*/ュ,/*ェ*/ョ,
	ッ,

	ー,

	KATAKANA_MAX
};

#define KATAKANA_SIZE_MAX 4
#define ALPHABET_SIZE_MAX 3
#define NULL_CHAR 1

typedef struct
{
	char m_alphabet[ALPHABET_SIZE_MAX + NULL_CHAR];
}Alphabet;

#define ESTIMATE_ALPHABET_MAX 4
typedef struct
{
	char m_katakana[KATAKANA_SIZE_MAX + NULL_CHAR];
	Alphabet m_alphabet[ESTIMATE_ALPHABET_MAX];
}KanaAlphabetTable;

typedef struct
{
	char m_ruby[WORD_CHAR_MAX];
}WordCandidate;
