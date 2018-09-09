#define _CRT_SECURE_NO_WARNINGS
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlStageSelect.h"
#include"OperateBattle.h"
#include"ControlGame.h"

void OperateBattle(SCENE* scene, int playerChara, int selectedStage, int selectedDeck, Deck* pMKDeck, Deck* pWMDeck,
	WordData* pMKWordDatas, TEXTUREID* pMKWordTex, WordData* pWMWordDatas, TEXTUREID* pWMWordTex,
	EnemyData* pEnemyDatas, CustomVertex* pMouseCursorVertices)
{
	static bool initUnionTex = true;

	static TEXTUREID unionTex[MAIN_UNION_TEX_MAX];

	static TEXTUREID enemyTex[ENEMY_MAX];

	static ActionEffectData actionEffectDatas[ACTION_EFFECT_MAX];

	static FONTID unionFont[MAIN_UNION_FONT_MAX];

	static CustomVertex back[RECT_VERTEX_NUM];

	static CustomVertex resultMask[RECT_VERTEX_NUM];

	if (initUnionTex)
	{
		RoadTexture("Texture/MainGame/Forest.png", &unionTex[森_BACK]);
		RoadTexture("Texture/MainGame/mainBG.png", &unionTex[遺跡_BACK]);
		RoadTexture("Texture/MainGame/CrystalCave.png", &unionTex[洞窟_BACK]);
		RoadTexture("Texture/MainGame/HP/HP.png", &unionTex[HP_BAR]);
		RoadTexture("Texture/MainGame/HP/HPFrame.png",&unionTex[HP_COVER]);
		RoadTexture("Texture/MainGame/HP/CTCount.png", &unionTex[PP_BAR]); 
		RoadTexture("Texture/MainGame/HP/CT.png", &unionTex[WORD_SELECT_EFFECT]);
		RoadTexture("Texture/MainGame/WordBlackBack.png", &unionTex[WORD_BLACK_BACK]);
		RoadTexture("Texture/MainGame/Enemy/Robot.png", &enemyTex[エーレ・ツヴァイ]);
		RoadTexture("Texture/MainGame/Enemy/dragon_karie.png", &enemyTex[ヴィーヴル]);
		RoadTexture("Texture/MainGame/Enemy/EDoubleCaster.png", &enemyTex[影の少女たち]);
		RoadTexture("Texture/MainGame/Enemy/cerberus.png", &enemyTex[ケルベロス]);
		RoadTexture("Texture/MainGame/Enemy/Gazer.png", &enemyTex[ゲイザー]);
		RoadTexture("Texture/MainGame/Enemy/LBウエポンマスターmob2.png",&enemyTex[エンデュミオン]);
		RoadTexture("Texture/MainGame/Enemy/LBウエポンマスターmob1.png",&enemyTex[エクスキューショナー]);
		RoadTexture("Texture/MainGame/Enemy/turtle.png",&enemyTex[シルトクレスタル]);
		
		actionEffectDatas[FLASH_RAZER].m_segmentX = 16;
		actionEffectDatas[FLASH_RAZER].m_segmentY = 10;
		actionEffectDatas[FLASH_RAZER].m_effectScale = DISPLAY_WIDTH * 0.5f;
		int a=RoadTexture("Texture/Effect/FL2AE.png", &(actionEffectDatas[FLASH_RAZER].m_tex));
		actionEffectDatas[FLASH_RAZER].m_color = 0xff4169e1;

		actionEffectDatas[FULL_BURST].m_segmentX = 10;
		actionEffectDatas[FULL_BURST].m_segmentY = 8;
		actionEffectDatas[FULL_BURST].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/FBAE.png", &(actionEffectDatas[FULL_BURST].m_tex));
		actionEffectDatas[FULL_BURST].m_color = 0xffffffff;

		actionEffectDatas[DIVINE_SWORD].m_segmentX = 10;
		actionEffectDatas[DIVINE_SWORD].m_segmentY = 2;
		actionEffectDatas[DIVINE_SWORD].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/DBSAE.png", &(actionEffectDatas[DIVINE_SWORD].m_tex));
		actionEffectDatas[DIVINE_SWORD].m_color = 0xffffff00;

		actionEffectDatas[TARGET].m_segmentX = 10;
		actionEffectDatas[TARGET].m_segmentY = 6;
		actionEffectDatas[TARGET].m_effectScale = DISPLAY_WIDTH * 0.25f;
		a = RoadTexture("Texture/Effect/TGAE.png", &(actionEffectDatas[TARGET].m_tex));
		actionEffectDatas[TARGET].m_color = 0xff808080;

		actionEffectDatas[ASTRAL_RAZER].m_segmentX = 10;
		actionEffectDatas[ASTRAL_RAZER].m_segmentY = 10;
		actionEffectDatas[ASTRAL_RAZER].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/RazerAE.png", &(actionEffectDatas[ASTRAL_RAZER].m_tex));
		actionEffectDatas[ASTRAL_RAZER].m_color = 0xff00ffff;

		actionEffectDatas[SMASH_AE].m_segmentX = 16;
		actionEffectDatas[SMASH_AE].m_segmentY = 2;
		actionEffectDatas[SMASH_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/SmashAE.png", &(actionEffectDatas[SMASH_AE].m_tex));
		actionEffectDatas[SMASH_AE].m_color = 0xff00ffff;

		actionEffectDatas[SLASH_AE].m_segmentX = 8;
		actionEffectDatas[SLASH_AE].m_segmentY = 2;
		actionEffectDatas[SLASH_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/SlashAE.png", &(actionEffectDatas[SLASH_AE].m_tex));
		actionEffectDatas[SLASH_AE].m_color = 0xff00ffff;

		actionEffectDatas[PENE_AE].m_segmentX = 16;
		actionEffectDatas[PENE_AE].m_segmentY = 2;
		actionEffectDatas[PENE_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/PenetrateAE.png", &(actionEffectDatas[PENE_AE].m_tex));
		actionEffectDatas[PENE_AE].m_color = 0xff00ffff;

		actionEffectDatas[TWIN_CYCLON_AE].m_segmentX = 10;
		actionEffectDatas[TWIN_CYCLON_AE].m_segmentY = 6;
		actionEffectDatas[TWIN_CYCLON_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/TwinCyclon.png", &(actionEffectDatas[TWIN_CYCLON_AE].m_tex));
		actionEffectDatas[TWIN_CYCLON_AE].m_color = 0xffffffff;

		actionEffectDatas[TILANT_WING_AE].m_segmentX = 16;
		actionEffectDatas[TILANT_WING_AE].m_segmentY = 2;
		actionEffectDatas[TILANT_WING_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/wind.png", &(actionEffectDatas[TILANT_WING_AE].m_tex));
		actionEffectDatas[TILANT_WING_AE].m_color = 0xff00ffff;

		actionEffectDatas[DARK_FRAME_AE].m_segmentX = 32;
		actionEffectDatas[DARK_FRAME_AE].m_segmentY = 4;
		actionEffectDatas[DARK_FRAME_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/DarkFlame.png", &(actionEffectDatas[DARK_FRAME_AE].m_tex));
		actionEffectDatas[DARK_FRAME_AE].m_color = 0xffffffff;

		actionEffectDatas[CHARGE_FORCE_AE].m_segmentX = 10;
		actionEffectDatas[CHARGE_FORCE_AE].m_segmentY = 2;
		actionEffectDatas[CHARGE_FORCE_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/Charge.png", &(actionEffectDatas[CHARGE_FORCE_AE].m_tex));
		actionEffectDatas[CHARGE_FORCE_AE].m_color = 0xffffff00;

		actionEffectDatas[CRYSTAL_RAZER_AE].m_segmentX = 30;
		actionEffectDatas[CRYSTAL_RAZER_AE].m_segmentY = 1;
		actionEffectDatas[CRYSTAL_RAZER_AE].m_effectScale = DISPLAY_WIDTH * 0.5f;
		a = RoadTexture("Texture/Effect/MultiSlash.png", &(actionEffectDatas[CRYSTAL_RAZER_AE].m_tex));
		actionEffectDatas[CRYSTAL_RAZER_AE].m_color = 0xff00ffff;

		actionEffectDatas[NONE_AE].m_segmentX = 10;
		actionEffectDatas[NONE_AE].m_segmentY = 4;
		actionEffectDatas[NONE_AE].m_effectScale = DISPLAY_WIDTH * 0.2f;
		a = RoadTexture("Texture/Effect/NAAE.png", &(actionEffectDatas[NONE_AE].m_tex));
		actionEffectDatas[NONE_AE].m_color = 0xffffffff;
		
		SetFont(DISPLAY_WIDTH / 70, DISPLAY_WIDTH / 48, "HGP明朝B", &unionFont[ENEMY_NAME_FONT], 5);
		SetFont(DISPLAY_WIDTH / 35, DISPLAY_WIDTH / 24, "HGP明朝B", &unionFont[ENEMY_ACTION_FONT], 25);

		CustomImageVerticies(back, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f,
			DISPLAY_WIDTH *0.5f, DISPLAY_HEIGHT * 0.5f);

		ZeroMemory(resultMask, sizeof(CustomVertex)*RECT_VERTEX_NUM);

		/*for (int deckWord = 0; (pMKDeck[selectedDeck].m_wordId[deckWord] = 
			pWMDeck[selectedDeck].m_wordId[deckWord] = deckWord) < DECK_WORD_MAX; ++deckWord);*/

		initUnionTex = false;
	}

	static BattleData battleData;

	static StageData stageDatas[STAGE_MAX];
	
	static int floor = 0;

	ImagesCustomVertex handVertices[HAND_MAX];

	const int SCROLL_SPEED = 4;
	const int START_ANIMATION_FRAME = 120;
	
	CustomVertex enemyHPVertices[RECT_VERTEX_NUM];
	CustomVertex playerHPVertices[RECT_VERTEX_NUM];

	CustomVertex enemyVertices[RECT_VERTEX_NUM];

	CustomVertex charaCutInVertices[RECT_VERTEX_NUM];

	switch (playerChara)
	{
	case MAGIC_KNIGHT:
	{
		static TEXTUREID mKWordTex[MK_MAIN_TEX_MAX];
		static int frameCount = INIT_FRAME;

		const int ACTION_WORD_MAX = MK_ACTION_WORD_MAX;

		const int WORD_SELECT_EFFECT_MAX = 2 * ACTION_WORD_MAX;
		WordSelectEffect wordSelectEffect[WORD_SELECT_EFFECT_MAX];

		if (frameCount == INIT_FRAME)
		{
			InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, MK_MAX_PP,
				selectedDeck, pMKDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);

			RoadTexture("Texture/CharaChoice/MagicKnight.png", &mKWordTex[MK_CHARA]);
			RoadTexture("Texture/MainGame/MKActionWordFrame.png", &mKWordTex[MK_ACTION_SEAT]);
			RoadTexture("Texture/MainGame/WordUnderBoard.png", &mKWordTex[MK_WORD_SEAT]);
			RoadTexture("Texture/MainGame/MKCutIn.png", &mKWordTex[MK_CUT_IN]);

			frameCount = 0;
		}

		if (!frameCount)
		{
			InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, MK_MAX_PP,
				selectedDeck, pMKDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);
		}

		const float HAND_WIDTH = DISPLAY_WIDTH * 0.1f;
		const float HAND_HEIGHT = HAND_WIDTH * 0.2f;

		SetHandVertices(frameCount, START_ANIMATION_FRAME, handVertices,
			DISPLAY_WIDTH *0.89f, DISPLAY_HEIGHT*0.5f,
			HAND_WIDTH, HAND_HEIGHT, DISPLAY_WIDTH * 1.3f, SCROLL_SPEED, &battleData);

		const float ACTION_WORD_WIDTH = DISPLAY_WIDTH * 0.08f;
		const float ACTION_WORD_HEIGHT = ACTION_WORD_WIDTH * 0.25f;
		const float ACTION_WORD_POS_X = DISPLAY_WIDTH * 0.095f;
		const float ACTION_WORD_POS_Y = DISPLAY_HEIGHT * 0.92f/* 0.975f*/;
		ImagesCustomVertex actionWordVertices[ACTION_WORD_MAX];

		SetActionWordVertices(actionWordVertices, ACTION_WORD_MAX, ACTION_WORD_POS_X, ACTION_WORD_POS_Y,
			ACTION_WORD_WIDTH, ACTION_WORD_HEIGHT);

		IOAction(frameCount, START_ANIMATION_FRAME, pMouseCursorVertices,
			handVertices, HAND_WIDTH, HAND_HEIGHT,
			actionWordVertices, ACTION_WORD_WIDTH, ACTION_WORD_HEIGHT,
			pMKWordDatas, wordSelectEffect, WORD_SELECT_EFFECT_MAX, &battleData, ACTION_WORD_MAX);

		if ((g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK]) && !battleData.m_useAction)
		{
			battleData.m_useAction = true;
			CalcActionDamage(&battleData, ACTION_WORD_MAX, pMKWordDatas, actionEffectDatas);
			battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_damage;
			InitHand(&battleData, pMKDeck, selectedDeck);
		}

		const int WORD_SELECT_EFFECT_FRAME = 15;

		MoveSelectWordEffect(wordSelectEffect, WORD_SELECT_EFFECT_MAX, WORD_SELECT_EFFECT_FRAME);

		DrawImage(back, unionTex[selectedStage]);

		static int battleFrameCount = 0;

		const int ACTION_EFFECT_BLANK = 3;

		const int ACTION_WORD_STAGE_FRAME = 90;

		int playerActionEffectFrame = actionEffectDatas[battleData.m_playerEffectId].m_segmentX*
			actionEffectDatas[battleData.m_playerEffectId].m_segmentY*ACTION_EFFECT_BLANK;

		const int REDUCE_ENEMY_HP_FRAME = 60;

		const int ENEMY_ACTION_NAME_STAGE_FRAME = 90;

		int enemyEffectId = battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_effectId;
		int enemyActionEffectFrame = actionEffectDatas[enemyEffectId].m_segmentX*
			actionEffectDatas[enemyEffectId].m_segmentY*ACTION_EFFECT_BLANK;

		const int REDUCE_PLAYER_HP_FRAME = 60;

		const float ENEMY_SCALE = DISPLAY_WIDTH * 0.15f;

		CustomImageVerticies(enemyVertices, DISPLAY_WIDTH *0.5f, DISPLAY_HEIGHT * 0.5f,
			ENEMY_SCALE, ENEMY_SCALE, GetColor(255, 255, 255, 255));

		switch (battleData.m_result)
		{
		case WIN:
		{
			const int ENEMY_DELETE_FRAME = 120;

			static int enemyDeleteFrameCount = 0;

			GetCustomVerTexColor(enemyVertices,
				GetColor((UCHAR)(255 * (1.f - enemyDeleteFrameCount / (float)ENEMY_DELETE_FRAME)), 255, 255, 255));

			if (enemyDeleteFrameCount < ENEMY_DELETE_FRAME)
			{
				++enemyDeleteFrameCount;
			}

			if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK])
			{
				*scene = HOME_SCENE;
				InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, MK_MAX_PP,
					selectedDeck, pMKDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);
				frameCount = 0;
				enemyDeleteFrameCount = 0;
				battleFrameCount = 0;

				return;
			}
		}

		break;

		case LOSE:
		{
			const int BLACK_OUT_FRAME = 120;

			static int blackOutFrameCount = 0;

			CustomImageVerticies(resultMask, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f,
				DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f,
				GetColor((UCHAR)(255 * (blackOutFrameCount / (float)BLACK_OUT_FRAME)), 0, 0, 0));

			if (blackOutFrameCount < BLACK_OUT_FRAME)
			{
				++blackOutFrameCount;
			}

			if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK])
			{
				*scene = HOME_SCENE;
				InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, MK_MAX_PP,
					selectedDeck, pMKDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);
				DrawImage(resultMask, NULL);
				ZeroMemory(resultMask, sizeof(CustomVertex)*RECT_VERTEX_NUM);
				frameCount = 0;
				blackOutFrameCount = 0;
				battleFrameCount = 0;

				return;
			}
		}

		break;
		}

		DrawImage(enemyVertices, enemyTex[stageDatas[selectedStage].m_enemy[floor]]);

		if (battleData.m_useAction && !battleData.m_result)
		{
			if (battleFrameCount < ACTION_WORD_STAGE_FRAME)
			{
				if (battleData.m_enemyData.m_currentHP <= battleData.m_playerActionDamage)
				{
					if (battleFrameCount < ACTION_WORD_STAGE_FRAME / 2)
					{
						CustomImageVerticies(charaCutInVertices, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.28f,
							DISPLAY_WIDTH*0.5f*(battleFrameCount / (float)(ACTION_WORD_STAGE_FRAME/2)), DISPLAY_HEIGHT*0.15f,
							GetColor(255, 255, 255, 255),
							(0.5f*(1.f - battleFrameCount / (float)(ACTION_WORD_STAGE_FRAME/2))), 0.f,
							DISPLAY_WIDTH*(battleFrameCount / (float)(ACTION_WORD_STAGE_FRAME/2)),
							1.f, (float)DISPLAY_WIDTH, 1.f);
					}

					else
					{
						CustomImageVerticies(charaCutInVertices, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.28f,
							DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.15f);
					}

					DrawImage(charaCutInVertices, mKWordTex[MK_CUT_IN]);
				}

				if (battleFrameCount + 1 == ACTION_WORD_STAGE_FRAME)
				{
					ZeroMemory(battleData.m_playerAction, sizeof(int)*ACTION_WORD_MAX);
				}

				StageActionWord(battleFrameCount, ACTION_WORD_STAGE_FRAME, actionWordVertices, ACTION_WORD_MAX,&battleData, &unionTex[WORD_BLACK_BACK]);
			}

			if (ACTION_WORD_STAGE_FRAME <= battleFrameCount && battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame)
			{
				RenderActionEffect(battleFrameCount - ACTION_WORD_STAGE_FRAME, ACTION_EFFECT_BLANK,
					DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f, actionEffectDatas[battleData.m_playerEffectId].m_effectScale,
					&actionEffectDatas[battleData.m_playerEffectId], GetColor(200, 255, 20, 20));
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME)
			{
				ReduceEnemyHPGradually(REDUCE_ENEMY_HP_FRAME, &battleData);

				HealPlayerHPGradually(REDUCE_ENEMY_HP_FRAME, &battleData);

				char playerActionDamageBuf[20];
				_itoa(battleData.m_playerActionDamage, playerActionDamageBuf, 10);

				WriteText((int)(DISPLAY_WIDTH*0.5f), (int)(DISPLAY_HEIGHT*0.75f),
					playerActionDamageBuf, DT_CENTER, unionFont[ENEMY_ACTION_FONT],
					GetColor(255, 180, 180, 180));

				char playerHealHPBuf[20];
				_itoa(battleData.m_playerHPTmp, playerHealHPBuf, 10);

				if (battleData.m_playerHPTmp)
				{
					WriteText((int)(DISPLAY_WIDTH*0.25f), (int)(DISPLAY_HEIGHT*0.75f),
						playerHealHPBuf, DT_CENTER, unionFont[ENEMY_NAME_FONT],
						GetColor(255, 127, 255, 0));
				}
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame
				+ REDUCE_ENEMY_HP_FRAME + ENEMY_ACTION_NAME_STAGE_FRAME)
			{
				WriteText((int)(DISPLAY_WIDTH*0.5f), (int)(DISPLAY_HEIGHT*0.2f),
					battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_name,
					DT_CENTER, unionFont[ENEMY_ACTION_FONT],
					GetColor(255, 255, 30, 30));
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame +
				REDUCE_ENEMY_HP_FRAME + ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame)
			{
				RenderActionEffect(battleFrameCount -
					(ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
						+ ENEMY_ACTION_NAME_STAGE_FRAME), ACTION_EFFECT_BLANK,
					DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f, actionEffectDatas[enemyEffectId].m_effectScale,
					&actionEffectDatas[enemyEffectId], GetColor(200, 255, 20, 20));
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame + REDUCE_PLAYER_HP_FRAME)
			{
				ReducePlayerHPGradually(REDUCE_PLAYER_HP_FRAME, &battleData);

				char enemyActionDamageBuf[20];
				_itoa(battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_damage,
					enemyActionDamageBuf, 10);

				WriteText((int)(DISPLAY_WIDTH*0.25f), (int)(DISPLAY_HEIGHT*0.75f),
					enemyActionDamageBuf, DT_CENTER, unionFont[ENEMY_NAME_FONT],
					GetColor(255, 180, 180, 180));
			}

			++battleFrameCount;

			if (battleFrameCount >= ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame + REDUCE_PLAYER_HP_FRAME)
			{
				PrepareNextTurn(&battleFrameCount, &battleData, ACTION_WORD_MAX);
			}
		}

		if (battleFrameCount - 1 <= ACTION_WORD_STAGE_FRAME)
		{
			if (!battleFrameCount)
			{
				for (int hand = 0; hand < HAND_MAX; ++hand)
				{
					DrawImage(handVertices[hand].ImageVertex, mKWordTex[MK_WORD_SEAT]);
					DrawImage(handVertices[hand].ImageVertex, pMKWordTex[battleData.m_hand[hand]]);
				}
			}

			RenderActionSeat(frameCount, START_ANIMATION_FRAME, &mKWordTex[MK_ACTION_SEAT]);

			RenderActionWord(ACTION_WORD_MAX, WORD_SELECT_EFFECT_MAX, wordSelectEffect,
				&battleData, actionWordVertices, pMKWordTex,unionTex,playerChara);

			DrawWordSelectEffect(wordSelectEffect, WORD_SELECT_EFFECT_MAX, &unionTex[WORD_SELECT_EFFECT]);

			for (int hand = 0; hand < HAND_MAX; ++hand)
			{
				int handWord = battleData.m_hand[hand];
				
				if (RectToRectCollisionCheak(handVertices[hand].ImageVertex, pMouseCursorVertices)&&handWord)
				{
					char maxCostBuf[5];

					_itoa(pMKWordDatas[handWord].m_costMax, maxCostBuf, 10);

					const int TEXT_POS_X = (int)(DISPLAY_WIDTH * 0.7f);
					const int TEXT_POS_Y = (int)(DISPLAY_HEIGHT * 0.49f);
					const int TEXT_Y_BLANK = (int)(DISPLAY_HEIGHT*0.05f);
					WriteText(TEXT_POS_X, TEXT_POS_Y, maxCostBuf, DT_CENTER, unionFont[ENEMY_NAME_FONT],0xFF000000);

					char elementBuf[ELEMENT_ATTRIBUTES_MAX][10]=
					{
						{"火"},{"水"},{"風"},{"光"},{"闇"},{""}
					};

					WriteText(TEXT_POS_X, TEXT_POS_Y+ TEXT_Y_BLANK, &elementBuf[pMKWordDatas[handWord].m_element][0],
						DT_CENTER, unionFont[ENEMY_NAME_FONT], 0xFF000000);

					char attackBuf[ATTACK_ATTRIBUTES_MAX][10] =
					{
						{"斬"},{"打"},{"突"},{""},
					};

					WriteText(TEXT_POS_X, TEXT_POS_Y + 2*TEXT_Y_BLANK, &attackBuf[pMKWordDatas[handWord].m_attack][0],
						DT_CENTER, unionFont[ENEMY_NAME_FONT], 0xFF000000);
				}
			}
		}

		WriteText((int)(DISPLAY_WIDTH*0.35), (int)(DISPLAY_HEIGHT*0.03),
			battleData.m_enemyData.m_name, DT_CENTER, unionFont[ENEMY_NAME_FONT], GetColor(255, 255, 30, 30));

		CustomImageVerticies(enemyHPVertices, DISPLAY_WIDTH *0.5f, DISPLAY_HEIGHT*0.1f,
			DISPLAY_WIDTH*0.3f, DISPLAY_HEIGHT*0.03f, 0xFFFFFFFF,
			0.5f*(1.f - battleData.m_enemyData.m_currentHP / (float)(battleData.m_enemyData.m_maxHP)),
			0.f, 0.5f, 1.f, 1.f, 1.f);

		DrawImage(enemyHPVertices, unionTex[HP_BAR]);

		CustomImageVerticies(enemyHPVertices, DISPLAY_WIDTH *0.5f, DISPLAY_HEIGHT*0.1f,
			DISPLAY_WIDTH*0.3f, DISPLAY_HEIGHT*0.03f, 0xFFFFFFFF);

		DrawImage(enemyHPVertices, unionTex[HP_COVER]);

		CustomImageVerticies(playerHPVertices, DISPLAY_WIDTH *0.12f, DISPLAY_HEIGHT*0.82f,
			DISPLAY_WIDTH*0.1f, DISPLAY_HEIGHT*0.01f, 0xFFFFFFFF,
			0.5f*(1.f - battleData.m_playerHPCurrent / (float)(battleData.m_playerHPMax)),
			0.f, 0.5f, 1.f, 1.f, 1.f);

		DrawImage(playerHPVertices, unionTex[HP_BAR]);

		CustomImageVerticies(playerHPVertices, DISPLAY_WIDTH *0.12f, DISPLAY_HEIGHT*0.82f,
			DISPLAY_WIDTH*0.1f, DISPLAY_HEIGHT*0.01f, 0xFFFFFFFF);

		DrawImage(playerHPVertices, unionTex[HP_COVER]);

		char pPBuf[10];
		sprintf(pPBuf, "%d/%d", battleData.m_pPCurrent, battleData.m_pPMax);

		WriteText((int)(DISPLAY_WIDTH *0.26f), (int)(DISPLAY_HEIGHT*0.8187f), pPBuf, DT_CENTER,
			unionFont[ENEMY_NAME_FONT], GetColor(255, 0, 50, 255));

		DrawImage(resultMask, NULL);

		if (frameCount < START_ANIMATION_FRAME)
		{
			++frameCount;
		}
	}

	break;

	case WEAPON_MASTER://////////////////////////////////////////////////////////////////////////////////////////////////////ウェポンマスター/////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		static TEXTUREID wMWordTex[WM_MAIN_TEX_MAX];
		static int frameCount = INIT_FRAME;

		const int ACTION_WORD_MAX = WM_ACTION_WORD_MAX;

		const int WORD_SELECT_EFFECT_MAX = 2 * ACTION_WORD_MAX;
		WordSelectEffect wordSelectEffect[WORD_SELECT_EFFECT_MAX];

		if (frameCount == INIT_FRAME)
		{
			InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, WM_MAX_PP,
				selectedDeck, pWMDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);

			RoadTexture("Texture/CharaChoice/WeaponMaster.png", &wMWordTex[WM_CHARA]);
			RoadTexture("Texture/MainGame/frame.png", &wMWordTex[WM_ACTION_SEAT]);
			RoadTexture("Texture/MainGame/ListBG.png", &wMWordTex[WM_WORD_SEAT]);
			RoadTexture("Texture/MainGame/WMCutIn.png", &wMWordTex[WM_CUT_IN]);
			RoadTexture("Texture/MainGame/WMUnderAction.png", &wMWordTex[WM_UNDER_ACTION]);

			frameCount = 0;
		}

		if (!frameCount)
		{
			InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, WM_MAX_PP,
				selectedDeck, pWMDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);
		}

		const float HAND_WIDTH = DISPLAY_WIDTH * 0.033f;
		const float HAND_HEIGHT = HAND_WIDTH;

		SetHandVertices(frameCount, START_ANIMATION_FRAME, handVertices,
			DISPLAY_WIDTH *0.89f, DISPLAY_HEIGHT*0.5f,
			HAND_WIDTH, HAND_HEIGHT, DISPLAY_WIDTH * 1.4f, SCROLL_SPEED, &battleData);

		const float ACTION_WORD_WIDTH = DISPLAY_WIDTH * 0.033f;
		const float ACTION_WORD_HEIGHT = ACTION_WORD_WIDTH;
		const float ACTION_WORD_POS_X = DISPLAY_WIDTH * 0.12f;
		const float ACTION_WORD_POS_Y = DISPLAY_HEIGHT * 0.92f/* 0.975f*/;
		ImagesCustomVertex actionWordVertices[ACTION_WORD_MAX];

		SetActionWordVertices(actionWordVertices, ACTION_WORD_MAX, ACTION_WORD_POS_X, ACTION_WORD_POS_Y,
			ACTION_WORD_WIDTH, ACTION_WORD_HEIGHT);

		IOAction(frameCount, START_ANIMATION_FRAME, pMouseCursorVertices,
			handVertices, HAND_WIDTH, HAND_HEIGHT,
			actionWordVertices, ACTION_WORD_WIDTH, ACTION_WORD_HEIGHT,
			pWMWordDatas, wordSelectEffect, WORD_SELECT_EFFECT_MAX, &battleData, ACTION_WORD_MAX);

		if ((g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK]) && !battleData.m_useAction)
		{
			battleData.m_useAction = true;
			CalcActionDamage(&battleData, ACTION_WORD_MAX, pWMWordDatas, actionEffectDatas);
			battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_damage;
			InitHand(&battleData, pWMDeck, selectedDeck);
		}

		const int WORD_SELECT_EFFECT_FRAME = 15;

		MoveSelectWordEffect(wordSelectEffect, WORD_SELECT_EFFECT_MAX, WORD_SELECT_EFFECT_FRAME);

		DrawImage(back, unionTex[selectedStage]);

		static int battleFrameCount = 0;

		const int ACTION_EFFECT_BLANK = 3;

		const int ACTION_WORD_STAGE_FRAME = 90;

		int playerActionEffectFrame = actionEffectDatas[battleData.m_playerEffectId].m_segmentX*
			actionEffectDatas[battleData.m_playerEffectId].m_segmentY*ACTION_EFFECT_BLANK;

		const int REDUCE_ENEMY_HP_FRAME = 60;

		const int ENEMY_ACTION_NAME_STAGE_FRAME = 90;

		int enemyEffectId = battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_effectId;
		int enemyActionEffectFrame = actionEffectDatas[enemyEffectId].m_segmentX*
			actionEffectDatas[enemyEffectId].m_segmentY*ACTION_EFFECT_BLANK;

		const int REDUCE_PLAYER_HP_FRAME = 60;

		const float ENEMY_SCALE = DISPLAY_WIDTH * 0.15f;

		CustomImageVerticies(enemyVertices, DISPLAY_WIDTH *0.5f, DISPLAY_HEIGHT * 0.5f,
			ENEMY_SCALE, ENEMY_SCALE, GetColor(255, 255, 255, 255));

		switch (battleData.m_result)
		{
		case WIN:
		{
			const int ENEMY_DELETE_FRAME = 120;

			static int enemyDeleteFrameCount = 0;

			GetCustomVerTexColor(enemyVertices,
				GetColor((UCHAR)(255 * (1.f - enemyDeleteFrameCount / (float)ENEMY_DELETE_FRAME)), 255, 255, 255));

			if (enemyDeleteFrameCount < ENEMY_DELETE_FRAME)
			{
				++enemyDeleteFrameCount;
			}

			if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK])
			{
				*scene = HOME_SCENE;
				InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, WM_MAX_PP,
					selectedDeck, pWMDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);
				frameCount = 0;
				enemyDeleteFrameCount = 0;
				battleFrameCount = 0;

				return;
			}
		}

		break;

		case LOSE:
		{
			const int BLACK_OUT_FRAME = 120;

			static int blackOutFrameCount = 0;

			CustomImageVerticies(resultMask, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f,
				DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f,
				GetColor((UCHAR)(255 * (blackOutFrameCount / (float)BLACK_OUT_FRAME)), 0, 0, 0));

			if (blackOutFrameCount < BLACK_OUT_FRAME)
			{
				++blackOutFrameCount;
			}

			if (g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[RIGHT_CLICK])
			{
				*scene = HOME_SCENE;
				InitOperateBattleDatas(&battleData, pEnemyDatas, stageDatas, selectedStage, WM_MAX_PP,
					selectedDeck, pWMDeck, wordSelectEffect, WORD_SELECT_EFFECT_MAX);
				DrawImage(resultMask, NULL);
				ZeroMemory(resultMask, sizeof(CustomVertex)*RECT_VERTEX_NUM);
				frameCount = 0;
				blackOutFrameCount = 0;
				battleFrameCount = 0;

				return;
			}
		}

		break;
		}

		DrawImage(enemyVertices, enemyTex[stageDatas[selectedStage].m_enemy[floor]]);

		if (battleData.m_useAction && !battleData.m_result)
		{
			if (battleFrameCount < ACTION_WORD_STAGE_FRAME)
			{
				if (battleData.m_enemyData.m_currentHP <= battleData.m_playerActionDamage)
				{
					if (battleFrameCount < ACTION_WORD_STAGE_FRAME / 2)
					{
						CustomImageVerticies(charaCutInVertices, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.28f,
							DISPLAY_WIDTH*0.5f*(battleFrameCount / (float)(ACTION_WORD_STAGE_FRAME / 2)), DISPLAY_HEIGHT*0.15f,
							GetColor(255, 255, 255, 255),
							(0.5f*(1.f - battleFrameCount / (float)(ACTION_WORD_STAGE_FRAME / 2))), 0.f,
							DISPLAY_WIDTH*(battleFrameCount / (float)(ACTION_WORD_STAGE_FRAME / 2)),
							1.f, (float)DISPLAY_WIDTH, 1.f);
					}

					else
					{
						CustomImageVerticies(charaCutInVertices, DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.28f,
							DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.15f);
					}

					DrawImage(charaCutInVertices, wMWordTex[WM_CUT_IN]);
				}

				if (battleFrameCount + 1 == ACTION_WORD_STAGE_FRAME)
				{
					ZeroMemory(battleData.m_playerAction, sizeof(int)*ACTION_WORD_MAX);
				}

				StageActionWord(battleFrameCount, ACTION_WORD_STAGE_FRAME, actionWordVertices, ACTION_WORD_MAX, &battleData,&wMWordTex[WM_UNDER_ACTION]);
			}

			if (ACTION_WORD_STAGE_FRAME <= battleFrameCount && battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame)
			{
				RenderActionEffect(battleFrameCount - ACTION_WORD_STAGE_FRAME, ACTION_EFFECT_BLANK,
					DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f, actionEffectDatas[battleData.m_playerEffectId].m_effectScale,
					&actionEffectDatas[battleData.m_playerEffectId], GetColor(200, 255, 20, 20));
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME)
			{
				ReduceEnemyHPGradually(REDUCE_ENEMY_HP_FRAME, &battleData);

				HealPlayerHPGradually(REDUCE_ENEMY_HP_FRAME, &battleData);

				char playerActionDamageBuf[20];
				_itoa(battleData.m_playerActionDamage, playerActionDamageBuf, 10);

				WriteText((int)(DISPLAY_WIDTH*0.5f), (int)(DISPLAY_HEIGHT*0.75f),
					playerActionDamageBuf, DT_CENTER, unionFont[ENEMY_ACTION_FONT],
					GetColor(255, 180, 180, 180));

				char playerHealHPBuf[20];
				_itoa(battleData.m_playerHPTmp, playerHealHPBuf, 10);

				if (battleData.m_playerHPTmp)
				{
					WriteText((int)(DISPLAY_WIDTH*0.25f), (int)(DISPLAY_HEIGHT*0.75f),
						playerHealHPBuf, DT_CENTER, unionFont[ENEMY_NAME_FONT],
						GetColor(255, 127, 255, 0));
				}
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame
				+ REDUCE_ENEMY_HP_FRAME + ENEMY_ACTION_NAME_STAGE_FRAME)
			{
				WriteText((int)(DISPLAY_WIDTH*0.5f), (int)(DISPLAY_HEIGHT*0.2f),
					battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_name,
					DT_CENTER, unionFont[ENEMY_ACTION_FONT],
					GetColor(255, 255, 30, 30));
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame +
				REDUCE_ENEMY_HP_FRAME + ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame)
			{
				RenderActionEffect(battleFrameCount -
					(ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
						+ ENEMY_ACTION_NAME_STAGE_FRAME), ACTION_EFFECT_BLANK,
					DISPLAY_WIDTH*0.5f, DISPLAY_HEIGHT*0.5f, actionEffectDatas[enemyEffectId].m_effectScale,
					&actionEffectDatas[enemyEffectId], GetColor(200, 255, 20, 20));
			}

			if (ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame <= battleFrameCount &&
				battleFrameCount < ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame + REDUCE_PLAYER_HP_FRAME)
			{
				ReducePlayerHPGradually(REDUCE_PLAYER_HP_FRAME, &battleData);

				char enemyActionDamageBuf[20];
				_itoa(battleData.m_enemyData.m_enemyAction[(battleData.m_turn - 1) % ENEMY_ACTION_MAX].m_damage,
					enemyActionDamageBuf, 10);

				WriteText((int)(DISPLAY_WIDTH*0.25f), (int)(DISPLAY_HEIGHT*0.75f),
					enemyActionDamageBuf, DT_CENTER, unionFont[ENEMY_NAME_FONT],
					GetColor(255, 180, 180, 180));
			}

			++battleFrameCount;

			if (battleFrameCount >= ACTION_WORD_STAGE_FRAME + playerActionEffectFrame + REDUCE_ENEMY_HP_FRAME
				+ ENEMY_ACTION_NAME_STAGE_FRAME + enemyActionEffectFrame + REDUCE_PLAYER_HP_FRAME)
			{
				PrepareNextTurn(&battleFrameCount, &battleData, ACTION_WORD_MAX);
			}
		}

		if (battleFrameCount - 1 <= ACTION_WORD_STAGE_FRAME)
		{
			if (!battleFrameCount)
			{
				for (int hand = 0; hand < HAND_MAX; ++hand)
				{
					DrawImage(handVertices[hand].ImageVertex, wMWordTex[WM_WORD_SEAT]);
					DrawImage(handVertices[hand].ImageVertex, pWMWordTex[battleData.m_hand[hand]]);
				}
			}

			RenderActionSeat(frameCount, START_ANIMATION_FRAME, &wMWordTex[WM_ACTION_SEAT]);

			RenderActionWord(ACTION_WORD_MAX, WORD_SELECT_EFFECT_MAX, wordSelectEffect,
				&battleData, actionWordVertices, pWMWordTex, unionTex, playerChara);

			DrawWordSelectEffect(wordSelectEffect, WORD_SELECT_EFFECT_MAX, &unionTex[WORD_SELECT_EFFECT]);

			for (int hand = 0; hand < HAND_MAX; ++hand)
			{
				int handWord = battleData.m_hand[hand];

				if (RectToRectCollisionCheak(handVertices[hand].ImageVertex, pMouseCursorVertices) && handWord)
				{
					char maxCostBuf[5];

					_itoa(pWMWordDatas[handWord].m_costMax, maxCostBuf, 10);

					const int TEXT_POS_X = (int)(DISPLAY_WIDTH * 0.7f);
					const int TEXT_POS_Y = (int)(DISPLAY_HEIGHT * 0.49f);
					const int TEXT_Y_BLANK = (int)(DISPLAY_HEIGHT*0.05f);
					WriteText(TEXT_POS_X, TEXT_POS_Y, maxCostBuf, DT_CENTER, unionFont[ENEMY_NAME_FONT], 0xFF000000);

					char elementBuf[ELEMENT_ATTRIBUTES_MAX][10] =
					{
						{ "火" },{ "水" },{ "風" },{ "光" },{ "闇" },{ "" }
					};

					WriteText(TEXT_POS_X, TEXT_POS_Y + TEXT_Y_BLANK, &elementBuf[pWMWordDatas[handWord].m_element][0],
						DT_CENTER, unionFont[ENEMY_NAME_FONT], 0xFF000000);

					char attackBuf[ATTACK_ATTRIBUTES_MAX][10] =
					{
						{ "斬" },{ "打" },{ "突" },{ "" },
					};

					WriteText(TEXT_POS_X, TEXT_POS_Y + 2 * TEXT_Y_BLANK, &attackBuf[pWMWordDatas[handWord].m_attack][0],
						DT_CENTER, unionFont[ENEMY_NAME_FONT], 0xFF000000);
				}
			}
		}

		WriteText((int)(DISPLAY_WIDTH*0.35), (int)(DISPLAY_HEIGHT*0.03),
			battleData.m_enemyData.m_name, DT_CENTER, unionFont[ENEMY_NAME_FONT], GetColor(255, 255, 30, 30));

		CustomImageVerticies(enemyHPVertices, DISPLAY_WIDTH *0.5f, DISPLAY_HEIGHT*0.1f,
			DISPLAY_WIDTH*0.3f, DISPLAY_HEIGHT*0.03f, 0xFFFFFFFF,
			0.5f*(1.f - battleData.m_enemyData.m_currentHP / (float)(battleData.m_enemyData.m_maxHP)),
			0.f, 0.5f, 1.f, 1.f, 1.f);

		DrawImage(enemyHPVertices, unionTex[HP_BAR]);

		CustomImageVerticies(enemyHPVertices, DISPLAY_WIDTH *0.5f, DISPLAY_HEIGHT*0.1f,
			DISPLAY_WIDTH*0.3f, DISPLAY_HEIGHT*0.03f, 0xFFFFFFFF);

		DrawImage(enemyHPVertices, unionTex[HP_COVER]);

		CustomImageVerticies(playerHPVertices, DISPLAY_WIDTH *0.12f, DISPLAY_HEIGHT*0.82f,
			DISPLAY_WIDTH*0.1f, DISPLAY_HEIGHT*0.01f, 0xFFFFFFFF,
			0.5f*(1.f - battleData.m_playerHPCurrent / (float)(battleData.m_playerHPMax)),
			0.f, 0.5f, 1.f, 1.f, 1.f);

		DrawImage(playerHPVertices, unionTex[HP_BAR]);

		CustomImageVerticies(playerHPVertices, DISPLAY_WIDTH *0.12f, DISPLAY_HEIGHT*0.82f,
			DISPLAY_WIDTH*0.1f, DISPLAY_HEIGHT*0.01f, 0xFFFFFFFF);

		DrawImage(playerHPVertices, unionTex[HP_COVER]);

		char pPBuf[10];
		sprintf(pPBuf, "%d/%d", battleData.m_pPCurrent, battleData.m_pPMax);

		WriteText((int)(DISPLAY_WIDTH *0.26f), (int)(DISPLAY_HEIGHT*0.8187f), pPBuf, DT_CENTER,
			unionFont[ENEMY_NAME_FONT], GetColor(255, 0, 50, 255));

		DrawImage(resultMask, NULL);

		if (frameCount < START_ANIMATION_FRAME)
		{
			++frameCount;
		}
	}
	}

	return;
}

bool InitOperateBattleDatas(BattleData* pBattleData, EnemyData* pEnemyDatas,
	StageData* pStageDatas,int selectedStage,int maxPP,int selectedDeck, Deck* pDeck,
	WordSelectEffect* pWordSelectEffects,int wordSelectEffectMax)
{
	InitStageData(pStageDatas);
	InitEnemyData(pEnemyDatas);

	int firstEnemyId = pStageDatas[selectedStage].m_enemy[0];

	ZeroMemory(pBattleData, sizeof(BattleData));

	ZeroMemory(pWordSelectEffects, sizeof(WordSelectEffect)*wordSelectEffectMax);

	InitHand(pBattleData, pDeck, selectedDeck);

	pBattleData->m_playerActionLimit = FIRST_ACTION_LIMIT;
	pBattleData->m_playerHPMax = MAX_HP;
	pBattleData->m_playerHPCurrent = MAX_HP;
	pBattleData->m_pPMax = maxPP;
	pBattleData->m_pPCurrent = maxPP;
	pBattleData->m_turn = 1;
	memcpy(&pBattleData->m_enemyData, &pEnemyDatas[firstEnemyId],sizeof(EnemyData));
	pBattleData->m_enemyData.m_currentHP = pEnemyDatas[firstEnemyId].m_maxHP;

	return true;
}

void InitStageData(StageData* pStageDatas)
{
	FILE* pForestStageFile;

	pForestStageFile = fopen("Files/Stage/ForestStage.csv","r");

	for (int floor = 0; floor < FLOOR_MAX; ++floor)
	{
		fscanf(pForestStageFile, "%d,%d,", &pStageDatas[森].m_enemy[floor], &pStageDatas[森].m_clear[floor]);
	}

	fclose(pForestStageFile);

	FILE* pRuinStageFile;

	pRuinStageFile = fopen("Files/Stage/RuinStage.csv", "r");

	for (int floor = 0; floor < FLOOR_MAX; ++floor)
	{
		fscanf(pForestStageFile, "%d,%d,", &pStageDatas[遺跡].m_enemy[floor], &pStageDatas[遺跡].m_clear[floor]);
	}

	fclose(pRuinStageFile);

	FILE* pCaveStageFile;

	pCaveStageFile = fopen("Files/Stage/CaveStage.csv", "r");

	for (int floor = 0; floor < FLOOR_MAX; ++floor)
	{
		fscanf(pCaveStageFile, "%d,%d,", &pStageDatas[洞窟].m_enemy[floor], &pStageDatas[洞窟].m_clear[floor]);
	}

	fclose(pCaveStageFile);

	return;
}

void InitEnemyData(EnemyData* pEnemyDatas)
{
	FILE* pEnemyDataFile;

	pEnemyDataFile = fopen("Files/Enemy/EnemyData.csv", "r");

	for (int enemy = 0; enemy < ENEMY_MAX; ++enemy)
	{
		if (enemy > 0)
		{
			fscanf(pEnemyDataFile, "%*c");
		}

		fscanf(pEnemyDataFile, "%[^,],%d,%u,%d,%d,%d,",
			pEnemyDatas[enemy].m_name, &pEnemyDatas[enemy].m_maxHP,
			&pEnemyDatas[enemy].m_attackWeak, &pEnemyDatas[enemy].m_elementWeak,
			&pEnemyDatas[enemy].m_attackResist, &pEnemyDatas[enemy].m_elementResist);

		for (int action = 0; action < ENEMY_ACTION_MAX; ++action)
		{
			fscanf(pEnemyDataFile, "%[^,],%d,%u,%d,",
				pEnemyDatas[enemy].m_enemyAction[action].m_name,
				&pEnemyDatas[enemy].m_enemyAction[action].m_damage,
				&pEnemyDatas[enemy].m_enemyAction[action].m_ability,
				&pEnemyDatas[enemy].m_enemyAction[action].m_effectId);
		}
	}

	fclose(pEnemyDataFile);

	return;
}

void InitHand(BattleData* pBattleData,Deck* pDeck,int selectedDeck)
{
	bool haveHand = false;

	for (int hand=0; hand < HAND_MAX; ++hand)
	{
		if (pBattleData->m_hand[hand])
		{
			haveHand = true;
		}
	}

	for (int hand=0; (hand < HAND_MAX)&&!haveHand; ++hand)
	{
		pBattleData->m_hand[hand] = pDeck[selectedDeck].m_wordId[hand];
	}

	return;
}

void SetHandVertices(int frameCount,int startAnimatationFrame,ImagesCustomVertex* pHandVertices,
	float handPosX, float handPosY, float handWidth, float handHeight, float circulatePosX,int scrollSpeed,BattleData* pBattleData)
{
	static int degree = 0;

	if (frameCount < startAnimatationFrame)
	{
		for (int hand = 0; hand < HAND_MAX; ++hand)
		{
			CustomImageVerticies(pHandVertices[hand].ImageVertex,
				handPosX, handPosY,handWidth, handHeight);

			CirculateImageDeg(pHandVertices[hand].ImageVertex,
				pHandVertices[hand].ImageVertex, 
				(float)(((360 / HAND_MAX)*(hand)) + (360/ startAnimatationFrame) * 
				(-frameCount - 1)), circulatePosX, handPosY);
		}
	}

	else
	{
		if (!pBattleData->m_useAction)
		{
			if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ > 0)
			{
				degree -= scrollSpeed;
			}

			if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ < 0)
			{
				degree += scrollSpeed;
			}

			if (degree >= 360 || degree <= -360)
			{
				degree = 0;
			}
		}

		for (int hand = 0; hand < HAND_MAX; ++hand)
		{
			CustomImageVerticies(pHandVertices[hand].ImageVertex,
				handPosX, handPosY,
				handWidth, handHeight);

			CirculateImageDeg(pHandVertices[hand].ImageVertex,
				pHandVertices[hand].ImageVertex,
				(float)(((360 / HAND_MAX)*(hand)) + degree), circulatePosX, handPosY);
		}
	}

	return;
}

void SetActionWordVertices(ImagesCustomVertex* pActionWordVertices, int actionWordMax,
	float actionWordPosX, float actionWordPosY,float actionWordWidth,float actionWordHeight)
{
	for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
	{
		CustomImageVerticies(pActionWordVertices[actionWord].ImageVertex,
			actionWordPosX + actionWordWidth * 2 * actionWord,
			actionWordPosY,
			actionWordWidth, actionWordHeight);
	}

	return;
}

void IOAction(int frameCount, int startAnimatationFrame,CustomVertex* pMouseCursorVertices,
	ImagesCustomVertex* pHandVertices, float handWidth, float handHeight,
	ImagesCustomVertex* pActionWordVertices, float actionWordWidth, float actionWordHeight,
	WordData* pWordDatas,WordSelectEffect* pWordSelectEffect, int selectEffectMax, BattleData* pBattleData,int actionWordMax)
{
	const int ACTION_FULL = 10;
	int actionSpace = ACTION_FULL;

	if (frameCount >= startAnimatationFrame&& !pBattleData->m_useAction)
	{
		//左クリックされていなかったら
		if (!g_mouseState.mousePush[LEFT_CLICK])
		{
			return;
		}

		//手札の数だけ調べる
		for (int hand = 0; hand < HAND_MAX; ++hand)
		{
			//当たっていない
			if (!RectToRectCollisionCheak(pMouseCursorVertices,
				pHandVertices[hand].ImageVertex))
			{
				continue;
			}

			int handCurrent = pBattleData->m_hand[hand];
			
			//VOID_W0RD
			if (!handCurrent)
			{
				break;
			}

			//PPオーバー
			if (pBattleData->m_pPCurrent - pWordDatas[handCurrent].m_costMax <0)
			{
				break;
			}

			int actionWordNum = 0;

			//現在いくつ必殺技に単語が入っているか
			for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
			{
				if (pBattleData->m_playerAction[actionWord])
				{
					++actionWordNum;
				}
			}

			//必殺技の単語の個数制限
			if (actionWordNum+1 > pBattleData->m_playerActionLimit)
			{
				break;
			}

			//必殺技のスペースを探す
			for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
			{
				if (!pBattleData->m_playerAction[actionWord])
				{
					actionSpace = actionWord;

					break;
				}
			}

			//スペースがなかったら
			if (actionSpace == ACTION_FULL)
			{
				break;
			}

			SetEffect(pWordSelectEffect, selectEffectMax,
				pHandVertices, handWidth, handHeight, hand,
				pActionWordVertices, actionWordWidth, actionWordHeight, actionSpace);

			//必殺技に代入
			pBattleData->m_playerAction[actionSpace] = handCurrent;
			++(pBattleData->m_playerActionCurrent);
			pBattleData->m_pPCurrent -= pWordDatas[handCurrent].m_costMax;
			pBattleData->m_hand[hand] = 0;

			//手札の位置
			pBattleData->m_handPos[actionSpace] = hand;
		}

		//必殺技
		for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
		{
			//当たっていなかったら
			if (!RectToRectCollisionCheak(pMouseCursorVertices,
				pActionWordVertices[actionWord].ImageVertex))
			{
				continue;
			}

			if (pBattleData->m_playerAction[actionWord] == 0)
			{
				break;
			}

			int actionWordCurrent = pBattleData->m_playerAction[actionWord];

			//リムーブ
			--(pBattleData->m_playerActionCurrent);
			pBattleData->m_pPCurrent += pWordDatas[actionWordCurrent].m_costMax;
			pBattleData->m_hand[(pBattleData->m_handPos[actionWord])] = actionWordCurrent;
			pBattleData->m_playerAction[actionWord] = 0;
			pBattleData->m_handPos[actionWord] = 0;
		}
	}

	return; 
}

void SetEffect(WordSelectEffect* pWordSelectEffect, int selectEffectMax,
	ImagesCustomVertex* pHandVertices, float handWidth, float handHeight, int hand,
	ImagesCustomVertex* pActionWordVertices, float actionWordWidth, float actionWordHeight, int actionSpace)
{
	for (int effect = 0; effect < selectEffectMax; ++effect)
	{
		if (!pWordSelectEffect[effect].m_valid)
		{
			float handPosX = pHandVertices[hand].ImageVertex[0].m_x + handWidth;
			float handPosY = pHandVertices[hand].ImageVertex[0].m_y + handHeight;

			float actionWordPosX = pActionWordVertices[actionSpace].ImageVertex[0].m_x + actionWordWidth;
			float actionWordPosY = pActionWordVertices[actionSpace].ImageVertex[0].m_y + actionWordHeight;

			CalculateDistanceBetweenTwoPointsXY(&pWordSelectEffect[effect].m_homingVect, handPosX, handPosY, actionWordPosX, actionWordPosY);

			const float effectScale = DISPLAY_HEIGHT / 50.f;
			CustomImageVerticies(pWordSelectEffect[effect].m_vertices, handPosX, handPosY, effectScale, effectScale);

			pWordSelectEffect[effect].m_actionPos = actionSpace;

			pWordSelectEffect[effect].m_valid = true;

			break;
		}
	}

	return;
}

void CalcActionDamage(BattleData* pBattleData, int actionWordMax, 
	WordData* pWordDatas, ActionEffectData* pActionEffectDatas)
{
	bool decidePlayerAttack = false;
	bool decidePlayerElement = false;

	for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
	{
		if (!pBattleData->m_playerAction[actionWord])
		{
			if (actionWord < actionWordMax - 1)
			{
				pBattleData->m_playerAction[actionWord] = 
					pBattleData->m_playerAction[actionWord + 1];
				pBattleData->m_playerAction[actionWord + 1] = 0;
			}
		}
	}

	for (int actionWord = actionWordMax - 1; actionWord >= 0; --actionWord)
	{
		int actionWordCurrent = pBattleData->m_playerAction[actionWord];

		if (!actionWordCurrent)
		{
			continue;
		}

		int wordAttack = pWordDatas[actionWordCurrent].m_attack;

		if (!decidePlayerAttack&&wordAttack !=VOID_ATTACK)
		{
			pBattleData->m_playerActionAttack   = wordAttack;

			decidePlayerAttack = true;
		}

		int wordElement = pWordDatas[actionWordCurrent].m_element;

		if (!decidePlayerElement&&wordElement != VOID_ELEMENT)
		{
			pBattleData->m_playerActionElement = wordElement;

			decidePlayerElement = true;
		}

		/*int actionWordPlusCurrent = pWordDatas[actionWordCurrent].m_plusDamage;*/

		switch (pWordDatas[actionWordCurrent].m_costMax)
		{
		case 1:

			pBattleData->m_playerActionDamage += MK_COST_1_DAMAGE/* +
				MK_COST_1_PLUS__DAMAGE * actionWordPlusCurrent*/;

			break;

		case 3:

			pBattleData->m_playerActionDamage += MK_COST_3_DAMAGE/* +
				MK_COST_3_PLUS__DAMAGE * actionWordPlusCurrent*/;

			break;

		case 5:

			pBattleData->m_playerActionDamage += MK_COST_5_DAMAGE/* +
				MK_COST_5_PLUS__DAMAGE * actionWordPlusCurrent*/;

			break;

		case 12:

			pBattleData->m_playerActionDamage += MK_COST_12_DAMAGE/* +
				MK_COST_12_PLUS__DAMAGE * actionWordPlusCurrent*/;

			break;
		}
	}

	if (!decidePlayerAttack)
	{
		pBattleData->m_playerActionAttack = VOID_ATTACK;

		decidePlayerAttack = true;
	}

	if (!decidePlayerElement)
	{
		pBattleData->m_playerActionElement = VOID_ELEMENT;

		decidePlayerElement = true;
	}

	CalcDamageBonusWithSkills(pBattleData,actionWordMax, pWordDatas);

	pBattleData->m_playerActionDamage = 20400000;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	pBattleData->m_playerEffectId = pBattleData->m_playerActionAttack + 6;

	const DWORD ELEMENT_COLORS[ELEMENT_ATTRIBUTES_MAX] =
	{ 0xffff0000,0xff0000ff,0xff00ff00,0xffffff00,0xff800080 ,0xffffffff};

	pActionEffectDatas[(pBattleData->m_playerEffectId)].m_color = ELEMENT_COLORS[(pBattleData->m_playerActionElement)];

	return;
}

void CalcDamageBonusWithSkills(BattleData* pBattleData, int actionWordMax, WordData* pWordDatas)
{
	int actionElement = pBattleData->m_playerActionElement;

	if (pBattleData->m_enemyData.m_elementWeak == actionElement)
	{
		pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage * ELEMENT_RESIST);
	}

	if (pBattleData->m_enemyData.m_elementResist == actionElement)
	{
		pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage * ELEMENT_WEAK);
	}

	int actionAttack = pBattleData->m_playerActionAttack;

	if (pBattleData->m_enemyData.m_attackWeak == actionAttack)
	{
		pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage * ATTACK_RESIST);
	}

	if (pBattleData->m_enemyData.m_attackResist == actionAttack)
	{
		pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage * ATTACK_WEAK);
	}

	for (int skill = 1; skill < SKILL_MAX; ++skill)
	{
		for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
		{
			int actionWordId = pBattleData->m_playerAction[actionWord];

			for (int skillSlot = 0; skillSlot < SKILL_SLOT_MAX; ++skillSlot)
			{
				if (pWordDatas[actionWordId].m_skillSlot[skillSlot]==skill)
				{
					++(pBattleData->m_playerActionSkillsCurrent[skill]);
				}
			}
		}

		switch (skill)
		{
		case 1:

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsCurrent[skill]; ++sameSkill)
			{
				pBattleData->m_pPTmp += 2;
			}

			break;

		case 2:

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsCurrent[skill]; ++sameSkill)
			{
				++(pBattleData->m_playerActionSkillsPrev[skill]);
			}

			break;

		case 3:

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsCurrent[skill]; ++sameSkill)
			{
				pBattleData->m_playerHPTmp += (UINT)(pBattleData->m_playerHPMax*0.25f);
			}

			break;

		case 4:

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsPrev[skill]; ++sameSkill)
			{
				pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage*1.4f);
			}

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsCurrent[skill]; ++sameSkill)
			{
				++(pBattleData->m_playerActionSkillsPrev[skill]);
			}

			break;

		case 5:

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsCurrent[skill]; ++sameSkill)
			{
				pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage*1.1f);
			}

			break;

		case 6:

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsCurrent[skill]; ++sameSkill)
			{
				pBattleData->m_playerActionDamage=(UINT)(pBattleData->m_playerActionDamage*1.25f);
			}

			break;

		case 7:

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsPrev[skill]; ++sameSkill)
			{
				pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage*0.8f);
				++(pBattleData->m_playerActionSkillsPrev[skill]);
			}

			for (int sameSkill = 0; sameSkill < pBattleData->m_playerActionSkillsCurrent[skill]; ++sameSkill)
			{
				pBattleData->m_playerActionDamage = (UINT)(pBattleData->m_playerActionDamage*1.8f);
				++(pBattleData->m_playerActionSkillsPrev[skill]);
			}

			break;
		}
	}

	return;
}

void RenderActionSeat(int frameCount,int startAnimationFrame,TEXTUREID* pActionSeatTex)
{
	CustomVertex actionSeatVertices[RECT_VERTEX_NUM];

	static UCHAR frameAlpha = 0;

	const int animationSegment = (startAnimationFrame / 6);

	if (!frameCount)
	{
		frameAlpha = 0;
	}

	if (frameCount<animationSegment)
	{
		frameAlpha += 240 / animationSegment;
	}

	if (animationSegment <= frameCount && 2 * animationSegment)
	{
		frameAlpha -= 200 / animationSegment;
	}

	if (2 * animationSegment <= frameCount && frameCount < 4 * animationSegment)
	{
		frameAlpha += 180 / animationSegment;
	}

	if (4 * animationSegment <= frameCount && frameCount < 5 * animationSegment)
	{
		frameAlpha -= 200 / animationSegment;
	}

	if (5 * animationSegment <= frameCount && frameCount < 6 * animationSegment)
	{
		frameAlpha += 230 / animationSegment;
	}

	if (6 * animationSegment <= frameCount)
	{
		frameAlpha = 255;
	}

	CustomImageVerticies(actionSeatVertices, DISPLAY_WIDTH / 2.4f, DISPLAY_HEIGHT*0.92f, 
		DISPLAY_WIDTH/2.4f, DISPLAY_HEIGHT*0.08f, GetColor(frameAlpha, 255, 255, 255));

	DrawImage(actionSeatVertices, *pActionSeatTex);

	return;
}

void RenderActionWord(int actionWordMax, int wordSelectEffectMax, WordSelectEffect* pWordSelectEffect,
	BattleData* pBattleData,ImagesCustomVertex* pActionWordVertices,TEXTUREID* pWordTex,TEXTUREID* pUnionTex, int playerChara)
{
	for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
	{
		bool hideActionWord = false;

		for (int effect = 0; effect < wordSelectEffectMax; ++effect)
		{
			if (pWordSelectEffect[effect].m_valid&&pWordSelectEffect[effect].m_actionPos == actionWord)
			{
				hideActionWord = true;

				break;
			}
		}

		if (!hideActionWord&&pBattleData->m_playerAction[actionWord])
		{
			DrawImage(pActionWordVertices[actionWord].ImageVertex,
				pWordTex[pBattleData->m_playerAction[actionWord]]);
		}
	}

	return;
}

void StageActionWord(int battleFrameCount, int stageFrame, ImagesCustomVertex* pActionWordVertices,
	int actionWordMax, BattleData* pBattleData,TEXTUREID* pTextureId)
{
	const int actionWordStageSegment = stageFrame / actionWordMax;
	
	int actionWordNum = 0;

	for (int actionWord = 0; actionWord < actionWordMax; ++actionWord)
	{
		if (pBattleData->m_playerAction[actionWord])
		{
			++actionWordNum;
		}
	}

	float  actionWordWidth = (pActionWordVertices[0].ImageVertex[1].m_x - pActionWordVertices[0].ImageVertex[0].m_x)*0.62f;
	float  actionWordHeight = (pActionWordVertices[0].ImageVertex[3].m_y - pActionWordVertices[0].ImageVertex[0].m_y)*0.62f;
	float actionWordPosX = DISPLAY_WIDTH * 0.5f - (actionWordWidth* actionWordNum) + actionWordWidth;

	for (int actionWord = 0; actionWord < actionWordNum; ++actionWord)
	{
		if (battleFrameCount >= actionWordStageSegment * actionWord)
		{
			CustomImageVerticies(pActionWordVertices[actionWord].ImageVertex, 
				actionWordPosX + actionWordWidth*2.f * actionWord,DISPLAY_HEIGHT*0.5f,
				actionWordWidth, actionWordHeight);

			DrawImage(pActionWordVertices[actionWord].ImageVertex, *pTextureId);
		}
	}

	return;
}

void RenderActionEffect(int actionEffectCount,int actionEffectBlank,
	float posX, float posY, float effectScale, ActionEffectData* pActionEffectData, DWORD color)
{
	const int ACTION_EFFECT_SEGMENT_X = pActionEffectData->m_segmentX;
	const int ACTION_EFFECT_SEGMENT_Y = pActionEffectData->m_segmentY;
	CustomVertex ActionEeffectVertices[RECT_VERTEX_NUM];
	CustomImageVerticies(ActionEeffectVertices, posX, posY, effectScale, effectScale, pActionEffectData->m_color,

		2 * effectScale*((actionEffectCount % (actionEffectBlank*ACTION_EFFECT_SEGMENT_X)) / actionEffectBlank),
		2 * effectScale*((actionEffectCount %(actionEffectBlank*ACTION_EFFECT_SEGMENT_X*ACTION_EFFECT_SEGMENT_Y))
			/ (actionEffectBlank * ACTION_EFFECT_SEGMENT_X)),

		2 * effectScale,
		2 * effectScale,

		ACTION_EFFECT_SEGMENT_X * 2 * effectScale,
		ACTION_EFFECT_SEGMENT_Y * 2 * effectScale);

	DrawImage(ActionEeffectVertices, pActionEffectData->m_tex);

	return;
}

void ReduceEnemyHPGradually(int reduceEnemyHPFrame ,BattleData* pBattleData)
{
	UINT currentReduceHP = pBattleData->m_playerActionDamage / reduceEnemyHPFrame;

	if (pBattleData->m_enemyData.m_currentHP <= currentReduceHP)
	{
		pBattleData->m_enemyData.m_currentHP = 0;
	}

	else
	{
		pBattleData->m_enemyData.m_currentHP -= currentReduceHP;
	}
	
	if (!pBattleData->m_enemyData.m_currentHP)
	{
		pBattleData->m_result = WIN;
	}

	return;
}

void HealPlayerHPGradually(int healHPFrame, BattleData* pBattleData)
{
	pBattleData->m_playerHPCurrent+= (UINT)(pBattleData->m_playerHPTmp / (float)healHPFrame);

	if (pBattleData->m_playerHPCurrent > pBattleData->m_playerHPMax)
	{
		pBattleData->m_playerHPCurrent = pBattleData->m_playerHPMax;
	}

	return;
}

void ReducePlayerHPGradually(int reducePlayerHPFrame, BattleData* pBattleData)
{
	UINT currentReduceHP = 
		(UINT)(pBattleData->m_enemyData.m_enemyAction[(pBattleData->m_turn - 1)%ENEMY_ACTION_MAX].m_damage*
		(1 - 0.25f*pBattleData->m_playerActionSkillsPrev[2]) / (float)reducePlayerHPFrame);

	if (pBattleData->m_playerHPCurrent <= currentReduceHP)
	{
		pBattleData->m_playerHPCurrent = 0;
	}

	else
	{
		pBattleData->m_playerHPCurrent -= currentReduceHP;
	}

	if (!pBattleData->m_playerHPCurrent)
	{
		pBattleData->m_result = LOSE;
	}

	return;
}

void PrepareNextTurn(int* pBattleFrameCount,BattleData* pBattleData,int actionWordMax)
{
	pBattleData->m_pPCurrent = pBattleData->m_pPMax + pBattleData->m_pPTmp;
	pBattleData->m_pPTmp = 0;
	pBattleData->m_playerHPTmp = 0;

	for (int skill = 0; skill < SKILL_MAX; ++skill)
	{
		pBattleData->m_playerActionSkillsPrev[skill] = 
			pBattleData->m_playerActionSkillsCurrent[skill];
	}

	if (pBattleData->m_playerActionLimit < actionWordMax)
	{
		++(pBattleData->m_playerActionLimit);
	}

	ZeroMemory(pBattleData->m_playerActionSkillsCurrent, sizeof(int)*SKILL_MAX);
	pBattleData->m_playerActionDamage = 0;
	++(pBattleData->m_turn);
	pBattleData->m_useAction = false;

	*pBattleFrameCount = 0;

	return;
}

void DrawWordSelectEffect(WordSelectEffect* pWordSelectEffect,int wordSelectEffectMax, 
	TEXTUREID* pWordSelectEffectTex)
{
	for (int effect = 0; effect < wordSelectEffectMax; ++effect)
	{
		if (pWordSelectEffect[effect].m_valid)
		{
			DrawImage(pWordSelectEffect[effect].m_vertices, *pWordSelectEffectTex);
		}
	}

	return;
}

void MoveSelectWordEffect(WordSelectEffect* pWordSelectEffect,int wordSelectEffectMax,int wordSelectEffectFrame)
{
	for (int effect = 0; effect < wordSelectEffectMax; ++effect)
	{
		if (pWordSelectEffect[effect].m_valid)
		{
			MoveImage(pWordSelectEffect[effect].m_vertices, pWordSelectEffect[effect].m_vertices,
				(float)(pWordSelectEffect[effect].m_homingVect.m_x *(1 / (float)wordSelectEffectFrame)),
				(float)(pWordSelectEffect[effect].m_homingVect.m_y*(1 / (float)wordSelectEffectFrame)));

			pWordSelectEffect[effect].m_count++;

			if (pWordSelectEffect[effect].m_count > wordSelectEffectFrame)
			{
				pWordSelectEffect[effect].m_count = 0;

				pWordSelectEffect[effect].m_valid = false;
			}
		}
	}

	return;
}
