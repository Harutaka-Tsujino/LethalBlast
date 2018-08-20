#include "DX9Lib.h"
#include "ControlHP.h"
#include "RenderHP.h"


void RenderHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pFrameCount, int* pCTCount)
{
	static int frameCount = -1;

	static TEXTUREID textureIds[TEX_MAX];

	static FONTID fontIds[HP_FONT_MAX];
	char test[64];

	if (frameCount == -1)
	{
		RoadTexture("playerHPGauge.jpg", &textureIds[PLAYER_HP_TEX]);
		RoadTexture("enemyHPGauge.jpg", &textureIds[ENEMY_HP_TEX]);
		RoadTexture("Texture/MainGame/HP/LB.Hp_waku.png", &textureIds[ENEMY_HP_FRAME_TEX]);
		RoadTexture("CT.jpg", &textureIds[ENEMY_ATK_TEX]);
		RoadTexture("Texture/MainGame/HP/ct.png", &textureIds[ENEMY_CT_TEX]);

		SetFont(40, 40, "Times New Roman", &fontIds[HP_FONT], 20);

		frameCount = 0;
	}

	RenderPlayerHP(pPlayer, &textureIds[PLAYER_HP_TEX]);

	RenderEnemyHP(pEnemy, textureIds);

	RenderEnemyATKGauge(&textureIds[ENEMY_ATK_TEX], pFrameCount);

	RenderEnemyCTGauge(&textureIds[ENEMY_CT_TEX], pCTCount);

#ifdef _DEBUG
	sprintf_s(test, 64, "%d", pEnemy->m_HP);
	WriteText(300, 300, test, DT_CENTER, fontIds[HP_FONT], 0xffff0000);

	sprintf_s(test, 64, "%d", pPlayer->m_HP);
	WriteText(300, 350, test, DT_CENTER, fontIds[HP_FONT], 0xffff0000);
#endif
	frameCount++;

	if (frameCount > 120000)
	{
		frameCount = 0;
	}

	return;
}


void RenderPlayerHP(PlayerState* pPlayer, TEXTUREID* pTextureIds)
{
	float playerHPRatio = pPlayer->m_HP / pPlayer->m_maxHP;

	float playerMoveX = -((pPlayer->m_maxHP - pPlayer->m_HP) / pPlayer->m_maxHP / 2 * 200);

	CustomVertex playerHPSrc[4];

	CustomImageVerticies(playerHPSrc, 150.f, 600.f, 100.f, 20.f, GetColor(255, 0, 255, 0));

	CustomVertex playerHPMoved[4];

	RescaleImage(playerHPMoved, playerHPSrc, playerHPRatio, 1);

	MoveImage(playerHPMoved, playerHPMoved, playerMoveX, 0);

	DrawImage(playerHPMoved, *pTextureIds);
}


void RenderEnemyHP(EnemyState* pEnemy, TEXTUREID* pTextureIds)
{
	float enemyHPRatio = pEnemy->m_HP / pEnemy->m_maxHP;

	float enemyMoveX = -((pEnemy->m_maxHP - pEnemy->m_HP) / pEnemy->m_maxHP / 2 * 400);

	CustomVertex enemyHPSrc[4];
	CustomVertex enemyHPFrameSrc[4];

	CustomImageVerticies(enemyHPSrc, 640.f, 100.f, 200.f, 20.f, GetColor(255, 0, 0, 255));
	CustomImageVerticies(enemyHPFrameSrc, 640.f, 100.f, 200.f, 20.f, GetColor(255, 255, 255, 255));

	CustomVertex enemyHPMoved[4];

	RescaleImage(enemyHPMoved, enemyHPSrc, enemyHPRatio, 1);

	MoveImage(enemyHPMoved, enemyHPMoved, enemyMoveX, 0);

	DrawImage(enemyHPMoved, pTextureIds[ENEMY_HP_TEX]);
	DrawImage(enemyHPFrameSrc, pTextureIds[ENEMY_HP_FRAME_TEX]);
}


void RenderEnemyATKGauge(TEXTUREID* pTextureIds, int* pFrameCount)
{
	float enemyATKRatio = (*pFrameCount) / 720.0;

	float enemyATKMoveX = (*pFrameCount) / 720.0 / 2 * 400;

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
	CustomVertex enemyCT4Src[4];

	int color = 0;

	CustomImageVerticies(enemyCT1Src, 450.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	CustomImageVerticies(enemyCT2Src, 500.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	CustomImageVerticies(enemyCT3Src, 550.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	CustomImageVerticies(enemyCT4Src, 600.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));

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

	if (*pCTCount >= 4)
	{
		color = 255;
		CustomImageVerticies(enemyCT4Src, 600.f, 200.f, 20.f, 20.f, GetColor(255, color, color, color));
	}

	DrawImage(enemyCT1Src, *pTextureIds);
	DrawImage(enemyCT2Src, *pTextureIds);
	DrawImage(enemyCT3Src, *pTextureIds);
	DrawImage(enemyCT4Src, *pTextureIds);
}