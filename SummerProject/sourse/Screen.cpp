// �S���F����

/*
	�w�i��X�N���[���Ȃǂ̉�ʊ֌W�̏������܂Ƃ߂�����
*/

#include "DxLib.h"
#include "WinMain.h"
#include "SceneAction.h"

/*
	@brief	��ʊ֌W�̏�����
*/
void SceneAction::InitScreen()
{
	// �X�N���[���̏�����
	gScrollX = 0;
	gScrollY = 0;
}

/*
	@brief	�X�N���[���̏���
*/
void SceneAction::ProcessScreen()
{
	// ��ʂ̍����Ƀv���C���[������悤�ɂ���
	gScrollX = pl.x - SCREEN_W / 8;
	gScrollY = pl.y - SCREEN_H / 8;

	// �X�N���[�����}�b�v�f�[�^�O�܂ł��Ȃ��悤�ɐ���
	if (gScrollX < 0) { gScrollX = 0; }
	if (gScrollX + SCREEN_W >= MAPSIZE_W * CHIP_W) { gScrollX = MAPSIZE_W * CHIP_W - SCREEN_W; }
	if (gScrollY < 0) { gScrollY = 0; }
	if (gScrollY + SCREEN_H >= MAPSIZE_H * CHIP_H) { gScrollY = MAPSIZE_H * CHIP_H - SCREEN_H; }

}

/*
	@brief	�w�i�`��
*/
void SceneAction::DrawScreen()
{
	for (int i = 0; i < 122400; i += 1920)
	{
		DrawGraph(i - gScrollX, 0, _cgBg, FALSE);
	}
}