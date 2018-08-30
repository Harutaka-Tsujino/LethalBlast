#define _CRT_SECURE_NO_WARNINGS

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"RenderMagicKnigtMainGame.h"

//static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
//static MagicKnightPlayingDeck magicKnightPlayingDeck;
//static MagicKnightAction magicKnightAction;
//CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];
//CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

void RenderMagicKnightMainGame(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex, TEXTUREID* wordTexIds, HomingEffect* pHominEffect,
	CustomVertex* resultMask)
{
	static TEXTUREID collisionTestTexId[MK_MAIN_GAME_TEX_MAX];
	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/MainGame/WordUnderBoard.png", &collisionTestTexId[MK_UNDER_WORD_BOARD]);
		RoadTexture("texture/MainGame/MKActionWordFrame.png", &collisionTestTexId[MK_ACTION_WORD_FRAME]);
		RoadTexture("Texture/MainGame/HP/ct.png", &collisionTestTexId[MK_SELECT_WORD_EFFECT_TEX]);

		frameCount = 0;
	}

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

	DrawImage(resultMask, NULL);

	return;
}

void RenderWhileLoad(SCENE* scene,SCENE destScene, TEXTUREID* wordTexIds)
{
	static TEXTUREID LoadTexId[2];

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/Load/LoadScene1.png", &LoadTexId[0]);
		RoadTexture("texture/Load/LoadScene2.png", &LoadTexId[1]);

		frameCount = 0;
	}

	CustomVertex LoadScene[4];

	CustomImageVerticies(LoadScene, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);

	DrawImage(LoadScene, LoadTexId[rand()%2]);

	*scene = destScene;

	return;
}
