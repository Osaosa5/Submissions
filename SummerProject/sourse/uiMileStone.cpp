// �S���F����

/*
	�v���C���[�����݃X�e�[�W�̂ǂ��ɂ��邩��\������UI
*/

#include "uiMileStone.h"
#include "DxLib.h"

/*
	@brief	�R���X�g���N�^
*/
uiMileStone::uiMileStone() { 
	// �摜�ǂݍ���
	_cgPlayerPosDisplay	= LoadGraph("res/UI/UI_Face.png");
	_cgMileStone		= LoadGraph("res/UI/location.png");
	// ���W�ݒ�
	_mileStone_x		= 265;
	_mileStone_y		= 980;
	_playerPosDisplay_x	= 0;
	_playerPosDisplay_y	= _mileStone_y;
	// �����p�ϐ�������
	_mapDistance	= 0;
	_ranRate		= 0;
	_uiMapDistance	= 1264;
}

/*
	@brief	�f�X�g���N�^
*/
uiMileStone::~uiMileStone() { 
	// �摜�폜
	DeleteGraph(_cgPlayerPosDisplay);
	DeleteGraph(_cgMileStone);
}

/*
	@brief	�X�V
	@param	x		�F�v���C���[�̑��s����
	@param	start	�F�R�[�X�̃X�^�[�g�n�_
	@param	end		�F�R�[�X�̃S�[���n�_
*/
void uiMileStone::Process(int x, int start, int end) {
	// �R�[�X�̑��s����
	_mapDistance		= end - start;
	// �v���C���[�̑���������
	_ranRate			= x / _mapDistance;
	// �v���C���[�̑�����������UI�ɔ��f������
	_playerPosDisplay_x = _ranRate * _uiMapDistance + _mileStone_x;
}

/*
	@brief	�`��
*/
void uiMileStone::Draw() {
	// �}�C���X�g�[���̕`��
	DrawGraph(_mileStone_x, _mileStone_y + 10, _cgMileStone, TRUE);
	// �v���C���[���s�ʒu
	DrawGraph(_playerPosDisplay_x, _playerPosDisplay_y, _cgPlayerPosDisplay, TRUE);
}