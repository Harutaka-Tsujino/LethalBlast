//#include"DX9Lib.h"
//#include"WinMain.h"
//#include"ControlCharaChoice.h"
//#include"ControlMagicKnightMainGame.h"
//#include"ControlWeaponMasterAction.h"
//
//void ControlAlterDeck(SCENE* scene,WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks, ImagesCustomVertex* pChoiseWordCollisionsVertex,ImagesCustomVertex* pDeckComponentCollisionsVertex,
//	CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices,CustomVertex* pWordDatasBackVertices,int* pDeckNumToAlter,bool* clickedWord)
//{
//	static int frameCount = -1;
//
//	if (frameCount == -1)
//	{
//		memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
//
//		frameCount = 0;
//	}
//
//	//マウス
//	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];
//
//	const float MOUSE_CURSOR_SCALE = 0.5f;
//	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);
//
//	const float WORD_COLLISION_SCALE_X = (DISPLAY_WIDTH) / 14;
//	const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X / 5;
//
//	float listWordPosX = (float)(WORD_COLLISION_SCALE_X*1.3);
//	float listWordPosY = WORD_COLLISION_SCALE_X;
//
//	float deckComponentPosX = (float)(WORD_COLLISION_SCALE_X * 1.3);
//	float deckComponentPosY = DISPLAY_HEIGHT * 0.765f;
//
//	const int WORD_NEW_LINE = 4;
//	
//	memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*MAGIC_KNIGHT_WORD_MAX);
//	memset(pDeckComponentCollisionsVertex, 0, sizeof(ImagesCustomVertex)*MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX);
//
//	static int wordSlidePosY = 0;
//	const int SLIDE_SPEED = 40;
//
//	CustomImageVerticies(pBackgroundVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*(0.65f + 0.175f), DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.175f, 0xFFFFD500);
//	CustomImageVerticies(pWordDatasBackVertices, DISPLAY_WIDTH*0.875f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH*0.125f, DISPLAY_HEIGHT / 2.f, 0xFFF5F5F5);
//
//	if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
//	{
//		if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
//		{
//			if (g_keyState.keyHold[DIK_COMMA]||g_mouseState.directInputMouseState.lZ>0)
//			{
//				wordSlidePosY += SLIDE_SPEED;
//			}
//
//			if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ<0)
//			{
//				wordSlidePosY -= SLIDE_SPEED;
//			}
//		}
//	}
//
//	int haveWordNum = 0;
//
//	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
//	{
//		if (pMagicKnightWordDatas[wordDatas].m_have)
//		{
//			haveWordNum++;
//		}
//	}
//
//	if (wordSlidePosY > 0)
//	{
//		wordSlidePosY = 0;
//	}
//
//	if (wordSlidePosY < (int)(-WORD_COLLISION_SCALE_X * 1.2 * (haveWordNum / (WORD_NEW_LINE))))
//	{
//		wordSlidePosY = (int)(-WORD_COLLISION_SCALE_X * 1.2 * (haveWordNum / (WORD_NEW_LINE)));
//	}
//
//	haveWordNum = 0;
//
//	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
//	{
//		if (pMagicKnightWordDatas[wordDatas].m_have)
//		{
//			haveWordNum++;
//
//			CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, listWordPosX, listWordPosY + wordSlidePosY, WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);
//			
//			listWordPosX += (WORD_COLLISION_SCALE_X * 2.3f);
//
//			if (!((haveWordNum) % (WORD_NEW_LINE)))
//			{
//				listWordPosX = (float)(WORD_COLLISION_SCALE_X*1.3);
//				listWordPosY += (float)(WORD_COLLISION_SCALE_X*1.2);
//			}
//		}
//	}
//
//	static int deckComponentSlidePosX = 0;
//
//	if (RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
//	{
//		if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ>0)
//		{
//			deckComponentSlidePosX += SLIDE_SPEED;
//		}
//
//		if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ<0)
//		{
//			deckComponentSlidePosX -= SLIDE_SPEED;
//		}
//	}
//
//	const int DECK_COMPONENT_NEW_LINE = 20;
//
//	if (deckComponentSlidePosX > 0)
//	{
//		deckComponentSlidePosX = 0;
//	}
//
//	if (deckComponentSlidePosX <(int)(-WORD_COLLISION_SCALE_X*2*(DECK_COMPONENT_NEW_LINE-1)))
//	{
//		deckComponentSlidePosX = (int)(-WORD_COLLISION_SCALE_X * 2 * (DECK_COMPONENT_NEW_LINE-1));
//	}
//
//	for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
//	{
//		CustomImageVerticies(pDeckComponentCollisionsVertex[wordDatas].ImageVertex, deckComponentPosX + deckComponentSlidePosX, deckComponentPosY, 
//			WORD_COLLISION_SCALE_X, WORD_COLLISION_SCALE_Y);
//
//		deckComponentPosX += (float)(WORD_COLLISION_SCALE_X * 2.3);
//
//		if (!((wordDatas + 1) % (DECK_COMPONENT_NEW_LINE)))
//		{
//			deckComponentPosX = (float)(WORD_COLLISION_SCALE_X*1.3);
//			deckComponentPosY += (float)(WORD_COLLISION_SCALE_X * 0.9f);
//		}
//	}
//
//	CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);
//
//	for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
//	{
//		clickedWord[(pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = true;
//	}
//
//	if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
//	{
//		for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
//		{
//			if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
//			{
//				if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
//				{
//					if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
//					{
//						for (int deckSpace = 0; deckSpace < DECK_WORD_MAX; ++deckSpace)
//						{
//							if (!pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] && !clickedWord[wordDatas])
//							{
//								pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] = (MAGIC_KNIGHT_WORD)wordDatas;
//
//								clickedWord[wordDatas] = true;
//							}
//						}
//					}
//				}
//			}
//		}
//
//		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
//		{
//			if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
//			{
//				if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pDeckComponentCollisionsVertex[wordDatas].ImageVertex))
//				{
//					clickedWord[(pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = false;
//
//					pMagicKnightDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas] = VOID_WORD;
//				}
//			}
//		}
//
//		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
//		{
//			memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
//
//			*scene = HOME_SCENE;
//		}
//	}
//
//	return;
//}
//
//void ControlWeaponMasterAlterDeck(SCENE* scene, WeaponMasterWordData* pWeaponMasterWordDatas, WeaponMasterDeck* pWeaponMasterDecks, ImagesCustomVertex* pChoiseWordCollisionsVertex, ImagesCustomVertex* pDeckComponentCollisionsVertex,
//	CustomVertex* pEndDeckAlterVertices, CustomVertex* pBackgroundVertices, CustomVertex* pWordDatasBackVertices, int* pDeckNumToAlter, bool* clickedWord)
//{
//	static int frameCount = -1;
//
//	if (frameCount == -1)
//	{
//		memset(clickedWord, 0, sizeof(bool)*WEAPON_MASTER_WORD_MAX);
//
//		frameCount = 0;
//	}
//
//	//マウス
//	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];
//
//	const float MOUSE_CURSOR_SCALE = 0.5f;
//	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);
//
//	const int SLIDE_SPEED = 40;
//	
//	const float HAVE_WORD_COLLISION_XSCALE = DISPLAY_WIDTH / 38.f;
//	const float HAVE_WORD_COLLISION_YSCALE = HAVE_WORD_COLLISION_XSCALE;
//
//	float listWordPosX = DISPLAY_WIDTH / 2.5f;
//	float listWordPosY = DISPLAY_HEIGHT * 0.15f;
//
//	memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*WEAPON_MASTER_WORD_MAX);
//
//	//持っている文字リスト背景の頂点設定
//	CustomImageVerticies(pWordDatasBackVertices, (DISPLAY_WIDTH / 3.f) * 2, (DISPLAY_HEIGHT / 3.f), DISPLAY_WIDTH / 3.f, (DISPLAY_HEIGHT / 3.f));
//
//	static int wordSlidePosY = 0;
//	const int WORD_NEW_LINE = 5;
//
//	//持っている文字のスクロール処理
//	if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pWordDatasBackVertices))
//	{
//		if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ > 0)
//		{
//			wordSlidePosY += SLIDE_SPEED;
//		}
//
//		if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ < 0)
//		{
//			wordSlidePosY -= SLIDE_SPEED;
//		}
//	}
//
//	int haveWordNum = 0;
//
//	for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
//	{
//		if (pWeaponMasterWordDatas[wordDatas].m_have)
//		{
//			haveWordNum++;
//		}
//	}
//
//	if (wordSlidePosY > 0)
//	{
//		wordSlidePosY = 0;
//	}
//
//	if (wordSlidePosY < (int)(-HAVE_WORD_COLLISION_XSCALE * 2.8 * (haveWordNum / (WORD_NEW_LINE))))
//	{
//		wordSlidePosY = (int)(-HAVE_WORD_COLLISION_XSCALE * 2.8 * (haveWordNum / (WORD_NEW_LINE)));
//	}
//
//	haveWordNum = 0;
//
//	for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
//	{
//		if (pWeaponMasterWordDatas[wordDatas].m_have)
//		{
//			haveWordNum++;
//
//			CustomImageVerticies(pChoiseWordCollisionsVertex[wordDatas].ImageVertex, listWordPosX, listWordPosY + wordSlidePosY, HAVE_WORD_COLLISION_XSCALE, HAVE_WORD_COLLISION_YSCALE);
//
//			listWordPosX += (HAVE_WORD_COLLISION_XSCALE * 4.5f);
//
//			if (!((haveWordNum) % (WORD_NEW_LINE)))
//			{
//				listWordPosX = DISPLAY_WIDTH / 2.5f;
//				listWordPosY += (float)(HAVE_WORD_COLLISION_XSCALE * 3.f);
//			}
//		}
//	}
//
//	//デッキの文字のスクロール処理
//	static int deckComponentSlidePosY = 0;
//	static float upEffect = 23.f;
//
//	CustomImageVerticies(pBackgroundVertices, (DISPLAY_WIDTH / 6.f), DISPLAY_HEIGHT / 2.f + (upEffect), (DISPLAY_WIDTH / 6.f), DISPLAY_HEIGHT / 1.9f);
//
//	float deckComponentPosX = (DISPLAY_WIDTH / 3.f) - (DISPLAY_WIDTH / 4.5f);
//	float deckComponentPosY = (DISPLAY_HEIGHT * 0.15f);
//
//	if (RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
//	{
//		if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ>0)
//		{
//			deckComponentSlidePosY += SLIDE_SPEED;
//			upEffect = 23.f;
//		}
//
//		if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ<0)
//		{
//			deckComponentSlidePosY -= SLIDE_SPEED;
//			upEffect = 23.f;
//		}
//	}
//
//	const int DECK_COMPONENT_NEW_LINE = 2;
//
//	if (deckComponentSlidePosY > 0)
//	{
//		deckComponentSlidePosY = 0;
//	}
//
//	if (deckComponentSlidePosY <(int)(-HAVE_WORD_COLLISION_XSCALE * 62.5 * (DECK_COMPONENT_NEW_LINE - 1)))
//	{
//		deckComponentSlidePosY = (int)(-HAVE_WORD_COLLISION_XSCALE * 62.5 * (DECK_COMPONENT_NEW_LINE - 1));
//		upEffect = -23.f;
//	}
//
//	for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
//	{
//		CustomImageVerticies(pDeckComponentCollisionsVertex[wordDatas].ImageVertex, deckComponentPosX, deckComponentPosY + deckComponentSlidePosY,
//			HAVE_WORD_COLLISION_XSCALE, HAVE_WORD_COLLISION_YSCALE);
//
//		deckComponentPosX += (float)(HAVE_WORD_COLLISION_XSCALE * 4.f);
//
//		if (!((wordDatas + 1) % (DECK_COMPONENT_NEW_LINE)))
//		{
//			deckComponentPosX = (float)(HAVE_WORD_COLLISION_XSCALE * 4);
//			deckComponentPosY += (float)(HAVE_WORD_COLLISION_XSCALE * 4);
//		}
//	}
//
//	//完了ボタンの頂点設定
//	CustomImageVerticies(pEndDeckAlterVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);
//
//	for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
//	{
//		clickedWord[(pWeaponMasterDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = true;
//	}
//
//	if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
//	{
//		for (int wordDatas = 0; wordDatas < WEAPON_MASTER_WORD_MAX; ++wordDatas)
//		{
//			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
//			{
//				for (int deckSpace = 0; deckSpace < DECK_WORD_MAX; ++deckSpace)
//				{
//					if (!pWeaponMasterDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] && !clickedWord[wordDatas])
//					{
//						pWeaponMasterDecks[(*pDeckNumToAlter)].m_wordIds[deckSpace] = (WEAPON_MASTER_WORD_LISTS)wordDatas;
//
//						clickedWord[wordDatas] = true;
//					}
//				}
//			}
//		}
//
//		for (int wordDatas = 0; wordDatas < DECK_WORD_MAX; ++wordDatas)
//		{
//			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pDeckComponentCollisionsVertex[wordDatas].ImageVertex))
//			{
//				clickedWord[(pWeaponMasterDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas])] = false;
//
//				pWeaponMasterDecks[(*pDeckNumToAlter)].m_wordIds[wordDatas] = SPACE_WORD;
//			}	
//		}
//
//		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndDeckAlterVertices))
//		{
//			memset(clickedWord, 0, sizeof(bool)*WEAPON_MASTER_WORD_MAX);
//
//			*scene = HOME_SCENE;
//		}
//	}
//
//	return;
//}