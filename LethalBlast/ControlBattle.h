//#pragma once
//
//
//#define MK_COST_1_DAMAGE 1500000
//#define MK_COST_1_PLUS__DAMAGE 50000
//
//#define MK_COST_3_DAMAGE 3500000
//#define MK_COST_3_PLUS__DAMAGE 45000
//
//#define MK_COST_5_DAMAGE 5000000
//#define MK_COST_5_PLUS__DAMAGE 40000
//
//#define MK_COST_12_DAMAGE 15000000
//#define MK_COST_12_PLUS__DAMAGE 25000
//
//#define ELEMENT_WEAK 1.2f
//#define ELEMENT_RESIST 0.7f
//
//#define ATTACK_WEAK 1.1f
//#define ATTACK_RESIST 0.8f
//
//enum ENEMY
//{
//	VOID_ENEMY,
//	エーレ・ツヴァイ人型,
//	ENEMY_MAX,
//};
//
//typedef struct
//{
//	int m_cTCurrentCount;
//	int m_cT;
//	int m_cTMax;
//	int m_cTBlank;
//	bool m_enemyWon;
//	bool m_playerWon;
//	bool m_draw;
//	int m_elementEffectId;
//	int m_attackEffectId;
//	int m_enemyId;
//	UINT m_playerDamage;
//	UINT m_enemyDamage;
//}VSData;
//
//#define ACTION_NAME_MAX 60
//
//typedef struct
//{
//	char m_name[ACTION_NAME_MAX];
//	bool m_ActionElements[ELEMENT_ATTRIBUTES_MAX];
//	bool m_ActionAttacks[ATTACK_ATTRIBUTES_MAX];
//	UINT m_ActionDamage;
//}ActionDamage;
//
//#define ENEMY_NAME_MAX 30
//#define ENEMY_ACTION_MAX 3
//
//typedef struct
//{
//	char m_name[ENEMY_NAME_MAX];
//	ActionDamage m_enemyAction[ENEMY_ACTION_MAX];
//	int m_cTNum;
//	int m_cTBlank;
//}EnemyST;
//
//#include"ControlMagicKnightMainGame.h"
//
//void ControlBattle(WordData* pMagicKnightWordDatas, int* frameCount, VSData* battleData,
//	MagicKnightAction* pMagicKnightAction, EnemyST enemyState, int enemyActionNum);
//
//void CalcWeakResistDamage(ActionDamage* action, ActionDamage* enemyAction);
