#pragma once

#include"DX9Lib.h"
#include"WinMain.h"

/*
*キャラ選択のための関数
*(引数1)SCENE* scene	シーン移行するための変数
*(引数2)int* cursol		キャラ選択のための変数
*(引数3)PLAYERTYPE* playerType	キャラ選択の列挙型を入れる
*/
void ControlCharaChoice(SCENE* scene, int* cursol, PLAYERTYPE* playerType);

bool RectToRectCollisionCheak(CustomVertex* pObjA, CustomVertex* pObjB);
