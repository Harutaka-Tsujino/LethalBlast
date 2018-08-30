#include"DX9Lib.h"
#include"WinMain.h"

void OperatePV(SCENE* scene)
{
	static int frameCount = -1;

	const int TEX_MAX = 36;
	static TEXTUREID PVTex[TEX_MAX];

	if (frameCount == -1)
	{
		RoadTexture("Texture/PV/LBtitlerogo_k005.png",&PVTex[0]);
		RoadTexture("Texture/PV/LBtitlerogo_001.png", &PVTex[1]);
		RoadTexture("Texture/PV/LBtitlerogo_002.png", &PVTex[2]);
		RoadTexture("Texture/PV/LBtitlerogo_003.png", &PVTex[3]);
		RoadTexture("Texture/PV/LBtitlerogo_004.png", &PVTex[4]);
		RoadTexture("Texture/PV/LBtitlerogo_005.png", &PVTex[5]);
		RoadTexture("Texture/PV/LBtitlerogo_006.png", &PVTex[6]);
		RoadTexture("Texture/PV/LBtitlerogo_007.png", &PVTex[7]);
		RoadTexture("Texture/PV/LBtitlerogo_008.png", &PVTex[8]);
		RoadTexture("Texture/PV/LBtitlerogo_009.png", &PVTex[9]);
		RoadTexture("Texture/PV/LBtitlerogo_010.png", &PVTex[10]);
		RoadTexture("Texture/PV/LBtitlerogo_011.png", &PVTex[11]);
		RoadTexture("Texture/PV/LBtitlerogo_012.png", &PVTex[12]);
		RoadTexture("Texture/PV/LBtitlerogo_013.png", &PVTex[13]);
		RoadTexture("Texture/PV/LBtitlerogo_014.png", &PVTex[14]);
		RoadTexture("Texture/PV/LBtitlerogo_015.png", &PVTex[15]);
		RoadTexture("Texture/PV/LBtitlerogo_016.png", &PVTex[16]);
		RoadTexture("Texture/PV/LBtitlerogo_017.png", &PVTex[17]);
		RoadTexture("Texture/PV/LBtitlerogo_018.png", &PVTex[18]);
		RoadTexture("Texture/PV/LBtitlerogo_019.png", &PVTex[19]);
		RoadTexture("Texture/PV/LBtitlerogo_020.png", &PVTex[20]);
		RoadTexture("Texture/PV/LBtitlerogo_021.png", &PVTex[21]);
		RoadTexture("Texture/PV/LBtitlerogo_022.png", &PVTex[22]);
		RoadTexture("Texture/PV/LBtitlerogo_023.png", &PVTex[23]);
		RoadTexture("Texture/PV/LBtitlerogo_024.png", &PVTex[24]);
		RoadTexture("Texture/PV/LBtitlerogo_025.png", &PVTex[25]);
		RoadTexture("Texture/PV/LBtitlerogo_026.png", &PVTex[26]);
		RoadTexture("Texture/PV/LBtitlerogo_027.png", &PVTex[27]);
		RoadTexture("Texture/PV/LBtitlerogo_028.png", &PVTex[28]);
		RoadTexture("Texture/PV/LBtitlerogo_029.png", &PVTex[29]);
		RoadTexture("Texture/PV/LBtitlerogo_030.png", &PVTex[30]);
		RoadTexture("Texture/PV/LBtitlerogo_031.png", &PVTex[31]);
		RoadTexture("Texture/PV/LBtitlerogo_032.png", &PVTex[32]);
		RoadTexture("Texture/PV/LBtitlerogo_033.png", &PVTex[33]);
		RoadTexture("Texture/PV/LBtitlerogo_k007.png", &PVTex[34]);
		RoadTexture("Texture/PV/LBtitlerogo_k008.png", &PVTex[35]);

		frameCount = 0;
	}

	static CustomVertex PV[4];
	static CustomVertex PVBack[4];

	if (frameCount < 60)
	{
		CustomImageVerticies(PV, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, GetColor((UCHAR)(4 * frameCount + 15), 255, 255, 255));
	}

	if (frameCount >= 126&& frameCount < 156)
	{
		CustomImageVerticies(PVBack, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, GetColor((UCHAR)(8 * (frameCount-126) + 15), 255, 255, 255));
	}

	DrawImage(PV, PVTex[0]);

	if (frameCount >= 60&& frameCount<126)
	{
		for (int tex = 1; tex < (frameCount - 60) / 2 + 1; ++tex)
		{
			DrawImage(PV, PVTex[tex]);
		}
	}

	if (frameCount >= 126)
	{
		DrawImage(PVBack, PVTex[35]);
		DrawImage(PV, PVTex[34]);
	}

	if (frameCount>=186||g_keyState.keyPush[DIK_RETURN] || g_mouseState.mousePush[LEFT_CLICK])
	{
		*scene = TITLE_SCENE;

		for (int tex = 0; tex < TEX_MAX; ++tex)
		{
			SAFE_RELEASE(PVTex[tex]);//PVTexはTEXTUREID読み込んだ画像を開放している DX9Libをインクルードしなければいけない
		}

		return;
	}

	if (frameCount < 186)
	{
		frameCount++;
	}

	return;
}
