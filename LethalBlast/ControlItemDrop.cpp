#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlMagicKnightMainGame.h"

bool CheckDropItem(WordData* pMagicKnightWordDatas, MAGIC_KNIGHT_WORD wordId,int probabilityParcent)
{
	int probability = (100 / probabilityParcent);

	bool notDropedItem = rand() % probability;
	
	if (!notDropedItem)
	{
		pMagicKnightWordDatas[wordId].m_have = true;

		return true;
	}

	return false;
}
