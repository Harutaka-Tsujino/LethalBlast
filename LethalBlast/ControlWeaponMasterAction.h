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

	 //���O
	 char m_word[WORD_NAME];

	 //���ꑮ���̎��ʎq
	 ELEMENT_ATTRIBUTE m_element;

	 //���������̎��ʎq
	 ATTACK_ATTRIBUTE m_attack;

	 //������ʃr�b�g�t���O
	 unsigned long m_specialAbilities;

	 //�R�X�g
	 int m_cost;

	 //�_���[�W
	 int m_damage;
}WeaponMasterWordData;

#define DECK_WORD_MAX 40

#define DECK_NAME 40

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

	//�_���[�W
	int m_damage;
}WeaponMasterDeck;

#define WEAPON_MASTER_ACTION_LISTS 10

typedef struct
{
	//�\�����Ă���P��̎��ʎq
	WEAPON_MASTER_WORD_LISTS m_componentWordIds[WEAPON_MASTER_ACTION_LISTS];

	//���ꑮ���ʂ̍��v��
	char m_elementTotals[ELEMENT_ATTRIBUTES_MAX];

	//���������ʂ̍��v��
	char m_attackTotals[ATTACK_ATTRIBUTES_MAX];

	//������ʃr�b�g�t���O
	unsigned long m_specialAbilities;

	//�K�E�Z���������
	bool m_useAction;

}WeaponMasterActionData;

void ControlWeaponMasterAction(WeaponMasterWordData* pWeaponMasterWordData, WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionWords,
	ImagesCustomVertex* pWeaponMasterDeckVerticies, int* pPage);

void WeaponMasterWordListsPageTransition(ImagesCustomVertex* pWeaponMasterDeckVerticies, int wordLists);
