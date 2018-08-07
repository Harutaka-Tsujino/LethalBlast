#pragma once

#include"DX9Lib.h"
#include"WinMain.h"


enum CHARA_CHOICE_TEX
{
	//キャラ選択画面の背景
	CHARA_CHOICE_BACKGROUND,

	//キャラ選択のカーソル
	CHARA_CHOICE_CURSOL,

	//キャラ選択時に出てくるウェポンマスターの立ち絵
	CHARA_CHOICE_WEAPON_MASTER,

	//キャラ選択時に出てくるマジックナイトの立ち絵
	CHARA_CHOICE_MAGIC_KNIGHT,

	//キャラ選択時に出てくるネクロマンサーとサモナーの立ち絵
	CHARA_CHOICE_NECROMANCER_AND_SUMMONER,

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

/*
*下の関数をまとめた関数
*(引数1)SCENE* scene　シーン遷移のための変数
*(引数2)int* cursol	キャラ選択のための変数
*/
void RenderCharaChoice(SCENE* scene,int* cursol);

/*
*画像読み込みやフォントの設定をしている関数
*(引数1)TEXTUREID* textureIds	画像情報をこの配列の中身に入れている
*(引数2) FONTID* fontIds	フォントの情報をこの配列の中身に入れている
*/
void RenderCharaChoiceInit(TEXTUREID* textureIds, FONTID* fontIds);

/*
*画像やフォントの描画関数
*(引数1)TEXTUREID* textureIds	画像情報をこの配列の中身に入れている
*(引数2) FONTID* fontIds	フォントの情報をこの配列の中身に入れている
*(引数3)int* cursol	キャラ選択のための変数
*/
void RenderCharaChoiceBackGround(TEXTUREID* textureIds, FONTID* fontIds,int* cursol);
