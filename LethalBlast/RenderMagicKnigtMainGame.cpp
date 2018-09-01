#define _CRT_SECURE_NO_WARNINGS

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"RenderMagicKnigtMainGame.h"
#include"ControlBattle.h"

//static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
//static MagicKnightPlayingDeck magicKnightPlayingDeck;
//static MagicKnightAction magicKnightAction;
//CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];
//CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

void RenderMagicKnightMainGame(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex, TEXTUREID* wordTexIds, 
	HomingEffect* pHominEffect,CustomVertex* resultMask, VSData* battleData, int enemyActionNum, int selectedStage, EnemyST pEnemyData)
{
	static TEXTUREID collisionTestTexId[MK_MAIN_GAME_TEX_MAX];
	static TEXTUREID enemyTexIds[ENEMY_MAX];
	static TEXTUREID stageTexIds[STAGE_MAX];
	static TEXTUREID uITexIds[UI_TEX_MAX];

	static FONTID fontId;

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/MainGame/WordUnderBoard.png", &collisionTestTexId[MK_UNDER_WORD_BOARD]);
		RoadTexture("texture/MainGame/MKActionWordFrame.png", &collisionTestTexId[MK_ACTION_WORD_FRAME]);
		RoadTexture("Texture/MainGame/HP/ct.png", &collisionTestTexId[MK_SELECT_WORD_EFFECT_TEX]);
		RoadTexture("Texture/MainGame/HP/HP.png",&uITexIds[HP_BAR]);
		RoadTexture("Texture/MainGame/HP/CTCount.png", &uITexIds[CT_BAR]);
		RoadTexture("Texture/MainGame/mainBG.png", &stageTexIds[FOREST_STAGE]);
		RoadTexture("Texture/MainGame/mainBG.png", &stageTexIds[RUIN_STAGE]);
		RoadTexture("Texture/MainGame/mainBG.png", &stageTexIds[CAVE_STAGE]);
		RoadTexture("Texture/MainGame/Enemy/Robot.png", &enemyTexIds[ŒÃ‘ã•ºŠílŒ^]);
		SetFont(DISPLAY_WIDTH / 70, DISPLAY_WIDTH / 48, "HGP–¾’©B", &fontId, 0);

		frameCount = 0;
	}

	CustomVertex back[4];
	CustomImageVerticies(back, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);

	DrawImage(back, stageTexIds[selectedStage]);

	CustomVertex enemyVertices[4];
	CustomImageVerticies(enemyVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT * 0.5f, DISPLAY_WIDTH / 6.f, DISPLAY_WIDTH / 6.f, GetColor(255, 229, 220, 220));

	DrawImage(enemyVertices, enemyTexIds[(battleData->m_enemyId)]);

	for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
	{
		DrawImage(pHandWordCollisionsVertex[handWord].ImageVertex, collisionTestTexId[MK_UNDER_WORD_BOARD]);
		DrawImage(pHandWordCollisionsVertex[handWord].ImageVertex, wordTexIds[(pMagicKnightPlayingDeck->m_handWordId[handWord])]);
	}

	CustomVertex frameVertices[RECT_VERTEX_NUM];

	static UCHAR frameAlpha = 0;

	if(frameCount<20)
	{
		frameAlpha += 12;
	}

	if (20 <= frameCount && frameCount < 40)
	{
		frameAlpha -= 10;
	}

	if (40 <= frameCount&& frameCount < 80)
	{
		frameAlpha += 5;
	}

	if (80 <= frameCount && frameCount < 100)
	{
		frameAlpha -= 10;
	}

	if (100 <= frameCount && frameCount < 120)
	{
		frameAlpha += 10;
	}

	if (120 <= frameCount)
	{
		frameAlpha = 255;
	}

	CustomImageVerticies(frameVertices, DISPLAY_WIDTH / 2.32f, DISPLAY_HEIGHT*0.97f, DISPLAY_WIDTH*0.4f, DISPLAY_HEIGHT*0.14f, GetColor(frameAlpha, 255, 255, 255));

	DrawImage(frameVertices, collisionTestTexId[MK_ACTION_WORD_FRAME]);

	for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
	{
		bool hideActionComponent= false;

		for (int effect = 0; effect < SELECT_EFFECT_MAX; ++effect)
		{
			if (pHominEffect[effect].m_valid)
			{
				if (pHominEffect[effect].m_actionPos == actionComponentWord)
				{
					hideActionComponent = true;

					break;
				}
			}
		}

		if (hideActionComponent)
		{
			continue;
		}

		if ((pMagicKnightAction->m_componentWordIds[actionComponentWord]))
		{
			DrawImage(pMagicKnightActionCollisionsVertex[actionComponentWord].ImageVertex, wordTexIds[(pMagicKnightAction->m_componentWordIds[actionComponentWord])]);
		}
	}

	for (int effect = 0; effect < SELECT_EFFECT_MAX; ++effect)
	{
		if (pHominEffect[effect].m_valid)
		{
			DrawImage(pHominEffect[effect].m_rect, collisionTestTexId[MK_SELECT_WORD_EFFECT_TEX]);
		}
	}

	if (frameCount < 120)
	{
		frameCount++;
	}

	CustomVertex barVertices[4];
	CustomImageVerticies(barVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.05f, DISPLAY_WIDTH*0.3f, DISPLAY_HEIGHT*0.02f, 0xFFFFFFFF, 
		0.5f*battleData->m_playerWon, 0.f, 0.5f, 1.f, 1.f, 1.f);

	DrawImage(barVertices, uITexIds[HP_BAR]);

	CustomImageVerticies(barVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.11f, DISPLAY_WIDTH*0.3f, DISPLAY_HEIGHT*0.02f, 0xFFFFFFFF,
		0.5f*(1.f - battleData->m_cTCurrentCount / (float)(battleData->m_cTBlank)), 0.f, 0.5f, 1.f, 1.f, 1.f);
	
	DrawImage(barVertices, uITexIds[CT_BAR]);

	CustomVertex cTVertices[4];
	for (int cTNum = 0; cTNum < battleData->m_cT; ++cTNum)
	{
		CustomImageVerticies(cTVertices, DISPLAY_WIDTH*0.216f+(DISPLAY_HEIGHT*0.07f*cTNum), DISPLAY_HEIGHT*0.18f, DISPLAY_HEIGHT*0.03f, DISPLAY_HEIGHT*0.03f, GetColor(frameAlpha, 255, 255, 255));

		DrawImage(cTVertices, collisionTestTexId[MK_SELECT_WORD_EFFECT_TEX]);
	}

	WriteText((int)(DISPLAY_WIDTH*0.1), (int)(DISPLAY_HEIGHT*0.03), pEnemyData.m_name, DT_CENTER, fontId, 0xFF111111);

	DrawImage(resultMask, NULL);

	return;
}

void RenderWhileLoad(SCENE* scene,SCENE destScene, TEXTUREID* wordTexIds)
{
	static TEXTUREID LoadTexId[2];

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/Load/LoadScene1.jpg", &LoadTexId[0]);
		RoadTexture("texture/Load/LoadScene2.jpg", &LoadTexId[1]);

		frameCount = 0;
	}

	CustomVertex LoadScene[4];

	CustomImageVerticies(LoadScene, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);

	DrawImage(LoadScene, LoadTexId[rand()%2]);

	*scene = destScene;

	return;
}
