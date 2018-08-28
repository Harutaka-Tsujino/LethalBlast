#pragma once
#include"WinMain.h"

//ベクトルの要素を入れる構造体
typedef struct
{
	//x要素
	double m_x;
	//y要素
	double m_y;
}Vect;

/*
*メインゲームシーンにおける操作関係
*(引数)SCENE* scene シーンを操作するため変数のアドレスを渡す
*/
void ControlGame(SCENE* scene);

/*
*円と円の当たり判定を調べる
*(戻り値)bool 円と円が接触していたならtrueそれ以外はfalseを返す
*/
bool CheckCirculeCollisionDetection(float circuleAPosX, float circuleAPosY, float circuleAhalfScale, float circuleBPosX, float circuleBPosY, float circuleBhalfScale);

/*
*ホーミングをするためのベクトルを生成する
*(引数)Vect* dest この構造体に生成したベクトルを詰める
*(引数)Vect* prevPerceivedShortestRouteUnitVect 前回のホーミングベクトル 初回は0で
*(引数)float degreeLimit 前回のホーミングベクトルとの角度制限
*/
void CreateHomingVect(Vect* dest, float objAPosX, float objAPosY, float objBPosX, float objBPosY, Vect prevPerceivedShortestRouteUnitVect, float degreeLimit);

/*
*2点間の距離を求める
*(戻り値)double 2点間の距離 
*/
double CalculateDistanceBetweenTwoPoints(double pointAPosX, double pointAPosY, double pointBPosX, double pointBPosY);

/*
*2点間の距離をベクトルで求める
*(引数)Vect* dest この構造体に生成したベクトルを詰める
*/
void CalculateDistanceBetweenTwoPointsXY(Vect* dest, double pointOPosX, double pointOPosY, double pointDstPosX, double pointDstPosY);

/*
*内積を算出する
*(戻り値)double 大きさ
*/
double Dot(Vect vectA, Vect vectB);

/*
*外積を算出する
*(戻り値)double ベクトル二つで形成される符号ありの平行四辺形
*/
double Cross(Vect vectA, Vect vectB);

/*
*画像を横幅で切り取る
*(引数)startTu posTu	スタート座標からの距離分描画する
*/
void SetTuCustomVertex(CustomVertex* pCustomVertex, FLOAT x1Pos, FLOAT x2Pos, FLOAT x3Pos, FLOAT x4Pos,
	FLOAT y1Pos, FLOAT y2Pos, FLOAT y3Pos, FLOAT y4Pos,
	FLOAT startTu, FLOAT posTu, FLOAT imageSizeTu);

/*
*画像を縦幅で切り取る
*(引数)startTv posTv	スタート座標からの距離分描画する
*/
void SetTvCustomVertex(CustomVertex* pCustomVertex, FLOAT x1Pos, FLOAT x2Pos, FLOAT x3Pos, FLOAT x4Pos,
	FLOAT y1Pos, FLOAT y2Pos, FLOAT y3Pos, FLOAT y4Pos,
	FLOAT startTv, FLOAT posTv, FLOAT imageSizeTv);
/*
*ポリゴンの色を設定する
*/
void GetCustomVerTexColor(CustomVertex* pCustomVertex, DWORD color);
