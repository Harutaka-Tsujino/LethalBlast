#pragma once
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlCharaChoice.h"

enum WEAPON_MASTER_WORD_LISTS
{
	#include"Files/Enum/WeaponMasterWordEnum.txt"
};

#define WORD_NAME 40

typedef struct
{

	 WEAPON_MASTER_WORD_LISTS m_weaponMasterWordListsId;

	 //名前
	 char m_word[WORD_NAME];

	 //特殊属性の識別子
	 ELEMENT_ATTRIBUTE m_element;

	 //物理属性の識別子
	 ATTACK_ATTRIBUTE m_attack;

	 //特殊効果ビットフラグ
	 unsigned long m_specialAbilities;

	 //コスト
	 int m_cost;

	 //ダメージ
	 int m_damage;
}WeaponMasterWordData;

#define DECK_WORD_MAX 40

#define DECK_NAME 40

typedef struct
{
	//デッキの名前
	char m_name[DECK_NAME];

	//デッキを構成している単語の識別子
	WEAPON_MASTER_WORD_LISTS m_wordIds[DECK_WORD_MAX];

	//特殊属性別の合計数
	int m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//物理属性別の合計数
	int m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//構成する単語の数
	int m_wordNum;

	//コスト
	int m_cost;

	//ダメージ
	int m_damage;
}WeaponMasterDeck;

#define WEAPON_MASTER_ACTION_LISTS 10

typedef struct
{
	//構成している単語の識別子
	WEAPON_MASTER_WORD_LISTS m_componentWordIds[WEAPON_MASTER_ACTION_LISTS];

	//特殊属性別の合計数
	char m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//物理属性別の合計数
	char m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//特殊効果ビットフラグ
	unsigned long m_specialAbilities;

	//必殺技を放ったか
	bool m_useAction;

}WeaponMasterActionData;

void ControlWeaponMasterAction(WeaponMasterWordData* pWeaponMasterWordData, WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionWords,
	ImagesCustomVertex* pWeaponMasterDeckVerticies, int* pPage);

void WeaponMasterWordListsPageTransition(ImagesCustomVertex* pWeaponMasterDeckVerticies, int wordLists);
