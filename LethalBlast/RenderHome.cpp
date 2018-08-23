#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlGame.h"
#include"RenderHome.h"

void RenderHome(CustomVertex* deckAlterPortal, CustomVertex* modifyWordPortal, CustomVertex* mainGamePortal, CustomVertex* charaChoicePortal,TEXTUREID* wordTexIds)
{
	static int frameCount = -1;

	static TEXTUREID homeTextures[HOME_TEX_MAX];

	const int PAGE_MAX = 15;
	const int PAGE_LIFE = 600;
	const int PAGE_LIFE_HEYDAY = 400;
	static int pageLife[PAGE_MAX];
	static TEXTUREID pageTexture[PAGE_MAX];
	static ImagesCustomVertex pageVertices[PAGE_MAX];

	if (frameCount == -1)
	{
		for (int page = 0; page < PAGE_MAX; ++page)
		{
			pageLife[page] = rand() % PAGE_LIFE;

			pageTexture[page] = NULL;
		}

		RoadTexture("Texture/Home/AlterDeckPortal.png", &homeTextures[ALTER_PORTAL_TEX]);
		RoadTexture("Texture/Home/CharaChoicePortal.png", &homeTextures[CHARA_CHOICE_PORTAL_TEX]);
		RoadTexture("Texture/Home/MainGamePortal.png", &homeTextures[QUEST_PORTAL_TEX]);
		RoadTexture("Texture/Home/ModifyWordPortal.png", &homeTextures[MODIFY_PORTAL_TEX]);
		RoadTexture("Texture/Home/Page1.png", &homeTextures[PAGE_1_TEX]);
		RoadTexture("Texture/Home/Page2.png", &homeTextures[PAGE_2_TEX]);
		RoadTexture("Texture/Home/Page3.png", &homeTextures[PAGE_3_TEX]);
		RoadTexture("Texture/Home/Page4.png", &homeTextures[PAGE_4_TEX]);
		RoadTexture("Texture/Home/Page5.png", &homeTextures[PAGE_5_TEX]);

		frameCount = 0;
	}

	const float PAGE_SCALE_RATIO_X= 25.f;
	const float PAGE_SCALE_RATIO_Y = 5.f;

	static Vect pageScale[PAGE_MAX];

	const int ALPHA_MAX = 190;
	const int RAND_NUM_WIDTH = 5;
	const int RAND_NUM_UNDER = 4;

	for (int page = 0; page < PAGE_MAX; ++page)
	{
		if (pageLife[page] == 0)
		{
			pageLife[page] = PAGE_LIFE;

			int randNum = rand() % RAND_NUM_WIDTH + RAND_NUM_UNDER;

			pageScale[page].m_x = (double)PAGE_SCALE_RATIO_X* randNum;
			pageScale[page].m_y = (double)PAGE_SCALE_RATIO_Y* randNum;

			CustomImageVerticies(pageVertices[page].ImageVertex, (float)(rand() % DISPLAY_WIDTH), (float)(rand() % DISPLAY_HEIGHT), 0,(float)pageScale[page].m_y, GetColor(0, 255, 255, 255));

			pageTexture[page] = wordTexIds[rand() % (MAGIC_KNIGHT_WORD_MAX - 1) + 1];
		}

		if (!pageTexture[page])
		{
			continue;
		}

		if (pageLife[page] >= (PAGE_LIFE - PAGE_LIFE_HEYDAY))
		{
			for (int vertices = 1; vertices < RECT_VERTEX_NUM - 1; ++vertices)
			{
				pageVertices[page].ImageVertex[vertices].m_x += ((float)pageScale[page].m_x*(1.f / PAGE_LIFE_HEYDAY));
			}

			for (int vertices = 0; vertices < RECT_VERTEX_NUM; ++vertices)
			{
				pageVertices[page].ImageVertex[vertices].m_color = GetColor((UCHAR)(ALPHA_MAX * (1.f - ((float)(pageLife[page] - PAGE_LIFE + PAGE_LIFE_HEYDAY) / PAGE_LIFE_HEYDAY))), 255, 255, 255);
			}
			
			SetImageTuTv(pageVertices[page].ImageVertex, pageVertices[page].ImageVertex, 0.f, 0.f, (float)pageScale[page].m_x * (1.f - (float)(pageLife[page] -PAGE_LIFE+ PAGE_LIFE_HEYDAY) / PAGE_LIFE_HEYDAY), 1.f, (float)pageScale[page].m_x, 1.f);
		}

		else
		{
			for (int vertices = 0; vertices < RECT_VERTEX_NUM; ++vertices)
			{
				pageVertices[page].ImageVertex[vertices].m_color = GetColor((UCHAR)(ALPHA_MAX * (float)(pageLife[page] / (float)(PAGE_LIFE-PAGE_LIFE_HEYDAY))), 255, 255, 255);
			}
		}

		DrawImage(pageVertices[page].ImageVertex, pageTexture[page]);
	}

	DrawImage(deckAlterPortal, homeTextures[ALTER_PORTAL_TEX]);
	DrawImage(modifyWordPortal, homeTextures[MODIFY_PORTAL_TEX]);
	DrawImage(mainGamePortal, homeTextures[QUEST_PORTAL_TEX]);
	DrawImage(charaChoicePortal, homeTextures[CHARA_CHOICE_PORTAL_TEX]);

	for (int page = 0; page < PAGE_MAX; ++page)
	{
		pageLife[page] -= 1;
	}

	return;
}
