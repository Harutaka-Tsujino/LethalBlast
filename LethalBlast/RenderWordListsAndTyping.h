#pragma once

#include "DX9Lib.h"
#include "ControlGame.h"
#include "RenderGame.h"
#include "WinMain.h"


enum Player
{
	MASIC_KNIGHT,
	WEAPON_MASTER,
	JOB_MAX,
};

/*
*リストの背景を描画する関数
*　※召喚士の背景はまだ作っていません
*/
void WordListsAndTypingRender();

/*
*ウェポンマスターの背景関数
*/
void WeaponMasterBackGround(CustomVertex* WordListsImage, TEXTUREID* textureIds);