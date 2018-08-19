#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"RenderModifyWord.h"

void RenderModify(WordData* pMagicKnightWordDatas,ImagesCustomVertex* pChoiseWordCollisionsVertex,
	CustomVertex* pWordDatasBackVertices, CustomVertex* pEndModifyVertices, CustomVertex* pBackgroundVertices,
	int* modifyWordBox, ImagesCustomVertex* modifyBoxVertices, CustomVertex* decideModify, TEXTUREID* wordTexIds)
{
	static TEXTUREID modifyTexId[MODIFY_TEX_MAX];

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("Texture/AlterDeck/EndAlterDeck.png",&modifyTexId[END_MODIFY_TEX]);
		RoadTexture("Texture/AlterDeck/EndAlterDeck.png", &modifyTexId[DECIDE_MODIFY_TEX]);

		frameCount = 0;
	}

	for (int word = 0; word < MAGIC_KNIGHT_WORD_MAX; ++word)
	{
		DrawImage(pChoiseWordCollisionsVertex[word].ImageVertex, wordTexIds[word]);
	}

	DrawImage(pBackgroundVertices, NULL);

	for (int word = 0; word < 2; ++word)
	{
		DrawImage(modifyBoxVertices[word].ImageVertex, wordTexIds[modifyWordBox[word]]);
	}

	DrawImage(pWordDatasBackVertices, NULL);

	DrawImage(decideModify, modifyTexId[DECIDE_MODIFY_TEX]);

	DrawImage(pEndModifyVertices, modifyTexId[END_MODIFY_TEX]);

	return;
}
