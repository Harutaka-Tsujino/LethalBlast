//#include"DX9Lib.h"
//#include"WinMain.h"
//#include"ControlCharaChoice.h"
//#include"ControlMagicKnightMainGame.h"
//
//void ControlModify(SCENE* scene, WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
//	ImagesCustomVertex* pChoiseWordCollisionsVertex, CustomVertex* pWordDatasBackVertices, CustomVertex* pEndModifyVertices, CustomVertex* pBackgroundVertices,
//	int* modifyWordBox, ImagesCustomVertex* modifyBoxVertices,CustomVertex* decideModify,bool* clickedWord)
//{
//	static int frameCount = -1;
//
//	if (frameCount == -1)
//	{
//		memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
//		ZeroMemory(modifyWordBox, sizeof(int) * MATERIALS_NUM);
//
//		frameCount = 0;
//	}
//
//	for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
//	{
//		CustomImageVerticies(modifyBoxVertices[modifyBox].ImageVertex, DISPLAY_WIDTH / 5.f + ((DISPLAY_WIDTH / 4.f)*(modifyBox)),
//			DISPLAY_HEIGHT -DISPLAY_HEIGHT / 5.8f, DISPLAY_WIDTH / 10.f, DISPLAY_WIDTH / 50.f);
//	}
//
//	CustomImageVerticies(decideModify, DISPLAY_WIDTH*0.65f, DISPLAY_HEIGHT-DISPLAY_HEIGHT / 8.f, DISPLAY_WIDTH / 20.f, DISPLAY_WIDTH / 40.f);
//
//	//マウス
//	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];
//
//	const float MOUSE_CURSOR_SCALE = 0.5f;
//	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);
//
//	const float WORD_COLLISION_SCALE_X = DISPLAY_WIDTH / 14;
//	const float WORD_COLLISION_SCALE_Y = WORD_COLLISION_SCALE_X / 5;
//
//	float listWordPosX = (float)(WORD_COLLISION_SCALE_X * 1.3);
//	float listWordPosY = WORD_COLLISION_SCALE_X;
//
//	const int WORD_NEW_LINE = 4;
//
//	memset(pChoiseWordCollisionsVertex, 0, sizeof(ImagesCustomVertex)*MAGIC_KNIGHT_WORD_MAX);
//
//	static int wordSlidePosY = 0;
//	const int SLIDE_SPEED = 40;
//
//	CustomImageVerticies(pWordDatasBackVertices, DISPLAY_WIDTH*0.875f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH*0.125f, DISPLAY_HEIGHT / 2.f, 0xFFF5F5F5);
//
//	CustomImageVerticies(pBackgroundVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*(0.65f + 0.175f), DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.175f, 0xFFFFD500);
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
//	if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
//	{
//		if (g_keyState.keyHold[DIK_COMMA] || g_mouseState.directInputMouseState.lZ>0)
//		{
//			wordSlidePosY += SLIDE_SPEED;
//		}
//
//		if (g_keyState.keyHold[DIK_PERIOD] || g_mouseState.directInputMouseState.lZ<0)
//		{
//			wordSlidePosY -= SLIDE_SPEED;
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
//			listWordPosX += (float)(WORD_COLLISION_SCALE_X * 2.3);
//
//			if (!((haveWordNum) % (WORD_NEW_LINE)))
//			{
//				listWordPosX = (float)(WORD_COLLISION_SCALE_X * 1.3);
//				listWordPosY += (float)(WORD_COLLISION_SCALE_X * 1.2);
//			}
//		}
//	}
//
//	CustomImageVerticies(pEndModifyVertices, DISPLAY_WIDTH*0.90f, DISPLAY_HEIGHT*0.90f, DISPLAY_WIDTH*0.025f, DISPLAY_HEIGHT*0.025f);
//
//	if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
//	{
//		for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
//		{
//			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
//			{
//				if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
//				{
//					for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
//					{
//						if (modifyWordBox[modifyBox] == 0)
//						{
//							if (modifyBox == 1 && modifyWordBox[0] == wordDatas)
//							{
//								break;
//							}
//
//							if (modifyBox == 0 && modifyWordBox[1] == wordDatas)
//							{
//								break;
//							}
//
//							modifyWordBox[modifyBox] = wordDatas;
//
//							clickedWord[wordDatas] = true;
//
//							break;
//						}
//					}
//				}
//			}
//		}
//
//		for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
//		{
//			if (RectToRectCollisionCheak(modifyBoxVertices[modifyBox].ImageVertex, mouseCursorCollisionVertex))
//			{
//				clickedWord[modifyWordBox[modifyBox]] = false;
//
//				modifyWordBox[modifyBox] = 0;
//			}
//		}
//
//		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, decideModify))
//		{
//			for (int modifyBox = 0; modifyBox < MATERIALS_NUM; ++modifyBox)
//			{
//				if (!modifyWordBox[modifyBox])
//				{
//					return;
//				}
//			}
//
//			for (int word = VOID_WORD + 1; word < MAGIC_KNIGHT_WORD_MAX; ++word)
//			{
//				if (pMagicKnightWordDatas[word].m_matterials[0] == modifyWordBox[0])
//				{
//					if (pMagicKnightWordDatas[word].m_matterials[1] == modifyWordBox[1])
//					{
//						pMagicKnightWordDatas[word].m_have = true;
//
//						break;
//					}
//				}
//
//				if (pMagicKnightWordDatas[word].m_matterials[0] == modifyWordBox[1])
//				{
//					if (pMagicKnightWordDatas[word].m_matterials[1] == modifyWordBox[0])
//					{
//						pMagicKnightWordDatas[word].m_have = true;
//
//						break;
//					}
//				}
//			}
//		}
//
//		if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pEndModifyVertices))
//		{
//			memset(clickedWord, 0, sizeof(bool)*MAGIC_KNIGHT_WORD_MAX);
//			memset(modifyWordBox, 0, sizeof(int)*MATERIALS_NUM);
//
//			*scene = HOME_SCENE;
//		}
//	}
//
//	return;
//}
