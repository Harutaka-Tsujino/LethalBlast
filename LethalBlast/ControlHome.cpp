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

	//ƒ}ƒEƒXƒJ[ƒ\ƒ‹
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
		RoadTexture("Texture/WeaponMasterWord/‰Î.png", &pWmFontIds[‰Î]);
		RoadTexture("Texture/WeaponMasterWord/”M.png", &pWmFontIds[”M]);
		RoadTexture("Texture/WeaponMasterWord/”R.png", &pWmFontIds[”R]);
		RoadTexture("Texture/WeaponMasterWord/“”.png", &pWmFontIds[“”]);
		RoadTexture("Texture/WeaponMasterWord/˜F.png", &pWmFontIds[˜F]);
		RoadTexture("Texture/WeaponMasterWord/g.png", &pWmFontIds[g]);
		RoadTexture("Texture/WeaponMasterWord/Ô.png", &pWmFontIds[Ô]);
		RoadTexture("Texture/WeaponMasterWord/….png", &pWmFontIds[…]);
		RoadTexture("Texture/WeaponMasterWord/Â.png", &pWmFontIds[Â]);
		RoadTexture("Texture/WeaponMasterWord/‰J.png", &pWmFontIds[‰J]);
		RoadTexture("Texture/WeaponMasterWord/•X.png", &pWmFontIds[•X]);
		RoadTexture("Texture/WeaponMasterWord/á.png", &pWmFontIds[á]);
		RoadTexture("Texture/WeaponMasterWord/—â.png", &pWmFontIds[—â]);
		RoadTexture("Texture/WeaponMasterWord/—Î.png", &pWmFontIds[—Î]);
		RoadTexture("Texture/WeaponMasterWord/Œõ.png", &pWmFontIds[Œõ]);
		RoadTexture("Texture/WeaponMasterWord/–¾.png", &pWmFontIds[–¾]);
		RoadTexture("Texture/WeaponMasterWord/ˆÃ.png", &pWmFontIds[ˆÃ]);
		RoadTexture("Texture/WeaponMasterWord/”’.png", &pWmFontIds[”’]);
		RoadTexture("Texture/WeaponMasterWord/•.png", &pWmFontIds[•]);
		RoadTexture("Texture/WeaponMasterWord/ˆ«.png", &pWmFontIds[ˆ«]);
		RoadTexture("Texture/WeaponMasterWord/n.png", &pWmFontIds[n]);
		RoadTexture("Texture/WeaponMasterWord/“.png", &pWmFontIds[“]);
		RoadTexture("Texture/WeaponMasterWord/’e.png", &pWmFontIds[’e]);
		RoadTexture("Texture/WeaponMasterWord/Ø.png", &pWmFontIds[Ø]);
		RoadTexture("Texture/WeaponMasterWord/‘Å.png", &pWmFontIds[‘Å]);
		RoadTexture("Texture/WeaponMasterWord/Œ.png", &pWmFontIds[Œ]);
		RoadTexture("Texture/WeaponMasterWord/’@.png", &pWmFontIds[’@]);
		RoadTexture("Texture/WeaponMasterWord/“Ë.png", &pWmFontIds[“Ë]);
		RoadTexture("Texture/WeaponMasterWord/–î.png", &pWmFontIds[–î]);
		RoadTexture("Texture/WeaponMasterWord/Žh.png", &pWmFontIds[Žh]);
		RoadTexture("Texture/WeaponMasterWord/’Ü.png", &pWmFontIds[’Ü]);
		RoadTexture("Texture/WeaponMasterWord/‹ó.png", &pWmFontIds[‹ó]);
		RoadTexture("Texture/WeaponMasterWord/ˆŸ.png", &pWmFontIds[ˆŸ]);
		RoadTexture("Texture/WeaponMasterWord/V.png", &pWmFontIds[V]);
		RoadTexture("Texture/WeaponMasterWord/Œ¹.png", &pWmFontIds[Œ¹]);
		RoadTexture("Texture/WeaponMasterWord/‰ä.png", &pWmFontIds[‰ä]);
		RoadTexture("Texture/WeaponMasterWord/î.png", &pWmFontIds[î]);
		RoadTexture("Texture/WeaponMasterWord/Š®.png", &pWmFontIds[Š®]);
		RoadTexture("Texture/WeaponMasterWord/‘S.png", &pWmFontIds[‘S]);
		RoadTexture("Texture/WeaponMasterWord/ˆê.png", &pWmFontIds[ˆê]);
		RoadTexture("Texture/WeaponMasterWord/ç.png", &pWmFontIds[ç]);
		RoadTexture("Texture/WeaponMasterWord/”V.png", &pWmFontIds[”V]);
		RoadTexture("Texture/WeaponMasterWord/‹C.png", &pWmFontIds[‹C]);
		RoadTexture("Texture/WeaponMasterWord/[.png", &pWmFontIds[[]);
		RoadTexture("Texture/WeaponMasterWord/‘¬.png", &pWmFontIds[‘¬]);
		RoadTexture("Texture/WeaponMasterWord/S.png", &pWmFontIds[S]);
		RoadTexture("Texture/WeaponMasterWord/Ž‡.png", &pWmFontIds[Ž‡]);
		RoadTexture("Texture/WeaponMasterWord/“d.png", &pWmFontIds[“d]);
		RoadTexture("Texture/WeaponMasterWord/‹|.png", &pWmFontIds[‹|]);
		RoadTexture("Texture/WeaponMasterWord/‹€.png", &pWmFontIds[‹€]);
		RoadTexture("Texture/WeaponMasterWord/‹†.png", &pWmFontIds[‹†]);
		RoadTexture("Texture/WeaponMasterWord/Žc.png", &pWmFontIds[Žc]);
		RoadTexture("Texture/WeaponMasterWord/Œ^.png", &pWmFontIds[Œ^]);
		RoadTexture("Texture/WeaponMasterWord/ˆë.png", &pWmFontIds[ˆë]);
		RoadTexture("Texture/WeaponMasterWord/“ó.png", &pWmFontIds[“ó]);
		RoadTexture("Texture/WeaponMasterWord/ŽQ.png", &pWmFontIds[ŽQ]);
		RoadTexture("Texture/WeaponMasterWord/ãæ.png", &pWmFontIds[ãæ]);
		RoadTexture("Texture/WeaponMasterWord/ŒÞ.png", &pWmFontIds[ŒÞ]);
		RoadTexture("Texture/WeaponMasterWord/—¤.png", &pWmFontIds[—¤]);
		RoadTexture("Texture/WeaponMasterWord/Ž½.png", &pWmFontIds[Ž½]);
		RoadTexture("Texture/WeaponMasterWord/›.png", &pWmFontIds[›]);
		RoadTexture("Texture/WeaponMasterWord/‹è.png", &pWmFontIds[‹è]);
		RoadTexture("Texture/WeaponMasterWord/E.png", &pWmFontIds[E]);
		RoadTexture("Texture/WeaponMasterWord/’n.png", &pWmFontIds[’n]);
		RoadTexture("Texture/WeaponMasterWord/”ò.png", &pWmFontIds[”ò]);
		RoadTexture("Texture/WeaponMasterWord/Šá.png", &pWmFontIds[Šá]);
		RoadTexture("Texture/WeaponMasterWord/Žm.png", &pWmFontIds[Žm]);
		RoadTexture("Texture/WeaponMasterWord/‰ë.png", &pWmFontIds[‰ë]);
		RoadTexture("Texture/WeaponMasterWord/w.png", &pWmFontIds[w]);
		RoadTexture("Texture/WeaponMasterWord/Ž~.png", &pWmFontIds[Ž~]);
		RoadTexture("Texture/WeaponMasterWord/‰Ô.png", &pWmFontIds[‰Ô]);
		RoadTexture("Texture/WeaponMasterWord/Ž.png", &pWmFontIds[Ž]);
		RoadTexture("Texture/WeaponMasterWord/ŠÂ.png", &pWmFontIds[ŠÂ]);
		RoadTexture("Texture/WeaponMasterWord/–].png", &pWmFontIds[–]]);
		RoadTexture("Texture/WeaponMasterWord/Š.png", &pWmFontIds[Š]);
		RoadTexture("Texture/WeaponMasterWord/~.png", &pWmFontIds[~]);
		RoadTexture("Texture/WeaponMasterWord/Z.png", &pWmFontIds[Z]);
		RoadTexture("Texture/WeaponMasterWord/“O.png", &pWmFontIds[“O]);
		RoadTexture("Texture/WeaponMasterWord/“§.png", &pWmFontIds[“§]);
		RoadTexture("Texture/WeaponMasterWord/’è.png", &pWmFontIds[’è]);
		RoadTexture("Texture/WeaponMasterWord/”½.png", &pWmFontIds[”½]);
		RoadTexture("Texture/WeaponMasterWord/‹t.png", &pWmFontIds[‹t]);
		RoadTexture("Texture/WeaponMasterWord/‘¦.png", &pWmFontIds[‘¦]);
		RoadTexture("Texture/WeaponMasterWord/ˆÓ.png", &pWmFontIds[ˆÓ]);
		RoadTexture("Texture/WeaponMasterWord/ŒÃ.png", &pWmFontIds[ŒÃ]);
		RoadTexture("Texture/WeaponMasterWord/r.png", &pWmFontIds[r]);
		RoadTexture("Texture/WeaponMasterWord/Œ}.png", &pWmFontIds[Œ}]);
		RoadTexture("Texture/WeaponMasterWord/‰_.png", &pWmFontIds[‰_]);
		RoadTexture("Texture/WeaponMasterWord/“ß.png", &pWmFontIds[“ß]);
		RoadTexture("Texture/WeaponMasterWord/”°.png", &pWmFontIds[”°]);
		RoadTexture("Texture/WeaponMasterWord/‘|.png", &pWmFontIds[‘|]);
		RoadTexture("Texture/WeaponMasterWord/˜.png", &pWmFontIds[˜]);
		RoadTexture("Texture/WeaponMasterWord/œ.png", &pWmFontIds[œ]);
		RoadTexture("Texture/WeaponMasterWord/‹}.png", &pWmFontIds[‹}]);
		RoadTexture("Texture/WeaponMasterWord/Œå.png", &pWmFontIds[Œå]);
		RoadTexture("Texture/WeaponMasterWord/Œ[.png", &pWmFontIds[Œ[]);
		RoadTexture("Texture/WeaponMasterWord/œa.png", &pWmFontIds[œa]);
		RoadTexture("Texture/WeaponMasterWord/ˆâ.png", &pWmFontIds[ˆâ]);
		RoadTexture("Texture/WeaponMasterWord/“].png", &pWmFontIds[“]]);
		RoadTexture("Texture/WeaponMasterWord/‰ñ.png", &pWmFontIds[‰ñ]);
		RoadTexture("Texture/WeaponMasterWord/’q.png", &pWmFontIds[’q]);
		RoadTexture("Texture/WeaponMasterWord/ˆ³.png", &pWmFontIds[ˆ³]);
		RoadTexture("Texture/WeaponMasterWord/”s.png", &pWmFontIds[”s]);
		RoadTexture("Texture/WeaponMasterWord/“e.png", &pWmFontIds[“e]);
		RoadTexture("Texture/WeaponMasterWord/ƒm.png", &pWmFontIds[ƒm]);
		RoadTexture("Texture/WeaponMasterWord/•ú.png", &pWmFontIds[•ú]);
		RoadTexture("Texture/WeaponMasterWord/—£.png", &pWmFontIds[—£]);
		RoadTexture("Texture/WeaponMasterWord/ˆó.png", &pWmFontIds[ˆó]);
		RoadTexture("Texture/WeaponMasterWord/‹N.png", &pWmFontIds[‹N]);
		RoadTexture("Texture/WeaponMasterWord/”ü.png", &pWmFontIds[”ü]);
		RoadTexture("Texture/WeaponMasterWord/C.png", &pWmFontIds[C]);
		RoadTexture("Texture/WeaponMasterWord/‘Î.png", &pWmFontIds[‘Î]);
		RoadTexture("Texture/WeaponMasterWord/Û.png", &pWmFontIds[Û]);
		RoadTexture("Texture/WeaponMasterWord/“Æ.png", &pWmFontIds[“Æ]);
		RoadTexture("Texture/WeaponMasterWord/‹á.png", &pWmFontIds[‹á]);
		RoadTexture("Texture/WeaponMasterWord/‹â.png", &pWmFontIds[‹â]);
		RoadTexture("Texture/WeaponMasterWord/’¿.png", &pWmFontIds[’¿]);
		RoadTexture("Texture/WeaponMasterWord/Å.png", &pWmFontIds[Å]);
		RoadTexture("Texture/WeaponMasterWord/‚.png", &pWmFontIds[‚]);
		RoadTexture("Texture/WeaponMasterWord/’á.png", &pWmFontIds[’á]);
		RoadTexture("Texture/WeaponMasterWord/“¢.png", &pWmFontIds[“¢]);
		RoadTexture("Texture/WeaponMasterWord/ŽË.png", &pWmFontIds[ŽË]);
		RoadTexture("Texture/WeaponMasterWord/‘_.png", &pWmFontIds[‘_]);
		RoadTexture("Texture/WeaponMasterWord/‘ˆ.png", &pWmFontIds[‘ˆ]);
		RoadTexture("Texture/WeaponMasterWord/Ã.png", &pWmFontIds[Ã]);
		RoadTexture("Texture/WeaponMasterWord/Œˆ.png", &pWmFontIds[Œˆ]);
		RoadTexture("Texture/WeaponMasterWord/ˆ.png", &pWmFontIds[ˆ]);
		RoadTexture("Texture/WeaponMasterWord/‰¡.png", &pWmFontIds[‰¡]);
		RoadTexture("Texture/WeaponMasterWord/c.png", &pWmFontIds[c]);
		RoadTexture("Texture/WeaponMasterWord/».png", &pWmFontIds[»]);
		RoadTexture("Texture/WeaponMasterWord/‰“.png", &pWmFontIds[‰“]);
		RoadTexture("Texture/WeaponMasterWord/”Í.png", &pWmFontIds[”Í]);
		RoadTexture("Texture/WeaponMasterWord/–œ.png", &pWmFontIds[–œ]);
		RoadTexture("Texture/WeaponMasterWord/i.png", &pWmFontIds[i]);
		RoadTexture("Texture/WeaponMasterWord/g.png", &pWmFontIds[g]);
		RoadTexture("Texture/WeaponMasterWord/•ò.png", &pWmFontIds[•ò]);
		RoadTexture("Texture/WeaponMasterWord/‘¾.png", &pWmFontIds[‘¾]);
		RoadTexture("Texture/WeaponMasterWord/¢.png", &pWmFontIds[¢]);
		RoadTexture("Texture/WeaponMasterWord/‹.png", &pWmFontIds[‹]);
		RoadTexture("Texture/WeaponMasterWord/‰ö.png", &pWmFontIds[‰ö]);
		RoadTexture("Texture/WeaponMasterWord/q.png", &pWmFontIds[q]);
		RoadTexture("Texture/WeaponMasterWord/Žë.png", &pWmFontIds[Žë]);
		RoadTexture("Texture/WeaponMasterWord/”š.png", &pWmFontIds[”š]);
		RoadTexture("Texture/WeaponMasterWord/‰Š.png", &pWmFontIds[‰Š]);
		RoadTexture("Texture/WeaponMasterWord/Ä.png", &pWmFontIds[Ä]);
		RoadTexture("Texture/WeaponMasterWord/ŽÜ.png", &pWmFontIds[ŽÜ]);
		RoadTexture("Texture/WeaponMasterWord/ŠC.png", &pWmFontIds[ŠC]);
		RoadTexture("Texture/WeaponMasterWord/”g.png", &pWmFontIds[”g]);
		RoadTexture("Texture/WeaponMasterWord/—¬.png", &pWmFontIds[—¬]);
		RoadTexture("Texture/WeaponMasterWord/˜I.png", &pWmFontIds[˜I]);
		RoadTexture("Texture/WeaponMasterWord/‘š.png", &pWmFontIds[‘š]);
		RoadTexture("Texture/WeaponMasterWord/è¹.png", &pWmFontIds[è¹]);
		RoadTexture("Texture/WeaponMasterWord/•—.png", &pWmFontIds[•—]);
		RoadTexture("Texture/WeaponMasterWord/Ž¾.png", &pWmFontIds[Ž¾]);
		RoadTexture("Texture/WeaponMasterWord/ù.png", &pWmFontIds[ù]);
		RoadTexture("Texture/WeaponMasterWord/‰.png", &pWmFontIds[‰]);
		RoadTexture("Texture/WeaponMasterWord/‹P.png", &pWmFontIds[‹P]);
		RoadTexture("Texture/WeaponMasterWord/“â.png", &pWmFontIds[“â]);
		RoadTexture("Texture/WeaponMasterWord/‘M.png", &pWmFontIds[‘M]);
		RoadTexture("Texture/WeaponMasterWord/—s.png", &pWmFontIds[—s]);
		RoadTexture("Texture/WeaponMasterWord/‰e.png", &pWmFontIds[‰e]);
		RoadTexture("Texture/WeaponMasterWord/Ž€.png", &pWmFontIds[Ž€]);
		RoadTexture("Texture/WeaponMasterWord/ß.png", &pWmFontIds[ß]);
		RoadTexture("Texture/WeaponMasterWord/–‚.png", &pWmFontIds[–‚]);
		RoadTexture("Texture/WeaponMasterWord/Ža.png", &pWmFontIds[Ža]);
		RoadTexture("Texture/WeaponMasterWord/Œ•.png", &pWmFontIds[Œ•]);
		RoadTexture("Texture/WeaponMasterWord/’f.png", &pWmFontIds[’f]);
		RoadTexture("Texture/WeaponMasterWord/R.png", &pWmFontIds[R]);
		RoadTexture("Texture/WeaponMasterWord/‹r.png", &pWmFontIds[‹r]);
		RoadTexture("Texture/WeaponMasterWord/‘„.png", &pWmFontIds[‘„]);
		RoadTexture("Texture/WeaponMasterWord/‰å.png", &pWmFontIds[‰å]);
		RoadTexture("Texture/WeaponMasterWord/‹•.png", &pWmFontIds[‹•]);
		RoadTexture("Texture/WeaponMasterWord/Œƒ.png", &pWmFontIds[Œƒ]);
		RoadTexture("Texture/WeaponMasterWord/™‹.png", &pWmFontIds[™‹]);
		RoadTexture("Texture/WeaponMasterWord/‰Ø.png", &pWmFontIds[‰Ø]);
		RoadTexture("Texture/WeaponMasterWord/—….png", &pWmFontIds[—…]);
		RoadTexture("Texture/WeaponMasterWord/‘o.png", &pWmFontIds[‘o]);
		RoadTexture("Texture/WeaponMasterWord/•‘.png", &pWmFontIds[•‘]);
		RoadTexture("Texture/WeaponMasterWord/Žç.png", &pWmFontIds[Žç]);
		RoadTexture("Texture/WeaponMasterWord/Œì.png", &pWmFontIds[Œì]);
		RoadTexture("Texture/WeaponMasterWord/–ü.png", &pWmFontIds[–ü]);
		RoadTexture("Texture/WeaponMasterWord/–³.png", &pWmFontIds[–³]);
		RoadTexture("Texture/WeaponMasterWord/—.png", &pWmFontIds[—]);
		RoadTexture("Texture/WeaponMasterWord/••.png", &pWmFontIds[••]);
		RoadTexture("Texture/WeaponMasterWord/Œ¶.png", &pWmFontIds[Œ¶]);
		RoadTexture("Texture/WeaponMasterWord/“{.png", &pWmFontIds[“{]);
		RoadTexture("Texture/WeaponMasterWord/‹S.png", &pWmFontIds[‹S]);
		RoadTexture("Texture/WeaponMasterWord/u.png", &pWmFontIds[u]);
		RoadTexture("Texture/WeaponMasterWord/–h.png", &pWmFontIds[–h]);
		RoadTexture("Texture/WeaponMasterWord/˜T.png", &pWmFontIds[˜T]);
		RoadTexture("Texture/WeaponMasterWord/•ö.png", &pWmFontIds[•ö]);
		RoadTexture("Texture/WeaponMasterWord/‰ó.png", &pWmFontIds[‰ó]);
		RoadTexture("Texture/WeaponMasterWord/‰¤.png", &pWmFontIds[‰¤]);
		RoadTexture("Texture/WeaponMasterWord/‹‡.png", &pWmFontIds[‹‡]);
		RoadTexture("Texture/WeaponMasterWord/‹z.png", &pWmFontIds[‹z]);
		RoadTexture("Texture/WeaponMasterWord/‹~.png", &pWmFontIds[‹~]);
		RoadTexture("Texture/WeaponMasterWord/ŽE.png", &pWmFontIds[ŽE]);
		RoadTexture("Texture/WeaponMasterWord/–P.png", &pWmFontIds[–P]);
		RoadTexture("Texture/WeaponMasterWord/’±.png", &pWmFontIds[’±]);
		RoadTexture("Texture/WeaponMasterWord/’´.png", &pWmFontIds[’´]);
		RoadTexture("Texture/WeaponMasterWord/‰.png", &pWmFontIds[‰]);
		RoadTexture("Texture/WeaponMasterWord/’G.png", &pWmFontIds[’G]);
		RoadTexture("Texture/WeaponMasterWord/‚.png", &pWmFontIds[‚]);
		RoadTexture("Texture/WeaponMasterWord/|.png", &pWmFontIds[|]);
		RoadTexture("Texture/WeaponMasterWord/‹¾.png", &pWmFontIds[‹¾]);
		RoadTexture("Texture/WeaponMasterWord/k.png", &pWmFontIds[k]);
		RoadTexture("Texture/WeaponMasterWord/˜@.png", &pWmFontIds[˜@]);
		RoadTexture("Texture/WeaponMasterWord/¶.png", &pWmFontIds[¶]);
		RoadTexture("Texture/WeaponMasterWord/–½.png", &pWmFontIds[–½]);
		RoadTexture("Texture/WeaponMasterWord/™Ž.png", &pWmFontIds[™Ž]);
		RoadTexture("Texture/WeaponMasterWord/Šˆ.png", &pWmFontIds[Šˆ]);
		RoadTexture("Texture/WeaponMasterWord/«.png", &pWmFontIds[«]);
		RoadTexture("Texture/WeaponMasterWord/‰£.png", &pWmFontIds[‰£]);
		RoadTexture("Texture/WeaponMasterWord/÷.png", &pWmFontIds[÷]);
		RoadTexture("Texture/WeaponMasterWord/|.png", &pWmFontIds[|]);
		RoadTexture("Texture/WeaponMasterWord/c.png", &pWmFontIds[c]);
		RoadTexture("Texture/WeaponMasterWord/Ó.png", &pWmFontIds[Ó]);
		RoadTexture("Texture/WeaponMasterWord/—Z.png", &pWmFontIds[—Z]);
		RoadTexture("Texture/WeaponMasterWord/”¾.png", &pWmFontIds[”¾]);
		RoadTexture("Texture/WeaponMasterWord/ŒÅ.png", &pWmFontIds[ŒÅ]);
		RoadTexture("Texture/WeaponMasterWord/ŒÏ.png", &pWmFontIds[ŒÏ]);
		RoadTexture("Texture/WeaponMasterWord/ŒÇ.png", &pWmFontIds[ŒÇ]);
		RoadTexture("Texture/WeaponMasterWord/x.png", &pWmFontIds[x]);
		RoadTexture("Texture/WeaponMasterWord/‰r.png", &pWmFontIds[‰r]);
		RoadTexture("Texture/WeaponMasterWord/—†.png", &pWmFontIds[—†]);
		RoadTexture("Texture/WeaponMasterWord/Šæ.png", &pWmFontIds[Šæ]);
		RoadTexture("Texture/WeaponMasterWord/‘é.png", &pWmFontIds[‘é]);
		RoadTexture("Texture/WeaponMasterWord/‹ç.png", &pWmFontIds[‹ç]);
		RoadTexture("Texture/WeaponMasterWord/”j.png", &pWmFontIds[”j]);
		RoadTexture("Texture/WeaponMasterWord/ŠD.png", &pWmFontIds[ŠD]);
		RoadTexture("Texture/WeaponMasterWord/í.png", &pWmFontIds[í]);
		RoadTexture("Texture/WeaponMasterWord/¨.png", &pWmFontIds[¨]);
		RoadTexture("Texture/WeaponMasterWord/¦.png", &pWmFontIds[¦]);
		RoadTexture("Texture/WeaponMasterWord/žž.png", &pWmFontIds[žž]);
		RoadTexture("Texture/WeaponMasterWord/Ù.png", &pWmFontIds[Ù]);
		RoadTexture("Texture/WeaponMasterWord/–Â.png", &pWmFontIds[–Â]);
		RoadTexture("Texture/WeaponMasterWord/Œ¸.png", &pWmFontIds[Œ¸]);
		RoadTexture("Texture/WeaponMasterWord/¶.png", &pWmFontIds[¶]);
		RoadTexture("Texture/WeaponMasterWord/“±.png", &pWmFontIds[“±]);
		RoadTexture("Texture/WeaponMasterWord/”¹.png", &pWmFontIds[”¹]);
		RoadTexture("Texture/WeaponMasterWord/˜A.png", &pWmFontIds[˜A]);
		RoadTexture("Texture/WeaponMasterWord/–².png", &pWmFontIds[–²]);
		RoadTexture("Texture/WeaponMasterWord/ŽŠ.png", &pWmFontIds[ŽŠ]);
		RoadTexture("Texture/WeaponMasterWord/¨.png", &pWmFontIds[¨]);
		RoadTexture("Texture/WeaponMasterWord/–C.png", &pWmFontIds[–C]);
		RoadTexture("Texture/WeaponMasterWord/P.png", &pWmFontIds[P]);
		RoadTexture("Texture/WeaponMasterWord/•–.png", &pWmFontIds[•–]);
		RoadTexture("Texture/WeaponMasterWord/‰à.png", &pWmFontIds[‰à]);
		RoadTexture("Texture/WeaponMasterWord/“Å.png", &pWmFontIds[“Å]);
		RoadTexture("Texture/WeaponMasterWord/‘Ï.png", &pWmFontIds[‘Ï]);
		RoadTexture("Texture/WeaponMasterWord/‹R.png", &pWmFontIds[‹R]);
		RoadTexture("Texture/WeaponMasterWord/ŸÓ.png", &pWmFontIds[ŸÓ]);
		RoadTexture("Texture/WeaponMasterWord/à.png", &pWmFontIds[à]);
		RoadTexture("Texture/WeaponMasterWord/™z.png", &pWmFontIds[™z]);
		RoadTexture("Texture/WeaponMasterWord/—d.png", &pWmFontIds[—d]);
		RoadTexture("Texture/WeaponMasterWord/ˆï.png", &pWmFontIds[ˆï]);
		RoadTexture("Texture/WeaponMasterWord/ž™.png", &pWmFontIds[ž™]);
		RoadTexture("Texture/WeaponMasterWord/‹¿.png", &pWmFontIds[‹¿]);
		RoadTexture("Texture/WeaponMasterWord/ƒ.png", &pWmFontIds[ƒ]);
		RoadTexture("Texture/WeaponMasterWord/‰‹.png", &pWmFontIds[‰‹]);
		RoadTexture("Texture/WeaponMasterWord/Å.png", &pWmFontIds[Å]);
		RoadTexture("Texture/WeaponMasterWord/‘“.png", &pWmFontIds[‘“]);
		RoadTexture("Texture/WeaponMasterWord/“€.png", &pWmFontIds[“€]);
		RoadTexture("Texture/WeaponMasterWord/—’.png", &pWmFontIds[—’]);
		RoadTexture("Texture/WeaponMasterWord/¹.png", &pWmFontIds[¹]);
		RoadTexture("Texture/WeaponMasterWord/“V.png", &pWmFontIds[“V]);
		RoadTexture("Texture/WeaponMasterWord/¯.png", &pWmFontIds[¯]);
		RoadTexture("Texture/WeaponMasterWord/ˆÅ.png", &pWmFontIds[ˆÅ]);
		RoadTexture("Texture/WeaponMasterWord/‰A.png", &pWmFontIds[‰A]);
		RoadTexture("Texture/WeaponMasterWord/Ž×.png", &pWmFontIds[Ž×]);
		RoadTexture("Texture/WeaponMasterWord/–».png", &pWmFontIds[–»]);
		RoadTexture("Texture/WeaponMasterWord/‘Â.png", &pWmFontIds[‘Â]);
		RoadTexture("Texture/WeaponMasterWord/™™.png", &pWmFontIds[™™]);
		RoadTexture("Texture/WeaponMasterWord/™›.png", &pWmFontIds[™›]);
		RoadTexture("Texture/WeaponMasterWord/Œ‚.png", &pWmFontIds[Œ‚]);
		RoadTexture("Texture/WeaponMasterWord/Õ.png", &pWmFontIds[Õ]);
		RoadTexture("Texture/WeaponMasterWord/ú.png", &pWmFontIds[ú]);
		RoadTexture("Texture/WeaponMasterWord/—ó.png", &pWmFontIds[—ó]);
		RoadTexture("Texture/WeaponMasterWord/—ô.png", &pWmFontIds[—ô]);
		RoadTexture("Texture/WeaponMasterWord/–.png", &pWmFontIds[–]);
		RoadTexture("Texture/WeaponMasterWord/‹É.png", &pWmFontIds[‹É]);
		RoadTexture("Texture/WeaponMasterWord/–Ò.png", &pWmFontIds[–Ò]);
		RoadTexture("Texture/WeaponMasterWord/^.png", &pWmFontIds[^]);
		RoadTexture("Texture/WeaponMasterWord/â.png", &pWmFontIds[â]);
		RoadTexture("Texture/WeaponMasterWord/°.png", &pWmFontIds[°]);
		RoadTexture("Texture/WeaponMasterWord/I.png", &pWmFontIds[I]);
		RoadTexture("Texture/WeaponMasterWord/‹¶.png", &pWmFontIds[‹¶]);
		RoadTexture("Texture/WeaponMasterWord/‹Å.png", &pWmFontIds[‹Å]);
		RoadTexture("Texture/WeaponMasterWord/_.png", &pWmFontIds[_]);
		RoadTexture("Texture/WeaponMasterWord/—³.png", &pWmFontIds[—³]);
		RoadTexture("Texture/WeaponMasterWord/—´.png", &pWmFontIds[—´]);
		RoadTexture("Texture/WeaponMasterWord/Ÿr.png", &pWmFontIds[Ÿr]);
		RoadTexture("Texture/WeaponMasterWord/„.png", &pWmFontIds[„]);
		RoadTexture("Texture/WeaponMasterWord/”e.png", &pWmFontIds[”e]);
		RoadTexture("Texture/WeaponMasterWord/Š‰.png", &pWmFontIds[Š‰]);
		RoadTexture("Texture/WeaponMasterWord/àŠ.png", &pWmFontIds[àŠ]);
		RoadTexture("Texture/WeaponMasterWord/˜Ô.png", &pWmFontIds[˜Ô]);
		RoadTexture("Texture/WeaponMasterWord/o.png", &pWmFontIds[o]);
		RoadTexture("Texture/WeaponMasterWord/–g.png", &pWmFontIds[–g]);
		RoadTexture("Texture/WeaponMasterWord/—ƒ.png", &pWmFontIds[—ƒ]);
		RoadTexture("Texture/WeaponMasterWord/Œ.png", &pWmFontIds[Œ]);
		RoadTexture("Texture/WeaponMasterWord/‹.png", &pWmFontIds[‹]);
		isFirstFrame = 0;
	}


	return;
}

