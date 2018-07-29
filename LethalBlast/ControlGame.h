#pragma once
#include"WinMain.h"

/*
*メインゲームシーンにおける操作関係
*(引数1)SCENE* シーンを操作するため変数のアドレスを渡す
*/
void ControlGame(SCENE* scene);

/*
*円と円の当たり判定を調べる
*戻り値 円と円が接触していたならtrueそれ以外はfalseを返す
*/
bool CheckCirculeCollisionDetection(float circuleAPosX, float circuleAPosY, float circuleAhalfScale, float circuleBPosX, float circuleBPosY, float circuleBhalfScale);
