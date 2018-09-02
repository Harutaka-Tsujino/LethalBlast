#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlWeaponMasterAction.h"
#include"ControlGame.h"
#include"RenderHome.h"

void RenderHome(SCENE* scene, CustomVertex* deckAlterPortal, CustomVertex* modifyWordPortal,
	CustomVertex* mainGamePortal, CustomVertex* charaChoicePortal, TEXTUREID* wordTexIds, TEXTUREID* weaponMasterWordIds,PLAYERTYPE* playerType,bool* initializedTex)
{
	static int frameCount = -1;

	static TEXTUREID homeTextures[HOME_TEX_MAX];

	const int PAGE_MAX = 8;
	const int PAGE_LIFE = 150;
	const int PAGE_LIFE_HEYDAY = 10;
	static int pageLife[PAGE_MAX];
	static TEXTUREID pageTexture[PAGE_MAX];
	static ImagesCustomVertex pageVertices[PAGE_MAX];

	const int BACK_NUM = 6;
	static int backFrameCount[BACK_NUM];

	if (frameCount == -1)
	{
		for (int page = 0; page < PAGE_MAX; ++page)
		{
			pageLife[page] = rand() % PAGE_LIFE;

			SAFE_RELEASE(pageTexture[page])
		}

		RoadTexture("Texture/Home/AlterDeckPortal.png", &homeTextures[ALTER_PORTAL_TEX]);
		RoadTexture("Texture/Home/CharaChoicePortal.png", &homeTextures[CHARA_CHOICE_PORTAL_TEX]);
		RoadTexture("Texture/Home/MainGamePortal.png", &homeTextures[QUEST_PORTAL_TEX]);
		RoadTexture("Texture/Home/ModifyWordPortal.png", &homeTextures[MODIFY_PORTAL_TEX]);
		RoadTexture("Texture/Home/HomeBackground1.png", &homeTextures[HOME_BACK_1_TEX]);
		RoadTexture("Texture/Home/HomeBackground01.png", &homeTextures[HOME_BACK_01_TEX]);
		RoadTexture("Texture/Home/HomeBackground02.png", &homeTextures[HOME_BACK_02_TEX]);
		RoadTexture("Texture/Home/HomeBackground03.png", &homeTextures[HOME_BACK_03_TEX]);
		RoadTexture("Texture/Home/HomeBackground04.png", &homeTextures[HOME_BACK_04_TEX]);
		RoadTexture("Texture/Home/HomeBackground05.png", &homeTextures[HOME_BACK_05_TEX]);
		RoadTexture("Texture/Home/HomeBackground06.png", &homeTextures[HOME_BACK_06_TEX]);
		RoadTexture("Texture/MainGame/Enemy/EDoubleCaster.png", &homeTextures[HOME_MAIN_CHARA_TEX]);

		ZeroMemory(backFrameCount, sizeof(int)*BACK_NUM);

		frameCount = 0;
	}

	static ImagesCustomVertex back[BACK_NUM];

	const float DRAW_SPACE = 14.f;

	if (DRAW_SPACE <= frameCount)
	{
		if (frameCount < DRAW_SPACE * 2)
		{
			CustomImageVerticies(back[1].ImageVertex, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f
				, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f,
				GetColor((UCHAR)(255 * ((backFrameCount[1] + 1) / DRAW_SPACE)), 255, 255, 255));

			backFrameCount[1]++;
		}

		DrawImage(back[1].ImageVertex, homeTextures[HOME_BACK_02_TEX]);
	}

	if (DRAW_SPACE * 2 <= frameCount)
	{
		if (frameCount < DRAW_SPACE * 3)
		{
			CustomImageVerticies(back[2].ImageVertex, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f,
				((DISPLAY_WIDTH / 2.f)*((backFrameCount[2] + 1) / DRAW_SPACE)), DISPLAY_HEIGHT / 2.f,
				0xFFFFFFFF,
				(DISPLAY_WIDTH / 2.f) - ((DISPLAY_WIDTH / 2.f)*((backFrameCount[2] + 1) / DRAW_SPACE)), DISPLAY_HEIGHT / 2.f,
				(DISPLAY_WIDTH / 2.f)*((backFrameCount[2] + 1) / DRAW_SPACE), (float)DISPLAY_HEIGHT, (float)DISPLAY_WIDTH, (float)DISPLAY_HEIGHT);

			backFrameCount[2]++;
		}

		DrawImage(back[2].ImageVertex, homeTextures[HOME_BACK_03_TEX]);
	}

	if (DRAW_SPACE * 3 <= frameCount)
	{
		if (frameCount < DRAW_SPACE * 4)
		{
			CustomImageVerticies(back[3].ImageVertex, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f,
				(DISPLAY_WIDTH / 2.f)*((backFrameCount[3] + 1) / DRAW_SPACE), DISPLAY_HEIGHT / 2.f,
				0xFFFFFFFF,
				0.f, 0.f,
				DISPLAY_WIDTH*((backFrameCount[3] + 1) / DRAW_SPACE), (float)DISPLAY_HEIGHT, (float)DISPLAY_WIDTH, (float)DISPLAY_HEIGHT);

			backFrameCount[3]++;
		}

		DrawImage(back[3].ImageVertex, homeTextures[HOME_BACK_04_TEX]);
	}

	if (DRAW_SPACE * 4 <= frameCount)
	{
		if (frameCount < DRAW_SPACE * 5)
		{
			CustomImageVerticies(back[4].ImageVertex, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f,
				(DISPLAY_WIDTH / 2.f) * ((backFrameCount[4] + 1) / DRAW_SPACE), DISPLAY_HEIGHT / 2.f,
				0xFFFFFFFF,
				DISPLAY_WIDTH - DISPLAY_WIDTH * ((backFrameCount[4] + 1) / DRAW_SPACE), 0.f,
				DISPLAY_WIDTH * ((backFrameCount[4] + 1) / DRAW_SPACE), (float)DISPLAY_HEIGHT, (float)DISPLAY_WIDTH, (float)DISPLAY_HEIGHT);

			backFrameCount[4]++;
		}

		DrawImage(back[4].ImageVertex, homeTextures[HOME_BACK_05_TEX]);
	}

	if (DRAW_SPACE * 5 <= frameCount)
	{
		if (frameCount < DRAW_SPACE * 6)
		{
			CustomImageVerticies(back[5].ImageVertex, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f,
				DISPLAY_WIDTH / 2.f, (DISPLAY_HEIGHT / 2.f) * ((backFrameCount[5] + 1) / DRAW_SPACE),
				0xFFFFFFFF,
				0.f, DISPLAY_HEIGHT - DISPLAY_HEIGHT * ((backFrameCount[5] + 1) / DRAW_SPACE),
				(float)DISPLAY_WIDTH, DISPLAY_HEIGHT * ((backFrameCount[5] + 1) / DRAW_SPACE),
				(float)DISPLAY_WIDTH, (float)DISPLAY_HEIGHT);

			backFrameCount[5]++;
		}

		DrawImage(back[5].ImageVertex, homeTextures[HOME_BACK_06_TEX]);
	}

	if (DRAW_SPACE * 6 <= frameCount)
	{
		if (frameCount < DRAW_SPACE * 7)
		{
			CustomImageVerticies(back[0].ImageVertex, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, GetColor((UCHAR)(255 * ((backFrameCount[0] + 1) / DRAW_SPACE)), 255, 255, 255));

			backFrameCount[0]++;
		}

		DrawImage(back[0].ImageVertex, homeTextures[HOME_BACK_1_TEX]);
	}

	const float PAGE_SCALE_RATIO_X = 25.f;
	const float PAGE_SCALE_RATIO_Y = 5.f;

	static Vect pageScale[PAGE_MAX];

	const int ALPHA_MAX = 190;
	const int RAND_NUM_WIDTH = 5;
	const int RAND_NUM_UNDER = 4;

	if (*playerType == MAGIC_KNIGHT && (*initializedTex))
	{
		for (int page = 0; page < PAGE_MAX; ++page)
		{
			if (pageLife[page] == 0)
			{
				pageLife[page] = PAGE_LIFE;

				int randNum = rand() % RAND_NUM_WIDTH + RAND_NUM_UNDER;

				pageScale[page].m_x = (double)PAGE_SCALE_RATIO_X* randNum;
				pageScale[page].m_y = (double)PAGE_SCALE_RATIO_Y* randNum;

				CustomImageVerticies(pageVertices[page].ImageVertex, (float)(rand() % DISPLAY_WIDTH), (float)(rand() % DISPLAY_HEIGHT), 0, (float)pageScale[page].m_y, GetColor(0, 255, 255, 255));

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

				SetImageTuTv(pageVertices[page].ImageVertex, pageVertices[page].ImageVertex, 0.f, 0.f, (float)pageScale[page].m_x * (1.f - (float)(pageLife[page] - PAGE_LIFE + PAGE_LIFE_HEYDAY) / PAGE_LIFE_HEYDAY), 1.f, (float)pageScale[page].m_x, 1.f);
			}

			else
			{
				for (int vertices = 0; vertices < RECT_VERTEX_NUM; ++vertices)
				{
					pageVertices[page].ImageVertex[vertices].m_color = GetColor((UCHAR)(ALPHA_MAX * (float)(pageLife[page] / (float)(PAGE_LIFE - PAGE_LIFE_HEYDAY))), 255, 255, 255);
				}
			}

			DrawImage(pageVertices[page].ImageVertex, pageTexture[page]);
		}
	}

	if (*playerType == WEAPON_MASTER&& (*initializedTex))
	{
		const float WM_WORD_SCALE_X = 9.f;
		const float WM_WORD_SCALE_Y = 6.5f;

		for (int page = 0; page < PAGE_MAX; ++page)
		{
			if (pageLife[page] == 0)
			{
				pageLife[page] = PAGE_LIFE;

				int randNum = rand() % RAND_NUM_WIDTH + RAND_NUM_UNDER;

				pageScale[page].m_x = (double)WM_WORD_SCALE_X* randNum;
				pageScale[page].m_y = (double)WM_WORD_SCALE_Y* randNum;

				CustomImageVerticies(pageVertices[page].ImageVertex, (float)(rand() % DISPLAY_WIDTH), (float)(rand() % DISPLAY_HEIGHT), 0, (float)pageScale[page].m_y, GetColor(0, 255, 255, 255));

				pageTexture[page] = weaponMasterWordIds[rand() % (WEAPON_MASTER_WORD_MAX - 1) + 1];
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

				SetImageTuTv(pageVertices[page].ImageVertex, pageVertices[page].ImageVertex, 0.f, 0.f, (float)pageScale[page].m_x * (1.f - (float)(pageLife[page] - PAGE_LIFE + PAGE_LIFE_HEYDAY) / PAGE_LIFE_HEYDAY), 1.f, (float)pageScale[page].m_x, 1.f);
			}

			else
			{
				for (int vertices = 0; vertices < RECT_VERTEX_NUM; ++vertices)
				{
					pageVertices[page].ImageVertex[vertices].m_color = GetColor((UCHAR)(ALPHA_MAX * (float)(pageLife[page] / (float)(PAGE_LIFE - PAGE_LIFE_HEYDAY))), 0, 0,0);
				}
			}

			DrawImage(pageVertices[page].ImageVertex, pageTexture[page]);
		}
	}

	CustomVertex MainChara[RECT_VERTEX_NUM];
	CustomImageVerticies(MainChara, DISPLAY_WIDTH / 4.f, DISPLAY_HEIGHT * 0.56f, DISPLAY_WIDTH / 4.f, DISPLAY_WIDTH / 4.f,GetColor(255,229,220,220));

	DrawImage(MainChara, homeTextures[HOME_MAIN_CHARA_TEX]);

	DrawImage(deckAlterPortal, homeTextures[ALTER_PORTAL_TEX]);
	DrawImage(modifyWordPortal, homeTextures[MODIFY_PORTAL_TEX]);
	DrawImage(mainGamePortal, homeTextures[QUEST_PORTAL_TEX]);
	DrawImage(charaChoicePortal, homeTextures[CHARA_CHOICE_PORTAL_TEX]);

	for (int page = 0; page < PAGE_MAX; ++page)
	{
		pageLife[page] -= 1;
	}

	if (frameCount < 7*DRAW_SPACE)
	{
		frameCount++;
	}

	if ((*scene) != HOME_SCENE)
	{
		frameCount = 0;

		for (int page = 0; page < PAGE_MAX; ++page)
		{
			pageLife[page] = rand() % PAGE_LIFE;

			pageTexture[page]=NULL;

			ZeroMemory(backFrameCount, sizeof(int)*BACK_NUM);
		}
	}

	return;
}
