#pragma once
#include"WinMain.h"

//テクスチャを識別するための列挙体
enum TEXTURE
{
	//背景0
	BACKGROUND_0_TEXTURE,

	//テクスチャの最大値
	TEXTURE_MAX
};

/*
*メインゲームシーンにおける描画関係
*(引数1)SCENE* シーンを操作するため変数のアドレスを渡す
*/
void RenderGame(SCENE* scene);
