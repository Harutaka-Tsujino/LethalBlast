#pragma once
#include "ControlHP.h"

enum HP_TEX
{
	PLAYER_HP_TEX,
	ENEMY_HP_TEX,
	ENEMY_ATK_TEX,
	ENEMY_CT_TEX,
	TEX_MAX
};

//HP描画関数
void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pCount, int* pCTCount, int playerType, int* pEnemyType);
//プレイヤーHP
void RenderPlayerHP(PlayerState* pPlayer, TEXTUREID* pTextureIds, int pPlayerType);
//敵HP
void RenderEnemyHP(EnemyState* pEnemy, TEXTUREID* pTextureIds, int* pEnemyType);
//敵の攻撃ゲージ
void RenderEnemyATKGauge(TEXTUREID* pTextureIds, int* pCount);
//敵のCTゲージ
void RenderEnemyCTGauge(TEXTUREID* pTextureIds, int* pCTCount);