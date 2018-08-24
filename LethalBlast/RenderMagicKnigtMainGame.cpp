#define _CRT_SECURE_NO_WARNINGS

#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlCharaChoice.h"
#include"ControlMagicKnightMainGame.h"

//static MagicKnightDeck magicKnightDecks[MAGIC_KNIGHT_DECKS_MAX];
//static MagicKnightPlayingDeck magicKnightPlayingDeck;
//static MagicKnightAction magicKnightAction;
//CustomVertex handWordCollisionsVertex[HAND_WORD_MAX*RECT_VERTEX_NUM];
//CustomVertex magicKnightActionCollisionsVertex[MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX*RECT_VERTEX_NUM];

void RenderMagicKnightMainGame(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex, TEXTUREID* wordTexIds)
{
	static TEXTUREID collisionTestTexId;
	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/TestRect.png", &collisionTestTexId);

		frameCount = 0;
	}

	for (int handWord = 0; handWord < HAND_WORD_MAX; ++handWord)
	{
		DrawImage(pHandWordCollisionsVertex[handWord].ImageVertex, wordTexIds[(pMagicKnightPlayingDeck->m_handWordId[handWord])]);
	}

	for (int actionComponentWord = 0; actionComponentWord < MAGIC_KNIGHT_ACTION_COMPONENT_WORDS_MAX; ++actionComponentWord)
	{
		DrawImage(pMagicKnightActionCollisionsVertex[actionComponentWord].ImageVertex, wordTexIds[(pMagicKnightAction->m_componentWordIds[actionComponentWord])]);
	}

	return;
}

void RenderWhileLoad(SCENE* scene,SCENE destScene, TEXTUREID* wordTexIds)
{
	static TEXTUREID LoadTexId;

	static int frameCount = INIT_FRAME;

	if (frameCount == INIT_FRAME)
	{
		RoadTexture("texture/Load/LoadScene.png", &LoadTexId);
		RoadTexture("Texture/MKWord/VOID_WORD.png", &wordTexIds[VOID_WORD]);

		
		FILE* pWordTexPathsFile;

		pWordTexPathsFile = fopen("Files/TexturePaths/MKWordTexPaths.csv", "r");

		for (int word = VOID_WORD + 1; word < MAGIC_KNIGHT_WORD_MAX; ++word)
		{
			char mkWordPath[60];

			fscanf(pWordTexPathsFile, "%s,", mkWordPath);

			RoadTexture(mkWordPath, &wordTexIds[word]);
		}

 		fclose(pWordTexPathsFile);

		frameCount = 0;
	}

	CustomVertex LoadScene[4];

	CustomImageVerticies(LoadScene, DISPLAY_WIDTH / 2.f-15, DISPLAY_HEIGHT / 2.f-35, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f);

	DrawImage(LoadScene, LoadTexId);

	*scene = destScene;

	return;
}
