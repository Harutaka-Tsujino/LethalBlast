#pragma once
#include<windows.h>
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"

#define HAND_MAX 40
#define MK_ACTION_WORD_MAX 5
#define WM_ACTION_WORD_MAX 10
#define TEXT_MAX 60

enum MAIN_UNION_TEX
{
	洞窟_BACK,
	遺跡_BACK,
	森_BACK,
	HP_BAR,
	HP_COVER,
	PP_BAR,
	WORD_SELECT_EFFECT,
	WORD_BLACK_BACK,
	MAIN_UNION_TEX_MAX
};

enum ACTION_EFFECT
{
	FLASH_RAZER,
	FULL_BURST,
	DIVINE_SWORD,
	CHARGE,
	ASTRAL_RAZER,
	TARGET,
	SLASH_AE,
	SMASH_AE,
	PENE_AE,
	NONE_AE,
	TWIN_CYCLON_AE,
	TILANT_WING_AE,
	DARK_FRAME_AE,
	CHARGE_FORCE_AE,
	CRYSTAL_RAZER_AE,
	PHOENIX_AE,
	EYES_AE,
	SHADOW_BALL_AE,
	SPELL_AE,
	DORAGON_AE,
	ACTION_EFFECT_MAX,
};

enum MAIN_UNION_FONT
{
	ENEMY_NAME_FONT,
	ENEMY_ACTION_FONT,
	MAIN_UNION_FONT_MAX
};

enum MK_MAIN_TEX
{
	MK_CHARA,
	MK_CUT_IN,
	MK_WORD_SEAT,
	MK_ACTION_SEAT,
	MK_MAIN_TEX_MAX
};

enum WM_MAIN_TEX
{
	WM_CHARA,
	WM_CUT_IN,
	WM_WORD_SEAT,
	WM_ACTION_SEAT,
	WM_UNDER_ACTION,
	WM_MAIN_TEX_MAX
};

#define FLOOR_MAX 1

typedef struct
{
	int m_enemy[FLOOR_MAX];
	bool m_clear[FLOOR_MAX];
}StageData;

enum ENEMY
{
	エーレ・ツヴァイ,
	ヴィーヴル,
	影の少女たち,
	ケルベロス,
	ゲイザー,
	エンデュミオン,
	エクスキューショナー,
	シルトクレスタル,
	ENEMY_MAX
};

typedef struct
{
	char m_name[TEXT_MAX];
	UINT m_damage;
	int m_ability;
	int m_effectId;
}EnemyAction;

#define ENEMY_ACTION_MAX 5

typedef struct
{
	char m_name[TEXT_MAX];
	UINT m_maxHP;
	UINT m_currentHP;
	EnemyAction m_enemyAction[ENEMY_ACTION_MAX];
	int m_attackWeak;
	int m_elementWeak;
	int m_attackResist;
	int m_elementResist;
}EnemyData;

enum RESULT
{
	WIN=1,
	LOSE,
};

typedef struct
{
	int m_turn;
	
	bool m_useAction;
	int m_playerAction[WM_ACTION_WORD_MAX];
	int m_playerActionCurrent;
	int m_playerActionLimit;
	UINT m_playerActionDamage;
	int m_playerActionSkillsCurrent[SKILL_MAX];
	int m_playerActionSkillsPrev[SKILL_MAX];
	int m_playerActionElement;
	int m_playerActionAttack;
	int m_playerEffectId;

	int m_hand[HAND_MAX];
	int m_handPos[WM_ACTION_WORD_MAX];

	UINT m_playerHPCurrent;
	UINT m_playerHPTmp;
	UINT m_playerHPMax;

	int m_pPCurrent;
	int m_pPTmp;
	int m_pPMax;
	
	int m_result;

	EnemyData m_enemyData;
}BattleData;

typedef struct
{
	TEXTUREID m_tex;
	int m_segmentX;
	int m_segmentY;
	float m_effectScale;
	DWORD m_color;
}ActionEffectData;

typedef struct
{
	CustomVertex m_vertices[RECT_VERTEX_NUM];
	Vect m_homingVect;
	int m_count;
	int m_actionPos;
	bool m_valid;
}WordSelectEffect;

#define MAX_HP 120000
#define FIRST_ACTION_LIMIT 1

#define MK_MAX_PP 24
#define WM_MAX_PP 33

#define MK_COST_1_DAMAGE 1500000
#define MK_COST_1_PLUS__DAMAGE 50000

#define MK_COST_3_DAMAGE 3500000
#define MK_COST_3_PLUS__DAMAGE 45000

#define MK_COST_5_DAMAGE 5000000
#define MK_COST_5_PLUS__DAMAGE 40000

#define MK_COST_12_DAMAGE 11000000
#define MK_COST_12_PLUS__DAMAGE 25000

#define ELEMENT_WEAK 1.2f
#define ELEMENT_RESIST 0.7f

#define ATTACK_WEAK 1.1f
#define ATTACK_RESIST 0.8f

void OperateBattle(SCENE* scene, int playerChara, int selectedStage, int selectedDeck, Deck* pMKDeck, Deck* pWMDeck,
	WordData* pMKWordDatas, TEXTUREID* pMKWordTex, WordData* pWMWordDatas, TEXTUREID* pWMWordTex,
	EnemyData* pEnemyDatas, CustomVertex* pMouseCursorVertices);

bool InitOperateBattleDatas(BattleData* pBattleData, EnemyData* pEnemyDatas,
	StageData* pStageDatas, int selectedStage, int maxPP, int selectedDeck, Deck* pDeck,
	WordSelectEffect* pWordSelectEffects, int wordSelectEffectMax);

void InitStageData(StageData* pStageDatas);

void InitEnemyData(EnemyData* pEnemyDatas);

void InitHand(BattleData* pBattleData, Deck* pDeck, int selectedDeck);

void SetHandVertices(int frameCount, int startAnimatationFrame, ImagesCustomVertex* pHandVertices,
	float handPosX, float handPosY, float handWidth, float handHeight, float circulatePosX, int scrollSpeed, BattleData* pBattleData);

void SetActionWordVertices(ImagesCustomVertex* pActionWordVertices, int actionWordMax,
	float actionWordPosX, float actionWordPosY, float actionWordWidth, float actionWordHeight);

void SetActionWordVertices(ImagesCustomVertex* pActionWordVertices, int actionWordMax,
	float actionWordPosX, float actionWordPosY, float actionWordWidth, float actionWordHeight);

void IOAction(int frameCount, int startAnimatationFrame, CustomVertex* pMouseCursorVertices,
	ImagesCustomVertex* pHandVertices, float handWidth, float handHeight,
	ImagesCustomVertex* pActionWordVertices, float actionWordWidth, float actionWordHeight,
	WordData* pWordDatas, WordSelectEffect* pWordSelectEffect, int selectEffectMax, BattleData* pBattleData, int actionWordMax);

void SetEffect(WordSelectEffect* pWordSelectEffect, int selectEffectMax,
	ImagesCustomVertex* pHandVertices, float handWidth, float handHeight, int hand,
	ImagesCustomVertex* pActionWordVertices, float actionWordWidth, float actionWordHeight, int actionSpace);

void CalcActionDamage(BattleData* pBattleData, int actionWordMax,
	WordData* pWordDatas, ActionEffectData* pActionEffectDatas);

void CalcDamageBonusWithSkills(BattleData* pBattleData, int actionWordMax, WordData* pWordDatas);

void RenderActionSeat(int frameCount, int startAnimationFrame, TEXTUREID* pActionSeatTex);

void RenderActionWord(int actionWordMax, int wordSelectEffectMax, WordSelectEffect* pWordSelectEffect,
	BattleData* pBattleData, ImagesCustomVertex* pActionWordVertices, TEXTUREID* pWordTex, TEXTUREID* pUnionTex, int playerChara);

void StageActionWord(int battleFrameCount, int stageFrame, ImagesCustomVertex* pActionWordVertices,
	int actionWordMax, BattleData* pBattleData, TEXTUREID* pTextureId);

void RenderActionEffect(int actionEffectCount, int actionEffectBlank,
	float posX, float posY, float effectScale, ActionEffectData* pActionEffectData, DWORD color);

void ReduceEnemyHPGradually(int reduceEnemyHPFrame, BattleData* pBattleData);

void HealPlayerHPGradually(int healHPFrame, BattleData* pBattleData);

void ReducePlayerHPGradually(int reducePlayerHPFrame, BattleData* pBattleData);

void PrepareNextTurn(int* pBattleFrameCount, BattleData* pBattleData, int actionWordMax);

void DrawWordSelectEffect(WordSelectEffect* pWordSelectEffect, int wordSelectEffectMax,
	TEXTUREID* pWordSelectEffectTex);

void MoveSelectWordEffect(WordSelectEffect* pWordSelectEffect, int wordSelectEffectMax, int wordSelectEffectFrame);

void LoadOriDeck(WordData* pWordData, Deck* pDeck, const char* filePath);
