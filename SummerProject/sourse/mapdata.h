#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "mymath.h"

class MapData 
{
public:
	MapData(int stageNumber);			// �R���X�g���N�^
	virtual ~MapData();	// �f�X�g���N�^

	void	Draw(int scrollX, int scrollY);		// �}�b�v�`��

	// �����蔻��֘A					// �L�����ƃ}�b�v�`�b�v�̓����蔻��

	int		CheckHitMapChip(int x, int y);											// �w��ʒu�̃`�b�v�������蔻�肠�肩�H
	int		CheckHitChip(int chip_no);												// �w��̃`�b�vID�������蔻�肠�肩�H
	int		IsHitCharaMap(int hit_x, int hit_y, int hit_w, int hit_h, int number);	// �L�����ƃ}�b�v�`�b�v�̓����蔻�菈��

// �}�b�v�`�b�v�֘A
#define	CHIPSIZE_W	120		 // �`�b�v�̉��T�C�Y
#define	CHIPSIZE_H	120		 // �`�b�v�̏c�T�C�Y
// �}�b�v�f�[�^				 
#define	MAPSIZE_W	1020		 // �}�b�v�̉��T�C�Y
#define	MAPSIZE_H	9		 // �}�b�v�̏c�T�C�Y
	
// �`�b�v��
#define CHIP_NUM	4

protected:
	int _gMapData[MAPSIZE_W * MAPSIZE_H];	// �}�b�v�f�[�^�i�[�ϐ�
	int	_cgChip[CHIP_NUM];							// �`�b�v�摜�n���h��
	int _stageNumber;						// ���݂̃X�e�[�W�i���o�[
};

