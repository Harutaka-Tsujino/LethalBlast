#pragma once
#include"ControlWordListsAndTyping.h"

//�G�̎��
enum ENEMY_TYPE
{
	MOB,
	BOSS,
	ENEMY_TYPE_MAX
};

//�v���C���[�̃X�e�[�^�X
typedef struct
{
	int m_HP;
	float m_maxHP;
	const char* m_name;
	int m_weekPoint;
}PlayerState;


//�G�̃X�e�[�^�X
typedef struct
{
	const char* m_name;
	int m_HP;
	float m_maxHP;
	int m_weakElement;
	int m_weakPhysicalAttak;
}EnemyState;

//HP�������֐�
void InitHP(PlayerState* pPlayer, EnemyState *pEnemy, int* pPlayerType, int* pEnemyType);
//HP����֐�
void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage, int* pPlayerType, int* pEnemyType, bool* pInitHPFlag,int* pCount,int* pCTCount, MagicKnightAction* pMagicKnightAction);