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

void RenderEffect(WordData* magicKnigtWords, WordList* magicKnightWordLists, MagicKnightAction* magicKnightAction, TEXTUREID* effectTexId,bool* endAttackEffect)
{
	for (int magicKnightActionNum = MAGIC_KNIGHT_ACTION_WORDS_MAX - 1; magicKnightActionNum >= 0; --magicKnightActionNum)
	{
		if (!magicKnightAction->m_componentWordIds[magicKnightActionNum])
		{
			continue;
		}

		static int effectCount = 0;

		const int EFFECT_RENDER_FRAME = 6;

		CustomVertex effectVertices[4];
		const float EFFECT_SCALE = 256.f;

		CustomImageVerticies(effectVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, EFFECT_SCALE, EFFECT_SCALE);

		switch (magicKnigtWords[magicKnightAction->m_componentWordIds[magicKnightActionNum]].m_element)
		{
		case FIRE_ELEMENT:
		{
			const int SEPARATED_FI_IMAGE_X = 32;
			const int SEPARATED_FI_IMAGE_Y = 4;

			CustomImageVerticies(effectVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, EFFECT_SCALE, EFFECT_SCALE, 0xBBFFFFFF,
				EFFECT_SCALE*((effectCount % (SEPARATED_FI_IMAGE_X*EFFECT_RENDER_FRAME)) / EFFECT_RENDER_FRAME),
				EFFECT_SCALE*(effectCount / (SEPARATED_FI_IMAGE_X * EFFECT_RENDER_FRAME)),
				EFFECT_SCALE, EFFECT_SCALE, SEPARATED_FI_IMAGE_X* EFFECT_SCALE, SEPARATED_FI_IMAGE_Y* EFFECT_SCALE);

			DrawImage(effectVertices, effectTexId[FLAME_EFF]);

			if (effectCount > ((SEPARATED_FI_IMAGE_X*(SEPARATED_FI_IMAGE_Y - 1)) + 4) *EFFECT_RENDER_FRAME)
			{
				effectCount = 0;
				*endAttackEffect = true;

				return;
			}

			effectCount++;
		}

		return;

		case WATER_ELEMENT:
		{
			const int SEPARATED_WA_IMAGE_X = 64;
			const int SEPARATED_WA_IMAGE_Y = 2;

			CustomImageVerticies(effectVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, EFFECT_SCALE, EFFECT_SCALE, 0xDDFFFFFF,
				EFFECT_SCALE*((effectCount % (SEPARATED_WA_IMAGE_X*EFFECT_RENDER_FRAME)) / EFFECT_RENDER_FRAME),
				EFFECT_SCALE*(effectCount / (SEPARATED_WA_IMAGE_X * EFFECT_RENDER_FRAME)),
				EFFECT_SCALE, EFFECT_SCALE, SEPARATED_WA_IMAGE_X* EFFECT_SCALE, SEPARATED_WA_IMAGE_Y* EFFECT_SCALE);

			DrawImage(effectVertices, effectTexId[NEEDLE_BOMB_EFF]);

			if (effectCount > ((SEPARATED_WA_IMAGE_X*(SEPARATED_WA_IMAGE_Y - 1)) + 13) *EFFECT_RENDER_FRAME)
			{
				effectCount = 0;
				*endAttackEffect = true;

				return;
			}

			effectCount++;
		}

		return;

		case WIND_ELEMENT:
		{
			const int SEPARATED_WI_IMAGE_X = 16;
			const int SEPARATED_WI_IMAGE_Y = 2;

			CustomImageVerticies(effectVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, EFFECT_SCALE, EFFECT_SCALE, 0xBBFFFFFF,
				EFFECT_SCALE*((effectCount % (SEPARATED_WI_IMAGE_X*EFFECT_RENDER_FRAME)) / EFFECT_RENDER_FRAME),
				EFFECT_SCALE*(effectCount / (SEPARATED_WI_IMAGE_X * EFFECT_RENDER_FRAME)),
				EFFECT_SCALE, EFFECT_SCALE, SEPARATED_WI_IMAGE_X* EFFECT_SCALE, SEPARATED_WI_IMAGE_Y* EFFECT_SCALE);

			DrawImage(effectVertices, effectTexId[WIND_EFF]);

			if (effectCount > ((SEPARATED_WI_IMAGE_X*(SEPARATED_WI_IMAGE_Y - 1)) + 9) *EFFECT_RENDER_FRAME)
			{
				effectCount = 0;
				*endAttackEffect = true;

				return;
			}

			effectCount++;
		}

		return;

		case SHINING_ELEMENT:
		{
			const int SEPARATED_SH_IMAGE_X = 30;
			const int SEPARATED_SH_IMAGE_Y = 1;

			CustomImageVerticies(effectVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, EFFECT_SCALE, EFFECT_SCALE, 0xBBFFFFFF,
				EFFECT_SCALE*((effectCount % (SEPARATED_SH_IMAGE_X*EFFECT_RENDER_FRAME)) / EFFECT_RENDER_FRAME),
				EFFECT_SCALE*(effectCount / (SEPARATED_SH_IMAGE_X * EFFECT_RENDER_FRAME)),
				EFFECT_SCALE, EFFECT_SCALE, SEPARATED_SH_IMAGE_X* EFFECT_SCALE, SEPARATED_SH_IMAGE_Y* EFFECT_SCALE);

			DrawImage(effectVertices, effectTexId[MULTI_SLASH_EFF]);

			if (effectCount > SEPARATED_SH_IMAGE_X*SEPARATED_SH_IMAGE_Y*EFFECT_RENDER_FRAME)
			{
				effectCount = 0;
				*endAttackEffect = true;

				return;
			}

			effectCount++;
		}

		return;

		case DARKNESS_ELEMENT:
		{
			const int SEPARATED_DA_IMAGE_X = 64;
			const int SEPARATED_DA_IMAGE_Y = 2;

			CustomImageVerticies(effectVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, EFFECT_SCALE, EFFECT_SCALE, 0xBBFFFFFF,
				EFFECT_SCALE*((effectCount % (SEPARATED_DA_IMAGE_X*EFFECT_RENDER_FRAME)) / EFFECT_RENDER_FRAME),
				EFFECT_SCALE*(effectCount / (SEPARATED_DA_IMAGE_X * EFFECT_RENDER_FRAME)),
				EFFECT_SCALE, EFFECT_SCALE, SEPARATED_DA_IMAGE_X* EFFECT_SCALE, SEPARATED_DA_IMAGE_Y* EFFECT_SCALE);

			DrawImage(effectVertices, effectTexId[SHADOW_BALL_EFF]);

			if (effectCount > ((SEPARATED_DA_IMAGE_X*(SEPARATED_DA_IMAGE_Y - 1)) + 36) *EFFECT_RENDER_FRAME)
			{
				effectCount = 0;
				*endAttackEffect = true;

				return;
			}

			effectCount++;
		}

		return;

		case VOID_ELEMENT:

			*endAttackEffect = true;

			return;
		}

		return;
	}

	return;
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

void RenderMasicKnightWordLists(FONTID* fontIds, WordData* magicKnigtWords, WordList* magicKnightWordLists, MagicKnightAction* magicKnightAction, WordCandidate* wordCandidates,int* wordNum,bool* endAttackEffect)
{
	static bool isFirstFrame = true;
	float typingPosY = 0.f;
	float rubyPosY = 0.f;

	static TEXTUREID attackEffectIds[EFF_MAX];
	static TEXTUREID enemyTexIds;

	if (isFirstFrame)
	{
		RoadTexture("Texture/Effect/DarkFlame.png", &attackEffectIds[DARK_FLAME_EFF]);
		RoadTexture("Texture/Effect/Flame.png", &attackEffectIds[FLAME_EFF]);
		RoadTexture("Texture/Effect/MultiSlash.png", &attackEffectIds[MULTI_SLASH_EFF]);
		RoadTexture("Texture/Effect/NeedleBomb.png", &attackEffectIds[NEEDLE_BOMB_EFF]);
		RoadTexture("Texture/Effect/ShadowBall2.png", &attackEffectIds[SHADOW_BALL_EFF]);
		RoadTexture("Texture/Effect/Thrown.png", &attackEffectIds[THROWN_EFF]);
		RoadTexture("Texture/Effect/Wind.png", &attackEffectIds[WIND_EFF]);

		RoadTexture("texture/MainGame/Enemy/Gazer.png", &enemyTexIds);

		SetFont((int)20.f, (int)40.f, "MS ゴシック", &fontIds[TYPING_FONT], 0, SHIFTJIS_CHARSET);
		SetFont((int)10.f, (int)20.f, "MS ゴシック", &fontIds[RUBY_FONT], 0, SHIFTJIS_CHARSET);

		isFirstFrame = false;
	}

	CustomVertex EnemyImage[4];
	const float ENEMY_SCALE = 300.f;
	CustomImageVerticies(EnemyImage, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, ENEMY_SCALE, ENEMY_SCALE);

	DrawImage(EnemyImage, enemyTexIds);

	for (int cnt = 0;cnt < 5;cnt++)
	{
		typingPosY += 25;
		WriteText(DISPLAY_WIDTH-140, (int)(DISPLAY_HEIGHT/15+ typingPosY), &magicKnigtWords[magicKnightWordLists[cnt].m_Id].m_word[0],
			DT_LEFT, fontIds[RUBY_FONT],0xFFf5f5f5);

		rubyPosY += 40;
		WriteText((int)(DISPLAY_WIDTH / 1.4), (int)(DISPLAY_HEIGHT / 2.3 + rubyPosY), &wordCandidates[cnt].m_ruby[0],
			DT_CENTER, fontIds[TYPING_FONT], 0xFFffffe0);
	}

	for (int wordNumber = 0; wordNumber < MAGIC_KNIGHT_ACTION_WORDS_MAX; ++wordNumber)
	{
		if (wordNumber == (*wordNum))
		{
			WriteText((int)(DISPLAY_WIDTH / 1.4), DISPLAY_HEIGHT - 100, &magicKnightAction->m_inputWords[*wordNum].m_word[0],
				DT_CENTER, fontIds[TYPING_FONT], 0xFFffd700);

			continue;
		}

		WriteText((int)(DISPLAY_WIDTH / 2)+ 150*wordNumber, DISPLAY_HEIGHT - 150, &magicKnightAction->m_inputWords[wordNumber].m_word[0],
			DT_CENTER, fontIds[RUBY_FONT], 0xFFf08080);
	}

	RenderEffect(magicKnigtWords, magicKnightWordLists, magicKnightAction, attackEffectIds, endAttackEffect);

	return;
}
