#include "DX9Lib.h"
#include "ControlHP.h"


void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy)
{
	enum TEX
	{
		PLAYER_HP_TEX,
		ENEMY_HP_TEX,
		TEX_MAX
	};

	enum FONT
	{
		HP_FONT,
		FONT_MAX
	};


	static int frameCount = -1;

	static TEXTUREID textureIds[TEX_MAX];

	static FONTID fontIds[FONT_MAX];

	float enemyHPRatio = pEnemy->m_HP / pEnemy->m_maxHP;

	float playerHPRatio = pPlayer->m_HP / pPlayer->m_maxHP;

	float enemyMoveX = (pEnemy->m_maxHP - pEnemy->m_HP) / 2 * 400;

	float playerMoveX = (pPlayer->m_maxHP - pPlayer->m_HP) / 2 * 400;

	if (frameCount == -1)
	{
		RoadTexture("HPGauge.jpg", &textureIds[PLAYER_HP_TEX]);
		RoadTexture("HPGauge.jpg", &textureIds[ENEMY_HP_TEX]);
		SetFont(40, 40, "Times New Roman", &fontIds[HP_FONT], 20);
		frameCount = 0;
	}

	typedef CustomVertex CV;

	CV enemyHPSrc[4];
	CV playerHPSrc[4];

	CustomImageVerticies(enemyHPSrc, 200.f, 200.f, 200.f, 200.f, GetColor(255, 64, 65, 240));
	CustomImageVerticies(playerHPSrc, 200.f, 200.f, 200.f, 200.f, GetColor(255, 64, 65, 240));

	CV enemyHPMoved[4];
	CV playerHPMoved[4];

	RescaleImage(enemyHPMoved, enemyHPSrc, enemyHPRatio, 1);

	MoveImage(enemyHPMoved, enemyHPMoved, enemyMoveX, 0);

	RescaleImage(playerHPMoved, playerHPSrc, enemyHPRatio, 1);

	MoveImage(playerHPMoved, playerHPMoved, enemyMoveX, 0);

	DrawImage(playerHPMoved, textureIds[PLAYER_HP_TEX]);

	DrawImage(enemyHPMoved, textureIds[ENEMY_HP_TEX]);

	char hoge[256];
	sprintf_s(hoge,256,"%d", pPlayer->m_HP);
	WriteText(300, 300, hoge, DT_RIGHT, fontIds[HP_FONT]);
	
	frameCount++;

	if (frameCount > 120000)
	{
		frameCount = 0;
	}

	return;
}
