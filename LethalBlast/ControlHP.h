#pragma once

////プレイヤーの種類
//enum PLAYER_TYPE
//{
//	MAGIC_KNIGHT,
//	WEAPON_MASTER,
//	SUMMONER,
//	PLAYER_TYPE_MAX,
//};

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
	int m_maxHP;
	const char* m_name;
	int m_weekPoint;
}PlayerState;


//敵のステータス
typedef struct
{
	const char* m_name;
	int m_HP;
	int m_maxHP;
	int m_weakElement;
	int m_weakPhysicalAttak;
}EnemyState;

//HP初期化関数
void InitHP(PlayerState* pPlayer, EnemyState *pEnemy, int* pPlayerType, int* pEnemyType);
//HP操作関数
void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pDamage, int* pPlayerType, int* pEnemyType, bool* initHPFlag);