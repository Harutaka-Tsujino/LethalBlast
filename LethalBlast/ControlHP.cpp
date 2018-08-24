#include "ControlHP.h"
#include "WinMain.h"
#include "ControlMagicKnightMainGame.h"
#include <math.h>
#include "ControlWeaponMasterAction.h"


void ControlHP(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage, PLAYERTYPE PlayerType, ENEMY_TYPE EnemyType, int* pFrameCount, int* pCTCount,
	MagicKnightAction* pMagicKnightAction, WordData* pWordData)
{
	//最初だけ初期化
	static int frameCount = INIT_FRAME;
	if (frameCount == INIT_FRAME)
	{
		InitHP(pPlayer, pEnemy, PlayerType, EnemyType);
		frameCount = 0;
	}

	//マジックナイトの時
	if (PlayerType == MAGIC_KNIGHT)
	{
		if (pMagicKnightAction->useAction)
		{
			CalcMagicKnightATKDamage(pPlayer, pEnemy, pPlayerATKDamage, pMagicKnightAction, pWordData);
		}
	}

	//ウェポンマスターの時
	if (PlayerType == WEAPON_MASTER)
	{

	}

	pEnemy->m_HP -= *pPlayerATKDamage;

	if (pEnemy->m_HP <= 0)
	{
		pEnemy->m_HP = 0;
	}

	CalcEnemyATKDamage(pPlayer, pEnemy, PlayerType, EnemyType, pPlayerATKDamage, pFrameCount, pCTCount);
}



void InitHP(PlayerState* pPlayer, EnemyState *pEnemy, PLAYERTYPE PlayerType, ENEMY_TYPE EnemyType)
{
	//プレイヤー種類ごとの初期HP設定
	if (PlayerType == MAGIC_KNIGHT)						//魔法剣士の時
	{
		pPlayer->m_maxHP = 800000;
		pPlayer->m_HP = 800000;
		pPlayer->m_delayAtackBuffFlag = false;
		pPlayer->m_suicideAtackBuffFlag = false;
		pPlayer->m_suicideAtackDebuffFlag = false;
		pPlayer->m_defenceBuffFlag = false;
	}
	else if (PlayerType == WEAPON_MASTER)				//ウェポンマスターの時
	{
		pPlayer->m_maxHP = 1000000;
		pPlayer->m_HP = 1000000;
		pPlayer->m_delayAtackBuffFlag = false;
		pPlayer->m_suicideAtackBuffFlag = false;
		pPlayer->m_suicideAtackDebuffFlag = false;
		pPlayer->m_defenceBuffFlag = false;
	}
	else if (PlayerType == NECROMAMCERANDSUMMONUR)		//召喚士の時
	{
		pPlayer->m_maxHP = 600000;
		pPlayer->m_HP = 600000;
		pPlayer->m_delayAtackBuffFlag = false;
		pPlayer->m_suicideAtackBuffFlag = false;
		pPlayer->m_suicideAtackDebuffFlag = false;
		pPlayer->m_defenceBuffFlag = false;
	}

	//敵種類ごとの初期HP設定
	if (EnemyType == SPIDER_ROBOT)			//雑魚敵の時
	{
		pEnemy->m_maxHP = 210000000;
		pEnemy->m_HP = 210000000;
		pEnemy->m_weakElementAttribute = WATER_ELEMENT;
		pEnemy->m_weakAttackAttribute = SMASH_ATTACK;
		pEnemy->m_resistElementAttribute = WIND_ELEMENT;
		pEnemy->m_resistAttackAttribute = PENETRATION_ATTACK;
	}
	else if (EnemyType == BOSS)		//ボスモンスターの時
	{
		pEnemy->m_maxHP = 100000;
		pEnemy->m_HP = 100000;
	}
}



void CalcMagicKnightATKDamage(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage, MagicKnightAction* pMagicKnightAction, WordData* pWordData)
{
	//ダメージ量の初期化
	*pPlayerATKDamage = 0;

	int  wordDamage = 0;							//文字ダメージ
	float elementAttributeMagnification = 1;		//属性倍率
	float atackAttributeMagnification = 1;			//物理属性倍率
	float specialAtackMagnification = 1;			//隠し効果倍率


	//コスト毎の文字ダメージ算出
	for (int actionConponentWord = 0; actionConponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; actionConponentWord++)
	{
		//文字が入ってないときはダメージを増やさない
		if (pMagicKnightAction->m_componentWordIds[actionConponentWord] == VOID_WORD)
		{
			continue;
		}

		//コスト1の時、150万文字ダメージ
		if (pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_cost == 1)
		{
			wordDamage += 1500000;
		}

		//コスト3の時、350万文字ダメージ
		if (pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_cost == 1)
		{
			wordDamage += 3500000;
		}

		//コスト5の時、600万文字ダメージ
		if (pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_cost == 1)
		{
			wordDamage += 6000000;
		}

		//コスト12の時、1000万文字ダメージ
		if (pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_cost == 1)
		{
			wordDamage += 10000000;
		}

	}


	ELEMENT_ATTRIBUTE ATKelementAttribute = VOID_ELEMENT;	//必殺技の属性
	//必殺技の属性を判別
	for (int actionConponentWord = MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX-1; actionConponentWord >= 0; actionConponentWord--)
	{
		if (pMagicKnightAction->m_componentWordIds[actionConponentWord] == VOID_WORD
			|| pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_element == VOID_ELEMENT)
		{
			continue;
		}
		else
		{
			ATKelementAttribute = pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_element;
			break;
		}
	}
	//属性倍率の算出
	if (pEnemy->m_weakElementAttribute == ATKelementAttribute)
	{
		elementAttributeMagnification = pow(1.2, (double)pMagicKnightAction->m_elementTotals[ATKelementAttribute]);
	}
	if (pEnemy->m_resistElementAttribute == ATKelementAttribute)
	{
		elementAttributeMagnification = pow(0.7, (double)pMagicKnightAction->m_elementTotals[ATKelementAttribute]);
	}


	ATTACK_ATTRIBUTE atackAttribute = VOID_ATTACK;	//必殺技の物理属性
	//必殺技の物理属性を判別
	for (int actionConponentWord = MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX-1; actionConponentWord >= 0; actionConponentWord--)
	{
		if (pMagicKnightAction->m_componentWordIds[actionConponentWord] == VOID_WORD
			|| pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_attack == VOID_ELEMENT)
		{
			continue;
		}
		else
		{
			atackAttribute = pWordData[pMagicKnightAction->m_componentWordIds[actionConponentWord]].m_attack;
			break;
		}
	}
	//物理属性倍率の算出
	if (pEnemy->m_weakAttackAttribute == atackAttribute)
	{
		atackAttributeMagnification = pow(1.1, (double)pMagicKnightAction->m_attackTotals[atackAttribute]);
	}
	if (pEnemy->m_resistAttackAttribute == atackAttribute)
	{
		atackAttributeMagnification = pow(0.8, (double)pMagicKnightAction->m_attackTotals[atackAttribute]);
	}


	//隠し効果
	//竜特攻
	if (pEnemy->m_phylum == DRAGON)
	{
		if (pMagicKnightAction->m_specialAbilities & DRAGON_EFECTIVE)
		{
			specialAtackMagnification = specialAtackMagnification * 1.3;
		}
	}
	//獣特攻
	if (pEnemy->m_phylum == BEAST)
	{
		if (pMagicKnightAction->m_specialAbilities & BEAST_EFECTTIV)
		{
			specialAtackMagnification = specialAtackMagnification * 1.3;
		}
	}
	//遅延ダメージUP
	if (pPlayer->m_delayAtackBuffFlag == true)
	{
		specialAtackMagnification = specialAtackMagnification * 1.3;
		pPlayer->m_delayAtackBuffFlag = false;
	}
	if (pMagicKnightAction->m_specialAbilities & DELAY_DAMAGE_UP)
	{
		pPlayer->m_delayAtackBuffFlag = true;
	}
	//ダメージUP
	if (pMagicKnightAction->m_specialAbilities & DAMAGE_UP)
	{
		specialAtackMagnification = specialAtackMagnification * 1.1;
	}
	//追撃
	if (pMagicKnightAction->m_specialAbilities & CHACE_ATTACK)
	{
		specialAtackMagnification = specialAtackMagnification * 1.25;
	}
	//一時的に攻撃力アップその後一時的に攻撃力ダウン
	if (pPlayer->m_suicideAtackDebuffFlag == true)
	{
		specialAtackMagnification = specialAtackMagnification * 0.8;
		pPlayer->m_suicideAtackDebuffFlag = false;
	}
	if (pPlayer->m_suicideAtackBuffFlag == true)
	{
		specialAtackMagnification = specialAtackMagnification * 1.4;
		pPlayer->m_suicideAtackDebuffFlag = true;
		pPlayer->m_suicideAtackBuffFlag = false;
	}
	if (pMagicKnightAction->m_specialAbilities & SUCIDE_ATTACK_DAMAGE_UP)
	{
		pPlayer->m_suicideAtackBuffFlag = true;
	}

	*pPlayerATKDamage = wordDamage * elementAttributeMagnification * atackAttributeMagnification * specialAtackMagnification;

//#ifdef _DEBUG
//	/*if (g_mouseState.mousePush[LEFT_CLICK])
//	{
//		*pPlayerATKDamage = 3500000;
//	*/}
//#endif

	//m_componentWordIdsのリセット
	for (int actionConponentWord = 0; actionConponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; actionConponentWord++)
	{
		pMagicKnightAction->m_componentWordIds[actionConponentWord] = VOID_WORD;
	}
	//m_specialAbilitiesのリセット
	pMagicKnightAction->m_specialAbilities = 0x00000000;
}



void  CalcWeaponMasterATKDamage(PlayerState* pPlayer, EnemyState* pEnemy, int* pPlayerATKDamage, WeaponMasterActionData* pWeaponMasterActionData, WeaponMasterWordData* pWeaponMasterWordData)
{
	//ダメージ量のリセット
	*pPlayerATKDamage = 0;

	int  wordDamage = 0;							//文字ダメージ
	float elementAttributeMagnification = 1;		//属性倍率
	float atackAttributeMagnification = 1;			//物理属性倍率
	float specialAtackMagnification = 1;			//隠し効果倍率


	//コスト毎の文字ダメージ算出
	for (int actionConponentWord = 0; actionConponentWord < WEAPON_MASTER_ACTION_LISTS; actionConponentWord++)
	{

	}
}



void CalcEnemyATKDamage(PlayerState* pPlayer, EnemyState* pEnemy, PLAYERTYPE PlayerType, ENEMY_TYPE EnemyType, int* pPlayerATKDamage, int* pFrameCount, int* pCTCount)
{
	//プレイヤーHP減少
	if (pPlayer->m_HP >= 0)
	{
		//12秒に1回ダメージ
		if (*pFrameCount >= 720)
		{
			//CTが溜まると必殺技を撃つ
			if (*pCTCount == 4)
			{
				pPlayer->m_HP -= 43530;
				(*pCTCount) = 0;
			}
			else
			{
				pPlayer->m_HP -= 12000;
				(*pFrameCount) = 0;
				(*pCTCount)++;
			}
		}
		(*pFrameCount)++;
	}
	else
	{
		pPlayer->m_HP = 0;
		(*pFrameCount) = 0;
	}
}