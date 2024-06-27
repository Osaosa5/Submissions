// �S���F����

/*
	�v���C���[��HP��\������UI
*/

#include "DxLib.h"
#include "uilife.h"

/*
	@brief	�R���X�g���N�^
*/
UILife::UILife() {
	// �摜�̓ǂݍ���
	_cgHeart_loss = LoadGraph("res/UI/heart-black.png");
	_cgHeart = LoadGraph("res/UI/heart.png");
	_cgDie = LoadGraph("res/effect/about_to_die.png");
	// ������
	_UIlife = 0;
	_lifeCnt = 0;
}

/*
	@brief	�f�X�g���N�^
*/
UILife::~UILife() {
	// �摜�̍폜
	DeleteGraph(_cgHeart_loss);
	DeleteGraph(_cgHeart);
}

/*
	@brief	�Z�b�^�[
	@param	life�FHP
*/
void	UILife::Set(int life) {
	_UIlife = life;
}

/*
	@brief	���X�n�[�g�Z�b�^�[
	@return	_UIlife�F���݂�HP
*/
int		UILife::Get() {
	return _UIlife;
}

/*
	@brief	�X�V
*/
void	UILife::Process() {
	// ���C�t��1�̎��ɓ_��
	if (_UIlife == 1) _lifeCnt++;
	// ���C�t��1���̎��͓_�ł��Ȃ�
	else _lifeCnt = 0;
}

// �`��
void	UILife::Draw() {

	// ���C�t��1�̎��͉�ʂ��Ԃ��Ȃ�
	if (_UIlife == 1) DrawGraph(0, 0, _cgDie, TRUE);
	// �摜��`�悷�����W
	int base_x = 40, base_y = 25;

	// �n�[�g�̃T�C�Y
	int heart_w = 84, heart_h = 70;
	int heart_one = 1;		// �ЂƂ̃n�[�g��life�������\�����邩

	// life���n�[�g�ŕ`��
	int x, y, w;
	x = 0; y = 0;
	w = 80;			// �n�[�g�ƃn�[�g�̃X�L�}
	int life = _UIlife;
	for (int i = 0; i < 320; i += w) {
		// �����n�[�g��`��
		DrawGraph(base_x + i, base_y, _cgHeart_loss, TRUE);
	}
	while(life > 0) {
		// _lifeCnt��60�Ŋ������]�肪30�����̎��Ƀn�[�g��`��
		if (_lifeCnt % 60 < 30) {
			DrawGraph(base_x + x, base_y + y, _cgHeart, TRUE);
		}
		life -= heart_one;	// �n�[�g�ЂƂ����C�t�����炷
		x += w;	// ���̃n�[�g�ʒu��
	}
}
