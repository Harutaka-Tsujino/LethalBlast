#include "DX9Lib.h"
#include "ControlHP.h"
#include "RenderHP.h"


void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pCount, int* pCTCount, int playerType, int* pEnemyType)
{
	static int frameCount = -1;

	enum FONT
	{
		testFONT,
		FONT_MAX
	};

	static TEXTUREID textureIds[TEX_MAX];

	static FONTID fontIds[FONT_MAX];
	char test[64];
	if (frameCount == -1)
	{
		RoadTexture("HPGauge.jpg", &textureIds[PLAYER_HP_TEX]);
		RoadTexture("HPGauge.jpg", &textureIds[ENEMY_HP_TEX]);
		RoadTexture("HPGauge.jpg", &textureIds[ENEMY_ATK_TEX]);
		RoadTexture("Texture/MainGame/ct.png", &textureIds[ENEMY_CT_TEX]);
		SetFont(40, 40, "Times New Roman", &fontIds[testFONT], 20);

		frameCount = 0;
	}

	RenderPlayerHP(pPlayer, &textureIds[PLAYER_HP_TEX], playerType);

	RenderEnemyHP(pEnemy, &textureIds[ENEMY_HP_TEX], pEnemyType);

	RenderEnemyATKGauge(&textureIds[ENEMY_ATK_TEX], pCount);

	RenderEnemyCTGauge(&textureIds[ENEMY_CT_TEX], pCTCount);

	sprintf_s(test, 64, "%d", pEnemy[*pEnemyType].m_HP);
	WriteText(300, 300, test, DT_RIGHT, fontIds[testFONT], 0xffff0000);

	frameCount++;

	if (frameCount > 120000)
	{
		frameCount = 0;
	}

	return;
}


void RenderPlayerHP(PlayerState* pPlayer, TEXTUREID* pTextureIds, int playerType)
{
	float playerHPRatio = pPlayer[playerType].m_HP / pPlayer[playerType].m_maxHP;

	float playerMoveX = -((pPlayer[playerType].m_maxHP - pPlayer[playerType].m_HP) / pPlayer[playerType].m_maxHP / 2 * 200);

	CustomVertex playerHPSrc[4];

	CustomImageVerticies(playerHPSrc, 150.f, 600.f, 100.f, 20.f, GetColor(255, 0, 255, 0));

	CustomVertex playerHPMoved[4];

	RescaleImage(playerHPMoved, playerHPSrc, playerHPRatio, 1);

	MoveImage(playerHPMoved, playerHPMoved, playerMoveX, 0);

	DrawImage(playerHPMoved, *pTextureIds);
}


void RenderEnemyHP(EnemyState* pEnemy, TEXTUREID* pTextureIds, int* pEnemyType)
{
	float enemyHPRatio = pEnemy[*pEnemyType].m_HP / pEnemy[*pEnemyType].m_maxHP;

	float enemyMoveX = -((pEnemy[*pEnemyType].m_maxHP - pEnemy[*pEnemyType].m_HP) / pEnemy[*pEnemyType].m_maxHP / 2 * 400);

	CustomVertex enemyHPSrc[4];

	CustomImageVerticies(enemyHPSrc, 640.f, 100.f, 200.f, 20.f, GetColor(255, 0, 0, 255));

	CustomVertex enemyHPMoved[4];

	RescaleImage(enemyHPMoved, enemyHPSrc, enemyHPRatio, 1);

	MoveImage(enemyHPMoved, enemyHPMoved, enemyMoveX, 0);

	DrawImage(enemyHPMoved, *pTextureIds);
}


void RenderEnemyATKGauge(TEXTUREID* pTextureIds, int* pCount)
{
	float enemyATKRatio = (*pCount) / 180.0;

	float enemyATKMoveX = (*pCount) / 180.0 / 2 * 400;

	CustomVertex enemyATKSrc[4];

	CustomImageVerticies(enemyATKSrc, 440.0f, 150.f, 200.f, 20.f, GetColor(255, 255, 0, 0));

	CustomVertex enemyATKMoved[4];

	RescaleImage(enemyATKMoved, enemyATKSrc, enemyATKRatio, 1);

	MoveImage(enemyATKMoved, enemyATKMoved, enemyATKMoveX, 0);

	DrawImage(enemyATKMoved, *pTextureIds);
}


void RenderEnemyCTGauge(TEXTUREID* pTextureIds, int* pCTCount)
{
	CustomVertex enemyCT1Src[4];
	CustomVertex enemyCT2Src[4];
	CustomVertex enemyCT3Src[4];

	int color = 0;

	CustomImageVerticies(enemyCT1Src, 450.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	CustomImageVerticies(enemyCT2Src, 500.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	CustomImageVerticies(enemyCT3Src, 550.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));

	if (*pCTCount >= 1)
	{
		color = 255;
		CustomImageVerticies(enemyCT1Src, 450.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	}

	if (*pCTCount >= 2)
	{
		color = 255;
		CustomImageVerticies(enemyCT2Src, 500.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	}

	if (*pCTCount >= 3)
	{
		color = 255;
		CustomImageVerticies(enemyCT3Src, 550.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	}

	DrawImage(enemyCT1Src, *pTextureIds);
	DrawImage(enemyCT2Src, *pTextureIds);
	DrawImage(enemyCT3Src, *pTextureIds);
}