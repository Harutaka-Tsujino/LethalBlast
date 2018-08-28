#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlMagicKnightMainGame.h"
#include"ControlBattle.h"

 void ControlBattle(WordData* pMagicKnightWordDatas, int* frameCount, VSData* battleData,
	 MagicKnightAction* pMagicKnightAction, EnemyST enemyState,int enemyActionNum)
{
	 static int cTCount = 0;

	if (*frameCount == INIT_FRAME)
	{
		(*frameCount) = 0;
	}

	if (*frameCount == 120)
	{
		ZeroMemory(battleData, sizeof(VSData));
	}

	if (pMagicKnightAction->useAction == true)
	{
		int actionAttack = VOID_ATTACK;
		int actionElement = VOID_ELEMENT;

		bool decideAttack = 0;
		bool decideElement = 0;

		ActionDamage playerAction;
		ZeroMemory(&playerAction, sizeof(ActionDamage));

		for (int actionCom = MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX-1; actionCom >=0 ; --actionCom)
		{
			int actionComWId = pMagicKnightAction->m_componentWordIds[actionCom];

			if (pMagicKnightWordDatas[actionComWId].m_attack != VOID_ATTACK&&!decideAttack)
			{
				actionAttack = pMagicKnightWordDatas[actionComWId].m_attack;

				decideAttack = true;
			}

			if (pMagicKnightWordDatas[actionComWId].m_element != VOID_ELEMENT&&!decideElement)
			{
				actionElement = pMagicKnightWordDatas[actionComWId].m_element;

				decideElement = true;
			}

			switch (pMagicKnightWordDatas[actionComWId].m_cost)
			{
			case 1:

				playerAction.m_ActionDamage += MK_COST_1_DAMAGE +
					MK_COST_1_PLUS__DAMAGE * pMagicKnightWordDatas[actionComWId].m_plusDamage;

				break;

			case 3:

				playerAction.m_ActionDamage += MK_COST_3_DAMAGE +
					MK_COST_3_PLUS__DAMAGE * pMagicKnightWordDatas[actionComWId].m_plusDamage;

				break;

			case 5:

				playerAction.m_ActionDamage += MK_COST_5_DAMAGE +
					MK_COST_5_PLUS__DAMAGE * pMagicKnightWordDatas[actionComWId].m_plusDamage;

				break;

			case 12:
				
				playerAction.m_ActionDamage += MK_COST_12_DAMAGE +
					MK_COST_12_PLUS__DAMAGE * pMagicKnightWordDatas[actionComWId].m_plusDamage;

				break;
			}

			ZeroMemory(pMagicKnightAction, sizeof(MagicKnightAction));
		}

		playerAction.m_ActionAttacks[actionAttack] = true;
		playerAction.m_ActionElements[actionElement] = true;
		
		CalcWeakResistDamage(&playerAction, &enemyState.m_enemyAction[enemyActionNum]);
		CalcWeakResistDamage(&enemyState.m_enemyAction[enemyActionNum], &playerAction);

		if (playerAction.m_ActionDamage > enemyState.m_enemyAction[enemyActionNum].m_ActionDamage)
		{
			battleData->m_playerWon = true;
		}

		else
		{
			if (playerAction.m_ActionDamage < enemyState.m_enemyAction[enemyActionNum].m_ActionDamage)
			{
				battleData->m_enemyWon = true;
				battleData->m_elementEffectId = actionElement;
				battleData->m_attackEffectId = actionAttack;
			}

			else
			{
				battleData->m_cTCurrentCount = 0;
				battleData->m_cT = 0;
				cTCount = 0;
				battleData->m_draw = true;
			}
		}

		battleData->m_playerDamage = playerAction.m_ActionDamage;
		battleData->m_enemyDamage = enemyState.m_enemyAction[enemyActionNum].m_ActionDamage;

		return;
	}

	if (*frameCount >= 120)
	{
		if ((*frameCount) == 120)
		{
			cTCount = 0;
			(*frameCount)++;
		}

		battleData->m_cTMax = enemyState.m_cTNum;
		battleData->m_cTBlank = enemyState.m_cTBlank;

		++cTCount;
		battleData->m_cTCurrentCount = cTCount;

		if (battleData->m_cTCurrentCount >=battleData->m_cTBlank)
		{
			cTCount = 0;
			++battleData->m_cT;
		}

		if (battleData->m_cT >= battleData->m_cTMax)
		{
			battleData->m_cT = 0;

			battleData->m_enemyWon=true;
		}
	}

	return;
}

void CalcWeakResistDamage(ActionDamage* action, ActionDamage* enemyAction)/////////////////////////////////////////////////////////////////////////////////////////
{
	int decideElement = 0;
	int decideAttack = 0;

	for (int element = VOID_ELEMENT; element < ELEMENT_ATTRIBUTES_MAX; ++element)
	{
		if (action->m_ActionElements[element] == true)decideElement = element;
	}

	for (int attack = VOID_ATTACK; attack >=0; --attack)
	{
		if (action->m_ActionAttacks[attack] == true)decideElement = attack;
	}

	switch (decideElement)
	{
	case FIRE_ELEMENT:

		if (enemyAction->m_ActionElements[WATER_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_RESIST;
		}

		if (enemyAction->m_ActionElements[WIND_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_WEAK;
		}

		break;

	case WATER_ELEMENT:

		if (enemyAction->m_ActionElements[WIND_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_RESIST;
		}

		if (enemyAction->m_ActionElements[FIRE_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_WEAK;
		}

		break;

	case WIND_ELEMENT:

		if (enemyAction->m_ActionElements[FIRE_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_RESIST;
		}

		if (enemyAction->m_ActionElements[WATER_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_WEAK;
		}

		break;

	case SHINING_ELEMENT:

		if (enemyAction->m_ActionElements[DARKNESS_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_WEAK;
		}

		break;

	case DARKNESS_ELEMENT:

		if (enemyAction->m_ActionElements[SHINING_ELEMENT])
		{
			action->m_ActionDamage *= ELEMENT_WEAK;
		}

		break;
	}

	switch (decideAttack)
	{
	case SLASH_ATTACK:

		if (enemyAction->m_ActionAttacks[SMASH_ATTACK])
		{
			action->m_ActionDamage *= ATTACK_RESIST;
		}

		if (enemyAction->m_ActionAttacks[PENETRATION_ATTACK])
		{
			action->m_ActionDamage *= ATTACK_WEAK;
		}

		break;

	case SMASH_ATTACK:

		if (enemyAction->m_ActionAttacks[PENETRATION_ATTACK])
		{
			action->m_ActionDamage *= ATTACK_RESIST;
		}

		if (enemyAction->m_ActionAttacks[SLASH_ATTACK])
		{
			action->m_ActionDamage *= ATTACK_WEAK;
		}

		break;

	case PENETRATION_ATTACK:

		if (enemyAction->m_ActionAttacks[SLASH_ATTACK])
		{
			action->m_ActionDamage *= ATTACK_RESIST;
		}

		if (enemyAction->m_ActionAttacks[SMASH_ATTACK])
		{
			action->m_ActionDamage *= ATTACK_WEAK;
		}

		break;
	}

	return;
}
