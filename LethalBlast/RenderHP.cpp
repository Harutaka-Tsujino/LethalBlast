#include "DX9Lib.h"
#include "ControlHP.h"
#include "RenderHP.h"


void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy)
{
	/*static int frameCount = -1;

	static TEXTUREID textureIds[TEX_MAX];

	static FONTID fontIds[FONT_MAX];

	if (frameCount == -1)
	{
		RoadTexture("HPGauge.jpg", &textureIds[PLAYER_HP_TEX]);
		RoadTexture("HPGauge.jpg", &textureIds[ENEMY_HP_TEX]);
		SetFont(40, 40, "Times New Roman", &fontIds[HP_FONT], 20);
		frameCount = 0;
	}

	RenderPlayerHP(pPlayer, textureIds);

	RenderEnemyHP(pEnemy, textureIds);

	char hoge[256];
	sprintf_s(hoge,256,"%d", pPlayer->m_HP);
	WriteText(300, 300, hoge, DT_RIGHT, fontIds[HP_FONT]);
	
	frameCount++;

	if (frameCount > 120000)
	{
		frameCount = 0;
	}*/

	return;
}

void RenderPlayerHP(PlayerState* pPlayer, TEXTUREID* pTextureIds)
{
	/*float playerHPRatio = pPlayer->m_HP / pPlayer->m_maxHP;

	float playerMoveX = (pPlayer->m_maxHP - pPlayer->m_HP) / 2 * 400;

	CustomVertex playerHPSrc[4];

	CustomImageVerticies(playerHPSrc, 200.f, 200.f, 200.f, 200.f, GetColor(255, 64, 65, 240));

	CustomVertex playerHPMoved[4];

	RescaleImage(playerHPMoved, playerHPSrc, playerHPRatio, 1);

	MoveImage(playerHPMoved, playerHPMoved, playerMoveX, 0);

	DrawImage(playerHPMoved, pTextureIds[PLAYER_HP_TEX]);
*/
}

void RenderEnemyHP(EnemyState* pEnemy,TEXTUREID* pTextureIds)
{
	/*float enemyHPRatio = pEnemy->m_HP / pEnemy->m_maxHP;

	float enemyMoveX = (pEnemy->m_maxHP - pEnemy->m_HP) / 2 * 400;

	CustomVertex enemyHPSrc[4];

	CustomImageVerticies(enemyHPSrc, 200.f, 200.f, 200.f, 200.f, GetColor(255, 64, 65, 240));

	CustomVertex enemyHPMoved[4];

	RescaleImage(enemyHPMoved, enemyHPSrc, enemyHPRatio, 1);

	MoveImage(enemyHPMoved, enemyHPMoved, enemyMoveX, 0);

	DrawImage(enemyHPMoved, pTextureIds[ENEMY_HP_TEX]);*/

}