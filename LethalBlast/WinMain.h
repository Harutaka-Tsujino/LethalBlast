#pragma once

#define PI 3.1415f

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

//炎属性などの特殊属性列挙体
enum ELEMENT_ATTRIBUTE
{
	//特殊属性の最大値
	ELEMENT_ATTRIBUTE_MAX
};

//武器などによる物理属性列挙体
enum ATTACK_ATTRIBUTE
{
	//物理属性の最大数
	ATTACK_ATTRIBUTE_MAX
};

//シーンを操作する
extern SCENE scene;

//メッセージループでループさせる関数
void MainFunction(void);
