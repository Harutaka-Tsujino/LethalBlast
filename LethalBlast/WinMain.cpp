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
#include"ControlHP.h"
#include"RenderHP.h"
#include"ControlWeaponMasterAction.h"
#include"RenderWeaponMasterAction.h"
#include"ControlDeckChoice.h"
#include"RenderDeckChoice.h"
#include"ControlMagicKnightMainGame.h"
#include"RenderMagicKnigtMainGame.h"
#include"ControlAlterDeck.h"
#include"RenderAlterDeck.h"
#include"ControlHome.h"
#include"RenderHome.h"
#include"ControlModifyWord.h"
#include"RenderModifyWord.h"
#include"ControlStageSelect.h"
#include"RenderStageSelect.h"
#include"OperateResult.h"
#include"CharactarInfo.h"

SoundLib::SoundsManager soundsManager;
//音声の初期化
bool isSuccess = soundsManager.Initialize();

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	return CreateWindowAndRepeatToControlAndRender(hInst, "Lethal Blast", MainFunction, DISPLAY_WIDTH, DISPLAY_HEIGHT, TRUE , FALSE);
}

//メッセージループでループさせる関数
void MainFunction(void)
{
	static SCENE scene = (SCENE)0;

	static TEXTUREID textureIds[ALL_TEX_MAX];
	static FONTID fontIds[ALL_FONT_MAX];

	static WeaponMasterWordData weaponMasterWords[WEAPON_MASTER_WORD_MAX];
	static WeaponMasterDeck weaponMasterWordDecks[WEAPON_MASTER_DECK_MAX];
	static WeaponMasterActionData weaponMasterActionWords[WEAPON_MASTER_ACTION_LISTS];
	static ImagesCustomVertex weaponMasterDeckVerticies[DECK_WORD_MAX];
	static ImagesCustomVertex weaponMasterActionVerticies[WEAPON_MASTER_ACTION_LISTS];
	ImagesCustomVertex choiseWMWordCollisionsVertex[WEAPON_MASTER_WORD_MAX];
	static PlayerState player[JOB_MAX];
	static EnemyState enemy[ENEMY_TYPE_MAX];
	static int wordNum = 0;
	static bool endAttackEffect = false;
	static int cursol = 1;

	static PLAYERTYPE playerType = WEAPON_MASTER;
	static int playerATKDamage = 0;
	static ENEMY_TYPE enemyType = SPIDER_ROBOT;
	static int frameCount = 0;
	static int CTCount = 0;

	static int page = 1;

	static WordData magicKnightWordDatas[MAGIC_KNIGHT_WORD_MAX];
	static PlayerDeck magicKnightDeck[MAGIC_KNIGHT_DECKS_MAX];
	static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
	static MagicKnightPlayingDeck magicKnightPlayingDeck;
	static MagicKnightAction magicKnightAction;
	ImagesCustomVertex handWordCollisionsVertex[HAND_WORD_MAX];
	ImagesCustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX];
	ImagesCustomVertex choiseDeckCollisionsVertex[MAGIC_KNIGHT_DECKS_MAX];
	ImagesCustomVertex choiseWordCollisionsVertex[MAGIC_KNIGHT_WORD_MAX];
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

	static TEXTUREID wordTexIds[MAGIC_KNIGHT_WORD_MAX];
	static TEXTUREID weaponMasterWordIds[WEAPON_MASTER_WORD_MAX];

	CustomVertex endModifyVertices[4];
	static int modifyWordBox[2];
	ImagesCustomVertex modifyBoxVertices[2];
	CustomVertex decideModify[4];
	static bool clickedWord[MAGIC_KNIGHT_WORD_MAX];
	static bool RclickedWord[MAGIC_KNIGHT_WORD_MAX];
	static bool clickedWeaponMasterWord[WEAPON_MASTER_WORD_MAX];

	ImagesCustomVertex stageSelectPortals[STAGE_MAX];
	static int selectedStage;
	static bool scrollEffect = false;
	static HomingEffect hominEffect[SELECT_EFFECT_MAX];
	static VSData battleData; 
	static int enemyActionNum;
	static bool isClear=false;
	static bool makeRandSeed = true;
	static CustomVertex resultMask[RECT_VERTEX_NUM];

	static bool initializedTex = false;
	
	static StageDate stageData[STAGE_MAX];
	static EnemyST enemyData[ENEMY_MAX];

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

	case CHARA_CHOICE_SCENE:

		ControlCharaChoice(&scene,&cursol,&playerType);
		RenderCharaChoice(&scene, &cursol);

		break;

	case LOAD_TO_HOME_SCENE:

		RenderWhileLoad(&scene, HOME_SCENE, wordTexIds);

		break;

	case HOME_SCENE:

		ControlHome(&scene, magicKnightWordDatas, magicKnightDecks,
			&magicKnightPlayingDeck, &magicKnightAction,
			weaponMasterWords, weaponMasterWordDecks,
			deckAlterPortal, modifyWordPortal, mainGamePortal, charaChoicePortal, wordTexIds, weaponMasterWordIds, &playerType, &initializedTex);

		RenderHome(&scene, deckAlterPortal, modifyWordPortal, mainGamePortal, charaChoicePortal, wordTexIds, weaponMasterWordIds, &playerType,&initializedTex);

		break;

	case CHOSE_DECK_TO_ALTER_SCENE:

		ControlChoiceDeck(&scene, ALTER_DECK_SCENE, choiseDeckCollisionsVertex, &deckNumToAlter);
		RenderChoiceDeck(choiseDeckCollisionsVertex, magicKnightDecks);

		break;

	case ALTER_DECK_SCENE:

		switch (playerType)
		{
		/*case WEAPON_MASTER:

			ControlAlterDeck(&scene, magicKnigtWords, magicKnightDeck, choiseWordCollisionsVertex, deckComponentCollisionsVertex, skillInfo,
				endAlterDeckVertices, backgroundVertices, wordDatasBackVertices, playerType, &deckNumToAlter, clickedWord, RclickedWord);
			RenderWeaponMasterAlterDeck(choiseWMWordCollisionsVertex, deckComponentCollisionsVertex, endAlterDeckVertices,
				backgroundVertices, wordDatasBackVertices, weaponMasterWordIds, weaponMasterWords, weaponMasterWordDecks, &deckNumToAlter, clickedWeaponMasterWord);

			break;*/

		case MAGIC_KNIGHT:
			ControlAlterDeck(&scene, magicKnightWordDatas, &magicKnightDeck, choiseWordCollisionsVertex, deckComponentCollisionsVertex, skillInfo,
				endAlterDeckVertices, backgroundVertices, wordDatasBackVertices, &playerType, &deckNumToAlter, clickedWord, RclickedWord);
			RenderAlterDeck(choiseWordCollisionsVertex, deckComponentCollisionsVertex, skillInfo, endAlterDeckVertices, backgroundVertices, wordDatasBackVertices,
				wordTexIds, magicKnightWordDatas, &magicKnightDeck, &deckNumToAlter, clickedWord, RclickedWord);

			break;
		}
		
		break;

	/*case MODIFY_WORD_SCENE:

		ControlModify(&scene, magicKnightWordDatas, magicKnightDecks,
			choiseWordCollisionsVertex, wordDatasBackVertices, endModifyVertices, backgroundVertices,
			modifyWordBox, modifyBoxVertices, decideModify, clickedWord);
		RenderModify(magicKnightWordDatas, choiseWordCollisionsVertex,
			wordDatasBackVertices, endModifyVertices, backgroundVertices,
			modifyWordBox, modifyBoxVertices, decideModify, wordTexIds, clickedWord);

		break;*/

	case CHOSE_DECK_TO_BATTLE_SCENE:

		ControlChoiceDeck(&scene, LOAD_DECK_TO_PLAY_SCENE,choiseDeckCollisionsVertex, &magicKnightPlayingDeck.m_currentId);
		RenderChoiceDeck(choiseDeckCollisionsVertex, magicKnightDecks);


		break;

	case LOAD_DECK_TO_PLAY_SCENE:

		RenderWhileLoad(&scene, GAME_SCENE, wordTexIds);
		LoadMKdeck(&scene, magicKnightDecks, &magicKnightPlayingDeck);

		switch (playerType)
		{
		case WEAPON_MASTER:

			break;

		case MAGIC_KNIGHT:

			break;
		}

		break;
		
	case SELECT_STAGE_SCENE:

		ControlStageSelect(&scene, stageSelectPortals, &selectedStage, charaChoicePortal, stageData, enemyData);
		RenderStageSelect(stageSelectPortals, charaChoicePortal);

		break;

	case GAME_SCENE:

		ControlGame(&scene);
		RenderGame(&scene);
	switch (playerType)
		{
		case WEAPON_MASTER:
			ControlWeaponMasterAction(weaponMasterWords, weaponMasterWordDecks, weaponMasterActionWords,
				weaponMasterDeckVerticies,weaponMasterActionVerticies, &scrollEffect, &page);
			RenderWeaponMasterAction(weaponMasterDeckVerticies, weaponMasterActionVerticies, weaponMasterWordDecks, weaponMasterActionWords, page, &scrollEffect, weaponMasterWordIds);

			break;

		/*case MAGIC_KNIGHT:

			ControlMagicKnightMainGame(&scene, magicKnightWordDatas, magicKnightDecks, &magicKnightPlayingDeck,
				&magicKnightAction, handWordCollisionsVertex, magicKnightActionCollisionsVertex, hominEffect,
				&battleData, enemyActionNum, &isClear, resultMask, stageData, enemyData, selectedStage);

			RenderMagicKnightMainGame(magicKnightWordDatas, magicKnightDecks, &magicKnightPlayingDeck,
				&magicKnightAction, handWordCollisionsVertex, magicKnightActionCollisionsVertex, 
				wordTexIds, hominEffect, resultMask, &battleData, enemyActionNum, selectedStage, enemyData[battleData.m_enemyId]);

			break;*/
		}

		//ControlHP(player, enemy, &playerATKDamage, (PLAYERTYPE)playerType, enemyType,&frameCount,&CTCount, &magicKnightAction, magicKnightWordDatas);
		//RenderHP(player, enemy,&frameCount,&CTCount);
		
		break;

	case RESULT_SCENE:

		OperateResultScene(&scene, isClear);

		break;
	}

	return;
}
