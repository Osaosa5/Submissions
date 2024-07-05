// �S���F����

/*
	�Q�[���̃G���f�B���O����
*/

#include "DxLib.h"
#include "gamemain.h"
#include "SceneGameEnding.h"
#include "SceneGameTitle.h"

/*
	@brief	SceneGameEnding�̃R���X�g���N�^
*/
SceneGameEnding::SceneGameEnding() {
	// �摜�ǂݍ���
	_cgBg		= LoadGraph("res/cgBg/ending.png");
	// ���y�ǂݍ���
	bgm_ending	= LoadSoundMem("res/sound/Anxious.mp3");

	// �t���O������
	ed	= FALSE;
	end = FALSE;
}

/*
	@brief	SceneGameEnding�̃f�X�g���N�^
*/
SceneGameEnding::~SceneGameEnding() {
	// �O���t�B�b�N���������ォ��폜����
	// �w�i�폜
	DeleteGraph(_cgBg);

	// �������ɓǂ݂��񂾉��f�[�^���폜����
	// �G���f�B���O�폜
	DeleteSoundMem(bgm_ending);
}

/*
	@brief	SceneGameEnding�̏���
*/
void SceneGameEnding::Process() {
	// ����step���擾
	int step = _fade->GetStep();
	switch (step) {
	case 0:
		// FI�J�n
		_fade->ColorFadeIn(1);
		// ���̃X�e�b�v��
		step++;
		break;
	case 1:
		// �t�F�[�h�C���͏I���������H
		if (_fade->IsColorFade() == 0) {
			// ����Đ�
			ed = TRUE;
			// ���̃X�e�b�v��
			step++;
		}
		break;
	case 2:
		// b�{�^���œ���X�L�b�v
		if (gTrg & PAD_INPUT_4) {
			ed = FALSE;
		}
		if (ed == FALSE) {
			// �G���h��ʕ`��
			end = TRUE;
			// ���̃X�e�b�v��
			step++;
		}
		break;
	case 3:
		// bgm�Đ�
		PlaySoundMem(bgm_ending, DX_PLAYTYPE_LOOP);
		// FI�J�n
		_fade->ColorFadeIn(0);
		// ���̃X�e�b�v��
		step++;
		break;
	case 4:
		// �ʏ폈��
		if (gTrg & PAD_INPUT_4) {
			// �t�F�[�h�A�E�g�J�n
			_fade->ColorFadeOut(0, 0, 0, 30);
			// ���̃X�e�b�v��
			step++;
		}
		break;
	case 5:
		// �t�F�[�h�A�E�g�͏I���������H
		if (_fade->IsColorFade() == 0) {
			// step������
			step = 0;
			// �t�F�[�h�A�E�g�I��
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
		}
		break;
	}
	_fade->SetStep(step);
}

/*
	@brief	SceneGameEnding�̕`��
*/
void SceneGameEnding::Draw() {
	// ed��TRUE�Ȃ�Đ�
	if (ed == TRUE) {
		PlayMovie("res/staging/ed.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		// ����폜
		ed = FALSE;
	}
	// end��TRUE�Ȃ�`��
	if (end == TRUE) {
		DrawGraph(0, 0, _cgBg, FALSE);
	}
}