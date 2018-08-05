#include<windows.h>
#include<math.h>
#include"DX9Lib.h"
#include"WinMain.h"
#include"ControlGame.h"

void ControlGame(SCENE* scene)
{
	return;
}

bool CheckCirculeCollisionDetection(float circuleAPosX,float circuleAPosY,float circuleAhalfScale, float circuleBPosX, float circuleBPosY, float circuleBhalfScale)
{
	float centerDistance = (float)sqrt(pow(circuleAPosX - circuleBPosX, 2) + pow(circuleAPosY - circuleBPosY, 2));

	float totalHalfScale = circuleAhalfScale + circuleBhalfScale;

	if (centerDistance <= totalHalfScale)
	{
		return true;
	}

	return false;
}

void CreateHomingVect(Vect* dest,float objAPosX,float objAPosY, float objBPosX, float objBPosY,Vect prevPerceivedShortestRouteUnitVect,float degreeLimit)
{
	float centerDistance = (float)sqrt(pow(objAPosX - objBPosX, 2) + pow(objAPosY - objBPosY, 2));

	//操作している円への最短ルートを指す単位ベクトル
	Vect shortestRouteUnitVect;

	shortestRouteUnitVect.m_x = (objAPosX - objBPosX) / centerDistance;
	shortestRouteUnitVect.m_y = (objAPosY - objBPosY) / centerDistance;

	//内積を用いて現在のベクトルと操作している円への最短ルートへのベクトル角度を出している
	double rad = acos(shortestRouteUnitVect.m_x * prevPerceivedShortestRouteUnitVect.m_x + shortestRouteUnitVect.m_y * prevPerceivedShortestRouteUnitVect.m_y);

	//外積を用いて角度の符号を確かめている
	double cross = (double)(shortestRouteUnitVect.m_x * prevPerceivedShortestRouteUnitVect.m_y - shortestRouteUnitVect.m_y * prevPerceivedShortestRouteUnitVect.m_x);

	//ホーミングする円の前回のベクトルと現在のベクトルの角度の制限
	const double RAD_LIMIT = (double)(degreeLimit*PI / 180.f);

	//ホーミングする円が認識している操作している円への最短ルートを指す単位ベクトル
	Vect perceivedShortestRouteUnitVect = { shortestRouteUnitVect.m_x,shortestRouteUnitVect.m_y };

	//角度の制限を超えた場合に制限と同じ角度にする
	if (cross < 0)
	{
		if (RAD_LIMIT < rad)
		{
			perceivedShortestRouteUnitVect.m_x = prevPerceivedShortestRouteUnitVect.m_x * cos(RAD_LIMIT) - prevPerceivedShortestRouteUnitVect.m_y * sin(RAD_LIMIT);
			perceivedShortestRouteUnitVect.m_y = prevPerceivedShortestRouteUnitVect.m_x * sin(RAD_LIMIT) + prevPerceivedShortestRouteUnitVect.m_y * cos(RAD_LIMIT);
		}
	}

	if (0 < cross)
	{
		if (RAD_LIMIT < rad)
		{
			perceivedShortestRouteUnitVect.m_x = prevPerceivedShortestRouteUnitVect.m_x * cos(-RAD_LIMIT) - prevPerceivedShortestRouteUnitVect.m_y * sin(-RAD_LIMIT);
			perceivedShortestRouteUnitVect.m_y = prevPerceivedShortestRouteUnitVect.m_x * sin(-RAD_LIMIT) + prevPerceivedShortestRouteUnitVect.m_y * cos(-RAD_LIMIT);
		}
	}

	//アンダーフロー時角度が虚数になる
	if (isnan(rad))
	{
		perceivedShortestRouteUnitVect.m_x = prevPerceivedShortestRouteUnitVect.m_x * cos(-RAD_LIMIT) - prevPerceivedShortestRouteUnitVect.m_y * sin(-RAD_LIMIT);
		perceivedShortestRouteUnitVect.m_y = prevPerceivedShortestRouteUnitVect.m_x * sin(-RAD_LIMIT) + prevPerceivedShortestRouteUnitVect.m_y * cos(-RAD_LIMIT);
	}

	//初回のprevPerceivedShortestRouteUnitVect対策
	if (prevPerceivedShortestRouteUnitVect.m_x == -perceivedShortestRouteUnitVect.m_x&&prevPerceivedShortestRouteUnitVect.m_y == -perceivedShortestRouteUnitVect.m_y)
	{
		perceivedShortestRouteUnitVect.m_x = prevPerceivedShortestRouteUnitVect.m_x * cos(RAD_LIMIT) - prevPerceivedShortestRouteUnitVect.m_y * sin(RAD_LIMIT);
		perceivedShortestRouteUnitVect.m_y = prevPerceivedShortestRouteUnitVect.m_x * sin(RAD_LIMIT) + prevPerceivedShortestRouteUnitVect.m_y * cos(RAD_LIMIT);
	}

	//物体が止まってしまった場合に乱数を用い単位ベクトルを設定する
	if (!perceivedShortestRouteUnitVect.m_x && !perceivedShortestRouteUnitVect.m_y)
	{
		Vect perceivedShortestRouteVect;

		perceivedShortestRouteVect.m_x = rand() % 10 * (rand() % 2) ? 1 : -1;
		perceivedShortestRouteVect.m_y = rand() % 10 * (rand() % 2) ? 1 : -1;

		double perceivedShortestRouteSyntheticVect = sqrt(pow(perceivedShortestRouteVect.m_x, 2) + pow(perceivedShortestRouteVect.m_y, 2));

		perceivedShortestRouteUnitVect.m_x = perceivedShortestRouteVect.m_x / perceivedShortestRouteSyntheticVect;
		perceivedShortestRouteUnitVect.m_y = perceivedShortestRouteVect.m_y / perceivedShortestRouteSyntheticVect;
	}

	//渡された構造体にコピーする
	dest->m_x = perceivedShortestRouteUnitVect.m_x;
	dest->m_y = perceivedShortestRouteUnitVect.m_y;

	return;
}

//bool check2DOBBCollisionDetection(CustomVertex* objA, CustomVertex* objB)
//{
//	Vect objA01;
//
//	CalculateDistanceBetweenTwoPoints(Vect* objA01,);
//}

double CalculateDistanceBetweenTwoPoints(double pointAPosX, double pointAPosY, double pointBPosX, double pointBPosY)
{
	double pointsDistance = sqrt(pow(pointAPosX - pointBPosX, 2) + pow(pointAPosY - pointBPosY, 2));

	return pointsDistance;
}

void CalculateDistanceBetweenTwoPointsXY(Vect* dest,double pointAPosX, double pointAPosY, double pointBPosX, double pointBPosY)
{
	Vect pointsDistance = { sqrt(pow(pointAPosX - pointBPosX, 2)),sqrt(pow(pointAPosY - pointBPosY, 2)) };

	dest->m_x = pointsDistance.m_x;
	dest->m_y = pointsDistance.m_y;

	return;
}

double CalculateDot(Vect vectA, Vect vectB)
{
	double dot = vectA.m_x*vectB.m_x + vectA.m_y*vectB.m_y;

	return dot;
}
