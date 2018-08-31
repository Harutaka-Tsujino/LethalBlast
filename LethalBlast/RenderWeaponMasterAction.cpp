#define _CRT_SECURE_NO_WARNINGS
#include"RenderWeaponMasterAction.h"

void RenderWeaponMasterAction(ImagesCustomVertex* pWeaponMasterDeckVerticies, ImagesCustomVertex* pWeaponMasterAction,
	WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas, int pPage,bool* scrollEffect,TEXTUREID* pWmFontIds)
{
	static TEXTUREID textureIds[WEAPON_MASTER_ACTION_TEX_MAX];
	static FONTID fontIds[FONT_MAX];

	const float SET_FONT_SCALE = DISPLAY_WIDTH / 51.f;

	static int isFirstFrame = INIT_FRAME;

	if (isFirstFrame == INIT_FRAME)
	{
		RoadTexture("Texture/MainGame/PageCursol.png", &textureIds[WEAPON_MASTER_PAGE_CURSOL_TEX]);
		RoadTexture("Texture/MainGame/frame.png", &textureIds[WEAPON_MASTER_FRAME_TEX]);
		RoadTexture("Texture/MainGame/ListBG.png", &textureIds[LIST_BG_TEX]);
		RoadTexture("Texture/MainGame/ListScroll.png", &textureIds[LIST_SCROLL_TEX]);
		SetFont((int)SET_FONT_SCALE, (UINT)SET_FONT_SCALE, "Files/Font/SoukouMincho-Font/SoukouMincho.ttf", &fontIds[PAGE_FONT], 10);
		SetFont((int)SET_FONT_SCALE, (UINT)SET_FONT_SCALE, "Files/Font/SoukouMincho-Font/SoukouMincho.ttf", &fontIds[PAGE_FONT_MAX], 10);

		isFirstFrame = 0;
	}

	CustomVertex pageTransition[RECT_VERTEX_NUM];
	CustomVertex listBG[4];
	CustomVertex ActionFrame[4];
	CustomVertex scroll[4];

	if (*scrollEffect)
	{
		const float listBGPosX1 = (DISPLAY_WIDTH - (DISPLAY_WIDTH / 7.5f) + (DISPLAY_WIDTH / 9.f));
		const float listBGposX2 = (DISPLAY_WIDTH - (DISPLAY_WIDTH / 7.5f) - (DISPLAY_WIDTH / 9.f));

		static int scrollEffectCnt = 0;
		static float scrollPosY = 0.f;
		static float scrollTv = 0.f;

		CustomImageVerticies(scroll, DISPLAY_WIDTH - (DISPLAY_WIDTH / 7.5f), scrollPosY, DISPLAY_WIDTH / 8.f, DISPLAY_HEIGHT / 30.f);
		SetTvCustomVertex(listBG, listBGPosX1, listBGposX2, listBGposX2, listBGPosX1,
			scrollPosY, scrollPosY, (DISPLAY_HEIGHT / 2.6f) + (DISPLAY_HEIGHT / 2.6f), (DISPLAY_HEIGHT / 2.6f) + (DISPLAY_HEIGHT / 2.6f),
			scrollTv, 500.f , 500.f);
		
		if (scrollEffectCnt <= 40)
		{
			scrollEffectCnt++;
		}

		if (scrollEffectCnt <= 10)
		{
			scrollPosY += ((DISPLAY_HEIGHT / 2.6f) + (DISPLAY_HEIGHT / 2.6f)) / 10.f;
			scrollTv += 500.f / 10.f;
		}

		if (31 <= scrollEffectCnt && scrollEffectCnt <= 40)
		{
			scrollPosY -= ((DISPLAY_HEIGHT / 2.6f) + (DISPLAY_HEIGHT / 2.6f)) / 10.f;
			scrollTv -= 500.f / 10.f;
		}

		DrawImage(listBG, textureIds[LIST_BG_TEX]);
		DrawImage(scroll, textureIds[LIST_SCROLL_TEX]);

		if (scrollEffectCnt == 40)
		{
			*scrollEffect = false;
			scrollPosY = 0.f;
			scrollTv = 0.f;
			scrollEffectCnt = 0;
		}
	}

	if (!*scrollEffect)
	{
		//ÉfÉbÉLì‡ÇÃï∂éöÉäÉXÉgÇÃîwåiÇÃí∏ì_ê›íË
		CustomImageVerticies(listBG, DISPLAY_WIDTH - (DISPLAY_WIDTH / 7.5f), DISPLAY_HEIGHT / 2.6f, DISPLAY_WIDTH / 9.f, DISPLAY_HEIGHT / 2.6f);
		CustomImageVerticies(scroll, DISPLAY_WIDTH - (DISPLAY_WIDTH / 7.5f), DISPLAY_HEIGHT / 40.f, DISPLAY_WIDTH / 8.f, DISPLAY_HEIGHT / 40.f);

		DrawImage(listBG, textureIds[LIST_BG_TEX]);
		DrawImage(scroll, textureIds[LIST_SCROLL_TEX]);

		for (int rectForPageTransition = 0;rectForPageTransition < 2;rectForPageTransition++)
		{
			switch (rectForPageTransition)
			{
			case 0:
				CustomImageVerticies(pageTransition, DISPLAY_WIDTH - (DISPLAY_WIDTH / 5.f), DISPLAY_HEIGHT / 1.37f, DISPLAY_WIDTH / 76.f, DISPLAY_WIDTH / 90.f);

				RotateImageDeg(pageTransition, pageTransition, 180.f);

				if (pPage != 1)
				{
					DrawImage(pageTransition, textureIds[WEAPON_MASTER_PAGE_CURSOL_TEX]);
				}

				break;

			case 1:
				CustomImageVerticies(pageTransition, DISPLAY_WIDTH - (DISPLAY_WIDTH / 15.f), DISPLAY_HEIGHT / 1.37f, DISPLAY_WIDTH / 76.f, DISPLAY_WIDTH / 90.f);

				if (pPage != 4)
				{
					DrawImage(pageTransition, textureIds[WEAPON_MASTER_PAGE_CURSOL_TEX]);
				}

				break;
			}
		}

		for (int wordLists = (pPage - 1) * 10;wordLists < (pPage) * 10;++wordLists)
		{
			if (pWeaponMasterDeck->m_wordIds[wordLists] != SPACE_WORD)
			{
				DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, pWmFontIds[(pWeaponMasterDeck->m_wordIds[wordLists])]);
			}
		}
		
		const float PAGE_TRANSISTION_FONT_WIDTH = (float)(DISPLAY_WIDTH / 30);
		const float PAGE_TRANSISTION_FONT_HEIGHT = PAGE_TRANSISTION_FONT_WIDTH;
		char pageFont[4];

		sprintf(pageFont, "%d", pPage);

		WriteText((int)PAGE_TRANSISTION_FONT_WIDTH * 26.5f, (int)PAGE_TRANSISTION_FONT_WIDTH * 12.3f, "/4", DT_RIGHT, fontIds[PAGE_FONT_MAX]);
		WriteText((int)PAGE_TRANSISTION_FONT_WIDTH * 25.5f, (int)PAGE_TRANSISTION_FONT_HEIGHT * 12.3f, pageFont, DT_RIGHT, fontIds[PAGE_FONT]);
		
	}

	const float ACTION_COMPONENT_WORD_COLLISION_WIDTH = (float)(DISPLAY_WIDTH / 30);
	const float ACTION_COMPONENT_WORD_COLLISION_HEIGHT = ACTION_COMPONENT_WORD_COLLISION_WIDTH;

	//ïKéEãZÇÃê›íËÇµÇƒÇ¢ÇÈäOògÇÃí∏ì_ê›íË
	CustomImageVerticies(ActionFrame, (DISPLAY_WIDTH / 2.4f) + (ACTION_COMPONENT_WORD_COLLISION_WIDTH * 2), DISPLAY_HEIGHT - (ACTION_COMPONENT_WORD_COLLISION_HEIGHT * 2),
		ACTION_COMPONENT_WORD_COLLISION_WIDTH * 13, ACTION_COMPONENT_WORD_COLLISION_HEIGHT);

	DrawImage(ActionFrame, textureIds[WEAPON_MASTER_FRAME_TEX]);

	for (int inputWordData = 0;inputWordData < WEAPON_MASTER_ACTION_LISTS;++inputWordData)
	{
		if (pWeaponMasterActionDatas->m_componentWordIds[inputWordData] != SPACE_WORD)
		{
			DrawImage(pWeaponMasterAction[inputWordData].ImageVertex, pWmFontIds[(pWeaponMasterActionDatas->m_componentWordIds[inputWordData])]);
		}
	}
}
