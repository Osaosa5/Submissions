// �S���F����

/*
	�w�i��X�N���[���Ȃǂ̉�ʊ֌W�̏������܂Ƃ߂�����
*/

#include "Shadow.h"
#include "DxLib.h"

/*
	@brief	�w�i�`��
*/
Shadow::Shadow() {
	// �摜�ǂݍ���
	cgShadowPlayer = LoadGraph("res/UI/kage_240_120.png");
	cgShadowItem = LoadGraph("res/UI/kage_120_120.png");
}

/*
	@brief	�f�X�g���N�^
*/
Shadow::~Shadow() {
	DeleteGraph(cgShadowPlayer);
	DeleteGraph(cgShadowItem);
}

/*
	@brief	�v���C���[�̉e��`��
	@param	x:�v���C���[��x���W
	@param	y:�v���C���[��y���W
	@param	scroll_x:�X�N���[����
*/
void Shadow::DrawPlayer(int x, int y, int scroll_x) {
	// ���W
	int _x = x - scroll_x;
	int _y = y;
	DrawGraph(_x, _y, cgShadowPlayer, TRUE);

}

/*
	@brief	�A�C�e���̉e��`��
	@param	x:�A�C�e����x���W
	@param	y:�A�C�e����y���W
*/
void Shadow::DrawItem(int x, int y) {
	int _x = x;
	int _y = y;
	DrawGraph(_x, _y, cgShadowItem, TRUE);
}
