#pragma once

void RenderMagicKnightMainGame(WordData* pMagicKnightWordDatas, MagicKnightDeck* pMagicKnightDecks,
	MagicKnightPlayingDeck* pMagicKnightPlayingDeck, MagicKnightAction* pMagicKnightAction,
	ImagesCustomVertex* pHandWordCollisionsVertex, ImagesCustomVertex* pMagicKnightActionCollisionsVertex, TEXTUREID* wordTexIds);

void RenderWhileLoad(SCENE* scene, SCENE destScene, TEXTUREID* wordTexIds);
