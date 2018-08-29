#pragma once

enum RESULT_TEX
{
	GAME_OVER_TEX,
	STAGE_CLEAR_TEX,
	RESULT_TEX_MAX,
};

void OperateResultScene(SCENE* scene, bool isClear);
