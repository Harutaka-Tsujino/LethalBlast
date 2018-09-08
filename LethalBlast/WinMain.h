#pragma once

#include"DX9Lib.h"

#define PI 3.1415f
#define MULTI_BYTE 2
#define ALL_TEX_MAX 255
#define ALL_FONT_MAX 255
#define DEFAULT_COLOR 0xFFFFFFFF
#define RECT_VERTEX_NUM 4 
#define DRAGON_EFECTIVE 0x00000001
#define BEAST_EFECTTIV 0x00000002
#define GUARD 0x00000004
#define HEAL 0x00000008
#define DELAY_DAMAGE_UP 0x00000010
#define DAMAGE_UP 0x00000020
#define CHACE_ATTACK 0x00000040
#define SUCIDE_ATTACK_DAMAGE_UP 0x00000080

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

	//ホーム画面へ行くときのロード画面
	LOAD_TO_HOME_SCENE,

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

	//デッキのロード画面
	LOAD_DECK_TO_PLAY_SCENE,

	//ステージのセレクトシーン
	SELECT_STAGE_SCENE,

	//メインゲーム画面
	GAME_SCENE,

	//リザルトシーン
	RESULT_SCENE,

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

enum WEAPON_MASTER_WORD_LISTS
{
	SPACE_WORD,
#include"Files/Enum/WeaponMasterWordEnum.txt"
};

enum MAGIC_KNIGHT_WORD
{
	VOID_WORD,
#include"Files/Enum/MagicKnightWordEnum.txt"
};

//単語の名前の文字数最大値
#define WORD_NAME_CHAR_MAX 40

//修飾時の素材の数
#define MATERIALS_NUM 2

#define SKILL_SLOT_MAX 4
#define SKILL_MAX 8

//単語のデータ
typedef struct
{
	//名前
	char m_word[WORD_NAME_CHAR_MAX];

	//特殊属性の識別子
	ELEMENT_ATTRIBUTE m_element;

	//物理属性の識別子
	ATTACK_ATTRIBUTE m_attack;

	int m_skillSlot[SKILL_SLOT_MAX];
	
	int m_currentCost;

	//コスト
	int m_costMax;

	//所持しているかどうか
	int m_have;

}WordData;

//デッキの名前の最大文字数
#define DECK_NAME_CHAR_MAX 40

//デッキに入れることができる単語の最大数
#define DECK_WORD_MAX 40

//デッキの保存できる最大数
#define MAGIC_KNIGHT_DECKS_MAX 8

//単語の手札最大数
#define HAND_WORD_MAX 40

#define DECK_MAX 8

typedef struct
{
	int m_wordId[DECK_WORD_MAX];
	int m_wordNum;
	int m_costMax;
}Deck;

//シーンを操作する
extern SCENE scene;

//メッセージループでループさせる関数
void MainFunction(void);

//サウンドを追加する
extern SoundLib::SoundsManager soundsManager;

//音声ファイルのオンオフ
extern bool isSuccess;