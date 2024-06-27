// �S���F����

/*
	�v���C���[�̌��݂̃X�s�[�h��\������UI
*/

#include "DxLib.h"
#include "uispeedometer.h"

/*
	@brief	�R���X�g���N�^
*/
UISpeedoMeter::UISpeedoMeter() {
	// �摜�ǂݍ���
	LoadDivGraph("res/UI/speedometer.png", 7, 7, 1, 200, 200, &_cgSpeedMeter[0]);
	// �ϐ�������
	_speed = 0;
	_drawSpeed = 0;
}

/*
	@brief	�f�X�g���N�^
*/
UISpeedoMeter::~UISpeedoMeter() {
	// �摜�폜
	for (int i = 0; i < 7; i++) {
		DeleteGraph(_cgSpeedMeter[i]);
	}
}

/*
	@brief	�Z�b�^�[
	@param	speed�F���݂̃X�s�[�h
*/
void	UISpeedoMeter::Set(int speed) {
	_speed = speed;
}

/*
	@brief	�Q�b�^�[
	@return	_speed�F���݂̃X�s�[�h
*/
int		UISpeedoMeter::Get() {
	return _speed;
}

/*
	@brief	�X�V
	@param	speed		�F���݂̃X�s�[�h
	@param	min			�F�X�s�[�h�̍ŏ��l
	@param	max			�F�X�s�[�h�̍ő�l
	@param	cangeAmount	�F�X�s�[�h�̕ω���
*/
void	UISpeedoMeter::Process(int speed, int min, int max, int cangeAmount) {
	// player�̃X�s�[�h���烁�[�^�[�̐��l�����߂�
	// �X�s�[�h��0�Ȃ�ڐ����\��
	if (speed == 0) { _speed = 0; }
	// ����ȊO�Ȃ�X�s�[�h�ɉ������ڐ����\��
	else if(speed != 0){
		for (int i = 1; i < 7; i++) {
			// �X�s�[�h���ڐ���̍ŏ��l�ȏ�ő�l�ȉ��Ȃ�ڐ����\��
			if (speed == cangeAmount * (i - 1) + min) {
				_speed = i;
				break;
			}
		}
	}
	// �`��ڐ�������߂�
	_drawSpeed = _speed;
}

/*
	@brief	�`��
*/
void	UISpeedoMeter::Draw() {
	// ���ׂ�speed��`��
	DrawGraph(20, 100, _cgSpeedMeter[_drawSpeed], TRUE);
}
