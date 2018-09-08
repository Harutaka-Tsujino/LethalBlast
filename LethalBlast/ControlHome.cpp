#define _CRT_SECURE_NO_WARNINGS
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"CharactarInfo.h"
#include"ControlHome.h"

void ControlHome(SCENE* scene, WordData* pMagicKnightWordDatas, PlayerDeck* pMagicKnightDecks,
	WordData* pWeaponMAsterWordDatas, PlayerDeck* pWeaponMasterDecks,
	CustomVertex* pDeckAlterPortal, CustomVertex* pModifyWordPortal, CustomVertex* pMainGamePortal,
	CustomVertex* pCharaChoicePortal, TEXTUREID* wordTexIds, TEXTUREID* weaponMasterWordIds, PLAYERTYPE* playerType,
	bool* initializedTex)
{
	static int frameCount = -1;
	
	switch (*playerType)
	{
	case WEAPON_MASTER:

		if (!(*initializedTex))
		{
			/*LoadWeaponMasterWordDatas(pWeaponMAsterWordDatas);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck1.csv", 0);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck2.csv", 1);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck3.csv", 2);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck4.csv", 3);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck5.csv", 4);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck6.csv", 5);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck7.csv", 6);
			WeaponMasterLoadDeck(pWeaponMAsterWordDatas, pWeaponMasterDecks, "Files/WMDeck/WMDeck8.csv", 7);*/
			LordTextureWeaponMaster(weaponMasterWordIds);
			isSuccess = soundsManager.AddFile("Audio/perusona.mp3", _T("bgm"));

			*initializedTex = true;
		}
		
		break;
	
	case MAGIC_KNIGHT:

		if (!(*initializedTex))
		{
			LoadMagicKnightWordDatas(pMagicKnightWordDatas);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck1.csv", 0);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck2.csv", 1);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck3.csv", 2);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck4.csv", 3);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck5.csv", 4);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck6.csv", 5);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck7.csv", 6);
			LoadDeck(pMagicKnightWordDatas, pMagicKnightDecks, "Files/Deck/MKDeck8.csv", 7);
			isSuccess = soundsManager.AddFile("Audio/perusona.mp3", _T("bgm"));

			RoadTexture("Texture/MKWord/VOID_WORD.png", &wordTexIds[VOID_WORD]);

			FILE* pWordTexPathsFile;

			pWordTexPathsFile = fopen("Files/TexturePaths/MKWordTexPaths.csv", "r");

			for (int word = VOID_WORD + 1; word < MAGIC_KNIGHT_WORD_MAX; ++word)
			{
				char mkWordPath[60];

				fscanf(pWordTexPathsFile, "%s,", mkWordPath);
				RoadTexture(mkWordPath, &wordTexIds[word]);
			}

			fclose(pWordTexPathsFile);

			*initializedTex = true;
		}

		break;
	}

	isSuccess = soundsManager.Start(_T("bgm"), true);

	//}EXJ[\
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
				SAFE_RELEASE(weaponMasterWordIds[word]);
			}

			for (int word = 0; word < MAGIC_KNIGHT_WORD_MAX; ++word)
			{
				SAFE_RELEASE(wordTexIds[word]);
			}
		}
	}

	return;
}

void LordTextureWeaponMaster(TEXTUREID* pWmFontIds)
{
	static int isFirstFrame = INIT_FRAME;

	if (isFirstFrame == INIT_FRAME)
	{
		RoadTexture("Texture/WeaponMasterWord/Î.png", &pWmFontIds[Î]);
		RoadTexture("Texture/WeaponMasterWord/M.png", &pWmFontIds[M]);
		RoadTexture("Texture/WeaponMasterWord/R.png", &pWmFontIds[R]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/F.png", &pWmFontIds[F]);
		RoadTexture("Texture/WeaponMasterWord/g.png", &pWmFontIds[g]);
		RoadTexture("Texture/WeaponMasterWord/Ô.png", &pWmFontIds[Ô]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Â.png", &pWmFontIds[Â]);
		RoadTexture("Texture/WeaponMasterWord/J.png", &pWmFontIds[J]);
		RoadTexture("Texture/WeaponMasterWord/X.png", &pWmFontIds[X]);
		RoadTexture("Texture/WeaponMasterWord/á.png", &pWmFontIds[á]);
		RoadTexture("Texture/WeaponMasterWord/â.png", &pWmFontIds[â]);
		RoadTexture("Texture/WeaponMasterWord/Î.png", &pWmFontIds[Î]);
		RoadTexture("Texture/WeaponMasterWord/ő.png", &pWmFontIds[ő]);
		RoadTexture("Texture/WeaponMasterWord/ž.png", &pWmFontIds[ž]);
		RoadTexture("Texture/WeaponMasterWord/Ă.png", &pWmFontIds[Ă]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ť.png", &pWmFontIds[Ť]);
		RoadTexture("Texture/WeaponMasterWord/n.png", &pWmFontIds[n]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/e.png", &pWmFontIds[e]);
		RoadTexture("Texture/WeaponMasterWord/Ř.png", &pWmFontIds[Ř]);
		RoadTexture("Texture/WeaponMasterWord/Ĺ.png", &pWmFontIds[Ĺ]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/@.png", &pWmFontIds[@]);
		RoadTexture("Texture/WeaponMasterWord/Ë.png", &pWmFontIds[Ë]);
		RoadTexture("Texture/WeaponMasterWord/î.png", &pWmFontIds[î]);
		RoadTexture("Texture/WeaponMasterWord/h.png", &pWmFontIds[h]);
		RoadTexture("Texture/WeaponMasterWord/Ü.png", &pWmFontIds[Ü]);
		RoadTexture("Texture/WeaponMasterWord/ó.png", &pWmFontIds[ó]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/V.png", &pWmFontIds[V]);
		RoadTexture("Texture/WeaponMasterWord/š.png", &pWmFontIds[š]);
		RoadTexture("Texture/WeaponMasterWord/ä.png", &pWmFontIds[ä]);
		RoadTexture("Texture/WeaponMasterWord/î.png", &pWmFontIds[î]);
		RoadTexture("Texture/WeaponMasterWord/Ž.png", &pWmFontIds[Ž]);
		RoadTexture("Texture/WeaponMasterWord/S.png", &pWmFontIds[S]);
		RoadTexture("Texture/WeaponMasterWord/ę.png", &pWmFontIds[ę]);
		RoadTexture("Texture/WeaponMasterWord/ç.png", &pWmFontIds[ç]);
		RoadTexture("Texture/WeaponMasterWord/V.png", &pWmFontIds[V]);
		RoadTexture("Texture/WeaponMasterWord/C.png", &pWmFontIds[C]);
		RoadTexture("Texture/WeaponMasterWord/[.png", &pWmFontIds[[]);
		RoadTexture("Texture/WeaponMasterWord/Ź.png", &pWmFontIds[Ź]);
		RoadTexture("Texture/WeaponMasterWord/S.png", &pWmFontIds[S]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/d.png", &pWmFontIds[d]);
		RoadTexture("Texture/WeaponMasterWord/|.png", &pWmFontIds[|]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/c.png", &pWmFontIds[c]);
		RoadTexture("Texture/WeaponMasterWord/^.png", &pWmFontIds[^]);
		RoadTexture("Texture/WeaponMasterWord/ë.png", &pWmFontIds[ë]);
		RoadTexture("Texture/WeaponMasterWord/ó.png", &pWmFontIds[ó]);
		RoadTexture("Texture/WeaponMasterWord/Q.png", &pWmFontIds[Q]);
		RoadTexture("Texture/WeaponMasterWord/ăć.png", &pWmFontIds[ăć]);
		RoadTexture("Texture/WeaponMasterWord/Ţ.png", &pWmFontIds[Ţ]);
		RoadTexture("Texture/WeaponMasterWord/¤.png", &pWmFontIds[¤]);
		RoadTexture("Texture/WeaponMasterWord/˝.png", &pWmFontIds[˝]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/č.png", &pWmFontIds[č]);
		RoadTexture("Texture/WeaponMasterWord/E.png", &pWmFontIds[E]);
		RoadTexture("Texture/WeaponMasterWord/n.png", &pWmFontIds[n]);
		RoadTexture("Texture/WeaponMasterWord/ň.png", &pWmFontIds[ň]);
		RoadTexture("Texture/WeaponMasterWord/á.png", &pWmFontIds[á]);
		RoadTexture("Texture/WeaponMasterWord/m.png", &pWmFontIds[m]);
		RoadTexture("Texture/WeaponMasterWord/ë.png", &pWmFontIds[ë]);
		RoadTexture("Texture/WeaponMasterWord/w.png", &pWmFontIds[w]);
		RoadTexture("Texture/WeaponMasterWord/~.png", &pWmFontIds[~]);
		RoadTexture("Texture/WeaponMasterWord/Ô.png", &pWmFontIds[Ô]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Â.png", &pWmFontIds[Â]);
		RoadTexture("Texture/WeaponMasterWord/].png", &pWmFontIds[]]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/~.png", &pWmFontIds[~]);
		RoadTexture("Texture/WeaponMasterWord/Z.png", &pWmFontIds[Z]);
		RoadTexture("Texture/WeaponMasterWord/O.png", &pWmFontIds[O]);
		RoadTexture("Texture/WeaponMasterWord/§.png", &pWmFontIds[§]);
		RoadTexture("Texture/WeaponMasterWord/č.png", &pWmFontIds[č]);
		RoadTexture("Texture/WeaponMasterWord/˝.png", &pWmFontIds[˝]);
		RoadTexture("Texture/WeaponMasterWord/t.png", &pWmFontIds[t]);
		RoadTexture("Texture/WeaponMasterWord/Ś.png", &pWmFontIds[Ś]);
		RoadTexture("Texture/WeaponMasterWord/Ó.png", &pWmFontIds[Ó]);
		RoadTexture("Texture/WeaponMasterWord/Ă.png", &pWmFontIds[Ă]);
		RoadTexture("Texture/WeaponMasterWord/r.png", &pWmFontIds[r]);
		RoadTexture("Texture/WeaponMasterWord/}.png", &pWmFontIds[}]);
		RoadTexture("Texture/WeaponMasterWord/_.png", &pWmFontIds[_]);
		RoadTexture("Texture/WeaponMasterWord/ß.png", &pWmFontIds[ß]);
		RoadTexture("Texture/WeaponMasterWord/°.png", &pWmFontIds[°]);
		RoadTexture("Texture/WeaponMasterWord/|.png", &pWmFontIds[|]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/}.png", &pWmFontIds[}]);
		RoadTexture("Texture/WeaponMasterWord/ĺ.png", &pWmFontIds[ĺ]);
		RoadTexture("Texture/WeaponMasterWord/[.png", &pWmFontIds[[]);
		RoadTexture("Texture/WeaponMasterWord/a.png", &pWmFontIds[a]);
		RoadTexture("Texture/WeaponMasterWord/â.png", &pWmFontIds[â]);
		RoadTexture("Texture/WeaponMasterWord/].png", &pWmFontIds[]]);
		RoadTexture("Texture/WeaponMasterWord/ń.png", &pWmFontIds[ń]);
		RoadTexture("Texture/WeaponMasterWord/q.png", &pWmFontIds[q]);
		RoadTexture("Texture/WeaponMasterWord/ł.png", &pWmFontIds[ł]);
		RoadTexture("Texture/WeaponMasterWord/s.png", &pWmFontIds[s]);
		RoadTexture("Texture/WeaponMasterWord/e.png", &pWmFontIds[e]);
		RoadTexture("Texture/WeaponMasterWord/m.png", &pWmFontIds[m]);
		RoadTexture("Texture/WeaponMasterWord/ú.png", &pWmFontIds[ú]);
		RoadTexture("Texture/WeaponMasterWord/Ł.png", &pWmFontIds[Ł]);
		RoadTexture("Texture/WeaponMasterWord/ó.png", &pWmFontIds[ó]);
		RoadTexture("Texture/WeaponMasterWord/N.png", &pWmFontIds[N]);
		RoadTexture("Texture/WeaponMasterWord/ü.png", &pWmFontIds[ü]);
		RoadTexture("Texture/WeaponMasterWord/C.png", &pWmFontIds[C]);
		RoadTexture("Texture/WeaponMasterWord/Î.png", &pWmFontIds[Î]);
		RoadTexture("Texture/WeaponMasterWord/Ű.png", &pWmFontIds[Ű]);
		RoadTexture("Texture/WeaponMasterWord/Ć.png", &pWmFontIds[Ć]);
		RoadTexture("Texture/WeaponMasterWord/á.png", &pWmFontIds[á]);
		RoadTexture("Texture/WeaponMasterWord/â.png", &pWmFontIds[â]);
		RoadTexture("Texture/WeaponMasterWord/ż.png", &pWmFontIds[ż]);
		RoadTexture("Texture/WeaponMasterWord/Ĺ.png", &pWmFontIds[Ĺ]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/á.png", &pWmFontIds[á]);
		RoadTexture("Texture/WeaponMasterWord/˘.png", &pWmFontIds[˘]);
		RoadTexture("Texture/WeaponMasterWord/Ë.png", &pWmFontIds[Ë]);
		RoadTexture("Texture/WeaponMasterWord/_.png", &pWmFontIds[_]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ă.png", &pWmFontIds[Ă]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ą.png", &pWmFontIds[Ą]);
		RoadTexture("Texture/WeaponMasterWord/c.png", &pWmFontIds[c]);
		RoadTexture("Texture/WeaponMasterWord/ť.png", &pWmFontIds[ť]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Í.png", &pWmFontIds[Í]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/i.png", &pWmFontIds[i]);
		RoadTexture("Texture/WeaponMasterWord/g.png", &pWmFontIds[g]);
		RoadTexture("Texture/WeaponMasterWord/ň.png", &pWmFontIds[ň]);
		RoadTexture("Texture/WeaponMasterWord/ž.png", &pWmFontIds[ž]);
		RoadTexture("Texture/WeaponMasterWord/˘.png", &pWmFontIds[˘]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ö.png", &pWmFontIds[ö]);
		RoadTexture("Texture/WeaponMasterWord/q.png", &pWmFontIds[q]);
		RoadTexture("Texture/WeaponMasterWord/ë.png", &pWmFontIds[ë]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ä.png", &pWmFontIds[Ä]);
		RoadTexture("Texture/WeaponMasterWord/Ü.png", &pWmFontIds[Ü]);
		RoadTexture("Texture/WeaponMasterWord/C.png", &pWmFontIds[C]);
		RoadTexture("Texture/WeaponMasterWord/g.png", &pWmFontIds[g]);
		RoadTexture("Texture/WeaponMasterWord/Ź.png", &pWmFontIds[Ź]);
		RoadTexture("Texture/WeaponMasterWord/I.png", &pWmFontIds[I]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/čš.png", &pWmFontIds[čš]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ž.png", &pWmFontIds[ž]);
		RoadTexture("Texture/WeaponMasterWord/ů.png", &pWmFontIds[ů]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/P.png", &pWmFontIds[P]);
		RoadTexture("Texture/WeaponMasterWord/â.png", &pWmFontIds[â]);
		RoadTexture("Texture/WeaponMasterWord/M.png", &pWmFontIds[M]);
		RoadTexture("Texture/WeaponMasterWord/s.png", &pWmFontIds[s]);
		RoadTexture("Texture/WeaponMasterWord/e.png", &pWmFontIds[e]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ß.png", &pWmFontIds[ß]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/a.png", &pWmFontIds[a]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/f.png", &pWmFontIds[f]);
		RoadTexture("Texture/WeaponMasterWord/R.png", &pWmFontIds[R]);
		RoadTexture("Texture/WeaponMasterWord/r.png", &pWmFontIds[r]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ĺ.png", &pWmFontIds[ĺ]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ř.png", &pWmFontIds[Ř]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/o.png", &pWmFontIds[o]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ç.png", &pWmFontIds[ç]);
		RoadTexture("Texture/WeaponMasterWord/ě.png", &pWmFontIds[ě]);
		RoadTexture("Texture/WeaponMasterWord/ü.png", &pWmFontIds[ü]);
		RoadTexture("Texture/WeaponMasterWord/ł.png", &pWmFontIds[ł]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ś.png", &pWmFontIds[ś]);
		RoadTexture("Texture/WeaponMasterWord/{.png", &pWmFontIds[{]);
		RoadTexture("Texture/WeaponMasterWord/S.png", &pWmFontIds[S]);
		RoadTexture("Texture/WeaponMasterWord/u.png", &pWmFontIds[u]);
		RoadTexture("Texture/WeaponMasterWord/h.png", &pWmFontIds[h]);
		RoadTexture("Texture/WeaponMasterWord/T.png", &pWmFontIds[T]);
		RoadTexture("Texture/WeaponMasterWord/ö.png", &pWmFontIds[ö]);
		RoadTexture("Texture/WeaponMasterWord/ó.png", &pWmFontIds[ó]);
		RoadTexture("Texture/WeaponMasterWord/¤.png", &pWmFontIds[¤]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/z.png", &pWmFontIds[z]);
		RoadTexture("Texture/WeaponMasterWord/~.png", &pWmFontIds[~]);
		RoadTexture("Texture/WeaponMasterWord/E.png", &pWmFontIds[E]);
		RoadTexture("Texture/WeaponMasterWord/P.png", &pWmFontIds[P]);
		RoadTexture("Texture/WeaponMasterWord/ą.png", &pWmFontIds[ą]);
		RoadTexture("Texture/WeaponMasterWord/´.png", &pWmFontIds[´]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/G.png", &pWmFontIds[G]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/|.png", &pWmFontIds[|]);
		RoadTexture("Texture/WeaponMasterWord/ž.png", &pWmFontIds[ž]);
		RoadTexture("Texture/WeaponMasterWord/k.png", &pWmFontIds[k]);
		RoadTexture("Texture/WeaponMasterWord/@.png", &pWmFontIds[@]);
		RoadTexture("Texture/WeaponMasterWord/ś.png", &pWmFontIds[ś]);
		RoadTexture("Texture/WeaponMasterWord/˝.png", &pWmFontIds[˝]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ť.png", &pWmFontIds[Ť]);
		RoadTexture("Texture/WeaponMasterWord/Ł.png", &pWmFontIds[Ł]);
		RoadTexture("Texture/WeaponMasterWord/÷.png", &pWmFontIds[÷]);
		RoadTexture("Texture/WeaponMasterWord/|.png", &pWmFontIds[|]);
		RoadTexture("Texture/WeaponMasterWord/c.png", &pWmFontIds[c]);
		RoadTexture("Texture/WeaponMasterWord/Ó.png", &pWmFontIds[Ó]);
		RoadTexture("Texture/WeaponMasterWord/Z.png", &pWmFontIds[Z]);
		RoadTexture("Texture/WeaponMasterWord/ž.png", &pWmFontIds[ž]);
		RoadTexture("Texture/WeaponMasterWord/Ĺ.png", &pWmFontIds[Ĺ]);
		RoadTexture("Texture/WeaponMasterWord/Ď.png", &pWmFontIds[Ď]);
		RoadTexture("Texture/WeaponMasterWord/Ç.png", &pWmFontIds[Ç]);
		RoadTexture("Texture/WeaponMasterWord/x.png", &pWmFontIds[x]);
		RoadTexture("Texture/WeaponMasterWord/r.png", &pWmFontIds[r]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ć.png", &pWmFontIds[ć]);
		RoadTexture("Texture/WeaponMasterWord/é.png", &pWmFontIds[é]);
		RoadTexture("Texture/WeaponMasterWord/ç.png", &pWmFontIds[ç]);
		RoadTexture("Texture/WeaponMasterWord/j.png", &pWmFontIds[j]);
		RoadTexture("Texture/WeaponMasterWord/D.png", &pWmFontIds[D]);
		RoadTexture("Texture/WeaponMasterWord/í.png", &pWmFontIds[í]);
		RoadTexture("Texture/WeaponMasterWord/¨.png", &pWmFontIds[¨]);
		RoadTexture("Texture/WeaponMasterWord/Ś.png", &pWmFontIds[Ś]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ů.png", &pWmFontIds[Ů]);
		RoadTexture("Texture/WeaponMasterWord/Â.png", &pWmFontIds[Â]);
		RoadTexture("Texture/WeaponMasterWord/¸.png", &pWmFontIds[¸]);
		RoadTexture("Texture/WeaponMasterWord/ś.png", &pWmFontIds[ś]);
		RoadTexture("Texture/WeaponMasterWord/ą.png", &pWmFontIds[ą]);
		RoadTexture("Texture/WeaponMasterWord/š.png", &pWmFontIds[š]);
		RoadTexture("Texture/WeaponMasterWord/A.png", &pWmFontIds[A]);
		RoadTexture("Texture/WeaponMasterWord/˛.png", &pWmFontIds[˛]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/¨.png", &pWmFontIds[¨]);
		RoadTexture("Texture/WeaponMasterWord/C.png", &pWmFontIds[C]);
		RoadTexture("Texture/WeaponMasterWord/P.png", &pWmFontIds[P]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ŕ.png", &pWmFontIds[ŕ]);
		RoadTexture("Texture/WeaponMasterWord/Ĺ.png", &pWmFontIds[Ĺ]);
		RoadTexture("Texture/WeaponMasterWord/Ď.png", &pWmFontIds[Ď]);
		RoadTexture("Texture/WeaponMasterWord/R.png", &pWmFontIds[R]);
		RoadTexture("Texture/WeaponMasterWord/Ó.png", &pWmFontIds[Ó]);
		RoadTexture("Texture/WeaponMasterWord/ŕ.png", &pWmFontIds[ŕ]);
		RoadTexture("Texture/WeaponMasterWord/z.png", &pWmFontIds[z]);
		RoadTexture("Texture/WeaponMasterWord/d.png", &pWmFontIds[d]);
		RoadTexture("Texture/WeaponMasterWord/ď.png", &pWmFontIds[ď]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ż.png", &pWmFontIds[ż]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ĺ.png", &pWmFontIds[Ĺ]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/š.png", &pWmFontIds[š]);
		RoadTexture("Texture/WeaponMasterWord/V.png", &pWmFontIds[V]);
		RoadTexture("Texture/WeaponMasterWord/Ż.png", &pWmFontIds[Ż]);
		RoadTexture("Texture/WeaponMasterWord/Ĺ.png", &pWmFontIds[Ĺ]);
		RoadTexture("Texture/WeaponMasterWord/A.png", &pWmFontIds[A]);
		RoadTexture("Texture/WeaponMasterWord/×.png", &pWmFontIds[×]);
		RoadTexture("Texture/WeaponMasterWord/ť.png", &pWmFontIds[ť]);
		RoadTexture("Texture/WeaponMasterWord/Â.png", &pWmFontIds[Â]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/Ő.png", &pWmFontIds[Ő]);
		RoadTexture("Texture/WeaponMasterWord/ú.png", &pWmFontIds[ú]);
		RoadTexture("Texture/WeaponMasterWord/ó.png", &pWmFontIds[ó]);
		RoadTexture("Texture/WeaponMasterWord/ô.png", &pWmFontIds[ô]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/É.png", &pWmFontIds[É]);
		RoadTexture("Texture/WeaponMasterWord/Ň.png", &pWmFontIds[Ň]);
		RoadTexture("Texture/WeaponMasterWord/^.png", &pWmFontIds[^]);
		RoadTexture("Texture/WeaponMasterWord/â.png", &pWmFontIds[â]);
		RoadTexture("Texture/WeaponMasterWord/°.png", &pWmFontIds[°]);
		RoadTexture("Texture/WeaponMasterWord/I.png", &pWmFontIds[I]);
		RoadTexture("Texture/WeaponMasterWord/ś.png", &pWmFontIds[ś]);
		RoadTexture("Texture/WeaponMasterWord/Ĺ.png", &pWmFontIds[Ĺ]);
		RoadTexture("Texture/WeaponMasterWord/_.png", &pWmFontIds[_]);
		RoadTexture("Texture/WeaponMasterWord/ł.png", &pWmFontIds[ł]);
		RoadTexture("Texture/WeaponMasterWord/´.png", &pWmFontIds[´]);
		RoadTexture("Texture/WeaponMasterWord/r.png", &pWmFontIds[r]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/e.png", &pWmFontIds[e]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/ŕ.png", &pWmFontIds[ŕ]);
		RoadTexture("Texture/WeaponMasterWord/Ô.png", &pWmFontIds[Ô]);
		RoadTexture("Texture/WeaponMasterWord/o.png", &pWmFontIds[o]);
		RoadTexture("Texture/WeaponMasterWord/g.png", &pWmFontIds[g]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		RoadTexture("Texture/WeaponMasterWord/.png", &pWmFontIds[]);
		isFirstFrame = 0;
	}


	return;
}

