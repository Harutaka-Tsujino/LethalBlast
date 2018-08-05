#include"DX9Lib.h"
#include"WinMain.h"

void RenderPV(SCENE* scene)
{
	static int frameCount = -1;
	enum MAGIC_RASER_TEX
	{
		MR_0,MR_1,MR_2,MR_3,MR_4,MR_5,MR_MAX
	};

	static TEXTUREID magicRaserTex[MR_MAX];

	if (frameCount == -1)
	{
		RoadTexture("Texture/Effect/MagicRaser/MagicRaserIntegrated/MagicRaser0.png",
			&magicRaserTex[MR_0]);
		RoadTexture("Texture/Effect/MagicRaser/MagicRaserIntegrated/MagicRaser1.png",
			&magicRaserTex[MR_1]);
		RoadTexture("Texture/Effect/MagicRaser/MagicRaserIntegrated/MagicRaser2.png",
			&magicRaserTex[MR_2]);
		RoadTexture("Texture/Effect/MagicRaser/MagicRaserIntegrated/MagicRaser3.png",
			&magicRaserTex[MR_3]);
		RoadTexture("Texture/Effect/MagicRaser/MagicRaserIntegrated/MagicRaser4.png",
			&magicRaserTex[MR_4]);
		RoadTexture("Texture/Effect/MagicRaser/MagicRaserIntegrated/MagicRaser5.png",
			&magicRaserTex[MR_5]);

		frameCount = 0;
	}

	CustomVertex MagicRaser[4];

	CustomImageVerticies(MagicRaser, DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_HEIGHT / 2.f, DISPLAY_HEIGHT / 2.f);

	const float MAGIC_RASER_ILLUST_WIDTH = 512.f;
	const int SEPARATE_ILLUST_NUM = 16;
	const int MAGIC_RASER_ANIMATION_FRAME = 6;

	//frameCount%(SEPARATE_ILLUST_NUM*MAGIC_RASER_ANIMATION_FRAME)) / MAGIC_RASER_ANIMATION_FRAME 
	//フレームカウントが大きすぎても範囲内に戻す
	SetImageTuTv(MagicRaser, MagicRaser, MAGIC_RASER_ILLUST_WIDTH*(int)((frameCount%(SEPARATE_ILLUST_NUM*MAGIC_RASER_ANIMATION_FRAME)) / MAGIC_RASER_ANIMATION_FRAME), 0.f,
		MAGIC_RASER_ILLUST_WIDTH, MAGIC_RASER_ILLUST_WIDTH, MAGIC_RASER_ILLUST_WIDTH*SEPARATE_ILLUST_NUM, MAGIC_RASER_ILLUST_WIDTH);

	//(frameCount % (SEPARATE_ILLUST_NUM* MAGIC_RASER_ANIMATION_FRAME*MR_MAX) / (SEPARATE_ILLUST_NUM* MAGIC_RASER_ANIMATION_FRAME)
	//フレームカウントが大きすぎても範囲内に戻す
	DrawImage(MagicRaser, magicRaserTex[(frameCount % (SEPARATE_ILLUST_NUM* MAGIC_RASER_ANIMATION_FRAME*MR_MAX))
		/ (SEPARATE_ILLUST_NUM* MAGIC_RASER_ANIMATION_FRAME)]);

	const int INTEGRATED_MAGIC_RASER_REST = 2;
	if (frameCount >= (SEPARATE_ILLUST_NUM * MAGIC_RASER_ANIMATION_FRAME*(MR_MAX-1))+ INTEGRATED_MAGIC_RASER_REST)
	{
		*scene = TITLE_SCENE;

		return;
	}

	frameCount++;

		return;
}
