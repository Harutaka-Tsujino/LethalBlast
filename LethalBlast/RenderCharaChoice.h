#pragma once

#include"DX9Lib.h"
#include"WinMain.h"


enum CHARA_CHOICE_TEX
{
	//キャラ選択のカーソル
	CHARA_CHOICE_CURSOL,

	//キャラ選択時に出てくるウェポンマスターの立ち絵
	CHARA_CHOICE_WEAPON_MASTER,

	//キャラ選択時に出てくるマジックナイトの立ち絵
	CHARA_CHOICE_MAGIC_KNIGHT,

	//キャラ選択で使う最大画像枚数
	CHARA_CHOICE_TEX_MAX,
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
*/
void RenderCharaChoiceInit(TEXTUREID* textureIds);

/*
*画像やフォントの描画関数
*(引数1)TEXTUREID* textureIds	画像情報をこの配列の中身に入れている
*(引数2)int* cursol	キャラ選択のための変数
*/
void RenderCharaChoiceBackGround(TEXTUREID* textureIds,int* cursol);

void RenderWhileLoad(SCENE* scene, SCENE destScene);
