#pragma once
#include "ControlHP.h"

enum TEX
{
	PLAYER_HP_TEX,
	ENEMY_HP_TEX,
	TEX_MAX
};

//enum FONT
//{
//	HP_FONT,
//	FONT_MAX
//};

void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy);
void RenderPlayerHP(PlayerState* pPlayer, TEXTUREID* pTextureIds);
void RenderEnemyHP(EnemyState* pEnemy, TEXTUREID* pTextureIds);