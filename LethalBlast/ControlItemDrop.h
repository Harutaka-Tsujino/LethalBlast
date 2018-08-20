#pragma once

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlMagicKnightMainGame.h"

/*
アイテムのドロップを操作する関数
ワードデータ構造体の先頭アドレス
ドロップする単語の列挙子 ファイアーとか
パーセントでの確率100って入れたら絶対出る1って入れたら１パ－
*/
bool CheckDropItem(WordData* pMagicKnightWordDatas, MAGIC_KNIGHT_WORD wordId, int probabilityParcent);
