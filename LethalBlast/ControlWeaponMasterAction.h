#pragma once
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"
#include"ControlCharaChoice.h"

#define WORD_NAME 40

//�C�����̑f�ނ̐�
#define MATERIALS_NUM 2

typedef struct
{

	 WEAPON_MASTER_WORD_LISTS m_weaponMasterWordListsId;

	 //���O
	 char m_word[WORD_NAME];

	 //���ꑮ���̎��ʎq
	 ELEMENT_ATTRIBUTE m_element;

	 //���������̎��ʎq
	 ATTACK_ATTRIBUTE m_attack;

	 //������ʃr�b�g�t���O
	 unsigned long m_specialAbilities;

	 //�C�����̑f��
	 int m_matterials[MATERIALS_NUM];

	 //�R�X�g
	 int m_cost;

	 //���ꑮ���̔{��
	 int m_elementMultiPlus;

	 //�������Ă��邩�ǂ���
	 int m_have;
}WeaponMasterWordData;

#define DECK_WORD_MAX 40

#define DECK_NAME 40

#define WEAPON_MASTER_DECK_MAX 8

typedef struct
{
	//�f�b�L�̖��O
	char m_name[DECK_NAME];

	//�f�b�L���\�����Ă���P��̎��ʎq
	WEAPON_MASTER_WORD_LISTS m_wordIds[DECK_WORD_MAX];

	//���ꑮ���ʂ̍��v��
	int m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//���������ʂ̍��v��
	int m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//�\������P��̐�
	int m_wordNum;

	//�R�X�g
	int m_cost;

}WeaponMasterDeck;

#define WEAPON_MASTER_ACTION_LISTS 10

typedef struct
{
	//�\�����Ă���P��̎��ʎq
	WEAPON_MASTER_WORD_LISTS m_componentWordIds[WEAPON_MASTER_ACTION_LISTS];

	//���ꂽ�P�ꂪ��D�̉��Ԗڂɂ�������
	int m_handPos[WEAPON_MASTER_ACTION_LISTS];

	//���ꑮ���ʂ̍��v��
	char m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//���������ʂ̍��v��
	char m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//������ʃr�b�g�t���O
	unsigned long m_specialAbilities;

	//�K�E�Z���������
	bool m_useAction;

}WeaponMasterActionData;

void ControlWeaponMasterAction(WeaponMasterWordData* pWeaponMasterWordData, WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas,
	ImagesCustomVertex* pWeaponMasterDeckVerticies, ImagesCustomVertex* pWeaponMasterAction, bool* scrollEffect, int *pPage);

void WeaponMasterInputInfoToAction(WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas, ImagesCustomVertex* pWeaponMasterAction, CustomVertex* mouseState);

void WeaponMasterWordListsPageTransition(ImagesCustomVertex* pWeaponMasterDeckVerticies, int wordLists);
