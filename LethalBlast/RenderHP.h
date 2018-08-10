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


//HP�`��֐�
void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pCount, int* pCTCount, int playerType, int* pEnemyType);
//�v���C���[HP
void RenderPlayerHP(PlayerState* pPlayer, TEXTUREID* pTextureIds, int pPlayerType);
//�GHP
void RenderEnemyHP(EnemyState* pEnemy, TEXTUREID* pTextureIds, int* pEnemyType);
//�G�̍U���Q�[�W
void RenderEnemyATKGauge(TEXTUREID* pTextureIds, int* pCount);
//�G��CT�Q�[�W
void RenderEnemyCTGauge(TEXTUREID* pTextureIds, int* pCTCount);