#define _CRT_SECURE_NO_WARNINGS
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"CharactarInfo.h"
#include"ControlAlterDeck.h"
#include"RenderAlterDeck.h"

void RenderAlterDeck(ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex, ImagesCustomVertex* pSkillInfo,
	CustomVertex* endDeckAlterVertices,CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices,
	TEXTUREID* wordTexIds, WordData* pPlayerWordDatas, PlayerDeck* pPlayerDecks, int* pDeckNumToAlter, bool* clickedWord, bool* pChoiceWordData)
{
	static TEXTUREID alterDeckTexId[ALTER_DECK_TEX_MAX];
	static TEXTUREID explanationFontId[SKILL_MAX];

	static FONTID fontId[1];

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("Texture/AlterDeck/EndAlterDeck.png", &alterDeckTexId[EXIT_ALTER_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground1.jpg", &alterDeckTexId[ALTER_BACK_1_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground2.png", &alterDeckTexId[ALTER_BACK_2_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterBackground3.png", &alterDeckTexId[ALTER_BACK_3_TEX]);
		RoadTexture("Texture/AlterDeck/RedFrame.png", &alterDeckTexId[ALTER_CLICKED_EFFECT_TEX]);
		RoadTexture("Texture/AlterDeck/UnderAlterWordBoard.png", &alterDeckTexId[UNDER_ALTER_WORD_BOARD_TEX]);
		RoadTexture("Texture/AlterDeck/DeckAlterTag.jpg", &alterDeckTexId[DECK_ALTER_TAG_TEX]);
		RoadTexture("Texture/MainGame/PageCursol.png", &alterDeckTexId[CURSOL_TEX]);

		RoadTexture("Texture/AlterDeck/explanationFont/mojicost1_50.png", &explanationFontId[MPプラス２]);
		RoadTexture("Texture/AlterDeck/explanationFont/mojicost2_50.png", &explanationFontId[被ダメ２５％カット]);
		RoadTexture("Texture/AlterDeck/explanationFont/mojicost3_50.png", &explanationFontId[２５％回復]);
		RoadTexture("Texture/AlterDeck/explanationFont/mojicost4_50.png", &explanationFontId[次の与ダメ１．３倍]);
		RoadTexture("Texture/AlterDeck/explanationFont/mojicost5_50.png", &explanationFontId[与ダメ１．１倍]);
		RoadTexture("Texture/AlterDeck/explanationFont/mojicost6_50.png", &explanationFontId[追撃２５％]);
		RoadTexture("Texture/AlterDeck/explanationFont/mojicost7_50.png", &explanationFontId[今１．４倍次０．８倍]);

		SetFont(DISPLAY_WIDTH / 70, DISPLAY_WIDTH / 70, "HGP明朝B", &fontId,0);

		frameCount = 0;
	}

	CustomVertex alterBackVertices[4];
	CustomImageVerticies(alterBackVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);
	
	DrawImage(alterBackVertices, alterDeckTexId[ALTER_BACK_1_TEX]);
	
	for (int wordNum = 0; wordNum < MAGIC_KNIGHT_WORD_MAX; ++wordNum)
	{
		DrawImage(pChoiseWordCollisionsVertex[wordNum].ImageVertex, alterDeckTexId[UNDER_ALTER_WORD_BOARD_TEX]);
		DrawImage(pChoiseWordCollisionsVertex[wordNum].ImageVertex, wordTexIds[wordNum]);

		if (clickedWord[wordNum])
		{
			DrawImage(pChoiseWordCollisionsVertex[wordNum].ImageVertex, alterDeckTexId[ALTER_CLICKED_EFFECT_TEX]);
		}
	}
	
	DrawImage(alterBackVertices, alterDeckTexId[ALTER_BACK_2_TEX]);

	for (int deckNum = 0; deckNum < DECK_WORD_MAX; ++deckNum)
	{
		DrawImage(pDeckComponentCollisionsVertex[deckNum].ImageVertex, alterDeckTexId[UNDER_ALTER_WORD_BOARD_TEX]);

		if (pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[deckNum])
		{
			DrawImage(pDeckComponentCollisionsVertex[deckNum].ImageVertex, wordTexIds[(pPlayerDecks[(*pDeckNumToAlter)].m_wordIds[deckNum])]);
		}
	}
	
	DrawImage(alterBackVertices, alterDeckTexId[ALTER_BACK_3_TEX]);

	CustomVertex deckAlterTag[RECT_VERTEX_NUM];
	CustomImageVerticies(deckAlterTag, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.04f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.04f);

	DrawImage(deckAlterTag,alterDeckTexId[DECK_ALTER_TAG_TEX]);

	CustomVertex cursol[4];
	const float CURSOL_POSX = DISPLAY_WIDTH * 0.7f;
	const float CURSOL_SCALE = DISPLAY_WIDTH * 0.025f;

	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
	{
		if (pChoiceWordData[wordDatas] = true)
		{
			DrawImage(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, wordTexIds[wordDatas]);

			for (int costConfig = 1;costConfig < 3;++costConfig)
			{
				switch (costConfig)
				{
				case 1:
					CustomImageVerticies(cursol, CURSOL_POSX, DISPLAY_HEIGHT*0.7f, CURSOL_SCALE, CURSOL_SCALE);
					RotateImageDeg(cursol, cursol, 180.f);

					DrawImage(cursol, alterDeckTexId[CURSOL_TEX]);
					
					break;

				case 2:
					CustomImageVerticies(cursol, CURSOL_POSX + DISPLAY_WIDTH * 0.1f, DISPLAY_HEIGHT*0.7f, CURSOL_SCALE, CURSOL_SCALE);

					DrawImage(cursol, alterDeckTexId[CURSOL_TEX]);

					break;
				}

			}

			for (int skill = MPプラス２;skill < SKILL_MAX;++skill)
			{
				DrawImage(pSkillInfo[skill].ImageVertex, explanationFontId[skill]);
			}

			char cost[10];
			sprintf(cost, "%d", pPlayerWordDatas[wordDatas].m_costMax);

			WriteText(DISPLAY_WIDTH * 0.75, DISPLAY_HEIGHT * 0.7, cost, DT_RIGHT, fontId[0]);
		}
	}

	WriteText(DISPLAY_WIDTH * 0.8, DISPLAY_HEIGHT * 0.7, "/12", DT_RIGHT, fontId[1]);

	DrawImage(endDeckAlterVertices, alterDeckTexId[EXIT_ALTER_TEX]);

	return;
}

