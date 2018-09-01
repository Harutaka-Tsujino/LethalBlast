#pragma once

enum MK_MAIN_GAME_TEX
{
	MK_UNDER_WORD_BOARD,
	MK_ACTION_WORD_FRAME,
	MK_SELECT_WORD_EFFECT_TEX,
	MK_MAIN_GAME_TEX_MAX,
};

enum UI_TEX
{
	HP_BAR,
	CT_BAR,
	HP_FRAME,
	UI_TEX_MAX
};

void RenderMagicKnightMainGame(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex, TEXTUREID* wordTexIds,
	HomingEffect* pHominEffect, CustomVertex* resultMask, VSData* battleData, int enemyActionNum, int selectedStage, EnemyST pEnemyData);

void RenderWhileLoad(SCENE* scene, SCENE destScene, TEXTUREID* wordTexIds);
