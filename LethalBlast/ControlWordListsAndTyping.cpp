#include<windows.h>
#include<mbctype.h>
#include"DX9Lib.h"
#include"ControlWordListsAndTyping.h"

void ControlWordListsAndTyping()
{
	//カタカナ構造体にカタカナを入れる
	Katakana katakana[KATAKANA_FIRST_ROWS_MAX];
	memset(katakana, 0, sizeof(Katakana)*KATAKANA_FIRST_ROWS_MAX);

	strcpy_s(katakana[ファ].katakanaRow, "ファフィフフェフォ");
	strcpy_s(katakana[ヴァ].katakanaRow, "ヴァヴィヴヴェヴォ");
	strcpy_s(katakana[ジャ].katakanaRow, "ジャジジュジェジョ");//
	strcpy_s(katakana[ワ].katakanaRow, "ワウィウウェヲ");
	strcpy_s(katakana[ア].katakanaRow, "アイウエオ");
	strcpy_s(katakana[カ].katakanaRow, "カキクケコ");
	strcpy_s(katakana[サ].katakanaRow, "サシスセソ");
	strcpy_s(katakana[タ].katakanaRow, "タチツテト");
	strcpy_s(katakana[ナ].katakanaRow, "ナニヌネノ");
	strcpy_s(katakana[ハ].katakanaRow, "ハマヤラワ");
	strcpy_s(katakana[マ].katakanaRow, "マミムメモ");
	strcpy_s(katakana[ラ].katakanaRow, "ラリルレロ");
	strcpy_s(katakana[ヤ].katakanaRow, "ヤユヨ");
	strcpy_s(katakana[ン].katakanaRow, "ン");
	strcpy_s(katakana[パ].katakanaRow, "パピプペポ");
	strcpy_s(katakana[ガ].katakanaRow, "ガギグゲゴ");
	strcpy_s(katakana[ザ].katakanaRow, "ザジズゼゾ");
	strcpy_s(katakana[ダ].katakanaRow, "ダヂヅデド");
	strcpy_s(katakana[バ].katakanaRow, "バビブベボ");
	strcpy_s(katakana[ァ].katakanaRow, "ァィゥェォ");
	strcpy_s(katakana[ャ].katakanaRow, "ャュョ");
	strcpy_s(katakana[ッ].katakanaRow, "ッ");
	strcpy_s(katakana[ー].katakanaRow, "ー");

	FILE* pWordStatesFile;

	fopen_s(&pWordStatesFile, "Files/WordStates/MagicKnightWordStates.csv", "r");

	//魔法剣士のワードデータ
	WordData magicKnigtWords[MAGIC_KNIGHT_WORD_MAX];
	
	//初期化
	memset(magicKnigtWords, 0, sizeof(WordData)*MAGIC_KNIGHT_WORD_MAX);

	//魔法剣士のワードデーターを入れていく
	for (int wordsNum = ファイヤー; wordsNum < MAGIC_KNIGHT_WORD_MAX; wordsNum++)
	{
		//外部ファイルの属性を数字に直したいので一度文字列で保管する
		const int ELEMENTAL_WORDS_MAX = 22;
		char elemental[ELEMENTAL_WORDS_MAX];

		const int ATTACK_WORDS_MAX = 4;
		char attack[ATTACK_WORDS_MAX];

		//外部ファイルからの入力
		fscanf_s(pWordStatesFile, "%[^,],%[^,],%[^,],%x", &(magicKnigtWords[wordsNum].m_word), sizeof(char) * WORD_CHAR_MAX, elemental,
			sizeof(char) * ELEMENTAL_WORDS_MAX, attack, sizeof(char)*ATTACK_WORDS_MAX, magicKnigtWords[wordsNum].m_specialAbilities);

		//特殊属性の数だけ回す
		for (int elementalNum = 0; elementalNum < ELEMENT_ATTRIBUTES_MAX; elementalNum)
		{
			//属性が決まったかどうか
			bool wasInputElemental = false;

			//属性を文字列で保管していたので数字に変換する
			switch (elementalNum)
			{
			case FIRE_ELEMENT:

				if (!strcmp("FIRE_ELEMENT", elemental))
				{
					magicKnigtWords[wordsNum].m_element = FIRE_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case WATER_ELEMENT:

				if (!strcmp("WATER_ELEMENT", elemental))
				{
					magicKnigtWords[wordsNum].m_element = WATER_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case WIND_ELEMENT:

				if (!strcmp("WIND_ELEMENT", elemental))
				{
					magicKnigtWords[wordsNum].m_element = WIND_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case SHINING_ELEMENT:

				if (!strcmp("SHINING_ELEMENT", elemental))
				{
					magicKnigtWords[wordsNum].m_element = SHINING_ELEMENT;

					wasInputElemental = true;
				}

				break;

			case DARKNESS_ELEMENT:

				if (!strcmp("DARKNESS_ELEMENT", elemental))
				{
					magicKnigtWords[wordsNum].m_element = DARKNESS_ELEMENT;

					wasInputElemental = true;
				}

				break;
			}

			if (wasInputElemental)
			{
				break;
			}
		}

		//属性がない場合があるのでその対処
		const char VOID_ATTRIBUTE = '0';

		if (elemental[0] = VOID_ATTRIBUTE)
		{
			magicKnigtWords[wordsNum].m_element = VOID_ELEMENT;

			break;
		}

		//物理属性の数だけ回す
		for (int attackNum = 0; attackNum < ATTACK_ATTRIBUTES_MAX; attackNum++)
		{
			bool wasInputAttack = 0;

			switch (attackNum)
			{
			case SLASH_ATTACK:

				if (!strcmp("SLASH_ATTACK", attack))
				{
					magicKnigtWords[wordsNum].m_attack = SLASH_ATTACK;

					wasInputAttack = true;
				}

				break;

			case SMASH_ATTACK:

				if (!strcmp("SLASH_ATTACK", attack))
				{
					magicKnigtWords[wordsNum].m_attack = SLASH_ATTACK;

					wasInputAttack = true;
				}

				break;

			case PENETRATION_ATTACK:

				if (!strcmp("PENETRATION_ATTACK", attack))
				{
					magicKnigtWords[wordsNum].m_attack = PENETRATION_ATTACK;

					wasInputAttack = true;
				}

				break;
			}

			if (wasInputAttack = true)
			{
				break;
			}

		}
		
		if (elemental[0] = VOID_ATTRIBUTE)
		{
			magicKnigtWords[wordsNum].m_attack = VOID_ATTACK;

			break;
		}
	}

	fclose(pWordStatesFile);

	 const int MAGIC_KNIGHT_WORD_LISTS_MAX = 5;
	 WordList magicKnightWordLists[MAGIC_KNIGHT_WORD_LISTS_MAX];
	
	 //単語リストに入る単語の生成
	 for (int listWord = 0; listWord < MAGIC_KNIGHT_WORD_LISTS_MAX; listWord++)
	 {
		 //ワードenumにVOID_WORDが入ってるので-1、+1してる
		 magicKnightWordLists[listWord].m_Id = (MAGIC_KNIGHT_WORD)(rand() % (MAGIC_KNIGHT_WORD_MAX - 1) + 1);
	 }

	 ///////////////////////////////////////////////↑ワードの情報を入れてリストを作った↓タイピング

	 //単語の文字の何番目まで打たれているか
	 static int wordSpellPos = 0;
	 static MagicKnightAction magicKnightAction;
	 memset(&magicKnightAction, 0, sizeof(MagicKnightAction));
	 const int INPUT_CHAR_LIMIT = 20;

	 for (; magicKnightAction.m_inputWords[wordSpellPos] != 0; wordSpellPos++)
	 {
		 if (wordSpellPos > WORD_CHAR_MAX * MAGIC_KNIGHT_ACTION_WORDS_MAX - INPUT_CHAR_LIMIT - 1)
		 {
			 goto canInputCharMax;
		 }
	 }

	 for (BYTE keyId = DIK_MINUS; keyId <= DIK_M; keyId++)
	 {
		 if (g_keyState.keyPush[keyId])
		 {
			 /*for (int listWord = 0; listWord < MAGIC_KNIGHT_WORD_LISTS_MAX; listWord++)
			 {
				 if (magicKnigtWords[magicKnightWordLists[listWord].m_Id].m_word[wordSpellPos])
				 {

				 }現在打たれている文字がリストにあるか確認したい

			 }*/

			 switch (keyId)
			 {
			 case DIK_A:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'a';

				 wordSpellPos++;
				 
				 break;

			 case DIK_B:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'b';

				 wordSpellPos++;

				 break;

			 case DIK_C:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'c';

				 wordSpellPos++;

				 break;


			 case DIK_D:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'd';

				 wordSpellPos++;

				 break;

			 case DIK_E:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'e';

				 wordSpellPos++;

				 break;

			 case DIK_F:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'f';

				 wordSpellPos++;

				 break;

			 case DIK_G:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'g';

				 wordSpellPos++;

				 break;

			 case DIK_H:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'h';

				 wordSpellPos++;

				 break;

			 case DIK_I:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'i';

				 wordSpellPos++;

				 break;

			 case DIK_J:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'j';

				 wordSpellPos++;

				 break;

			 case DIK_K:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'k';

				 wordSpellPos++;

				 break;

			 case DIK_L:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'l';

				 wordSpellPos++;

				 break;

			 case DIK_M:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'm';

				 wordSpellPos++;

				 break;

			 case DIK_N:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'n';

				 wordSpellPos++;

				 break;

			 case DIK_O:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'o';

				 wordSpellPos++;

				 break;

			 case DIK_P:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'p';

				 wordSpellPos++;

				 break;

			 case DIK_Q:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'q';

				 wordSpellPos++;

				 break;

			 case DIK_R:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'r';

				 wordSpellPos++;

				 break;

			 case DIK_S:

				 magicKnightAction.m_inputWords[wordSpellPos] = 's';

				 wordSpellPos++;

				 break;

			 case DIK_T:

				 magicKnightAction.m_inputWords[wordSpellPos] = 't';

				 wordSpellPos++;

				 break;

			 case DIK_U:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'u';

				 wordSpellPos++;

				 break;

			 case DIK_V:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'v';

				 wordSpellPos++;

				 break;

			 case DIK_W:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'w';

				 wordSpellPos++;

				 break;

			 case DIK_X:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'x';

				 wordSpellPos++;

				 break;

			 case DIK_Y:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'y';

				 wordSpellPos++;

				 break;

			 case DIK_Z:

				 magicKnightAction.m_inputWords[wordSpellPos] = 'z';

				 wordSpellPos++;

				 break;

			 case DIK_MINUS:

				 memcpy_s(&magicKnightAction.m_inputWords[wordSpellPos], sizeof(char)*MULTI_BYTE,
					 "ー", sizeof(char)*MULTI_BYTE);

				 wordSpellPos += MULTI_BYTE;

				 break;

			 case DIK_BACK:
				 
				 //ここで二バイト文字の場合一文字だけ消しても意味ない関数があったからそれを使う_ismbblead　１バイト目　_ismbbtrail 2ばいとめ
				 if (_ismbbtrail(magicKnightAction.m_inputWords[wordSpellPos-1]))
				 {
					 magicKnightAction.m_inputWords[wordSpellPos - 1] = NULL;
					 magicKnightAction.m_inputWords[wordSpellPos - 2] = NULL;

					 wordSpellPos -= MULTI_BYTE;
				 }

				 else
				 {
					 magicKnightAction.m_inputWords[wordSpellPos-1] = NULL;

					 wordSpellPos--;
				 }

				 break;
			 }
		 }
	 }

	 canInputCharMax:
	 if (g_keyState.keyPush[DIK_BACK] & 0x80)
	 {
		 if (_ismbbtrail(magicKnightAction.m_inputWords[wordSpellPos - 1]))
		 {
			 magicKnightAction.m_inputWords[wordSpellPos - 1] = NULL;
			 magicKnightAction.m_inputWords[wordSpellPos - 2] = NULL;

			 wordSpellPos -= MULTI_BYTE;
		 }

		 else
		 {
			 magicKnightAction.m_inputWords[wordSpellPos - 1] = NULL;

			 wordSpellPos--;
		 }
	 }

	 ////////////////////////////////////////ここから下はアルファベットをカタカナに置き換えるテーブルの作成
	 for (int wordCheckPos = 0; wordCheckPos < WORD_CHAR_MAX * MAGIC_KNIGHT_ACTION_WORDS_MAX - INPUT_CHAR_LIMIT; wordCheckPos++)
	 {
		 const int MIN_CHAR_PREFIXES_MAX = 2;
		 const char L_X[MIN_CHAR_PREFIXES_MAX] = { 'l','x' };
		 const char VOWELS_MAX = 5;
		 const char VOWELS[] = { "aiueo" };
		 const char Y_VOWELS_MAX = 3;
		 const char Y_VOWELS[] = { "auo" };

		 for (int minCharPrefix = 0; minCharPrefix < MIN_CHAR_PREFIXES_MAX; minCharPrefix++)
		 {
			 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
			 {
				 //小文字ア行
				 if (magicKnightAction.m_inputWords[wordCheckPos] == L_X[minCharPrefix] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == VOWELS[vowel])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[ァ].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }

				 //大文字ア行
				 if (magicKnightAction.m_inputWords[wordCheckPos] == VOWELS[vowel])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[ア].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }
			 }

			 //小文字ヤ行
			 for (int yVowel = 0; yVowel < Y_VOWELS_MAX; yVowel++)
			 {
				 if ((magicKnightAction.m_inputWords[wordCheckPos] == L_X[minCharPrefix] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == 'y'&&
					 magicKnightAction.m_inputWords[wordCheckPos + 2] == Y_VOWELS[yVowel]))
				 {
					 magicKnightAction.m_inputWords[wordCheckPos + 2] = NULL;

					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[ャ].katakanaRow[yVowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }
			 }

			 //小文字ツ
			 if ((magicKnightAction.m_inputWords[wordCheckPos] == L_X[minCharPrefix] &&
				 magicKnightAction.m_inputWords[wordCheckPos + 1] == 't'&&
				 magicKnightAction.m_inputWords[wordCheckPos + 2] == 'u'))
			 {
				 magicKnightAction.m_inputWords[wordCheckPos + 2] = NULL;

				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
					 &katakana[ッ].katakanaRow[0], sizeof(char)*MULTI_BYTE);

				 break;
			 }
		 }

		 const char F_V_CONSTANTS_MAX = 2;
		 const char F_V[F_V_CONSTANTS_MAX] = { 'f','v' };
		 const char FU_VU = 4;
		 const char F_V_SOUND_NUMS_FROM_FIRST[] = { 0,4,8,10,14 };

		 //大文字ファとヴァ行
		 for (int fVConstant = 0; fVConstant < F_V_CONSTANTS_MAX; fVConstant++)
		 {
			 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
			 {
				 if (magicKnightAction.m_inputWords[wordCheckPos] == F_V[fVConstant] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == 'u')
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[ファ + fVConstant].katakanaRow[FU_VU*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }

				 if (magicKnightAction.m_inputWords[wordCheckPos] == F_V[fVConstant] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == VOWELS[vowel])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE * 2,
						 &katakana[ファ + fVConstant].katakanaRow[F_V_SOUND_NUMS_FROM_FIRST[vowel]], sizeof(char)*MULTI_BYTE * 2);

					 break;
				 }
			 }
		 }

		 const char WA = 0;
		 const char WU = 3;
		 const char WO = 6;
		 const char W_ONE_BYTE_VOWELS_MAX = 3;
		 const char W_ONE_BYTE_VOWELS[] = { "auo" };
		 const char W_SOUND_NUMS_FROM_FIRST[] = { 0,2.6,8,12 };

		 //大文字ワ行
		 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
		 {
			 if (vowel % 2 == 0)
			 {
				 if (magicKnightAction.m_inputWords[wordCheckPos] == 'w' &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == W_ONE_BYTE_VOWELS[vowel / 2])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[ワ].katakanaRow[W_SOUND_NUMS_FROM_FIRST[vowel]], sizeof(char)*MULTI_BYTE);

					 break;
				 }
			 }

			 if (magicKnightAction.m_inputWords[wordCheckPos] == 'w' &&
				 magicKnightAction.m_inputWords[wordCheckPos + 1] == VOWELS[vowel])
			 {
				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE * 2,
					 &katakana[ワ].katakanaRow[W_SOUND_NUMS_FROM_FIRST[vowel]], sizeof(char)*MULTI_BYTE * 2);

				 break;
			 }
		 }

		 const char CONSTANTS_MAX = 7;
		 const char CONSTANTS[] = { "kstnhmr" };

		 //大文字カサタナハマラ行
		 for (int consonant = 0; consonant < CONSTANTS_MAX; consonant++)
		 {
			 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
			 {
				 if (magicKnightAction.m_inputWords[wordCheckPos] == CONSTANTS[consonant] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == VOWELS[vowel])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[カ + consonant].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }
			 }
		 }

		 const char CONSTANT_PLUS_Y[] = { "ャィュェョ" };
		 //大文字カサタナハマラ行+小文字ヤ行
		 for (int consonant = 0; consonant < CONSTANTS_MAX; consonant++)
		 {
			 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
			 {
				 if (magicKnightAction.m_inputWords[wordCheckPos] == CONSTANTS[consonant] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == 'y'&&
					 magicKnightAction.m_inputWords[wordCheckPos + 2] == VOWELS[vowel])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[カ + consonant].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos + 2], sizeof(char)*MULTI_BYTE,
						 &CONSTANT_PLUS_Y[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }
			 }
		 }

		 //大文字ヤ行
		 for (int yVowel = 0; yVowel < Y_VOWELS_MAX; yVowel++)
		 {
			 if (magicKnightAction.m_inputWords[wordCheckPos] == 'y'&&
				 magicKnightAction.m_inputWords[wordCheckPos + 1] == Y_VOWELS[yVowel])
			 {
				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
					 &katakana[ヤ].katakanaRow[yVowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

				 wordCheckPos += MULTI_BYTE;
			 }
		 }

		 //大文字パ行
		 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
		 {
			 if (magicKnightAction.m_inputWords[wordCheckPos] == 'p' &&
				 magicKnightAction.m_inputWords[wordCheckPos + 1] == VOWELS[vowel])
			 {
				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
					 &katakana[パ].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

				 break;
			 }
		 }

		 //大文字パ行
		 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
		 {
			 if (magicKnightAction.m_inputWords[wordCheckPos] == 'p' &&
				 magicKnightAction.m_inputWords[wordCheckPos + 1] == 'y'&&
				 magicKnightAction.m_inputWords[wordCheckPos + 2] == VOWELS[vowel])
			 {
				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
					 &katakana[パ].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos + 2], sizeof(char)*MULTI_BYTE,
					 &CONSTANT_PLUS_Y[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

				 break;
			 }
		 }

		 const char DULLS_MAX = 4;
		 const char DULL_CONSTANTS[] = { "gzdb" };

		 //大文字ガザバダ行
		 for (int dull = 0; dull < DULLS_MAX; dull++)
		 {
			 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
			 {
				 if (magicKnightAction.m_inputWords[wordCheckPos] == DULL_CONSTANTS[dull] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == VOWELS[vowel])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[ガ + dull].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }
			 }
		 }

		 //大文字ガザバダ行+小文字ヤ行
		 for (int dull = 0; dull < DULLS_MAX; dull++)
		 {
			 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
			 {
				 if (magicKnightAction.m_inputWords[wordCheckPos] == DULL_CONSTANTS[dull] &&
					 magicKnightAction.m_inputWords[wordCheckPos + 1] == 'y'&&
					 magicKnightAction.m_inputWords[wordCheckPos + 2] == VOWELS[vowel])
				 {
					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
						 &katakana[ガ + dull].katakanaRow[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos + 2], sizeof(char)*MULTI_BYTE,
						 &CONSTANT_PLUS_Y[vowel*MULTI_BYTE], sizeof(char)*MULTI_BYTE);

					 break;
				 }
			 }
		 }

		 //nnでのン
		 if (magicKnightAction.m_inputWords[wordCheckPos] == 'n' &&
			 magicKnightAction.m_inputWords[wordCheckPos + 1] == 'n')
		 {
			 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
				 &katakana[ン].katakanaRow[0], sizeof(char)*MULTI_BYTE);
		 }

		 int notVowelCheckCount = 0;

		 //kkiでッkなどのッ,アイウエオはできない
		 if (_ismbblead(magicKnightAction.m_inputWords[wordCheckPos]) &&
			 _ismbbtrail(magicKnightAction.m_inputWords[wordCheckPos]))
		 {
			 continue;
		 }

		 for (int vowel = 0; vowel < VOWELS_MAX; vowel++)
		 {
			 if (memcmp(&magicKnightAction.m_inputWords[wordCheckPos],&VOWELS[vowel],sizeof(char)*MULTI_BYTE))
			 {
				 notVowelCheckCount++;
			 }
		 }

		 if (notVowelCheckCount >= VOWELS_MAX)
		 {
			 if (magicKnightAction.m_inputWords[wordCheckPos] == 
				 magicKnightAction.m_inputWords[wordCheckPos + 1])
			 {
				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos + 2], sizeof(char),
					 &magicKnightAction.m_inputWords[wordCheckPos], sizeof(char));

				 memcpy_s(&magicKnightAction.m_inputWords[wordCheckPos], sizeof(char)*MULTI_BYTE,
					 &katakana[ッ].katakanaRow[0], sizeof(char)*MULTI_BYTE);
			 }
		 }
	 }

	return;
}
