#include"RenderWeaponMasterAction.h"

void RenderWeaponMasterAction(WeaponMasterWordData* pWeaponMasterWordData,WeaponMasterDeck* pWeaponMasterDeck, WeaponMasterActionData* pWeaponMasterActionWords,
	ImagesCustomVertex* pWeaponMasterDeckVerticies,int pPage)
{
	static TEXTUREID textureIds[WEAPON_MASTER_ACTION_TEX_MAX];

	static int isFirstFrame = INIT_FRAME;

	if (isFirstFrame == INIT_FRAME)
	{
		RoadTexture("Texture/MainGame/PageCursol.png", &textureIds[WEAPON_MASTER_PAGE_CURSOL_TEX]);
		RoadTexture("Texture/MainGame/Font.png", &textureIds[WEAPON_MASTER_FONT_TEX]);

		isFirstFrame = 0;
	}

	CustomVertex pageTransition[RECT_VERTEX_NUM];

	for (int rectForPageTransition = 0;rectForPageTransition < 2;rectForPageTransition++)
	{
		switch (rectForPageTransition)
		{
		case 0:
			CustomImageVerticies(pageTransition, 1050.f, 500.f, 25 / 2.f, 25 / 2.f);
			
			if (pPage != 1)
			{
				DrawImage(pageTransition, textureIds[WEAPON_MASTER_PAGE_CURSOL_TEX]);
			}

			break;

		case 1:
			CustomImageVerticies(pageTransition, 1150.f, 500.f, 25 / 2.f, 25 / 2.f);
			
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
			PageTransitionForWeaponMasterWordLists(pWeaponMasterDeckVerticies, wordLists);
			DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, textureIds[WEAPON_MASTER_FONT_TEX]);
		}

		break;

	case 2:

		for (int wordLists = 10;wordLists < 20;wordLists++)
		{
			PageTransitionForWeaponMasterWordLists(pWeaponMasterDeckVerticies, wordLists);
			DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, textureIds[WEAPON_MASTER_FONT_TEX]);
		}

		break;

	case 3:

		for (int wordLists = 20;wordLists < 30;wordLists++)
		{
			PageTransitionForWeaponMasterWordLists(pWeaponMasterDeckVerticies, wordLists);
			DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, textureIds[WEAPON_MASTER_FONT_TEX]);
		}

		break;

	case 4:

		for (int wordLists = 30;wordLists < 40;wordLists++)
		{
			PageTransitionForWeaponMasterWordLists(pWeaponMasterDeckVerticies, wordLists);
			DrawImage(pWeaponMasterDeckVerticies[wordLists].ImageVertex, textureIds[WEAPON_MASTER_FONT_TEX]);
		}

		break;
	}
}

void PageTransitionForWeaponMasterWordLists(ImagesCustomVertex* pWeaponMasterDeckVerticies, int wordLists)
{
	switch (wordLists)
	{
	case 0:
	case 10:
	case 20:
	case 30:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1050.f, 50.f, 50 / 2.f, 50 / 2.f);
		break;

	case 1:
	case 11:
	case 21:
	case 31:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1150.f, 50.f, 50 / 2.f, 50 / 2.f);
		break;

	case 2:
	case 12:
	case 22:
	case 32:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1050.f, 150.f, 50 / 2.f, 50 / 2.f);
		break;

	case 3:
	case 13:
	case 23:
	case 33:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1150.f, 150.f, 50 / 2.f, 50 / 2.f);
		break;

	case 4:
	case 14:
	case 24:
	case 34:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1050.f, 250.f, 50 / 2.f, 50 / 2.f);
		break;

	case 5:
	case 15:
	case 25:
	case 35:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1150.f, 250.f, 50 / 2.f, 50 / 2.f);
		break;

	case 6:
	case 16:
	case 26:
	case 36:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1050.f, 350.f, 50 / 2.f, 50 / 2.f);
		break;

	case 7:
	case 17:
	case 27:
	case 37:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1150.f, 350.f, 50 / 2.f, 50 / 2.f);
		break;

	case 8:
	case 18:
	case 28:
	case 38:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1050.f, 450.f, 50 / 2.f, 50 / 2.f);
		break;

	case 9:
	case 19:
	case 29:
	case 39:

		CustomImageVerticies(pWeaponMasterDeckVerticies[wordLists].ImageVertex, 1150.f, 450.f, 50 / 2.f, 50 / 2.f);
		break;

	}
}