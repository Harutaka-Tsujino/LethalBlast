//#pragma once
//
//#include"DX9Lib.h"
//#include"WinMain.h"
//
////ウェポンマスターの単語
//enum WEAPON_MASTER_WORD_LISTS
//{
//	VOID_WORD,
//	#include"Files/Enum/WeaponMasterWordEnum.txt"
//};
//
////魔法剣士の単語
//enum MAGIC_KNIGHT_WORD
//{
//	VOID_WORD,
//#include"Files/Enum/MagicKnightWordEnum.txt"
//};
//
////単語の名前の文字数最大値
//#define WORD_NAME_CHAR_MAX 40
//
//typedef struct
//{
//	//文字の名前
//	char m_word[WORD_NAME_CHAR_MAX];
//
//	//特殊属性の識別子
//	ELEMENT_ATTRIBUTE m_element;
//
//	//物理属性の識別子
//	ATTACK_ATTRIBUTE m_attack;
//
//	//文字のスキルスロットのマックス値
//	int m_skillSlot[4];
//
//	//文字のコスト
//	int m_currentCost;
//
//	//文字のコスト最大値
//	int m_costMax;
//
//	//持っているか
//	bool m_have;
//
//}WordData;
//
////デッキの名前の最大文字数
//#define DECK_NAME_CHAR_MAX 40
//
////デッキに入れることができる単語の最大数
//#define DECK_WORD_MAX 40
//
////デッキの保存できる最大数
//#define PLAYER_DECKS_MAX 8
//
//typedef struct
//{
//
//	//構成する文字ID
//	int m_wordIds[MAGIC_KNIGHT_WORD_MAX];
//
//	//構成する単語の数
//	int m_wordNum;
//
//	//コスト上限
//	int m_costMax;
//
//}PlayerDeck;
//
////必殺技を構成する単語の最大数
//#define MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX 5
//
////WM用必殺技を構成する最大数
//#define WEAPON_MASTER_ACTION_LISTS 10