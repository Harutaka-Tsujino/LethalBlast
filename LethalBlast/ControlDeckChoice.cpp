#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlDeckChoice.h"

void ControlChoiceDeck(SCENE* scene, SCENE destScene, ImagesCustomVertex* pChoiseDeckCollisionsVertex, int* pDeckNum)
{
	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		frameCount = 0;
	}

	const int MOVE_DECK_FRAME = 20;

	/*マウスカーソルとの当たり判定用の頂点設定 開始*/

	//マウス
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];

	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x, (float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	//デッキ
	const float DECK_COLLISON_WEIGHT = (float)(DISPLAY_WIDTH / 30);
	const float DECK_COLLISON_HEIGHT = DECK_COLLISON_WEIGHT * 2.f;
	const int DECKS_HALF_NUM = MAGIC_KNIGHT_DECKS_MAX / 2;
	const float DECK_COLLISION_POS_X = (float)(DISPLAY_WIDTH / (DECKS_HALF_NUM*2));
	const float DECK_COLLISION_POS_Y = (float)(DISPLAY_HEIGHT*0.195f+ DECK_COLLISON_HEIGHT);

	for (int deckNum = 0; deckNum < MAGIC_KNIGHT_DECKS_MAX; ++deckNum)
	{
		CustomImageVerticies(pChoiseDeckCollisionsVertex[deckNum].ImageVertex,
			DECK_COLLISION_POS_X +(DECK_COLLISION_POS_X*2*(deckNum%DECKS_HALF_NUM)*(frameCount/(float)MOVE_DECK_FRAME)), DECK_COLLISION_POS_Y+(DECK_COLLISION_POS_Y*1.592f*(deckNum / DECKS_HALF_NUM)*(frameCount / (float)MOVE_DECK_FRAME)),
			DECK_COLLISON_WEIGHT, DECK_COLLISON_HEIGHT);
	}
	/*マウスカーソルとの当たり判定用の頂点設定 終了*/

	if (frameCount <MOVE_DECK_FRAME)
	{
		frameCount++;
	}

	/*マウスカーソルとの当たり判定及びその後の処理 開始*/
	if (g_mouseState.mousePush[LEFT_CLICK] || g_keyState.keyPush[DIK_RETURN])
	{
		for (int deckNum = 0; deckNum < MAGIC_KNIGHT_DECKS_MAX; ++deckNum)
		{
			if (RectToRectCollisionCheak(mouseCursorCollisionVertex, pChoiseDeckCollisionsVertex[deckNum].ImageVertex))
			{
				*pDeckNum = deckNum;

				*scene = destScene;

				frameCount = 0;

				break;
			}
		}
	}
	/*マウスカーソルとの当たり判定及びその後の処理 終了*/

	return;
}
