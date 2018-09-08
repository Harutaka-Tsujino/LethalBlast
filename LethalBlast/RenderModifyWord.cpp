//#define _CRT_SECURE_NO_WARNINGS
//#include"DX9Lib.h"
//#include"WinMain.h"
//#include"ControlCharaChoice.h"
//#include"ControlMagicKnightMainGame.h"
//#include"RenderModifyWord.h"
//
//void RenderModify(WordData* pMagicKnightWordDatas,ImagesCustomVertex* pChoiseWordCollisionsVertex,
//	CustomVertex* pWordDatasBackVertices, CustomVertex* pEndModifyVertices, CustomVertex* pBackgroundVertices,
//	int* modifyWordBox, ImagesCustomVertex* modifyBoxVertices, CustomVertex* decideModify, TEXTUREID* mKWordTex, bool* clickedWord)
//{
//	static TEXTUREID modifyTexId[MODIFY_TEX_MAX];
//
//	static int frameCount = INIT_FRAME;
//
//	static FONTID fontId;
//
//	if (frameCount == INIT_FRAME)
//	{
//		RoadTexture("Texture/AlterDeck/EndAlterDeck.png",&modifyTexId[END_MODIFY_TEX]);
//		RoadTexture("Texture/AlterDeck/EndAlterDeck.png", &modifyTexId[DECIDE_MODIFY_TEX]);
//		RoadTexture("Texture/AlterDeck/DeckAlterBackground1.jpg", &modifyTexId[MODIFY_BACK_1_TEX]);
//		RoadTexture("Texture/AlterDeck/DeckAlterBackground2.png", &modifyTexId[MODIFY_BACK_2_TEX]);
//		RoadTexture("Texture/AlterDeck/DeckAlterBackground3.png", &modifyTexId[MODIFY_BACK_3_TEX]);
//		RoadTexture("Texture/AlterDeck/RedFrame.png", &modifyTexId[MODIFY_CLICKED_EFFECT_TEX]);
//		RoadTexture("Texture/AlterDeck/UnderAlterWordBoard.png", &modifyTexId[UNDER_MODIFY_WORD_BOARD_TEX]);
//		RoadTexture("Texture/Modify/ModifyTag.jpg", &modifyTexId[MODIFY_TAG_TEX]);
//
//		SetFont(DISPLAY_WIDTH / 70, DISPLAY_WIDTH / 70, "HGP明朝B", &fontId, 0);
//
//		frameCount = 0;
//	}
//
//	CustomVertex modifyBackVertices[4];
//	CustomImageVerticies(modifyBackVertices, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);
//
//	DrawImage(modifyBackVertices, modifyTexId[MODIFY_BACK_1_TEX]);
//
//	for (int word = 0; word < MAGIC_KNIGHT_WORD_MAX; ++word)
//	{
//		DrawImage(pChoiseWordCollisionsVertex[word].ImageVertex, modifyTexId[UNDER_MODIFY_WORD_BOARD_TEX]);
//		DrawImage(pChoiseWordCollisionsVertex[word].ImageVertex, mKWordTex[word]);
//
//		if (clickedWord[word])
//		{
//			DrawImage(pChoiseWordCollisionsVertex[word].ImageVertex, modifyTexId[MODIFY_CLICKED_EFFECT_TEX]);
//		}
//	}
//
//	DrawImage(modifyBackVertices, modifyTexId[MODIFY_BACK_2_TEX]);
//
//	for (int word = 0; word < 2; ++word)
//	{
//		DrawImage(modifyBoxVertices[word].ImageVertex, modifyTexId[UNDER_MODIFY_WORD_BOARD_TEX]);
//
//		if (modifyWordBox[word])
//		{
//			DrawImage(modifyBoxVertices[word].ImageVertex, mKWordTex[modifyWordBox[word]]);
//		}
//	}
//
//	DrawImage(modifyBackVertices, modifyTexId[MODIFY_BACK_3_TEX]);
//
//	/*マウスカーソルとの当たり判定用の頂点設定 開始*/
//
//	//マウスカーソル
//	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];
//
//	const float MOUSE_CURSOR_SCALE = 0.5f;
//	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);
//
//	const DWORD FONT_COLOR = 0xFF000000;
//
//	for (int wordDatas = 0; wordDatas < MAGIC_KNIGHT_WORD_MAX; ++wordDatas)
//	{
//		if (!RectToRectCollisionCheak(pBackgroundVertices, mouseCursorCollisionVertex))
//		{
//			if (!RectToRectCollisionCheak(pWordDatasBackVertices, mouseCursorCollisionVertex))
//			{
//				if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseWordCollisionsVertex[wordDatas].ImageVertex))
//				{
//					const int ELEMENT_POS_X = (int)(DISPLAY_WIDTH*0.8f);
//					const int ELEMENT_POS_Y = (int)(DISPLAY_HEIGHT*0.1f);
//
//					switch (pMagicKnightWordDatas[wordDatas].m_element)
//					{
//					case FIRE_ELEMENT:
//
//						WriteText(ELEMENT_POS_X, ELEMENT_POS_Y, "特殊 火", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//
//					case WATER_ELEMENT:
//
//						WriteText(ELEMENT_POS_X, ELEMENT_POS_Y, "特殊 水", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//
//					case WIND_ELEMENT:
//
//						WriteText(ELEMENT_POS_X, ELEMENT_POS_Y, "特殊 風", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//
//					case DARKNESS_ELEMENT:
//
//						WriteText(ELEMENT_POS_X, ELEMENT_POS_Y, "特殊 闇", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//
//					case SHINING_ELEMENT:
//
//						WriteText(ELEMENT_POS_X, ELEMENT_POS_Y, "特殊 光", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//					}
//
//					const int ATTACK_POS_X = (int)(DISPLAY_WIDTH*0.8f);
//					const int ATTACK_POS_Y = (int)(DISPLAY_HEIGHT*0.2f);
//
//					switch (pMagicKnightWordDatas[wordDatas].m_attack)
//					{
//					case SLASH_ATTACK:
//
//						WriteText(ATTACK_POS_X, ATTACK_POS_Y, "物理 斬", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//
//					case SMASH_ATTACK:
//
//						WriteText(ATTACK_POS_X, ATTACK_POS_Y, "物理 打", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//
//					case PENETRATION_ATTACK:
//
//						WriteText(ATTACK_POS_X, ATTACK_POS_Y, "物理 突", DT_CENTER, fontId, FONT_COLOR);
//
//						break;
//					}
//
//					char cost[20] = "コスト";
//					sprintf(&cost[6], "%d", pMagicKnightWordDatas[wordDatas].m_cost);
//
//					WriteText((int)(DISPLAY_WIDTH*0.8f), (int)(DISPLAY_HEIGHT*0.3f), cost, DT_CENTER, fontId, FONT_COLOR);
//
//					break;
//				}
//			}
//		}
//	}
//
//	CustomVertex deckAlterTag[RECT_VERTEX_NUM];
//	CustomImageVerticies(deckAlterTag, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.04f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT*0.04f);
//
//	DrawImage(deckAlterTag, modifyTexId[MODIFY_TAG_TEX]);
//
//	DrawImage(decideModify, modifyTexId[DECIDE_MODIFY_TEX]);
//
//	DrawImage(pEndModifyVertices, modifyTexId[END_MODIFY_TEX]);
//
//	return;
//}
