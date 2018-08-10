#pragma once

#include "DX9Lib.h"
#include "ControlGame.h"
#include "RenderGame.h"
#include "WinMain.h"
#include "ControlWordListsAndTyping.h"

enum TYPING_FONT
{
	TYPING_FONT,

	RUBY_FONT,

	FONT_MAX,
};

enum ATTACK_EFFECT
{
	MAGIC_RASER_EFF,
	DARK_FLAME_EFF,
	FLAME_EFF,
	MULTI_SLASH_EFF,
	NEEDLE_BOMB_EFF,
	SHADOW_BALL_EFF,
	THROWN_EFF,
	WIND_EFF,
	EFF_MAX
};

/*
*リストの背景を描画する関数
*　※召喚士の背景はまだ作っていません
*(引数1)int* playerType	キャラ選択に列挙型を入れるための変数
*/
void WordListsAndTypingRender(int* playerType);

/*
*ウェポンマスターの背景関数
*/
void WeaponMasterBackGround(CustomVertex* WordListsImage, TEXTUREID* textureIds);

/*
*マジックナイトが打ち込めるフォントの描画
*(引数1)FONTID* fontIds フォントの情報を配列に詰める
*(引数2)WordData* magicKnigtWords	単語のデータをもらう
*(引数3)WordList* magicKnightWordLists	単語リストを描画する
*(引数4)MagicKnightAction* magicKnightAction	魔法剣士の必殺技情報
*(引数5)WordCandidate* wordCandidates	ルビの情報
*/
void RenderMasicKnightWordLists(FONTID* fontIds, WordData* magicKnigtWords, WordList* magicKnightWordLists, MagicKnightAction* magicKnightAction, WordCandidate* wordCandidates,int* wordNum, bool* endAttackEffect);

void RenderEffect(WordData* magicKnigtWords, WordList* magicKnightWordLists, MagicKnightAction* magicKnightAction, TEXTUREID* effectTexId, bool* endAttackEffect);