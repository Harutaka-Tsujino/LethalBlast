#pragma once

#define PI 3.1415f
#define MULTI_BYTE 2
#define ALL_TEX_MAX 255
#define ALL_FONT_MAX 255

//シーンに関する列挙体
enum SCENE
{
	//PV
	PV_SCENE,

	//タイトル
	TITLE_SCENE,

	//キャラ選択画面
	CHARA_CHOICE_SCENE,

	//メインゲーム
	GAME_SCENE,

	//シーンの最大数
	SCENE_MAX
};

enum PLAYERTYPE
{
	//魔法剣士
	MASIC_KNIGHT,

	//ウェポンマスター
	WEAPON_MASTER,

	//ネクロマンサーとサモナー
	NECROMAMCERANDSUMMONUR,

	//ジョブの人数
	JOB_MAX
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

enum MOUSE_STATE
{
	//左クリック
	LEFT_CLICK,

	//右クリック
	RIGHT_CLICK
};

//シーンを操作する
extern SCENE scene;

//キャラ選択の時に使う
extern int g_playerType;

//メッセージループでループさせる関数
void MainFunction(void);
