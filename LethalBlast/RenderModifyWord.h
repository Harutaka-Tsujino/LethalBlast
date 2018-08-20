#pragma once
enum MODIFY_TEX
{
	END_MODIFY_TEX,
	DECIDE_MODIFY_TEX,
	MODIFY_TEX_MAX,
};

void RenderModify(WordData* pMagicKnightWordDatas, ImagesCustomVertex* pChoiseWordCollisionsVertex,
	CustomVertex* pWordDatasBackVertices, CustomVertex* pEndDeckMdifyVertices, CustomVertex* pBackgroundVertices,
	int* modifyWordBox, ImagesCustomVertex* modifyBoxVertices, CustomVertex* decideModify, TEXTUREID* wordTexIds);
