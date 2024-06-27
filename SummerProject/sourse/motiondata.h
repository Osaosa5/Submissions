#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�

// �L�����N�^����e�[�u��
struct CHARA_MOTION_ITEM 
{
	int		frameId;	// �\���������t���[��ID
	int		frameCnt;	// ���t���[���\�����邩
	int		mx, my;		// �\�����A1�t���[��������ړ�����l
};

// �P���[�V����������A���[�V�����A�C�e���������܂ŏ����邩
#define	CHARA_MOTION_ITEM_MAX			64
#define ITEM_MOTION_ITEM_MAX			64
#define EFFECT_MOTION_ITEM_MAX			64

// ���[�V�����A�C�e���p�R�}���h�BframeId �Ɏw�肵�Ďg���BframeId�Əd�����Ă͂����Ȃ�
// �R�}���h�̓t���[���I�����ɏ�������邽�߁A�ŏ��̃t���[���ɂ͎w��ł��Ȃ��d�l
#define	CHARA_MOTION_CMD_LOOP			1	// ���[�V���������[�v����(frameCnt�Ƀ��[�V����index�w��)
#define	CHARA_MOTION_CMD_MOTION			2	// �ʂ̃��[�V������(frameCnt�Ƀ��[�V�����ԍ��w��)
#define CHARA_MOTION_CMD_MAINTENANCE	3	// ���[�V�������ێ�����
#define	CHARA_MOTION_CMD_PLAYSE			4	// ���ʉ��Đ�(frameCnt��SE_xxxx)
#define CHARA_MOTION_CMD_PLAYSE_STOP	5	// ���ʉ���~
#define	CHARA_CMD_OBSTACLE_HIT			6	// �R���e�i�t���O���I�t

struct CHARA_MOTION 
{
	CHARA_MOTION_ITEM	item[CHARA_MOTION_ITEM_MAX];
};

// ���[�V�����ԍ��B0�Ԃ���̒ʂ��ԍ��ł��邱��
// �v���C���[
#define	MOTION_WALK						0
#define	MOTION_DAMAGE					1
#define	MOTION_JUMP_UP 					2
#define MOTION_JUMP_DOWN				3
#define MOTION_MOVING_LEFT				4
#define MOTION_MOVING_RIGHT				5
// �A�C�e��
#define MOTION_BATTERY					10
#define MOTION_HEART					11
#define MOTION_JET						12

extern struct CHARA_MOTION tblMotion_chara[];
