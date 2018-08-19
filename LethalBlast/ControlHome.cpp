#define _CRT_SECURE_NO_WARNINGS
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlHome.h"

void ControlHome(SCENE* scene,WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	CustomVertex* pDeckAlterPortal, CustomVertex* pModifyWordPortal, CustomVertex* pMainGamePortal, CustomVertex* pCharaChoicePortal)
{
	static int frameCount = -1;

	if (frameCount == -1)
	{
		LoadMagicKnightWordDatas(pMagicKnightWordDatas);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck1.csv",0);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck2.csv",1);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck3.csv",2);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck4.csv",3);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck5.csv",4);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck6.csv",5);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck7.csv",6);
		LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck8.csv",7);

		frameCount = 0;
	}

	//マウスカーソル
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	const float MAIN_GAME_PORTAL_SCALE = DISPLAY_WIDTH / 10.f;
	CustomImageVerticies(pMainGamePortal, DISPLAY_WIDTH*0.625f, DISPLAY_HEIGHT*0.625f, MAIN_GAME_PORTAL_SCALE, MAIN_GAME_PORTAL_SCALE);

	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pMainGamePortal))
		{
			*scene = CHOSE_DECK_TO_BATTLE_SCENE;
		}
	}

	const float MID_PORTAL_SCALE_X = (float)(MAIN_GAME_PORTAL_SCALE * 0.8);
	const float MID_PORTAL_SCALE_Y = (float)(MAIN_GAME_PORTAL_SCALE * 0.4);

	CustomImageVerticies(pDeckAlterPortal, 
		(float)(DISPLAY_WIDTH*0.625f + MAIN_GAME_PORTAL_SCALE * 2), (float)(DISPLAY_HEIGHT*0.625f - MAIN_GAME_PORTAL_SCALE * 0.6),
		(float)MID_PORTAL_SCALE_X, (float)MID_PORTAL_SCALE_Y);

	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pDeckAlterPortal))
		{
			*scene = CHOSE_DECK_TO_ALTER_SCENE;
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
		}
	}

	CustomImageVerticies(pCharaChoicePortal, DISPLAY_WIDTH*0.04f, DISPLAY_HEIGHT*0.04f, DISPLAY_WIDTH*0.04f, DISPLAY_HEIGHT*0.04f);

	if (g_mouseState.mousePush[LEFT_CLICK])
	{
		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pCharaChoicePortal))
		{
			*scene = CHARA_CHOICE_SCENE;
		}
	}

	return;
}

void LoadMagicKnightWordDatas(WordData* pMagicKnightWordDatas)
{
	FILE* pWordStatesFile;

	fopen_s(&pWordStatesFile, "Files/WordStates/MagicKnightWordStates.csv", "r");

	memset(pMagicKnightWordDatas, 0, sizeof(WordData)*MAGIC_KNIGHT_WORD_MAX);

	//魔法剣士のワードデーターを入れていく
	for (int wordsNum = VOID_WORD + 1; wordsNum < MAGIC_KNIGHT_WORD_MAX; ++wordsNum)
	{
		//外部ファイルの属性を数字に直したいので一度文字列で保管する
		const int ELEMENTAL_WORDS_MAX = 10;
		char elemental[ELEMENTAL_WORDS_MAX];
		memset(elemental, 0, sizeof(char)*ELEMENTAL_WORDS_MAX);

		const int ATTACK_WORDS_MAX = 10;
		char attack[ATTACK_WORDS_MAX];
		memset(attack, 0, sizeof(char)*ATTACK_WORDS_MAX);

		//外部ファイルからの入力
		fscanf(pWordStatesFile, "%[^,],%[^,],%[^,],%x,%d,%d,%d,%d,%d", pMagicKnightWordDatas[wordsNum].m_word, elemental, attack, &pMagicKnightWordDatas[wordsNum].m_specialAbilities,
			&pMagicKnightWordDatas[wordsNum].m_matterials[0], &pMagicKnightWordDatas[wordsNum].m_matterials[1],
			&pMagicKnightWordDatas[wordsNum].m_cost, &pMagicKnightWordDatas[wordsNum].m_elementMultiPlus, &pMagicKnightWordDatas[wordsNum].m_have);

		//￥ｎの対処
		if (wordsNum > VOID_WORD + 1)
		{
			strcpy(&pMagicKnightWordDatas[wordsNum].m_word[0], &pMagicKnightWordDatas[wordsNum].m_word[1]);
		}

		//特殊属性の数だけ回す
		for (int elementalNum = 0; elementalNum < ELEMENT_ATTRIBUTES_MAX; ++elementalNum)
		{
			//属性が決まったかどうか
			bool wasInputElemental = false;

			//属性を文字列で保管していたので数字に変換する
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

		//物理属性の数だけ回す
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

void LoadDeck(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, const char* deckFilePath,int deckNum)
{
	FILE* pDeckFile;

	pDeckFile = fopen(deckFilePath, "r");

	memset(&pMagicKnightDecks[deckNum], 0, sizeof(MagicKnightDeck));

	fscanf(pDeckFile, "%[^,]", pMagicKnightDecks[deckNum].m_name);

	for (int deckWordNum = 0; deckWordNum < DECK_WORD_MAX; ++deckWordNum)
	{
		fseek(pDeckFile, 1, SEEK_CUR);
		fscanf(pDeckFile,"%d", &pMagicKnightDecks[deckNum].m_wordIds[deckWordNum]);

		int wordId = pMagicKnightDecks[deckNum].m_wordIds[deckWordNum];

		if (!wordId)
		{
			break;
		}

		pMagicKnightDecks[deckNum].m_elementTotals[(pMagicKnightWordDatas[wordId].m_element)] += 1;
		pMagicKnightDecks[deckNum].m_attackTotals[(pMagicKnightWordDatas[wordId].m_attack)]+=1;
		pMagicKnightDecks[deckNum].m_cost+=pMagicKnightWordDatas[wordId].m_cost;
		pMagicKnightDecks[deckNum].m_wordNum += 1;
	}

	fclose(pDeckFile);

	return;
}
