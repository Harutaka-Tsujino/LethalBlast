#pragma once

#include"DX9Lib.h"
#include"WinMain.h"


enum CHARA_CHOICE_TEX
{
	//キャラ選択画面の背景
	CHARA_CHOICE_BACKGROUND,

	//キャラ選択で使う最大画像枚数
	CHARA_CHOICE_TEX_MAX,
};
enum CHARA_CHOICE_FONT
{
	//ウェポンマスターの文字
	WEAPON_MASTER_FONT,

	//マジックナイトの文字
	MASIC_KNIGHT_FONT,

	//ネクロマンサーとサモナーの文字
	NECROMANCER_AND_SUMMONER_FONT,

	//キャラに使うフォント
	CHARA_CHOICE_FONT_MAX,
};

void RenderCharaChoice(SCENE* scene);

void RenderCharaChoiceInit(TEXTUREID* textureIds);

void RenderCharaChoiceBackGround(TEXTUREID* textureIds, FONTID* fontIds);
