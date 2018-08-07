#include"RenderWordListsAndTyping.h"
#include"ControlWordListsAndTyping.h"

void WordListsAndTypingRender()
{
	static TEXTUREID textureIds[TEXTURE_MAX];
	static FONTID fontIds[FONT_MAX];

	int g_playerType = WEAPON_MASTER;

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

void RenderMasicKnightWordLists(FONTID* fontIds, WordData* magicKnigtWords, WordList* magicKnightWordLists, MagicKnightAction* magicKnightAction, WordCandidate* wordCandidates)
{
	static bool isFirstFrame = true;
	int typingPosY = 0.f;
	int rubyPosY = 0.f;


	if (isFirstFrame)
	{
		SetFont(20.f, 40.f, "MS ゴシック", &fontIds[TYPING_FONT], 10.f, SHIFTJIS_CHARSET);
		SetFont(20.f, 40.f, "MS ゴシック", &fontIds[RUBY_FONT], 10.f, SHIFTJIS_CHARSET);

		isFirstFrame = false;
	}

	for (int cnt = 0;cnt < 5;cnt++)
	{
		typingPosY += 40;

		WriteText(DISPLAY_WIDTH/4.f, DISPLAY_HEIGHT/5+ typingPosY, &magicKnigtWords[magicKnightWordLists[cnt].m_Id].m_word[0],
			DT_CENTER, fontIds[TYPING_FONT],0xFF000000);
		
	}

	for (int cnt = 0;cnt < 5;cnt++)
	{
		rubyPosY += 40;

		&wordCandidates[cnt].m_ruby[0];
		WriteText(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 5+ rubyPosY, &magicKnightAction->m_inputWords[0].m_word[0],
			DT_CENTER, fontIds[RUBY_FONT], 0xFF000000);
	}

	return;

}
