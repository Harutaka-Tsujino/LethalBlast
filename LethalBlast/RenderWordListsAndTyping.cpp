#include"RenderWordListsAndTyping.h"

void WordListsAndTypingRender()
{
	static TEXTUREID textureIds[TEXTURE_MAX];

	//矩形のポリゴン生成
	CustomVertex WordListsImage[4];

	//リスト背景の描画位置の表示
	switch (g_playerType)
	{
	case MASIC_KNIGHT:	//マジックナイトの背景
		CustomImageVerticies(WordListsImage, 1080.f, 270.f, 250 / 2.f, 500 / 2.f, 0xFF000000);
		DrawImage(WordListsImage, textureIds[NULL]);
		break;

	case WEAPON_MASTER:	//ウェポンマスターの背景
		WeaponMasterBackGround(WordListsImage,textureIds);
		break;
	}
}

void WeaponMasterBackGround(CustomVertex* WordListsImage, TEXTUREID* textureIds)
{
	for (int i = 0;i < 8;i++)
	{
		switch (i)
		{
		case 0:
			CustomImageVerticies(WordListsImage, 1600.f, 200.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;

		case 1:
			CustomImageVerticies(WordListsImage, 1750.f, 200.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;

		case 2:

			CustomImageVerticies(WordListsImage, 1600.f, 400.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;

		case 3:
			CustomImageVerticies(WordListsImage, 1750.f, 400.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;

		case 4:
			CustomImageVerticies(WordListsImage, 1600.f, 600.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;

		case 5:
			CustomImageVerticies(WordListsImage, 1750.f, 600.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;

		case 6:
			CustomImageVerticies(WordListsImage, 1600.f, 800.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;

		case 7:
			CustomImageVerticies(WordListsImage, 1750.f, 800.f, 100 / 2.f, 100 / 2.f, 0xFF000000);
			DrawImage(WordListsImage, textureIds[NULL]);
			break;
		}
	}
}