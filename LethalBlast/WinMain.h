#pragma once

#include"DX9Lib.h"

#define PI 3.1415f
#define MULTI_BYTE 2
#define ALL_TEX_MAX 255
#define ALL_FONT_MAX 255
#define DEFAULT_COLOR 0xFFFFFFFF
#define WEPON_MASTER_CHOICE_TEXT_WIDTH 212

//初期化を行うときのフレームカウント
#define INIT_FRAME -1

//シーンに関する列挙体
enum SCENE
{
	//PV画面
	PV_SCENE,

	//タイトル画面
	TITLE_SCENE,

	//キャラ選択画面
	CHARA_CHOICE_SCENE,

	//待機画面
	HOME_SCENE,

	//デッキ改造のための選択画面
	CHOSE_DECK_TO_ALTER_SCENE,

	//デッキの改造画面
	ALTER_DECK_SCENE,

	//単語修飾画面
	MODIFY_WORD_SCENE,

	//戦闘のためのデッキ選択画面
	CHOSE_DECK_TO_BATTLE_SCENE,

	//デッキのロード
	LOAD_DECK_TO_PLAY,

	//メインゲーム画面
	GAME_SCENE,

	//シーンの最大数
	SCENE_MAX
};

enum PLAYERTYPE
{
	//魔法剣士
	MAGIC_KNIGHT,

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

typedef struct
{
	CustomVertex ImageVertex[RECT_VERTEX_NUM];
}ImagesCustomVertex;


//シーンを操作する
extern SCENE scene;

//メッセージループでループさせる関数
void MainFunction(void);
