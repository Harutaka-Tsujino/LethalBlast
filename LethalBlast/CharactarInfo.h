//#pragma once
//
//#include"DX9Lib.h"
//#include"WinMain.h"
//
////�E�F�|���}�X�^�[�̒P��
//enum WEAPON_MASTER_WORD_LISTS
//{
//	VOID_WORD,
//	#include"Files/Enum/WeaponMasterWordEnum.txt"
//};
//
////���@���m�̒P��
//enum MAGIC_KNIGHT_WORD
//{
//	VOID_WORD,
//#include"Files/Enum/MagicKnightWordEnum.txt"
//};
//
////�P��̖��O�̕������ő�l
//#define WORD_NAME_CHAR_MAX 40
//
//typedef struct
//{
//	//�����̖��O
//	char m_word[WORD_NAME_CHAR_MAX];
//
//	//���ꑮ���̎��ʎq
//	ELEMENT_ATTRIBUTE m_element;
//
//	//���������̎��ʎq
//	ATTACK_ATTRIBUTE m_attack;
//
//	//�����̃X�L���X���b�g�̃}�b�N�X�l
//	int m_skillSlot[4];
//
//	//�����̃R�X�g
//	int m_currentCost;
//
//	//�����̃R�X�g�ő�l
//	int m_costMax;
//
//	//�����Ă��邩
//	bool m_have;
//
//}WordData;
//
////�f�b�L�̖��O�̍ő啶����
//#define DECK_NAME_CHAR_MAX 40
//
////�f�b�L�ɓ���邱�Ƃ��ł���P��̍ő吔
//#define DECK_WORD_MAX 40
//
////�f�b�L�̕ۑ��ł���ő吔
//#define PLAYER_DECKS_MAX 8
//
//typedef struct
//{
//
//	//�\�����镶��ID
//	int m_wordIds[MAGIC_KNIGHT_WORD_MAX];
//
//	//�\������P��̐�
//	int m_wordNum;
//
//	//�R�X�g���
//	int m_costMax;
//
//}PlayerDeck;
//
////�K�E�Z���\������P��̍ő吔
//#define MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX 5
//
////WM�p�K�E�Z���\������ő吔
//#define WEAPON_MASTER_ACTION_LISTS 10