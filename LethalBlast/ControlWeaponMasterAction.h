#pragma once
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlCharaChoice.h"

#define WORD_NAME 40

//修飾時の素材の数
#define MATERIALS_NUM 2

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

	 //修飾時の素材
	 int m_matterials[MATERIALS_NUM];

	 //コスト
	 int m_cost;

	 //特殊属性の倍率
	 int m_elementMultiPlus;

	 //所持しているかどうか
	 int m_have;
}WeaponMasterWordData;

#define DECK_WORD_MAX 40

#define DECK_NAME 40

#define WEAPON_MASTER_DECK_MAX 8

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

}WeaponMasterDeck;

#define WEAPON_MASTER_ACTION_LISTS 10

typedef struct
{
	//構成している単語の識別子
	WEAPON_MASTER_WORD_LISTS m_componentWordIds[WEAPON_MASTER_ACTION_LISTS];

	//入れた単語が手札の何番目にあったか
	int m_handPos[WEAPON_MASTER_ACTION_LISTS];

	//特殊属性別の合計数
	char m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//物理属性別の合計数
	char m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//特殊効果ビットフラグ
	unsigned long m_specialAbilities;

	//必殺技を放ったか
	bool m_useAction;

}WeaponMasterActionData;

void ControlWeaponMasterAction(WeaponMasterWordData* pWeaponMasterWordData, WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas,
	ImagesCustomVertex* pWeaponMasterDeckVerticies, ImagesCustomVertex* pWeaponMasterAction, bool* scrollEffect, int *pPage);

void WeaponMasterInputInfoToAction(WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas, ImagesCustomVertex* pWeaponMasterAction, CustomVertex* mouseState);

void WeaponMasterWordListsPageTransition(ImagesCustomVertex* pWeaponMasterDeckVerticies, int wordLists);
