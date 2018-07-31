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
	//火属性
	FIRE_ELEMENT,

	//水属性
	WATER_ELEMENT,

	//風属性
	WIND_ELEMENT,

	//光属性
	SHINING_ELEMENT,

	//闇属性
	DARKNESS_ELEMENT,

	//属性なし
	VOID_ELEMENT,
	
	//特殊属性の最大値
	ELEMENT_ATTRIBUTES_MAX
};

//武器などによる物理属性列挙体
enum ATTACK_ATTRIBUTE
{
	//斬属性
	SLASH_ATTACK,

	//打属性
	SMASH_ATTACK,

	//貫属性
	PENETRATION_ATTACK,

	//属性なし
	VOID_ATTACK,

	//物理属性の最大数
	ATTACK_ATTRIBUTES_MAX
};

//シーンを操作する
extern SCENE scene;

//メッセージループでループさせる関数
void MainFunction(void);
