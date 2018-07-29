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
	float centerDistance = sqrt(pow(circuleAPosX - circuleBPosX, 2) + pow(circuleAPosY - circuleBPosY, 2));

	float totalHalfScale = circuleAhalfScale + circuleBhalfScale;

	if (centerDistance <= totalHalfScale)
	{
		return true;
	}

	return false;
}
