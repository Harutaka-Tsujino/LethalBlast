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


	//�}�E�X�J�[�\��
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

	//���@���m�̃��[�h�f�[�^�[�����Ă���
	for (int wordsNum = VOID_WORD + 1; wordsNum < MAGIC_KNIGHT_WORD_MAX; ++wordsNum)
	{
		//�O���t�@�C���̑����𐔎��ɒ��������̂ň�x������ŕۊǂ���
		const int ELEMENTAL_WORDS_MAX = 10;
		char elemental[ELEMENTAL_WORDS_MAX];
		memset(elemental, 0, sizeof(char)*ELEMENTAL_WORDS_MAX);

		const int ATTACK_WORDS_MAX = 10;
		char attack[ATTACK_WORDS_MAX];
		memset(attack, 0, sizeof(char)*ATTACK_WORDS_MAX);

		//�O���t�@�C������̓���
		fscanf(pWordStatesFile, "%[^,],%[^,],%[^,],%*x,%*d,%*d,%*d,%*d,%d", pMagicKnightWordDatas[wordsNum].m_word, elemental, attack, 
			&pMagicKnightWordDatas[wordsNum].m_have);

		//�����̑Ώ�
		if (wordsNum > VOID_WORD + 1)
		{
			strcpy(&pMagicKnightWordDatas[wordsNum].m_word[0], &pMagicKnightWordDatas[wordsNum].m_word[1]);
		}

		//���ꑮ���̐�������
		for (int elementalNum = 0; elementalNum < ELEMENT_ATTRIBUTES_MAX; ++elementalNum)
		{
			//���������܂������ǂ���
			bool wasInputElemental = false;

			//�����𕶎���ŕۊǂ��Ă����̂Ő����ɕϊ�����
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

		//���������̐�������
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
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�M.png", &pWmFontIds[�M]);
		RoadTexture("Texture/WeaponMasterWord/�R.png", &pWmFontIds[�R]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�F.png", &pWmFontIds[�F]);
		RoadTexture("Texture/WeaponMasterWord/�g.png", &pWmFontIds[�g]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�J.png", &pWmFontIds[�J]);
		RoadTexture("Texture/WeaponMasterWord/�X.png", &pWmFontIds[�X]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�n.png", &pWmFontIds[�n]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�e.png", &pWmFontIds[�e]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�@.png", &pWmFontIds[�@]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�h.png", &pWmFontIds[�h]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�V.png", &pWmFontIds[�V]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�S.png", &pWmFontIds[�S]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�V.png", &pWmFontIds[�V]);
		RoadTexture("Texture/WeaponMasterWord/�C.png", &pWmFontIds[�C]);
		RoadTexture("Texture/WeaponMasterWord/�[.png", &pWmFontIds[�[]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�S.png", &pWmFontIds[�S]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�d.png", &pWmFontIds[�d]);
		RoadTexture("Texture/WeaponMasterWord/�|.png", &pWmFontIds[�|]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�c.png", &pWmFontIds[�c]);
		RoadTexture("Texture/WeaponMasterWord/�^.png", &pWmFontIds[�^]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�Q.png", &pWmFontIds[�Q]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�E.png", &pWmFontIds[�E]);
		RoadTexture("Texture/WeaponMasterWord/�n.png", &pWmFontIds[�n]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�m.png", &pWmFontIds[�m]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�w.png", &pWmFontIds[�w]);
		RoadTexture("Texture/WeaponMasterWord/�~.png", &pWmFontIds[�~]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�].png", &pWmFontIds[�]]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�~.png", &pWmFontIds[�~]);
		RoadTexture("Texture/WeaponMasterWord/�Z.png", &pWmFontIds[�Z]);
		RoadTexture("Texture/WeaponMasterWord/�O.png", &pWmFontIds[�O]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�t.png", &pWmFontIds[�t]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�r.png", &pWmFontIds[�r]);
		RoadTexture("Texture/WeaponMasterWord/�}.png", &pWmFontIds[�}]);
		RoadTexture("Texture/WeaponMasterWord/�_.png", &pWmFontIds[�_]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�|.png", &pWmFontIds[�|]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�}.png", &pWmFontIds[�}]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�[.png", &pWmFontIds[�[]);
		RoadTexture("Texture/WeaponMasterWord/�a.png", &pWmFontIds[�a]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�].png", &pWmFontIds[�]]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�q.png", &pWmFontIds[�q]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�s.png", &pWmFontIds[�s]);
		RoadTexture("Texture/WeaponMasterWord/�e.png", &pWmFontIds[�e]);
		RoadTexture("Texture/WeaponMasterWord/�m.png", &pWmFontIds[�m]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�N.png", &pWmFontIds[�N]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�C.png", &pWmFontIds[�C]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�_.png", &pWmFontIds[�_]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�c.png", &pWmFontIds[�c]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�i.png", &pWmFontIds[�i]);
		RoadTexture("Texture/WeaponMasterWord/�g.png", &pWmFontIds[�g]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�q.png", &pWmFontIds[�q]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�C.png", &pWmFontIds[�C]);
		RoadTexture("Texture/WeaponMasterWord/�g.png", &pWmFontIds[�g]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�I.png", &pWmFontIds[�I]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�.png", &pWmFontIds[�]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�P.png", &pWmFontIds[�P]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�M.png", &pWmFontIds[�M]);
		RoadTexture("Texture/WeaponMasterWord/�s.png", &pWmFontIds[�s]);
		RoadTexture("Texture/WeaponMasterWord/�e.png", &pWmFontIds[�e]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�a.png", &pWmFontIds[�a]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�f.png", &pWmFontIds[�f]);
		RoadTexture("Texture/WeaponMasterWord/�R.png", &pWmFontIds[�R]);
		RoadTexture("Texture/WeaponMasterWord/�r.png", &pWmFontIds[�r]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�o.png", &pWmFontIds[�o]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�{.png", &pWmFontIds[�{]);
		RoadTexture("Texture/WeaponMasterWord/�S.png", &pWmFontIds[�S]);
		RoadTexture("Texture/WeaponMasterWord/�u.png", &pWmFontIds[�u]);
		RoadTexture("Texture/WeaponMasterWord/�h.png", &pWmFontIds[�h]);
		RoadTexture("Texture/WeaponMasterWord/�T.png", &pWmFontIds[�T]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�z.png", &pWmFontIds[�z]);
		RoadTexture("Texture/WeaponMasterWord/�~.png", &pWmFontIds[�~]);
		RoadTexture("Texture/WeaponMasterWord/�E.png", &pWmFontIds[�E]);
		RoadTexture("Texture/WeaponMasterWord/�P.png", &pWmFontIds[�P]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�G.png", &pWmFontIds[�G]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�|.png", &pWmFontIds[�|]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�k.png", &pWmFontIds[�k]);
		RoadTexture("Texture/WeaponMasterWord/�@.png", &pWmFontIds[�@]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�|.png", &pWmFontIds[�|]);
		RoadTexture("Texture/WeaponMasterWord/�c.png", &pWmFontIds[�c]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�Z.png", &pWmFontIds[�Z]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�x.png", &pWmFontIds[�x]);
		RoadTexture("Texture/WeaponMasterWord/�r.png", &pWmFontIds[�r]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�j.png", &pWmFontIds[�j]);
		RoadTexture("Texture/WeaponMasterWord/�D.png", &pWmFontIds[�D]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�A.png", &pWmFontIds[�A]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�C.png", &pWmFontIds[�C]);
		RoadTexture("Texture/WeaponMasterWord/�P.png", &pWmFontIds[�P]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�R.png", &pWmFontIds[�R]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�z.png", &pWmFontIds[�z]);
		RoadTexture("Texture/WeaponMasterWord/�d.png", &pWmFontIds[�d]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�V.png", &pWmFontIds[�V]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�A.png", &pWmFontIds[�A]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�^.png", &pWmFontIds[�^]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�I.png", &pWmFontIds[�I]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�_.png", &pWmFontIds[�_]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�r.png", &pWmFontIds[�r]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�e.png", &pWmFontIds[�e]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/�o.png", &pWmFontIds[�o]);
		RoadTexture("Texture/WeaponMasterWord/�g.png", &pWmFontIds[�g]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		RoadTexture("Texture/WeaponMasterWord/��.png", &pWmFontIds[��]);
		isFirstFrame = 0;
	}


	return;
}

