#include "ControlHP.h"
#include "WinMain.h"
#include"ControlWordListsAndTyping.h"

void InitHP(PlayerState* pPlayer, EnemyState *pEnemy,int* pPlayerType,int* pEnemyType)
{
	//プレイヤー種類ごとの初期HP設定
	if (*pPlayerType == MAGIC_KNIGHT)		//魔法剣士の時
	{
		pPlayer[MAGIC_KNIGHT].m_maxHP = 800;
		pPlayer[MAGIC_KNIGHT].m_HP = 800;
	}
	else if (*pPlayerType == WEAPON_MASTER)	//ウェポンマスターの時
	{
		pPlayer[WEAPON_MASTER].m_maxHP = 1000;
		pPlayer[WEAPON_MASTER].m_HP = 1000;	
	}
	else if (*pPlayerType == NECROMAMCERANDSUMMONUR)		//召喚士の時
	{
		pPlayer[NECROMAMCERANDSUMMONUR].m_maxHP = 600;
		pPlayer[NECROMAMCERANDSUMMONUR].m_HP = 600;
	}

	//敵種類ごとの初期HP設定
	if (*pEnemyType == MOB)			//雑魚敵の時
	{
		pEnemy[MOB].m_maxHP = 1000;
		pEnemy[MOB].m_HP = 1000;		
	}
	else if (*pEnemyType == BOSS)	//ボスモンスターの時
	{
		pEnemy[BOSS].m_maxHP = 100000;
		pEnemy[BOSS].m_HP = 100000;		
	}
}

void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage,int* pPlayerType,int* pEnemyType, bool* pInitHPFlag, int* pCount,int* pCTCount,  MagicKnightAction* pMagicKnightAction)
{

	//最初だけ初期化
	if (*pInitHPFlag ==true)
	{
		InitHP(pPlayer, pEnemy, pPlayerType, pEnemyType);
		*pInitHPFlag = false;
	}

	//プレイヤーHP減少

	//CTが溜まると必殺技を撃つ
	if (*pCTCount == 3)
	{
		pPlayer[*pPlayerType].m_HP -= 50;
		(*pCTCount) = 0;
	}

	//3秒に1回ダメージ
	if (*pCount >= 180)
	{
		pPlayer[*pPlayerType].m_HP -= 20;
		(*pCount) = 0;
		(*pCTCount)++;
	}

	(*pCount)++;

	//プレイヤーの攻撃ダメージ計算
	
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
