#pragma once

#include"DX9Lib.h"
#include"WinMain.h"


enum CHARA_CHOICE_TEX
{
	//�L�����I����ʂ̔w�i
	CHARA_CHOICE_BACKGROUND,

	//�L�����I���Ŏg���ő�摜����
	CHARA_CHOICE_TEX_MAX,
};
enum CHARA_CHOICE_FONT
{
	//�E�F�|���}�X�^�[�̕���
	WEAPON_MASTER_FONT,

	//�}�W�b�N�i�C�g�̕���
	MASIC_KNIGHT_FONT,

	//�l�N���}���T�[�ƃT���i�[�̕���
	NECROMANCER_AND_SUMMONER_FONT,

	//�L�����Ɏg���t�H���g
	CHARA_CHOICE_FONT_MAX,
};

void RenderCharaChoice(SCENE* scene);

void RenderCharaChoiceInit(TEXTUREID* textureIds);

void RenderCharaChoiceBackGround(TEXTUREID* textureIds, FONTID* fontIds);