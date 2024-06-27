// �S���F����

/*
	�^�C�g������
*/

#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "SceneGameTitle.h"
#include "SceneAction.h"

/*
	@brief	SceneGameTitle�̃R���X�g���N�^
*/
SceneGameTitle::SceneGameTitle() {
	// �摜�ǂݍ���
	_cgSchool	= LoadGraph("res/UI/AMG-LOGO.png");
	_cgLogo		= LoadGraph("res/UI/team_logo.png");
	_cgBg		= LoadGraph("res/cgBg/title.png");
	_cgStart	= LoadGraph("res/UI/ui_press_start_button.png");
	// ���y�ǂݍ���
	bgm_title	= LoadSoundMem("res/sound/Electric_Highway.mp3");

	// �t���O������
	school = FALSE;
	logo = FALSE;
	op = FALSE;
	start = FALSE;

	// time�֌W������
	instrumentationStart = 0;
	latency = 0;
}

/*
	@brief	SceneGameTitle�̃f�X�g���N�^
*/
SceneGameTitle::~SceneGameTitle() {
	DeleteGraph(_cgSchool);
	DeleteGraph(_cgLogo);
	DeleteGraph(_cgBg);
	DeleteSoundMem(bgm_title);
}

/*
	@brief	SceneGameTitle�̏���
*/
void SceneGameTitle::Process() {
	// ����step���擾
	int step = _fade->GetStep();
	// step�ŏ�����ς���
	switch (step) {
	case 0:
		// �v���J�n
		instrumentationStart = GetNowCount();
		// �w�Z���S�`��
		school = TRUE;
		// FI�J�n
		_fade->ColorFadeIn(50);
		// ���̃X�e�b�v��
		step++;
		break;
	case 1:
		// �t�F�[�h�C���͏I���������H
		if (_fade->IsColorFade() == 0) {
			// 2�b�o�������H
			if (GetNowCount() - instrumentationStart > LATENCY) {
				// �t�F�[�h�A�E�g�J�n
				_fade->ColorFadeOut(0, 0, 0, 60);
				// ���̃X�e�b�v��
				step++;
			}
		}
		break;
	case 2:
		// �t�F�[�h�A�E�g�͏I���������H
		if (_fade->IsColorFade() == 0) {
			// �w�Z���S�폜
			school = FALSE;
			// �v���J�n
			instrumentationStart = GetNowCount();
			// �`�[�����S�`��
			logo = TRUE;
			// FI�J�n
			_fade->ColorFadeIn(50);
			// ���̃X�e�b�v��
			step++;
		}
		break;
	case 3:
		// �t�F�[�h�C���͏I���������H
		if (_fade->IsColorFade() == 0) {
			// 2�b�o�������H
			if (GetNowCount() - instrumentationStart > LATENCY) {
				// �t�F�[�h�A�E�g�J�n
				_fade->ColorFadeOut(0, 0, 0, 40);
				// ���̃X�e�b�v��
				step++;
			}
		}
		break;
	case 4:
		// �t�F�[�h�A�E�g�͏I���������H
		if (_fade->IsColorFade() == 0) {
			// �`�[�����S�폜
			logo = FALSE;
			// ���̃X�e�b�v��
			step++;
		}
		break;
	case 5:
		// ����Đ�
		op = TRUE;
		// ���̃X�e�b�v��
		step++;
		break;
	case 6:
		// b�{�^���œ���X�L�b�v
		if (gTrg & PAD_INPUT_4) {
			op = FALSE;
		}
		if (op == FALSE) {
			// �t�F�[�h�A�E�g�J�n
			_fade->ColorFadeOut(0, 0, 0, 40);
			// ���̃X�e�b�v��
			step++;
		}
		break;
	case 7:
		// �t�F�[�h�A�E�g�͏I���������H
		if (_fade->IsColorFade() == 0) {
			// �X�^�[�g��ʕ`��
			start = TRUE;
			// FI�J�n
			_fade->ColorFadeIn(60);
			// bgm�Đ�
			PlaySoundMem(bgm_title, DX_PLAYTYPE_LOOP);
			// ���̃X�e�b�v��
			step++;
		}
		break;
	case 8:
		// �t�F�[�h�C���͏I���������H
		if (_fade->IsColorFade() == 0) {
			// �V�[���؂�ւ�����
			if (gTrg & PAD_INPUT_12 || gTrg & PAD_INPUT_10) {
				// �t�F�[�h�A�E�g�J�n
				_fade->ColorFadeOut(0, 0, 0, 10);
				// ���̃X�e�b�v��
				step++;
			}
		}
		break;
	case 9:
		// �t�F�[�h�A�E�g�͏I���������H
		if (_fade->IsColorFade() == 0) {
			// �X�^�[�g��ʍ폜
			start = FALSE;
			// step������
			step = NULL;
			// �t�F�[�h�A�E�g�I��
			SceneBase* scene = new SceneAction(0);
			ChangeScene(scene);
		}
		break;
	}
	_fade->SetStep(step);
}

/*
	@brief	SceneGameTitle�̕`��
*/
void SceneGameTitle::Draw() {
	// school��TRUE�Ȃ�`��
	if (school == TRUE) {
		int x = SCREEN_W / 2 - 640;
		int y = SCREEN_H / 2 - 84;
		DrawGraph(x, y, _cgSchool, TRUE);
	}
	// logo��TRUE�Ȃ�`��
	if (logo == TRUE) {
		DrawGraph(0, 0, _cgLogo, TRUE);
	}
	// op��TRUE�Ȃ�Đ�
	if (op == TRUE) {
		PlayMovie("res/staging/OP.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		// ����폜
		op = FALSE;
	}
	// start��TRUE�Ȃ�`��
	if (start == TRUE) {
		// �w�i�`��
		DrawGraph(0, 0, _cgBg, FALSE);
		int start_w = 500;
		int start_h = 150;
		int x = (SCREEN_W - start_w) / 2 - 15;
		int y = (SCREEN_H + start_h * 3) / 2 - 35;
		// �X�^�[�g�{�^���`��
		DrawGraph(x, y, _cgStart, TRUE);	
	}
}