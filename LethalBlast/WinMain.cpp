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
#include"ControlWordListsAndTyping.h"
#include"RenderWordListsAndTyping.h"
#include"ControlHP.h"
#include"RenderHP.h"
#include"ControlWeaponMasterAction.h"
#include"RenderWeaponMasterAction.h"


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	return CreateWindowAndRepeatToControlAndRender(hInst, "Lethal Blast", MainFunction, DISPLAY_WIDTH, DISPLAY_HEIGHT, FALSE);
}

//メッセージループでループさせる関数
void MainFunction(void)
{
	srand((unsigned int)time(NULL));

	static int cursol = 1;
	static bool listOpen = false;

	static SCENE scene = (SCENE)0;

	static TEXTUREID textureIds[ALL_TEX_MAX];
	static FONTID fontIds[ALL_FONT_MAX];

	static WordData magicKnigtWords[MAGIC_KNIGHT_WORD_MAX];
	static WordList magicKnightWordLists[5];
	static MagicKnightAction magicKnightAction;
	static WordCandidate wordCandidates[5];
	static WeaponMasterWordData weaponMasterWords[WEAPON_MASTER_WORD_MAX];
	static WeaponMasterDeck weaponMasterWordDecks[8];
	static WeaponMasterActionData weaponMasterActionWords[WEAPON_MASTER_ACTION_LISTS];
	static ImagesCustomVertex weaponMasterDeckVerticies[40];
	static PlayerState player[JOB_MAX];
	static EnemyState enemy[ENEMY_TYPE_MAX];
	static int wordNum = 0;
	static bool endAttackEffect = false;

	static int playerType;
	static int playerATKDamage;
	static int enemyType = BOSS;
	static bool initHPFlag = true;
	static bool initMagicKnightActionFlag;
	static int count = 0;
	static int CTCount = 0;
	static int page = 1;

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

	case GAME_SCENE:

		ControlGame(&scene);
		RenderGame(&scene);
		ControlWeaponMasterAction(weaponMasterWords, weaponMasterWordDecks, weaponMasterActionWords,
			weaponMasterDeckVerticies, &page);
		RenderWeaponMasterAction(weaponMasterWords, weaponMasterWordDecks, weaponMasterActionWords,
			weaponMasterDeckVerticies, page);
		/*ControlHP(player, enemy, &playerATKDamage, &playerType, &enemyType, &initHPFlag,&count,&CTCount, &magicKnightAction, &initMagicKnightActionFlag);
		RenderHP(player, enemy,&count,&CTCount, playerType, &enemyType);*/
		
		break;
	}

	return;
}
