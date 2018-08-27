#define _CRT_SECURE_NO_WARNINGS
#include"RenderWeaponMasterAction.h"

void RenderWeaponMasterAction(ImagesCustomVertex* pWeaponMasterDeckVerticies, ImagesCustomVertex* pWeaponMasterAction,
	WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionDatas, int pPage,TEXTUREID* pWmFontIds)
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
		SetFont((int)SET_FONT_SCALE, (UINT)SET_FONT_SCALE, "Files/Font/SoukouMincho-Font/SoukouMincho.ttf", &fontIds[PAGE_FONT], 10);
		SetFont((int)SET_FONT_SCALE, (UINT)SET_FONT_SCALE, "Files/Font/SoukouMincho-Font/SoukouMincho.ttf", &fontIds[PAGE_FONT_MAX], 10);

		isFirstFrame = 0;
	}

	CustomVertex pageTransition[RECT_VERTEX_NUM];
	CustomVertex listBG[4];
	CustomVertex ActionFrame[4];

	const float ACTION_COMPONENT_WORD_COLLISION_WIDTH = (float)(DISPLAY_WIDTH / 30);
	const float ACTION_COMPONENT_WORD_COLLISION_HEIGHT = ACTION_COMPONENT_WORD_COLLISION_WIDTH;

	CustomImageVerticies(ActionFrame, (DISPLAY_WIDTH / 2.4f) + (ACTION_COMPONENT_WORD_COLLISION_WIDTH * 2), DISPLAY_HEIGHT - (ACTION_COMPONENT_WORD_COLLISION_HEIGHT * 2),
		ACTION_COMPONENT_WORD_COLLISION_WIDTH*13, ACTION_COMPONENT_WORD_COLLISION_HEIGHT);

	CustomImageVerticies(listBG, DISPLAY_WIDTH - (DISPLAY_WIDTH / 7.f), DISPLAY_HEIGHT / 2.6f, DISPLAY_WIDTH / 9.f, DISPLAY_HEIGHT / 2.6f);

	DrawImage(ActionFrame, textureIds[WEAPON_MASTER_FRAME_TEX]);
	DrawImage(listBG, textureIds[LIST_BG_TEX]);

	for (int rectForPageTransition = 0;rectForPageTransition < 2;rectForPageTransition++)
	{
		switch (rectForPageTransition)
		{
		case 0:
			CustomImageVerticies(pageTransition, DISPLAY_WIDTH - (DISPLAY_WIDTH / 5.f), DISPLAY_HEIGHT / 1.4f, DISPLAY_WIDTH / 75.f, DISPLAY_WIDTH / 75.f);

			RotateImageDeg(pageTransition, pageTransition, 180.f);

			if (pPage != 1)
			{
				DrawImage(pageTransition, textureIds[WEAPON_MASTER_PAGE_CURSOL_TEX]);
			}

			break;

		case 1:
			CustomImageVerticies(pageTransition, DISPLAY_WIDTH - (DISPLAY_WIDTH / 15.f), DISPLAY_HEIGHT / 1.4f, DISPLAY_WIDTH / 75.f, DISPLAY_WIDTH / 75.f);
			
			if (pPage != 4)
			{
				DrawImage(pageTransition, textureIds[WEAPON_MASTER_PAGE_CURSOL_TEX]);
			}

			break;
		}
	}

	switch (pPage)
	{
	case 1:

		for (int wordLists = 0;wordLists < 10;wordLists++)
		{
			if (pWeaponMasterDeck->m_wordIds[wordLists] != SPACE_WORD)
			{
				DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, pWmFontIds[(pWeaponMasterDeck->m_wordIds[wordLists])]);
			}
		}

		break;

	case 2:

		for (int wordLists = 10;wordLists < 20;wordLists++)
		{
			if (pWeaponMasterDeck->m_wordIds[wordLists] != SPACE_WORD)
			{
				DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, pWmFontIds[(pWeaponMasterDeck->m_wordIds[wordLists])]);
			}
		}

		break;

	case 3:

		for (int wordLists = 20;wordLists < 30;wordLists++)
		{
			if (pWeaponMasterDeck->m_wordIds[wordLists] != SPACE_WORD)
			{
				DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, pWmFontIds[(pWeaponMasterDeck->m_wordIds[wordLists])]);
			}
		}

		break;

	case 4:

		for (int wordLists = 30;wordLists < 40;wordLists++)
		{
			if (pWeaponMasterDeck->m_wordIds[wordLists] != SPACE_WORD)
			{
				DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, pWmFontIds[(pWeaponMasterDeck->m_wordIds[wordLists])]);
			}
		}

		break;
	}

	const float PAGE_TRANSISTION_FONT_WIDTH = (float)(DISPLAY_WIDTH / 30);
	const float PAGE_TRANSISTION_FONT_HEIGHT = PAGE_TRANSISTION_FONT_WIDTH;
	char pageFont[] = "\0";

	sprintf(pageFont, "%d", pPage);

	WriteText(PAGE_TRANSISTION_FONT_WIDTH * 26.5f, PAGE_TRANSISTION_FONT_WIDTH * 12.f, "/4", DT_RIGHT, fontIds[PAGE_FONT_MAX]);
	WriteText(PAGE_TRANSISTION_FONT_WIDTH*25.5f, PAGE_TRANSISTION_FONT_HEIGHT * 12.f, pageFont, DT_RIGHT, fontIds[PAGE_FONT]);

	for (int inputWordData = 0;inputWordData < WEAPON_MASTER_ACTION_LISTS;++inputWordData)
	{
		if (pWeaponMasterActionDatas->m_componentWordIds[inputWordData] != SPACE_WORD)
		{
			DrawImage(pWeaponMasterAction[inputWordData].ImageVertex, pWmFontIds[(pWeaponMasterActionDatas->m_componentWordIds[inputWordData])]);
		}
	}
}
