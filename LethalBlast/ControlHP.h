#pragma once
#include "WinMain.h"
#include "ControlMagicKnightMainGame.h"
#include "ControlWeaponMasterAction.h"
#include "DX9Lib.h"

//敵の種類
enum ENEMY_TYPE
{
	SPIDER_ROBOT,
	BOSS,
	ENEMY_TYPE_MAX
};

//敵の種族
enum ENEMY_PHYLUM
{
	DRAGON,
	BEAST,
	ENEMY_PHYLUM_MAX
};

//プレイヤーのステータス
typedef struct
{
	int m_HP;
	float m_maxHP;
	bool m_delayAtackBuffFlag;
	bool m_suicideAtackBuffFlag;
	bool m_suicideAtackDebuffFlag;
	bool m_defenceBuffFlag;
}PlayerState;


//敵のステータス
typedef struct
{
	ENEMY_PHYLUM m_phylum;
	int m_HP;
	float m_maxHP;
	ELEMENT_ATTRIBUTE m_weakElementAttribute;
	ELEMENT_ATTRIBUTE m_resistElementAttribute;
	ATTACK_ATTRIBUTE m_weakAttackAttribute;
	ATTACK_ATTRIBUTE m_resistAttackAttribute;
}EnemyState;

//HP初期化関数
void InitHP(PlayerState* pPlayer, EnemyState *pEnemy, PLAYERTYPE PlayerType, ENEMY_TYPE EnemyType);

//HP操作関数
void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage, PLAYERTYPE PlayerType, ENEMY_TYPE EnemyType, int* pFrameCount, int* pCTCount,
	MagicKnightAction* pMagicKnightAction, WordData* pWordData);

//マジックナイトの攻撃ダメージ計算
void CalcMagicKnightATKDamage(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage, MagicKnightAction* pMagicKnightAction, WordData* pWordData);

//ウェポンマスターの攻撃ダメージ計算

//敵の攻撃ダメージ計算
void CalcEnemyATKDamage(PlayerState* pPlayer, EnemyState* pEnemy, PLAYERTYPE PlayerType, ENEMY_TYPE EnemyType, int* pPlayerATKDamage, int* pFrameCount, int* pCTCount);