#pragma once

#include"WinMain.h"
#include"ControlTitle.h"
#include"DX9Lib.h"

enum TITLETEX
{
	//タイトル背景
	TITLE_BG_TEX,

	//タイトルロゴ
	TITLE_ROGO_TEX,

	//タイトルで使う画像の最大枚数
	TITLE_TEX_MAX,
};

enum TITLEFONT
{
	//"PRESS ENTER"の文字フォント
	PRESS_ENTER_FONT,

	//タイトルで使うフォントの最大数
	TITLE_FONT_MAX,
};

/*
*メインのタイトルの描画関係の処理を行う関数
*(引数1)SCENE* シーンを操作するため変数のアドレスを渡す
*/
void TitleRender(SCENE *scene);

/*
*画像読み込みを行う関数
*(引数1)TEXTUREID*　配列の中身に読み込む画像を渡す
*/
void TitleRenderInit(TEXTUREID* textureIds);

/*
*タイトルロゴをフェードインの描画する関数
*(引数1)TEXTUREID*　配列の中身に読み込む画像を渡す
*/
void TitleRogoCanFadeIn(TEXTUREID* textureIds);

/*
*"press enter"の文字を描画する関数
*点滅処理も含まれてる
*(引数1)FONTID* 配列の中身に読み込む文字を出す
*/
void PressEnterFont(FONTID* fontIds);