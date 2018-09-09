#include<windows.h>
#include<time.h>
#include"DX9Lib.h"
#include"ControlGame.h"
#include"RenderGame.h"
#include"WinMain.h"
#include"OperateTitle.h"
#include"OperatePV.h"
#include"ControlCharaChoice.h"
#include"RenderCharaChoice.h"
#include"ControlHome.h"
#include"RenderHome.h"
#include"ControlDeckChoice.h"
#include"RenderDeckChoice.h"
#include"ControlAlterDeck.h"
#include"RenderAlterDeck.h"
#include"ControlModifyWord.h"
#include"RenderModifyWord.h"
#include"ControlStageSelect.h"
#include"RenderStageSelect.h"
#include"OperateResult.h"
#include"OperateBattle.h"
#include"CharactarInfo.h"

SoundLib::SoundsManager soundsManager;
//音声の初期化
bool isSuccess = soundsManager.Initialize();

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	return CreateWindowAndRepeatToControlAndRender(hInst, "Lethal Blast", MainFunction, DISPLAY_WIDTH, DISPLAY_HEIGHT, FALSE, FALSE);
}

//メッセージループでループさせる関数
void MainFunction(void)
{
	static SCENE scene = (SCENE)0;
	
	static WordData wMWordDatas[WEAPON_MASTER_WORD_MAX];
	ImagesCustomVertex choiseWMWordCollisionsVertex[WEAPON_MASTER_WORD_MAX];
	static int cursol = 1;

	static PLAYERTYPE playerType = WEAPON_MASTER;
	static int frameCount = 0;
	static int page = 1;
	static WordData magicKnightWordDatas[MAGIC_KNIGHT_WORD_MAX];
	
	ImagesCustomVertex choiseDeckCollisionsVertex[MAGIC_KNIGHT_DECKS_MAX];
	ImagesCustomVertex choiseWordCollisionsVertex[MAGIC_KNIGHT_WORD_MAX];
	ImagesCustomVertex wMChoiseWordCollisionsVertex[WEAPON_MASTER_WORD_MAX];
	ImagesCustomVertex deckComponentCollisionsVertex[DECK_WORD_MAX];
	ImagesCustomVertex skillInfo[SKILL_MAX];
	static int deckNumToAlter = 0;
	CustomVertex endAlterDeckVertices[4];
	CustomVertex backgroundVertices[4];
	CustomVertex wordDatasBackVertices[4];
	CustomVertex deckAlterPortal[4];
	CustomVertex CostFont[4];
	CustomVertex modifyWordPortal[4];
	CustomVertex mainGamePortal[4];
	static CustomVertex charaChoicePortal[4];
	static TEXTUREID mKWordTex[MAGIC_KNIGHT_WORD_MAX];
	static TEXTUREID wMWordTex[WEAPON_MASTER_WORD_MAX];
	static int modifyWordBox[2];
	static bool clickedWord[MAGIC_KNIGHT_WORD_MAX];
	static bool RclickedWord[MAGIC_KNIGHT_WORD_MAX];
	static bool clickedWeaponMasterWord[WEAPON_MASTER_WORD_MAX];
	static bool wMRclickedWord[WEAPON_MASTER_WORD_MAX];
	ImagesCustomVertex stageSelectPortals[STAGE_MAX];
	static int selectedStage;
	static bool scrollEffect = false;
	static bool makeRandSeed = true;
	static CustomVertex resultMask[RECT_VERTEX_NUM];
	static bool initializedTex = false;
	static Deck mKDecks[DECK_MAX];
	static Deck wMDecks[DECK_MAX];
	static EnemyData enemyDatas[ENEMY_MAX];
	const float MOUSE_CURSOR_SCALE = 0.5f;
	CustomVertex mouseCursorCollisionVertex[RECT_VERTEX_NUM];
	CustomImageVerticies(mouseCursorCollisionVertex, (float)g_mouseState.absolutePos.x,
		(float)g_mouseState.absolutePos.y, MOUSE_CURSOR_SCALE, MOUSE_CURSOR_SCALE);

	static int selectedDeck;

	//シーン分岐
	switch (scene)
	{
	case PV_SCENE:
	
	if (makeRandSeed == true)
	{
		srand((UINT)time(NULL));

		makeRandSeed = false;
	}

		OperatePV(&scene);

		break;

	case TITLE_SCENE:

		OperateTitle(&scene);

		break;

	case SOUND_LOAD_SCENE:

		SoundLoad(&scene, CHARA_CHOICE_SCENE);

		break;

	case CHARA_CHOICE_SCENE:

		ControlCharaChoice(&scene, &cursol, &playerType);
		RenderCharaChoice(&scene, &cursol);

		break;

	case LOAD_TO_HOME_SCENE:

		RenderWhileLoad(&scene, HOME_SCENE);

		break;

	case HOME_SCENE:

		ControlHome(&scene, magicKnightWordDatas, mKDecks,
			wMWordDatas, wMDecks,
			deckAlterPortal, modifyWordPortal, mainGamePortal, charaChoicePortal, mKWordTex, wMWordTex, &playerType, &initializedTex);

		RenderHome(playerType,&scene, deckAlterPortal, modifyWordPortal, mainGamePortal, charaChoicePortal, mKWordTex, wMWordTex, &playerType, &initializedTex);

		break;

	case CHOSE_DECK_TO_ALTER_SCENE:

		ControlChoiceDeck(&scene, ALTER_DECK_SCENE, choiseDeckCollisionsVertex, &deckNumToAlter);
		RenderChoiceDeck(choiseDeckCollisionsVertex);

		break;

	case ALTER_DECK_SCENE:

		switch (playerType)
		{
		case WEAPON_MASTER:

			ControlAlterDeck(&scene, wMWordDatas, wMDecks, wMChoiseWordCollisionsVertex, deckComponentCollisionsVertex, skillInfo,
				endAlterDeckVertices, backgroundVertices, wordDatasBackVertices, &playerType, &deckNumToAlter, clickedWeaponMasterWord, wMRclickedWord);
			RenderAlterDeck(wMChoiseWordCollisionsVertex, deckComponentCollisionsVertex, skillInfo, endAlterDeckVertices, backgroundVertices, wordDatasBackVertices,
				&playerType, wMWordTex, wMWordDatas, wMDecks, &deckNumToAlter, clickedWeaponMasterWord, wMRclickedWord);

			break;

		case MAGIC_KNIGHT:
			ControlAlterDeck(&scene, magicKnightWordDatas, mKDecks, choiseWordCollisionsVertex, deckComponentCollisionsVertex, skillInfo,
				endAlterDeckVertices, backgroundVertices, wordDatasBackVertices, &playerType, &deckNumToAlter, clickedWord, RclickedWord);
			RenderAlterDeck(choiseWordCollisionsVertex, deckComponentCollisionsVertex, skillInfo, endAlterDeckVertices, backgroundVertices, wordDatasBackVertices,
				&playerType,mKWordTex, magicKnightWordDatas, mKDecks, &deckNumToAlter, clickedWord, RclickedWord);

			break;
		}
		
		break;

	case MODIFY_WORD_SCENE:

		//ControlModify(&scene, magicKnightWordDatas, magicKnightDecks,
		//	choiseWordCollisionsVertex, wordDatasBackVertices, endModifyVertices, backgroundVertices,
		//	modifyWordBox, modifyBoxVertices, decideModify, clickedWord);
		//RenderModify(magicKnightWordDatas, choiseWordCollisionsVertex,
		//	wordDatasBackVertices, endModifyVertices, backgroundVertices,
		//	modifyWordBox, modifyBoxVertices, decideModify, mKWordTex, clickedWord);

		break;

	case CHOSE_DECK_TO_BATTLE_SCENE:

		ControlChoiceDeck(&scene, LOAD_DECK_TO_PLAY_SCENE, choiseDeckCollisionsVertex, &selectedDeck);
		RenderChoiceDeck(choiseDeckCollisionsVertex);

		break;

	case LOAD_DECK_TO_PLAY_SCENE:

		RenderWhileLoad(&scene, GAME_SCENE);

		break;
		
	case SELECT_STAGE_SCENE:

		ControlStageSelect(&scene, stageSelectPortals, &selectedStage, charaChoicePortal);
		RenderStageSelect(stageSelectPortals, charaChoicePortal);

		break;

	case GAME_SCENE:

		OperateBattle(&scene, playerType, selectedStage, selectedDeck, mKDecks, wMDecks,
			magicKnightWordDatas, mKWordTex, wMWordDatas, wMWordTex,
			enemyDatas, mouseCursorCollisionVertex);

		break;

	case RESULT_SCENE:

		break;
	}

	return;
}
