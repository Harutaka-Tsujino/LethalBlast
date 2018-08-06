#pragma once

#include "DX9Lib.h"
#include "ControlGame.h"
#include "RenderGame.h"
#include "WinMain.h"

/*
*リストの背景を描画する関数
*　※召喚士の背景はまだ作っていません
*/
void WordListsAndTypingRender();

/*
*ウェポンマスターの背景関数
*/
void WeaponMasterBackGround(CustomVertex* WordListsImage, TEXTUREID* textureIds);
