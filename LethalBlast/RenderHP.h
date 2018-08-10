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


//HP•`‰æŠÖ”
void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pCount, int* pCTCount, int playerType, int* pEnemyType);
//ƒvƒŒƒCƒ„[HP
void RenderPlayerHP(PlayerState* pPlayer, TEXTUREID* pTextureIds, int pPlayerType);
//“GHP
void RenderEnemyHP(EnemyState* pEnemy, TEXTUREID* pTextureIds, int* pEnemyType);
//“G‚ÌUŒ‚ƒQ[ƒW
void RenderEnemyATKGauge(TEXTUREID* pTextureIds, int* pCount);
//“G‚ÌCTƒQ[ƒW
void RenderEnemyCTGauge(TEXTUREID* pTextureIds, int* pCTCount);