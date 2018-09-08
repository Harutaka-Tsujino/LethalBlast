#define _CRT_SECURE_NO_WARNINGS
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"

void ControlHome(SCENE* scene, WordData* pMagicKnightWordDatas, Deck* pMagicKnightDecks,
	WordData* pWeaponMAsterWordDatas, Deck* pWeaponMasterDecks,
	CustomVertex* pDeckAlterPortal, CustomVertex* pModifyWordPortal, CustomVertex* pMainGamePortal,
	CustomVertex* pCharaChoicePortal, TEXTUREID* mKWordTex, TEXTUREID* wMWordTex, PLAYERTYPE* playerType,
	bool* initializedTex)
{
	static int frameCount = -1;
	
	switch (*playerType)
	{
	case WEAPON_MASTER:

		if (!(*initializedTex))
		{
			LoadWordDatas(pWeaponMAsterWordDatas,"Files/WordStates/WeaponMasterWordStates.csv",WEAPON_MASTER_WORD_MAX);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck1.csv", 0);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck2.csv", 1);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck3.csv", 2);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck4.csv", 3);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck5.csv", 4);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck6.csv", 5);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck7.csv", 6);
			LoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck8.csv", 7);
			LordTextureWeaponMaster(wMWordTex);
			isSuccess = soundsManager.AddFile("Audio/perusona.mp3", _T("bgm"));

			*initializedTex = true;
		}
		
		break;
	
	case MAGIC_KNIGHT:

		if (!(*initializedTex))
		{
			LoadWordDatas(pMagicKnightWordDatas,"Files/WordStates/MagicKnightWordStates.csv",MAGIC_KNIGHT_WORD_MAX);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck1.csv", 0);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck2.csv", 1);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck3.csv", 2);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck4.csv", 3);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck5.csv", 4);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck6.csv", 5);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck7.csv", 6);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck8.csv", 7);
			isSuccess = soundsManager.AddFile("Audio/perusona.mp3", _T("bgm"));

			RoadTexture("Texture/MKWord/VOID_WORD.png", &mKWordTex[VOID_WORD]);

			FILE* pWordTexPathsFile;

			pWordTexPathsFile = fopen("Files/TexturePaths/MKWordTexPaths.csv", "r");

			for (int word = VOID_WORD + 1; word < MAGIC_KNIGHT_WORD_MAX; ++word)
			{
				char mkWordPath[60];

				fscanf(pWordTexPathsFile, "%s,", mkWordPath);
				RoadTexture(mkWordPath, &mKWordTex[word]);
			}

			fclose(pWordTexPathsFile);

			*initializedTex = true;
		}

		break;
	}


	//É}ÉEÉXÉJÅ[É\Éã
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	const float MAIN_GAME_PORTAL_SCALE = DISPLAY_WIDTH / 10.f;
	CustomImageVerticies(pMainGamePortal, DISPLAY_WIDTH*0.625f, DISPLAY_HEIGHT*0.625f, MAIN_GAME_PORTAL_SCALE, MAIN_GAME_PORTAL_SCALE, 0xe5f0f0f0);

	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pMainGamePortal))
		{
			*scene = SELECT_STAGE_SCENE;
			isSuccess = soundsManager.Stop(_T("bgm"));
		}
	}

	const float MID_PORTAL_SCALE_X = (float)(MAIN_GAME_PORTAL_SCALE * 0.8);
	const float MID_PORTAL_SCALE_Y = (float)(MAIN_GAME_PORTAL_SCALE * 0.4);

	CustomImageVerticies(pDeckAlterPortal, 
		(float)(DISPLAY_WIDTH*0.625f + MAIN_GAME_PORTAL_SCALE * 2), (float)(DISPLAY_HEIGHT*0.625f - MAIN_GAME_PORTAL_SCALE * 0.6),
		(float)MID_PORTAL_SCALE_X, (float)MID_PORTAL_SCALE_Y);

	isSuccess = soundsManager.Start(_T("bgm"), true);

	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pDeckAlterPortal))
		{
			*scene = CHOSE_DECK_TO_ALTER_SCENE;
			isSuccess = soundsManager.Stop(_T("bgm"));
		}
	}

	CustomImageVerticies(pModifyWordPortal,
		(float)(DISPLAY_WIDTH*0.625f + MAIN_GAME_PORTAL_SCALE * 2), (float)(DISPLAY_HEIGHT*0.625f + MAIN_GAME_PORTAL_SCALE * 0.6),
		(float)MID_PORTAL_SCALE_X, (float)MID_PORTAL_SCALE_Y);

	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pModifyWordPortal))
		{
			*scene = MODIFY_WORD_SCENE;
			isSuccess = soundsManager.Stop(_T("bgm"));
		}
	}

	CustomImageVerticies(pCharaChoicePortal, DISPLAY_HEIGHT*0.08f, DISPLAY_HEIGHT*0.04f, DISPLAY_HEIGHT*0.08f, DISPLAY_HEIGHT*0.04f,0xe6ffeeee);

	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pCharaChoicePortal))
		{
			*scene = CHARA_CHOICE_SCENE;

			isSuccess = soundsManager.Stop(_T("bgm"));

			*initializedTex = false;

			for (int word = 0; word < WEAPON_MASTER_WORD_MAX; ++word)
			{
				SAFE_RELEASE(wMWordTex[word]);
			}

			for (int word = 0; word < MAGIC_KNIGHT_WORD_MAX; ++word)
			{
				SAFE_RELEASE(mKWordTex[word]);
			}
		}
	}

	return;
}

void LoadWordDatas(WordData* pMagicKnightWordDatas,const char *pFilePath,int wordDataMax)
{
	FILE* pWordStatesFile;

	fopen_s(&pWordStatesFile, pFilePath, "r");

	memset(pMagicKnightWordDatas, 0, sizeof(WordData)*wordDataMax);

	//ñÇñ@åïémÇÃÉèÅ[ÉhÉfÅ[É^Å[Çì¸ÇÍÇƒÇ¢Ç≠
	for (int wordsNum = VOID_WORD + 1; wordsNum < MAGIC_KNIGHT_WORD_MAX; ++wordsNum)
	{
		//äOïîÉtÉ@ÉCÉãÇÃëÆê´ÇêîéöÇ…íºÇµÇΩÇ¢ÇÃÇ≈àÍìxï∂éöóÒÇ≈ï€ä«Ç∑ÇÈ
		const int ELEMENTAL_WORDS_MAX = 10;
		char elemental[ELEMENTAL_WORDS_MAX];
		memset(elemental, 0, sizeof(char)*ELEMENTAL_WORDS_MAX);

		const int ATTACK_WORDS_MAX = 10;
		char attack[ATTACK_WORDS_MAX];
		memset(attack, 0, sizeof(char)*ATTACK_WORDS_MAX);

		//äOïîÉtÉ@ÉCÉãÇ©ÇÁÇÃì¸óÕ
		fscanf(pWordStatesFile, "%[^,],%[^,],%[^,],%*x,%*d,%*d,%*d,%*d,%d", pMagicKnightWordDatas[wordsNum].m_word, elemental, attack, 
			&pMagicKnightWordDatas[wordsNum].m_have);

		//ÅèÇéÇÃëŒèà
		if (wordsNum > VOID_WORD + 1)
		{
			strcpy(&pMagicKnightWordDatas[wordsNum].m_word[0], &pMagicKnightWordDatas[wordsNum].m_word[1]);
		}

		//ì¡éÍëÆê´ÇÃêîÇæÇØâÒÇ∑
		for (int elementalNum = 0; elementalNum < ELEMENT_ATTRIBUTES_MAX; ++elementalNum)
		{
			//ëÆê´Ç™åàÇ‹Ç¡ÇΩÇ©Ç«Ç§Ç©
			bool wasInputElemental = false;

			//ëÆê´Çï∂éöóÒÇ≈ï€ä«ÇµÇƒÇ¢ÇΩÇÃÇ≈êîéöÇ…ïœä∑Ç∑ÇÈ
			switch (elementalNum)
			{
			case FIRE_ELEMENT:

				if (!strcmp("fi", elemental))
				{
					pMagicKnightWordDatas[wordsNum].m_element = FIRE_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case WATER_ELEMENT:

				if (!strcmp("wa", elemental))
				{
					pMagicKnightWordDatas[wordsNum].m_element = WATER_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case WIND_ELEMENT:

				if (!strcmp("wi", elemental))
				{
					pMagicKnightWordDatas[wordsNum].m_element = WIND_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case SHINING_ELEMENT:

				if (!strcmp("sh", elemental))
				{
					pMagicKnightWordDatas[wordsNum].m_element = SHINING_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case DARKNESS_ELEMENT:

				if (!strcmp("da", elemental))
				{
					pMagicKnightWordDatas[wordsNum].m_element = DARKNESS_ELEMENT;

					wasInputElemental = true;
				}

			case VOID_ELEMENT:

				if (!strcmp("0", elemental))
				{
					pMagicKnightWordDatas[wordsNum].m_element = VOID_ELEMENT;

					wasInputElemental = true;
				}

				break;
			}

			if (wasInputElemental)
			{
				break;
			}
		}

		//ï®óùëÆê´ÇÃêîÇæÇØâÒÇ∑
		for (int attackNum = 0; attackNum < ATTACK_ATTRIBUTES_MAX; ++attackNum)
		{
			bool wasInputAttack = 0;

			switch (attackNum)
			{
			case SLASH_ATTACK:

				if (!strcmp("sl", attack))
				{
					pMagicKnightWordDatas[wordsNum].m_attack = SLASH_ATTACK;

					wasInputAttack = true;
				}

				break;

			case SMASH_ATTACK:

				if (!strcmp("sm", attack))
				{
					pMagicKnightWordDatas[wordsNum].m_attack = SMASH_ATTACK;

					wasInputAttack = true;
				}

				break;

			case PENETRATION_ATTACK:

				if (!strcmp("pe", attack))
				{
					pMagicKnightWordDatas[wordsNum].m_attack = PENETRATION_ATTACK;

					wasInputAttack = true;
				}

				break;

			case VOID_ATTACK:

				if (!strcmp("0", attack))
				{
					pMagicKnightWordDatas[wordsNum].m_attack = VOID_ATTACK;
				}

				break;
			}

			if (wasInputAttack)
			{
				break;
			}
		}
	}

	fclose(pWordStatesFile);

	return;
}

void LoadDeck(WordData* pMagicKnightWordDatas, Deck* pMagicKnightDecks, const char* deckFilePath,int deckNum)
{
	FILE* pDeckFile;

	pDeckFile = fopen(deckFilePath, "r");

	memset(&pMagicKnightDecks[deckNum], 0, sizeof(Deck));

	fscanf(pDeckFile, "%*[^,]");

	for (int deckWordNum = 0; deckWordNum < DECK_WORD_MAX; ++deckWordNum)
	{
		fseek(pDeckFile, 1, SEEK_CUR);
		fscanf(pDeckFile,"%d", &pMagicKnightDecks[deckNum].m_wordId[deckWordNum]);

		int wordId = pMagicKnightDecks[deckNum].m_wordId[deckWordNum];

		if (!wordId)
		{
			break;
		}

		pMagicKnightDecks[deckNum].m_wordNum += 1;
	}

	fclose(pDeckFile);

	return;
}

void LordTextureWeaponMaster(TEXTUREID* pWmFontIds)
{
	static int isFirstFrame = INIT_FRAME;

	if (isFirstFrame == INIT_FRAME)
	{
		RoadTexture("Texture/WeaponMasterWord/VoidWord.png", &pWmFontIds[VOID_WORD]);
		RoadTexture("Texture/WeaponMasterWord/âŒ.png", &pWmFontIds[âŒ]);
		RoadTexture("Texture/WeaponMasterWord/îM.png", &pWmFontIds[îM]);
		RoadTexture("Texture/WeaponMasterWord/îR.png", &pWmFontIds[îR]);
		RoadTexture("Texture/WeaponMasterWord/ìî.png", &pWmFontIds[ìî]);
		RoadTexture("Texture/WeaponMasterWord/òF.png", &pWmFontIds[òF]);
		RoadTexture("Texture/WeaponMasterWord/çg.png", &pWmFontIds[çg]);
		RoadTexture("Texture/WeaponMasterWord/ê‘.png", &pWmFontIds[ê‘]);
		RoadTexture("Texture/WeaponMasterWord/êÖ.png", &pWmFontIds[êÖ]);
		RoadTexture("Texture/WeaponMasterWord/ê¬.png", &pWmFontIds[ê¬]);
		RoadTexture("Texture/WeaponMasterWord/âJ.png", &pWmFontIds[âJ]);
		RoadTexture("Texture/WeaponMasterWord/ïX.png", &pWmFontIds[ïX]);
		RoadTexture("Texture/WeaponMasterWord/ê·.png", &pWmFontIds[ê·]);
		RoadTexture("Texture/WeaponMasterWord/ó‚.png", &pWmFontIds[ó‚]);
		RoadTexture("Texture/WeaponMasterWord/óŒ.png", &pWmFontIds[óŒ]);
		RoadTexture("Texture/WeaponMasterWord/åı.png", &pWmFontIds[åı]);
		RoadTexture("Texture/WeaponMasterWord/ñæ.png", &pWmFontIds[ñæ]);
		RoadTexture("Texture/WeaponMasterWord/à√.png", &pWmFontIds[à√]);
		RoadTexture("Texture/WeaponMasterWord/îí.png", &pWmFontIds[îí]);
		RoadTexture("Texture/WeaponMasterWord/çï.png", &pWmFontIds[çï]);
		RoadTexture("Texture/WeaponMasterWord/à´.png", &pWmFontIds[à´]);
		RoadTexture("Texture/WeaponMasterWord/ên.png", &pWmFontIds[ên]);
		RoadTexture("Texture/WeaponMasterWord/ìÅ.png", &pWmFontIds[ìÅ]);
		RoadTexture("Texture/WeaponMasterWord/íe.png", &pWmFontIds[íe]);
		RoadTexture("Texture/WeaponMasterWord/êÿ.png", &pWmFontIds[êÿ]);
		RoadTexture("Texture/WeaponMasterWord/ë≈.png", &pWmFontIds[ë≈]);
		RoadTexture("Texture/WeaponMasterWord/åù.png", &pWmFontIds[åù]);
		RoadTexture("Texture/WeaponMasterWord/í@.png", &pWmFontIds[í@]);
		RoadTexture("Texture/WeaponMasterWord/ìÀ.png", &pWmFontIds[ìÀ]);
		RoadTexture("Texture/WeaponMasterWord/ñÓ.png", &pWmFontIds[ñÓ]);
		RoadTexture("Texture/WeaponMasterWord/éh.png", &pWmFontIds[éh]);
		RoadTexture("Texture/WeaponMasterWord/í‹.png", &pWmFontIds[í‹]);
		RoadTexture("Texture/WeaponMasterWord/ãÛ.png", &pWmFontIds[ãÛ]);
		RoadTexture("Texture/WeaponMasterWord/àü.png", &pWmFontIds[àü]);
		RoadTexture("Texture/WeaponMasterWord/êV.png", &pWmFontIds[êV]);
		RoadTexture("Texture/WeaponMasterWord/åπ.png", &pWmFontIds[åπ]);
		RoadTexture("Texture/WeaponMasterWord/â‰.png", &pWmFontIds[â‰]);
		RoadTexture("Texture/WeaponMasterWord/êÓ.png", &pWmFontIds[êÓ]);
		RoadTexture("Texture/WeaponMasterWord/äÆ.png", &pWmFontIds[äÆ]);
		RoadTexture("Texture/WeaponMasterWord/ëS.png", &pWmFontIds[ëS]);
		RoadTexture("Texture/WeaponMasterWord/àÍ.png", &pWmFontIds[àÍ]);
		RoadTexture("Texture/WeaponMasterWord/êÁ.png", &pWmFontIds[êÁ]);
		RoadTexture("Texture/WeaponMasterWord/îV.png", &pWmFontIds[îV]);
		RoadTexture("Texture/WeaponMasterWord/ãC.png", &pWmFontIds[ãC]);
		RoadTexture("Texture/WeaponMasterWord/ê[.png", &pWmFontIds[ê[]);
		RoadTexture("Texture/WeaponMasterWord/ë¨.png", &pWmFontIds[ë¨]);
		RoadTexture("Texture/WeaponMasterWord/êS.png", &pWmFontIds[êS]);
		RoadTexture("Texture/WeaponMasterWord/éá.png", &pWmFontIds[éá]);
		RoadTexture("Texture/WeaponMasterWord/ìd.png", &pWmFontIds[ìd]);
		RoadTexture("Texture/WeaponMasterWord/ã|.png", &pWmFontIds[ã|]);
		RoadTexture("Texture/WeaponMasterWord/ãÄ.png", &pWmFontIds[ãÄ]);
		RoadTexture("Texture/WeaponMasterWord/ãÜ.png", &pWmFontIds[ãÜ]);
		RoadTexture("Texture/WeaponMasterWord/éc.png", &pWmFontIds[éc]);
		RoadTexture("Texture/WeaponMasterWord/å^.png", &pWmFontIds[å^]);
		RoadTexture("Texture/WeaponMasterWord/àÎ.png", &pWmFontIds[àÎ]);
		RoadTexture("Texture/WeaponMasterWord/ìÛ.png", &pWmFontIds[ìÛ]);
		RoadTexture("Texture/WeaponMasterWord/éQ.png", &pWmFontIds[éQ]);
		RoadTexture("Texture/WeaponMasterWord/„Ê.png", &pWmFontIds[„Ê]);
		RoadTexture("Texture/WeaponMasterWord/åﬁ.png", &pWmFontIds[åﬁ]);
		RoadTexture("Texture/WeaponMasterWord/ó§.png", &pWmFontIds[ó§]);
		RoadTexture("Texture/WeaponMasterWord/éΩ.png", &pWmFontIds[éΩ]);
		RoadTexture("Texture/WeaponMasterWord/ùõ.png", &pWmFontIds[ùõ]);
		RoadTexture("Texture/WeaponMasterWord/ãË.png", &pWmFontIds[ãË]);
		RoadTexture("Texture/WeaponMasterWord/èE.png", &pWmFontIds[èE]);
		RoadTexture("Texture/WeaponMasterWord/ín.png", &pWmFontIds[ín]);
		RoadTexture("Texture/WeaponMasterWord/îÚ.png", &pWmFontIds[îÚ]);
		RoadTexture("Texture/WeaponMasterWord/ä·.png", &pWmFontIds[ä·]);
		RoadTexture("Texture/WeaponMasterWord/ém.png", &pWmFontIds[ém]);
		RoadTexture("Texture/WeaponMasterWord/âÎ.png", &pWmFontIds[âÎ]);
		RoadTexture("Texture/WeaponMasterWord/êw.png", &pWmFontIds[êw]);
		RoadTexture("Texture/WeaponMasterWord/é~.png", &pWmFontIds[é~]);
		RoadTexture("Texture/WeaponMasterWord/â‘.png", &pWmFontIds[â‘]);
		RoadTexture("Texture/WeaponMasterWord/çé.png", &pWmFontIds[çé]);
		RoadTexture("Texture/WeaponMasterWord/ä¬.png", &pWmFontIds[ä¬]);
		RoadTexture("Texture/WeaponMasterWord/ñ].png", &pWmFontIds[ñ]]);
		RoadTexture("Texture/WeaponMasterWord/äê.png", &pWmFontIds[äê]);
		RoadTexture("Texture/WeaponMasterWord/ç~.png", &pWmFontIds[ç~]);
		RoadTexture("Texture/WeaponMasterWord/êZ.png", &pWmFontIds[êZ]);
		RoadTexture("Texture/WeaponMasterWord/ìO.png", &pWmFontIds[ìO]);
		RoadTexture("Texture/WeaponMasterWord/ìß.png", &pWmFontIds[ìß]);
		RoadTexture("Texture/WeaponMasterWord/íË.png", &pWmFontIds[íË]);
		RoadTexture("Texture/WeaponMasterWord/îΩ.png", &pWmFontIds[îΩ]);
		RoadTexture("Texture/WeaponMasterWord/ãt.png", &pWmFontIds[ãt]);
		RoadTexture("Texture/WeaponMasterWord/ë¶.png", &pWmFontIds[ë¶]);
		RoadTexture("Texture/WeaponMasterWord/à”.png", &pWmFontIds[à”]);
		RoadTexture("Texture/WeaponMasterWord/å√.png", &pWmFontIds[å√]);
		RoadTexture("Texture/WeaponMasterWord/êr.png", &pWmFontIds[êr]);
		RoadTexture("Texture/WeaponMasterWord/å}.png", &pWmFontIds[å}]);
		RoadTexture("Texture/WeaponMasterWord/â_.png", &pWmFontIds[â_]);
		RoadTexture("Texture/WeaponMasterWord/ìﬂ.png", &pWmFontIds[ìﬂ]);
		RoadTexture("Texture/WeaponMasterWord/î∞.png", &pWmFontIds[î∞]);
		RoadTexture("Texture/WeaponMasterWord/ë|.png", &pWmFontIds[ë|]);
		RoadTexture("Texture/WeaponMasterWord/èò.png", &pWmFontIds[èò]);
		RoadTexture("Texture/WeaponMasterWord/èú.png", &pWmFontIds[èú]);
		RoadTexture("Texture/WeaponMasterWord/ã}.png", &pWmFontIds[ã}]);
		RoadTexture("Texture/WeaponMasterWord/åÂ.png", &pWmFontIds[åÂ]);
		RoadTexture("Texture/WeaponMasterWord/å[.png", &pWmFontIds[å[]);
		RoadTexture("Texture/WeaponMasterWord/úa.png", &pWmFontIds[úa]);
		RoadTexture("Texture/WeaponMasterWord/à‚.png", &pWmFontIds[à‚]);
		RoadTexture("Texture/WeaponMasterWord/ì].png", &pWmFontIds[ì]]);
		RoadTexture("Texture/WeaponMasterWord/âÒ.png", &pWmFontIds[âÒ]);
		RoadTexture("Texture/WeaponMasterWord/íq.png", &pWmFontIds[íq]);
		RoadTexture("Texture/WeaponMasterWord/à≥.png", &pWmFontIds[à≥]);
		RoadTexture("Texture/WeaponMasterWord/îs.png", &pWmFontIds[îs]);
		RoadTexture("Texture/WeaponMasterWord/ìe.png", &pWmFontIds[ìe]);
		RoadTexture("Texture/WeaponMasterWord/Ém.png", &pWmFontIds[Ém]);
		RoadTexture("Texture/WeaponMasterWord/ï˙.png", &pWmFontIds[ï˙]);
		RoadTexture("Texture/WeaponMasterWord/ó£.png", &pWmFontIds[ó£]);
		RoadTexture("Texture/WeaponMasterWord/àÛ.png", &pWmFontIds[àÛ]);
		RoadTexture("Texture/WeaponMasterWord/ãN.png", &pWmFontIds[ãN]);
		RoadTexture("Texture/WeaponMasterWord/î¸.png", &pWmFontIds[î¸]);
		RoadTexture("Texture/WeaponMasterWord/çC.png", &pWmFontIds[çC]);
		RoadTexture("Texture/WeaponMasterWord/ëŒ.png", &pWmFontIds[ëŒ]);
		RoadTexture("Texture/WeaponMasterWord/è€.png", &pWmFontIds[è€]);
		RoadTexture("Texture/WeaponMasterWord/ì∆.png", &pWmFontIds[ì∆]);
		RoadTexture("Texture/WeaponMasterWord/ã·.png", &pWmFontIds[ã·]);
		RoadTexture("Texture/WeaponMasterWord/ã‚.png", &pWmFontIds[ã‚]);
		RoadTexture("Texture/WeaponMasterWord/íø.png", &pWmFontIds[íø]);
		RoadTexture("Texture/WeaponMasterWord/ç≈.png", &pWmFontIds[ç≈]);
		RoadTexture("Texture/WeaponMasterWord/çÇ.png", &pWmFontIds[çÇ]);
		RoadTexture("Texture/WeaponMasterWord/í·.png", &pWmFontIds[í·]);
		RoadTexture("Texture/WeaponMasterWord/ì¢.png", &pWmFontIds[ì¢]);
		RoadTexture("Texture/WeaponMasterWord/éÀ.png", &pWmFontIds[éÀ]);
		RoadTexture("Texture/WeaponMasterWord/ë_.png", &pWmFontIds[ë_]);
		RoadTexture("Texture/WeaponMasterWord/ëà.png", &pWmFontIds[ëà]);
		RoadTexture("Texture/WeaponMasterWord/ê√.png", &pWmFontIds[ê√]);
		RoadTexture("Texture/WeaponMasterWord/åà.png", &pWmFontIds[åà]);
		RoadTexture("Texture/WeaponMasterWord/èà.png", &pWmFontIds[èà]);
		RoadTexture("Texture/WeaponMasterWord/â°.png", &pWmFontIds[â°]);
		RoadTexture("Texture/WeaponMasterWord/èc.png", &pWmFontIds[èc]);
		RoadTexture("Texture/WeaponMasterWord/çª.png", &pWmFontIds[çª]);
		RoadTexture("Texture/WeaponMasterWord/âì.png", &pWmFontIds[âì]);
		RoadTexture("Texture/WeaponMasterWord/îÕ.png", &pWmFontIds[îÕ]);
		RoadTexture("Texture/WeaponMasterWord/ñú.png", &pWmFontIds[ñú]);
		RoadTexture("Texture/WeaponMasterWord/çi.png", &pWmFontIds[çi]);
		RoadTexture("Texture/WeaponMasterWord/êg.png", &pWmFontIds[êg]);
		RoadTexture("Texture/WeaponMasterWord/ïÚ.png", &pWmFontIds[ïÚ]);
		RoadTexture("Texture/WeaponMasterWord/ëæ.png", &pWmFontIds[ëæ]);
		RoadTexture("Texture/WeaponMasterWord/ê¢.png", &pWmFontIds[ê¢]);
		RoadTexture("Texture/WeaponMasterWord/ãê.png", &pWmFontIds[ãê]);
		RoadTexture("Texture/WeaponMasterWord/âˆ.png", &pWmFontIds[âˆ]);
		RoadTexture("Texture/WeaponMasterWord/èq.png", &pWmFontIds[èq]);
		RoadTexture("Texture/WeaponMasterWord/éÎ.png", &pWmFontIds[éÎ]);
		RoadTexture("Texture/WeaponMasterWord/îö.png", &pWmFontIds[îö]);
		RoadTexture("Texture/WeaponMasterWord/âä.png", &pWmFontIds[âä]);
		RoadTexture("Texture/WeaponMasterWord/èƒ.png", &pWmFontIds[èƒ]);
		RoadTexture("Texture/WeaponMasterWord/é‹.png", &pWmFontIds[é‹]);
		RoadTexture("Texture/WeaponMasterWord/äC.png", &pWmFontIds[äC]);
		RoadTexture("Texture/WeaponMasterWord/îg.png", &pWmFontIds[îg]);
		RoadTexture("Texture/WeaponMasterWord/ó¨.png", &pWmFontIds[ó¨]);
		RoadTexture("Texture/WeaponMasterWord/òI.png", &pWmFontIds[òI]);
		RoadTexture("Texture/WeaponMasterWord/ëö.png", &pWmFontIds[ëö]);
		RoadTexture("Texture/WeaponMasterWord/Ëπ.png", &pWmFontIds[Ëπ]);
		RoadTexture("Texture/WeaponMasterWord/ïó.png", &pWmFontIds[ïó]);
		RoadTexture("Texture/WeaponMasterWord/éæ.png", &pWmFontIds[éæ]);
		RoadTexture("Texture/WeaponMasterWord/ê˘.png", &pWmFontIds[ê˘]);
		RoadTexture("Texture/WeaponMasterWord/êâ.png", &pWmFontIds[êâ]);
		RoadTexture("Texture/WeaponMasterWord/ãP.png", &pWmFontIds[ãP]);
		RoadTexture("Texture/WeaponMasterWord/ì‚.png", &pWmFontIds[ì‚]);
		RoadTexture("Texture/WeaponMasterWord/ëM.png", &pWmFontIds[ëM]);
		RoadTexture("Texture/WeaponMasterWord/ós.png", &pWmFontIds[ós]);
		RoadTexture("Texture/WeaponMasterWord/âe.png", &pWmFontIds[âe]);
		RoadTexture("Texture/WeaponMasterWord/éÄ.png", &pWmFontIds[éÄ]);
		RoadTexture("Texture/WeaponMasterWord/çﬂ.png", &pWmFontIds[çﬂ]);
		RoadTexture("Texture/WeaponMasterWord/ñÇ.png", &pWmFontIds[ñÇ]);
		RoadTexture("Texture/WeaponMasterWord/éa.png", &pWmFontIds[éa]);
		RoadTexture("Texture/WeaponMasterWord/åï.png", &pWmFontIds[åï]);
		RoadTexture("Texture/WeaponMasterWord/íf.png", &pWmFontIds[íf]);
		RoadTexture("Texture/WeaponMasterWord/èR.png", &pWmFontIds[èR]);
		RoadTexture("Texture/WeaponMasterWord/ãr.png", &pWmFontIds[ãr]);
		RoadTexture("Texture/WeaponMasterWord/ëÑ.png", &pWmFontIds[ëÑ]);
		RoadTexture("Texture/WeaponMasterWord/âÂ.png", &pWmFontIds[âÂ]);
		RoadTexture("Texture/WeaponMasterWord/ãï.png", &pWmFontIds[ãï]);
		RoadTexture("Texture/WeaponMasterWord/åÉ.png", &pWmFontIds[åÉ]);
		RoadTexture("Texture/WeaponMasterWord/ôã.png", &pWmFontIds[ôã]);
		RoadTexture("Texture/WeaponMasterWord/âÿ.png", &pWmFontIds[âÿ]);
		RoadTexture("Texture/WeaponMasterWord/óÖ.png", &pWmFontIds[óÖ]);
		RoadTexture("Texture/WeaponMasterWord/ëo.png", &pWmFontIds[ëo]);
		RoadTexture("Texture/WeaponMasterWord/ïë.png", &pWmFontIds[ïë]);
		RoadTexture("Texture/WeaponMasterWord/éÁ.png", &pWmFontIds[éÁ]);
		RoadTexture("Texture/WeaponMasterWord/åÏ.png", &pWmFontIds[åÏ]);
		RoadTexture("Texture/WeaponMasterWord/ñ¸.png", &pWmFontIds[ñ¸]);
		RoadTexture("Texture/WeaponMasterWord/ñ≥.png", &pWmFontIds[ñ≥]);
		RoadTexture("Texture/WeaponMasterWord/óê.png", &pWmFontIds[óê]);
		RoadTexture("Texture/WeaponMasterWord/ïï.png", &pWmFontIds[ïï]);
		RoadTexture("Texture/WeaponMasterWord/å∂.png", &pWmFontIds[å∂]);
		RoadTexture("Texture/WeaponMasterWord/ì{.png", &pWmFontIds[ì{]);
		RoadTexture("Texture/WeaponMasterWord/ãS.png", &pWmFontIds[ãS]);
		RoadTexture("Texture/WeaponMasterWord/èu.png", &pWmFontIds[èu]);
		RoadTexture("Texture/WeaponMasterWord/ñh.png", &pWmFontIds[ñh]);
		RoadTexture("Texture/WeaponMasterWord/òT.png", &pWmFontIds[òT]);
		RoadTexture("Texture/WeaponMasterWord/ïˆ.png", &pWmFontIds[ïˆ]);
		RoadTexture("Texture/WeaponMasterWord/âÛ.png", &pWmFontIds[âÛ]);
		RoadTexture("Texture/WeaponMasterWord/â§.png", &pWmFontIds[â§]);
		RoadTexture("Texture/WeaponMasterWord/ãá.png", &pWmFontIds[ãá]);
		RoadTexture("Texture/WeaponMasterWord/ãz.png", &pWmFontIds[ãz]);
		RoadTexture("Texture/WeaponMasterWord/ã~.png", &pWmFontIds[ã~]);
		RoadTexture("Texture/WeaponMasterWord/éE.png", &pWmFontIds[éE]);
		RoadTexture("Texture/WeaponMasterWord/ñP.png", &pWmFontIds[ñP]);
		RoadTexture("Texture/WeaponMasterWord/í±.png", &pWmFontIds[í±]);
		RoadTexture("Texture/WeaponMasterWord/í¥.png", &pWmFontIds[í¥]);
		RoadTexture("Texture/WeaponMasterWord/âç.png", &pWmFontIds[âç]);
		RoadTexture("Texture/WeaponMasterWord/íG.png", &pWmFontIds[íG]);
		RoadTexture("Texture/WeaponMasterWord/èÇ.png", &pWmFontIds[èÇ]);
		RoadTexture("Texture/WeaponMasterWord/è|.png", &pWmFontIds[è|]);
		RoadTexture("Texture/WeaponMasterWord/ãæ.png", &pWmFontIds[ãæ]);
		RoadTexture("Texture/WeaponMasterWord/êk.png", &pWmFontIds[êk]);
		RoadTexture("Texture/WeaponMasterWord/ò@.png", &pWmFontIds[ò@]);
		RoadTexture("Texture/WeaponMasterWord/ê∂.png", &pWmFontIds[ê∂]);
		RoadTexture("Texture/WeaponMasterWord/ñΩ.png", &pWmFontIds[ñΩ]);
		RoadTexture("Texture/WeaponMasterWord/ôé.png", &pWmFontIds[ôé]);
		RoadTexture("Texture/WeaponMasterWord/äà.png", &pWmFontIds[äà]);
		RoadTexture("Texture/WeaponMasterWord/ê´.png", &pWmFontIds[ê´]);
		RoadTexture("Texture/WeaponMasterWord/â£.png", &pWmFontIds[â£]);
		RoadTexture("Texture/WeaponMasterWord/ç˜.png", &pWmFontIds[ç˜]);
		RoadTexture("Texture/WeaponMasterWord/ç|.png", &pWmFontIds[ç|]);
		RoadTexture("Texture/WeaponMasterWord/çc.png", &pWmFontIds[çc]);
		RoadTexture("Texture/WeaponMasterWord/ç”.png", &pWmFontIds[ç”]);
		RoadTexture("Texture/WeaponMasterWord/óZ.png", &pWmFontIds[óZ]);
		RoadTexture("Texture/WeaponMasterWord/îæ.png", &pWmFontIds[îæ]);
		RoadTexture("Texture/WeaponMasterWord/å≈.png", &pWmFontIds[å≈]);
		RoadTexture("Texture/WeaponMasterWord/åœ.png", &pWmFontIds[åœ]);
		RoadTexture("Texture/WeaponMasterWord/å«.png", &pWmFontIds[å«]);
		RoadTexture("Texture/WeaponMasterWord/êx.png", &pWmFontIds[êx]);
		RoadTexture("Texture/WeaponMasterWord/âr.png", &pWmFontIds[âr]);
		RoadTexture("Texture/WeaponMasterWord/óÜ.png", &pWmFontIds[óÜ]);
		RoadTexture("Texture/WeaponMasterWord/äÊ.png", &pWmFontIds[äÊ]);
		RoadTexture("Texture/WeaponMasterWord/ëÈ.png", &pWmFontIds[ëÈ]);
		RoadTexture("Texture/WeaponMasterWord/ãÁ.png", &pWmFontIds[ãÁ]);
		RoadTexture("Texture/WeaponMasterWord/îj.png", &pWmFontIds[îj]);
		RoadTexture("Texture/WeaponMasterWord/äD.png", &pWmFontIds[äD]);
		RoadTexture("Texture/WeaponMasterWord/êÌ.png", &pWmFontIds[êÌ]);
		RoadTexture("Texture/WeaponMasterWord/ç®.png", &pWmFontIds[ç®]);
		RoadTexture("Texture/WeaponMasterWord/ç¶.png", &pWmFontIds[ç¶]);
		RoadTexture("Texture/WeaponMasterWord/ûû.png", &pWmFontIds[ûû]);
		RoadTexture("Texture/WeaponMasterWord/çŸ.png", &pWmFontIds[çŸ]);
		RoadTexture("Texture/WeaponMasterWord/ñ¬.png", &pWmFontIds[ñ¬]);
		RoadTexture("Texture/WeaponMasterWord/å∏.png", &pWmFontIds[å∏]);
		RoadTexture("Texture/WeaponMasterWord/è∂.png", &pWmFontIds[è∂]);
		RoadTexture("Texture/WeaponMasterWord/ì±.png", &pWmFontIds[ì±]);
		RoadTexture("Texture/WeaponMasterWord/îπ.png", &pWmFontIds[îπ]);
		RoadTexture("Texture/WeaponMasterWord/òA.png", &pWmFontIds[òA]);
		RoadTexture("Texture/WeaponMasterWord/ñ≤.png", &pWmFontIds[ñ≤]);
		RoadTexture("Texture/WeaponMasterWord/éä.png", &pWmFontIds[éä]);
		RoadTexture("Texture/WeaponMasterWord/ê®.png", &pWmFontIds[ê®]);
		RoadTexture("Texture/WeaponMasterWord/ñC.png", &pWmFontIds[ñC]);
		RoadTexture("Texture/WeaponMasterWord/èP.png", &pWmFontIds[èP]);
		RoadTexture("Texture/WeaponMasterWord/ïñ.png", &pWmFontIds[ïñ]);
		RoadTexture("Texture/WeaponMasterWord/â‡.png", &pWmFontIds[â‡]);
		RoadTexture("Texture/WeaponMasterWord/ì≈.png", &pWmFontIds[ì≈]);
		RoadTexture("Texture/WeaponMasterWord/ëœ.png", &pWmFontIds[ëœ]);
		RoadTexture("Texture/WeaponMasterWord/ãR.png", &pWmFontIds[ãR]);
		RoadTexture("Texture/WeaponMasterWord/ü”.png", &pWmFontIds[ü”]);
		RoadTexture("Texture/WeaponMasterWord/‡Å.png", &pWmFontIds[‡Å]);
		RoadTexture("Texture/WeaponMasterWord/ôz.png", &pWmFontIds[ôz]);
		RoadTexture("Texture/WeaponMasterWord/ód.png", &pWmFontIds[ód]);
		RoadTexture("Texture/WeaponMasterWord/àÔ.png", &pWmFontIds[àÔ]);
		RoadTexture("Texture/WeaponMasterWord/ûô.png", &pWmFontIds[ûô]);
		RoadTexture("Texture/WeaponMasterWord/ãø.png", &pWmFontIds[ãø]);
		RoadTexture("Texture/WeaponMasterWord/èÉ.png", &pWmFontIds[èÉ]);
		RoadTexture("Texture/WeaponMasterWord/âã.png", &pWmFontIds[âã]);
		RoadTexture("Texture/WeaponMasterWord/è≈.png", &pWmFontIds[è≈]);
		RoadTexture("Texture/WeaponMasterWord/ëì.png", &pWmFontIds[ëì]);
		RoadTexture("Texture/WeaponMasterWord/ìÄ.png", &pWmFontIds[ìÄ]);
		RoadTexture("Texture/WeaponMasterWord/óí.png", &pWmFontIds[óí]);
		RoadTexture("Texture/WeaponMasterWord/êπ.png", &pWmFontIds[êπ]);
		RoadTexture("Texture/WeaponMasterWord/ìV.png", &pWmFontIds[ìV]);
		RoadTexture("Texture/WeaponMasterWord/êØ.png", &pWmFontIds[êØ]);
		RoadTexture("Texture/WeaponMasterWord/à≈.png", &pWmFontIds[à≈]);
		RoadTexture("Texture/WeaponMasterWord/âA.png", &pWmFontIds[âA]);
		RoadTexture("Texture/WeaponMasterWord/é◊.png", &pWmFontIds[é◊]);
		RoadTexture("Texture/WeaponMasterWord/ñª.png", &pWmFontIds[ñª]);
		RoadTexture("Texture/WeaponMasterWord/ë¬.png", &pWmFontIds[ë¬]);
		RoadTexture("Texture/WeaponMasterWord/ôô.png", &pWmFontIds[ôô]);
		RoadTexture("Texture/WeaponMasterWord/ôõ.png", &pWmFontIds[ôõ]);
		RoadTexture("Texture/WeaponMasterWord/åÇ.png", &pWmFontIds[åÇ]);
		RoadTexture("Texture/WeaponMasterWord/è’.png", &pWmFontIds[è’]);
		RoadTexture("Texture/WeaponMasterWord/ê˙.png", &pWmFontIds[ê˙]);
		RoadTexture("Texture/WeaponMasterWord/óÛ.png", &pWmFontIds[óÛ]);
		RoadTexture("Texture/WeaponMasterWord/óÙ.png", &pWmFontIds[óÙ]);
		RoadTexture("Texture/WeaponMasterWord/çñ.png", &pWmFontIds[çñ]);
		RoadTexture("Texture/WeaponMasterWord/ã….png", &pWmFontIds[ã…]);
		RoadTexture("Texture/WeaponMasterWord/ñ“.png", &pWmFontIds[ñ“]);
		RoadTexture("Texture/WeaponMasterWord/ê^.png", &pWmFontIds[ê^]);
		RoadTexture("Texture/WeaponMasterWord/ê‚.png", &pWmFontIds[ê‚]);
		RoadTexture("Texture/WeaponMasterWord/ç∞.png", &pWmFontIds[ç∞]);
		RoadTexture("Texture/WeaponMasterWord/èI.png", &pWmFontIds[èI]);
		RoadTexture("Texture/WeaponMasterWord/ã∂.png", &pWmFontIds[ã∂]);
		RoadTexture("Texture/WeaponMasterWord/ã≈.png", &pWmFontIds[ã≈]);
		RoadTexture("Texture/WeaponMasterWord/ê_.png", &pWmFontIds[ê_]);
		RoadTexture("Texture/WeaponMasterWord/ó≥.png", &pWmFontIds[ó≥]);
		RoadTexture("Texture/WeaponMasterWord/ó¥.png", &pWmFontIds[ó¥]);
		RoadTexture("Texture/WeaponMasterWord/ür.png", &pWmFontIds[ür]);
		RoadTexture("Texture/WeaponMasterWord/çÑ.png", &pWmFontIds[çÑ]);
		RoadTexture("Texture/WeaponMasterWord/îe.png", &pWmFontIds[îe]);
		RoadTexture("Texture/WeaponMasterWord/äâ.png", &pWmFontIds[äâ]);
		RoadTexture("Texture/WeaponMasterWord/‡ä.png", &pWmFontIds[‡ä]);
		RoadTexture("Texture/WeaponMasterWord/ò‘.png", &pWmFontIds[ò‘]);
		RoadTexture("Texture/WeaponMasterWord/êo.png", &pWmFontIds[êo]);
		RoadTexture("Texture/WeaponMasterWord/ñg.png", &pWmFontIds[ñg]);
		RoadTexture("Texture/WeaponMasterWord/óÉ.png", &pWmFontIds[óÉ]);
		RoadTexture("Texture/WeaponMasterWord/çå.png", &pWmFontIds[çå]);
		RoadTexture("Texture/WeaponMasterWord/çã.png", &pWmFontIds[çã]);
		isFirstFrame = 0;
	}


	return;
}

