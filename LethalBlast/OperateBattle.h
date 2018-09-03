#pragma once
#include<windows.h>
#include"DX9Lib.h"

#define HAND_MAX 40
#define MK_ACTION_MAX 5
#define WM_ACTION_MAX 10
#define TEXT_MAX 60

typedef struct
{
	char m_name[TEXT_MAX];
	UINT m_damage;
	int m_ability;
	int m_effectId;
}ActionEnemy;

typedef struct
{
	char m_name[TEXT_MAX];
	TEXTUREID m_texId;
	ActionEnemy m_actionEnemy;
	int m_attackWeak;
	int m_elementWeak;
	int m_attackResist;
	int m_elementResist;
}EnemyData;

typedef struct
{
	int m_actionPlayer[WM_ACTION_MAX];
	int m_actionPlayerLimit;
	int m_actionPlayerElement;
	int m_actionPlayerAttack;
	UINT m_actionPlayerDamage;

	int m_hand[HAND_MAX];
	int m_handPos[WM_ACTION_MAX];
	UINT m_hPPlayerCurrent;
	UINT m_hPPlayerMax;
	int m_pPCurrent;
	int m_pPMax;
	
	int m_effectIdPlayer;
	bool m_win;
	bool m_lose;
}Battle;
