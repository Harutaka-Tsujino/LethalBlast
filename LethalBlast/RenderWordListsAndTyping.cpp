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
	float typingPosY = 0.f;
	float rubyPosY = 0.f;

	if (isFirstFrame)
	{
		SetFont((int)20.f, (int)40.f, "MS ゴシック", &fontIds[TYPING_FONT], 0.f, SHIFTJIS_CHARSET);
		SetFont((int)20.f, (int)40.f, "MS ゴシック", &fontIds[RUBY_FONT], 0.f, SHIFTJIS_CHARSET);

		isFirstFrame = false;
	}

	for (int cnt = 0;cnt < 5;cnt++)
	{
		typingPosY += 40;
		WriteText(DISPLAY_WIDTH/4.f, DISPLAY_HEIGHT/5+ typingPosY, &magicKnigtWords[magicKnightWordLists[cnt].m_Id].m_word[0],
			DT_CENTER, fontIds[TYPING_FONT],0xFF000000);

		rubyPosY += 40;
		WriteText(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 5 + (int)rubyPosY, &wordCandidates[cnt].m_ruby[0],
			DT_CENTER, fontIds[RUBY_FONT], 0xFF000000);

		WriteText(DISPLAY_WIDTH - 200, DISPLAY_HEIGHT / 10 + (int)rubyPosY, &magicKnightAction->m_inputWords[cnt].m_word[0],
			DT_CENTER, fontIds[RUBY_FONT], 0xFF000000);
	}

	return;
}
