#pragma once

#define PI 3.1415.f

//シーンに関する列挙体
enum SCENE
{
	//タイトル
	TITLE_SCENE,

	//メインゲーム
	GAME_SCENE,

	//シーンの最大数
	SCENE_MAX
};

//シーンを操作する
extern SCENE scene;

//メッセージループでループさせる関数
void MainFunction(void);
