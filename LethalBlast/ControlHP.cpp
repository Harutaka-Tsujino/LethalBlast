#include "ControlHP.h"


//HP初期化関数
void InitHP(PlayerState* pPlayer, EnemyState *pEnemy,int* pPlayerType,int* pEnemyType)
{
	//プレイヤー種類ごとの初期HP設定
	if (*pPlayerType == MAGIC_KNIGHT)		//魔法剣士の時
	{
		pPlayer[MAGIC_KNIGHT].m_maxHP = 1000;
		pPlayer[MAGIC_KNIGHT].m_HP = 1000;
	}
	else if (*pPlayerType == WEAPON_MASTER)	//ウェポンマスターの時
	{
		pPlayer[WEAPON_MASTER].m_maxHP = 1000;
		pPlayer[WEAPON_MASTER].m_HP = 1000;	
	}
	else if (*pPlayerType == SUMMONER)		//召喚士の時
	{
		pPlayer[SUMMONER].m_maxHP = 1000;
		pPlayer[SUMMONER].m_HP = 1000;
	}

	//敵種類ごとの初期HP設定
	if (*pEnemyType == MOB)			//雑魚敵の時
	{
		pEnemy[MOB].m_maxHP = 1000;
		pEnemy[MOB].m_HP = 1000;		
	}
	else if (*pEnemyType == BOSS)	//ボスモンスターの時
	{
		pEnemy[BOSS].m_maxHP = 1000;
		pEnemy[BOSS].m_HP = 1000;		
	}
}

//HP操作関数
void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pDamage,int* pPlayerType,int* pEnemyType)
{
	static int count = 0;
	static int CTCount = 0;
		
		//CTが溜まると必殺技を撃つ
		if (CTCount = 5)
		{
			pPlayer[*pPlayerType].m_HP -= 100;
		}

		//3秒に1回ダメージ
		if (count >= 180)
		{
			pPlayer[*pPlayerType].m_HP -= 100;
			count = 0;
			CTCount++;
		}

		count ++;
	
		pEnemy[*pEnemyType].m_HP -= *pDamage;
}