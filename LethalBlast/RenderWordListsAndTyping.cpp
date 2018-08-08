#include"RenderWordListsAndTyping.h"
#include"ControlWordListsAndTyping.h"

void WordListsAndTypingRender(int* playerType)
{
	static TEXTUREID textureIds[TEXTURE_MAX];
	static FONTID fontIds[FONT_MAX];

	//矩形のポリゴン生成
	CustomVertex WordListsImage[4];

	//リスト背景の描画位置の表示
	switch (*playerType)
	{
	case MAGIC_KNIGHT:	//マジックナイトの背景
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

void RenderMasicKnightWordLists(FONTID* fontIds, WordData* magicKnigtWords, WordList* magicKnightWordLists, MagicKnightAction* magicKnightAction, WordCandidate* wordCandidates)
{
	static bool isFirstFrame = true;
	static float typingPosY = 0.f, rubyPosY = 0.f;


	if (isFirstFrame)
	{
		SetFont(40, 20, "MS ゴシック", &fontIds[TYPING_FONT], 10);
		SetFont(30, 10, "MS ゴシック", &fontIds[RUBY_FONT], 10);

		isFirstFrame = false;
	}

	for (int cnt = 0;cnt < 5;cnt++)
	{
		typingPosY += 100.f;

		WriteText(1600,  (int)typingPosY, &magicKnigtWords[magicKnightWordLists[cnt].m_Id].m_word[0], DT_LEFT, fontIds[TYPING_FONT]);
		
	}

	for (int cnt = 0;cnt < 5;cnt++)
	{
		rubyPosY += 90.f;

		&wordCandidates[cnt].m_ruby[0];
		WriteText(1600, (int)rubyPosY, &magicKnightAction->m_inputWords[0].m_word[0], DT_LEFT, fontIds[RUBY_FONT]);
	}

}
