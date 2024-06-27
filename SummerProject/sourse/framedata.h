#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "ItemData.h"

// �L�����N�^�t���[���\����
// 1���̃t���[���Ɋւ���ݒ�
struct CHARA_FRAME 
{
	int		frameId;	// �t���[��ID�B�ŗL�̔ԍ���U��
	int		cgId;		// �g�p�摜�ԍ� cgChara[]
	int		cx, cy;		// �摜�̊�_�B
	int		w, h;		// �摜�T�C�Y
};

struct ITEM_FRAME 
{
	int		frameId;	// �t���[��ID�B�ŗL�̔ԍ���U��
	int		cgId;		// �g�p�摜�ԍ� cgChara[]
	int		cx, cy;		// �摜�̊�_�B
	int		w, h;		// �摜�T�C�Y
};

struct EFFECT_FRAME
{
	int		frameId;	// �t���[��ID�B�ŗL�̔ԍ���U��
	int		cgId;		// �g�p�摜�ԍ� cgChara[]
	int		cx, cy;		// �摜�̊�_�B
	int		w, h;		// �摜�T�C�Y
};

extern struct CHARA_FRAME tblFrame_chara[];

extern struct ITEM_FRAME tblFrame_item[];

extern struct EFFECT_FRAME tblFrame_effect[];


