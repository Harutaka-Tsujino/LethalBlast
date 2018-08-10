#include "ControlHP.h"
#include "WinMain.h"
#include"ControlWordListsAndTyping.h"

void InitHP(PlayerState* pPlayer, EnemyState *pEnemy,int* pPlayerType,int* pEnemyType)
{
	//�v���C���[��ނ��Ƃ̏���HP�ݒ�
	if (*pPlayerType == MAGIC_KNIGHT)		//���@���m�̎�
	{
		pPlayer[MAGIC_KNIGHT].m_maxHP = 800;
		pPlayer[MAGIC_KNIGHT].m_HP = 800;
	}
	else if (*pPlayerType == WEAPON_MASTER)	//�E�F�|���}�X�^�[�̎�
	{
		pPlayer[WEAPON_MASTER].m_maxHP = 1000;
		pPlayer[WEAPON_MASTER].m_HP = 1000;	
	}
	else if (*pPlayerType == NECROMAMCERANDSUMMONUR)		//�����m�̎�
	{
		pPlayer[NECROMAMCERANDSUMMONUR].m_maxHP = 600;
		pPlayer[NECROMAMCERANDSUMMONUR].m_HP = 600;
	}

	//�G��ނ��Ƃ̏���HP�ݒ�
	if (*pEnemyType == MOB)			//�G���G�̎�
	{
		pEnemy[MOB].m_maxHP = 1000;
		pEnemy[MOB].m_HP = 1000;		
	}
	else if (*pEnemyType == BOSS)	//�{�X�����X�^�[�̎�
	{
		pEnemy[BOSS].m_maxHP = 100000;
		pEnemy[BOSS].m_HP = 100000;		
	}
}

void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage,int* pPlayerType,int* pEnemyType, bool* pInitHPFlag, int* pCount,int* pCTCount,  MagicKnightAction* pMagicKnightAction)
{

	//�ŏ�����������
	if (*pInitHPFlag ==true)
	{
		InitHP(pPlayer, pEnemy, pPlayerType, pEnemyType);
		*pInitHPFlag = false;
	}

	//�v���C���[HP����

	//CT�����܂�ƕK�E�Z������
	if (*pCTCount == 3)
	{
		pPlayer[*pPlayerType].m_HP -= 50;
		(*pCTCount) = 0;
	}

	//3�b��1��_���[�W
	if (*pCount >= 180)
	{
		pPlayer[*pPlayerType].m_HP -= 20;
		(*pCount) = 0;
		(*pCTCount)++;
	}

	(*pCount)++;

	//�v���C���[�̍U���_���[�W�v�Z
	
	(*pPlayerATKDamage) = 0;

	int wordCount = 0;

	for (int i = 0; i < 5; i++)
	{
		if (pMagicKnightAction->m_componentWordIds[i] != 0)
		{
			wordCount++;
		}
	}

	(*pPlayerATKDamage) = wordCount * 100;

	if(pEnemy[*pEnemyType].m_HP != 0)
	{ 
		pEnemy[*pEnemyType].m_HP -= *pPlayerATKDamage;
	}
}
