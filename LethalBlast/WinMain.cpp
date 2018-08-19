#include<windows.h>
#include<time.h>
#include"DX9Lib.h"
#include"ControlGame.h"
#include"RenderGame.h"
#include"WinMain.h"
#include"ControlTitle.h"
#include"RenderTitle.h"
#include"ControlPV.h"
#include"RenderPV.h"
#include"ControlCharaChoice.h"
#include"RenderCharaChoice.h"
//#include"ControlWordListsAndTyping.h"
//#include"RenderWordListsAndTyping.h"
//#include"ControlHP.h"
//#include"RenderHP.h"
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

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	return CreateWindowAndRepeatToControlAndRender(hInst, "Lethal Blast", MainFunction, DISPLAY_WIDTH, DISPLAY_HEIGHT, FALSE);
}

//メッセージループでループさせる関数
void MainFunction(void)
{
	srand((unsigned int)time(NULL));

	static int cursol = 1;  

	static SCENE scene = (SCENE)0;

	static TEXTUREID textureIds[ALL_TEX_MAX];
	static FONTID fontIds[ALL_FONT_MAX];

	/*static WordData magicKnigtWords[MAGIC_KNIGHT_WORD_MAX];
	static WordList magicKnightWordLists[5];
	static MagicKnightAction magicKnightAction;
	static WordCandidate wordCandidates[5];
	static int wordNum = 0;
	static bool endAttackEffect = false;*/

	/*static PlayerState player[JOB_MAX];
	static EnemyState enemy[ENEMY_TYPE_MAX];
	static int playerATKDamage;
	static int enemyType = BOSS;
	static bool initHPFlag = true;
	static bool initMagicKnightActionFlag;
	static int count = 0;
	static int CTCount = 0;*/
	static int playerType;

	static WordData magicKnightWordDatas[MAGIC_KNIGHT_WORD_MAX];
	static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
	static MagicKnightPlayingDeck magicKnightPlayingDeck;
	static MagicKnightAction magicKnightAction;
	ImagesCustomVertex handWordCollisionsVertex[HAND_WORD_MAX];
	ImagesCustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX];

	ImagesCustomVertex choiseDeckCollisionsVertex[MAGIC_KNIGHT_DECKS_MAX];
	ImagesCustomVertex choiseWordCollisionsVertex[MAGIC_KNIGHT_WORD_MAX];
	ImagesCustomVertex deckComponentCollisionsVertex[DECK_WORD_MAX];
	static int deckNumToAlter = 0;

	CustomVertex endAlterDeckVertices[4];
	CustomVertex backgroundVertices[4];
	CustomVertex wordDatasBackVertices[4];

	CustomVertex deckAlterPortal[4];
	CustomVertex modifyWordPortal[4]; 
	CustomVertex mainGamePortal[4];
	CustomVertex charaChoicePortal[4];

	static TEXTUREID wordTexIds[MAGIC_KNIGHT_WORD_MAX];

	CustomVertex endModifyVertices[4];
	static int modifyWordBox[2];
	ImagesCustomVertex modifyBoxVertices[2];
	CustomVertex decideModify[4];

	//シーン分岐
	switch (scene)
	{
	case PV_SCENE:

		ControlPV(&scene);
		RenderPV(&scene);

		break;

	case TITLE_SCENE:

		TitleContorol(&scene);
		TitleRender(&scene);

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
			deckAlterPortal, modifyWordPortal, mainGamePortal, charaChoicePortal);
		RenderHome(deckAlterPortal, modifyWordPortal, mainGamePortal, charaChoicePortal);

		break;

	case CHOSE_DECK_TO_ALTER_SCENE:

		ControlChoiceDeck(&scene, ALTER_DECK_SCENE, choiseDeckCollisionsVertex, &deckNumToAlter);
		RenderChoiceDeck(choiseDeckCollisionsVertex, magicKnightDecks);

		break;

	case ALTER_DECK_SCENE:

		ControlAlterDeck(&scene, magicKnightWordDatas, magicKnightDecks, choiseWordCollisionsVertex,
			deckComponentCollisionsVertex, endAlterDeckVertices, backgroundVertices, wordDatasBackVertices, &deckNumToAlter);
		RenderAlterDeck(choiseWordCollisionsVertex, deckComponentCollisionsVertex, endAlterDeckVertices,
			backgroundVertices, wordDatasBackVertices, wordTexIds, magicKnightWordDatas, magicKnightDecks,&deckNumToAlter);

		break;

	case MODIFY_WORD_SCENE:

		ControlModify(&scene, magicKnightWordDatas, magicKnightDecks,
			choiseWordCollisionsVertex, wordDatasBackVertices, endModifyVertices, backgroundVertices,
			modifyWordBox, modifyBoxVertices, decideModify);
		RenderModify(magicKnightWordDatas, choiseWordCollisionsVertex,
			wordDatasBackVertices, endModifyVertices, backgroundVertices,
			modifyWordBox, modifyBoxVertices, decideModify, wordTexIds);

		break;

	case CHOSE_DECK_TO_BATTLE_SCENE:

		ControlChoiceDeck(&scene, LOAD_DECK_TO_PLAY_SCENE,choiseDeckCollisionsVertex, &magicKnightPlayingDeck.m_currentId);
		RenderChoiceDeck(choiseDeckCollisionsVertex, magicKnightDecks);


		break;

	case LOAD_DECK_TO_PLAY_SCENE:

		RenderWhileLoad(&scene, LOAD_DECK_TO_PLAY_SCENE, wordTexIds);
		LoadMKdeck(&scene, magicKnightDecks, &magicKnightPlayingDeck);

		break;

	case GAME_SCENE:

		ControlGame(&scene);
		RenderGame(&scene);

		ControlMagicKnightMainGame(magicKnightWordDatas, magicKnightDecks, &magicKnightPlayingDeck,
			&magicKnightAction, handWordCollisionsVertex, magicKnightActionCollisionsVertex);
		RenderMagicKnightMainGame(magicKnightWordDatas, magicKnightDecks, &magicKnightPlayingDeck,
			&magicKnightAction, handWordCollisionsVertex, magicKnightActionCollisionsVertex, wordTexIds);

		/*ControlTyping(magicKnigtWords, magicKnightWordLists, &magicKnightAction, wordCandidates, &wordNum,&endAttackEffect);
		RenderMasicKnightWordLists(fontIds, magicKnigtWords, magicKnightWordLists, &magicKnightAction, wordCandidates,&wordNum,&endAttackEffect);
		ControlHP(player, enemy, &playerATKDamage, &playerType, &enemyType, &initHPFlag,&count,&CTCount, &magicKnightAction, &initMagicKnightActionFlag);
		RenderHP(player, enemy,&count,&CTCount, playerType, &enemyType);*/
		
		break;
	}

	return;
}
