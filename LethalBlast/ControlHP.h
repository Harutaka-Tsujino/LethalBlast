#pragma once
#include"ControlWordListsAndTyping.h"

//敵の種類
enum ENEMY_TYPE
{
	MOB,
	BOSS,
	ENEMY_TYPE_MAX
};

//プレイヤーのステータス
typedef struct
{
	int m_HP;
	float m_maxHP;
	const char* m_name;
	int m_weekPoint;
}PlayerState;


//敵のステータス
typedef struct
{
	const char* m_name;
	int m_HP;
	float m_maxHP;
	int m_weakElement;
	int m_weakPhysicalAttak;
}EnemyState;

//HP初期化関数
void InitHP(PlayerState* pPlayer, EnemyState *pEnemy, int* pPlayerType, int* pEnemyType);
//HP操作関数
void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage, int* pPlayerType, int* pEnemyType, bool* pInitHPFlag, int* pCount, int* pCTCount, MagicKnightAction* pMagicKnightAction, bool* pInitMagicKnightActionFlag);