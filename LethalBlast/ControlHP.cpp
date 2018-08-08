#include "ControlHP.h"


//HP�������֐�
void InitHP(PlayerState* pPlayer, EnemyState *pEnemy,int* pPlayerType,int* pEnemyType)
{
	//�v���C���[��ނ��Ƃ̏���HP�ݒ�
	if (*pPlayerType == MAGIC_KNIGHT)		//���@���m�̎�
	{
		pPlayer[MAGIC_KNIGHT].m_maxHP = 1000;
		pPlayer[MAGIC_KNIGHT].m_HP = 1000;
	}
	else if (*pPlayerType == WEAPON_MASTER)	//�E�F�|���}�X�^�[�̎�
	{
		pPlayer[WEAPON_MASTER].m_maxHP = 1000;
		pPlayer[WEAPON_MASTER].m_HP = 1000;	
	}
	else if (*pPlayerType == SUMMONER)		//�����m�̎�
	{
		pPlayer[SUMMONER].m_maxHP = 1000;
		pPlayer[SUMMONER].m_HP = 1000;
	}

	//�G��ނ��Ƃ̏���HP�ݒ�
	if (*pEnemyType == MOB)			//�G���G�̎�
	{
		pEnemy[MOB].m_maxHP = 1000;
		pEnemy[MOB].m_HP = 1000;		
	}
	else if (*pEnemyType == BOSS)	//�{�X�����X�^�[�̎�
	{
		pEnemy[BOSS].m_maxHP = 1000;
		pEnemy[BOSS].m_HP = 1000;		
	}
}

//HP����֐�
void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pDamage,int* pPlayerType,int* pEnemyType)
{
	static int count = 0;
	static int CTCount = 0;
		
		//CT�����܂�ƕK�E�Z������
		if (CTCount = 5)
		{
			pPlayer[*pPlayerType].m_HP -= 100;
		}

		//3�b��1��_���[�W
		if (count >= 180)
		{
			pPlayer[*pPlayerType].m_HP -= 100;
			count = 0;
			CTCount++;
		}

		count ++;
	
		pEnemy[*pEnemyType].m_HP -= *pDamage;
}