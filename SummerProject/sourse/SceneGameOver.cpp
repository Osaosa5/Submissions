// �S���F����

/*
	�Q�[���I�[�o�[����
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneGameOver.h"
#include "SceneGameTitle.h"
#include "SceneAction.h"

/*
	@brief	SceneGameOver�̃R���X�g���N�^
*/
SceneGameOver::SceneGameOver() {
	// �w�i
	_cgBg = LoadGraph("res/cgBg/gameover.png");

	// continue?
	_cgContinue = LoadGraph("res/UI/gameover/continue2.png");

	// Yes or No
	_cgYes[COLLOR_BLUE] = LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE] = LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/No4.png");

	// bgm
	bgm_gameover = LoadSoundMem("res/sound/��.mp3");
	// se
	se[SE_SELECT_] = LoadSoundMem("res/sound/select.mp3");						// �I����
	se[SE_DETERMINATION_] = LoadSoundMem("res/sound/determination.mp3");		// ���艹
	
	// �I������������
	option.menu_Yes = OPTION_YES;
	option.menu_No	= OPTION_NO;
	
	// �I�����̑���
	option.menu_Num = _OPTION_ALL_;

	// �I��
	nowSelect = option.menu_Yes;

	// �t���O������
	retry = FALSE;
	end = FALSE;
}

/*
	@brief	SceneGameOver�̃f�X�g���N�^
*/
SceneGameOver::~SceneGameOver() {
	// �O���t�B�b�N���������ォ��폜����
	// �w�i�폜
	DeleteGraph(_cgBg);
	// continue�폜
	DeleteGraph(_cgContinue);
	// ���ڍ폜
	for (int i = 0; i < _OPTION_ALL_; i++) {
		DeleteGraph(_cgYes[i]);
		DeleteGraph(_cgNo[i]);
	}
	// �������ɓǂ݂��񂾉��f�[�^���폜����
	// bgm�폜
	DeleteSoundMem(bgm_gameover);
	// se�폜
	for (int i = 0; i < _SE_ALL_; i++) {
		DeleteGraph(se[i]);
	}
}

/*
	@brief	SceneGameOver�̏���
*/
void SceneGameOver::Process() {
	// ��ʏ���
	int step = _fade->GetStep();	// ���݂̃X�e�b�v���擾
	switch (step) {
	case 0:
		_fade->ColorFadeIn(60);	// 60f��FI
		PlaySoundMem(bgm_gameover, DX_PLAYTYPE_LOOP);	// bgm���Đ�
		step++;	// ���̃X�e�b�v��
		break;
	case 1:
		if (_fade->IsColorFade() == 0) {	// FI�͏I���������H
			// �t�F�[�h�C���I��
			step++;	// ���̃X�e�b�v��
		}
		break;
	case 2:
		// ���C������
		
		// �I�������������
		if (gTrg & PAD_INPUT_DOWN) {	// ���ɓ��͂����H
			nowSelect = (nowSelect + 1) % option.menu_Num;	// ���̑I������I��
			PlaySoundMem(se[SE_SELECT_], DX_PLAYTYPE_BACK);	// �I����
		}
		// �I��������グ��
		if (gTrg & PAD_INPUT_UP) {	// ��ɓ��͂����H
			nowSelect = (nowSelect + (option.menu_Num - 1)) % option.menu_Num;	// ��̑I������I��
			PlaySoundMem(se[SE_SELECT_], DX_PLAYTYPE_BACK);	// �I����
		}
		switch (nowSelect) {	// ����I�����Ă��邩
		case OPTION_YES:	// Yes��I�����Ă���ꍇ
			if (gTrg & PAD_INPUT_4) {	// A�L�[
				PlaySoundMem(se[SE_DETERMINATION_], DX_PLAYTYPE_BACK);	// �I����
				// �t���O�I��
				retry = TRUE;
				// �t�F�[�h�A�E�g�J�n
				_fade->ColorFadeOut(0, 0, 0, 60);
				step++;	// ���̃X�e�b�v��
			}
			break;
		case OPTION_NO:	// No��I�����Ă���ꍇ
			if (gTrg & PAD_INPUT_4) {	// A�L�[
				PlaySoundMem(se[SE_DETERMINATION_], DX_PLAYTYPE_BACK);	// �I����
				// �t���O�I��
				end = TRUE;
				// �t�F�[�h�A�E�g�J�n
				_fade->ColorFadeOut(0, 0, 0, 60);
				step++;	// ���̃X�e�b�v��
			}
			break;
		}
		break;
	case 3:
		if (_fade->IsColorFade() == 0) {	// FO�͏I���������H
			// step������
			step = 0;
			// �t�F�[�h�A�E�g�I��
			if (retry == TRUE) {
				SceneBase* scene = new SceneAction(0);
				ChangeScene(scene);	// ActionScene�ɐ؂�ւ���
			}
			if (end == TRUE) {
				SceneBase* scene = new SceneGameTitle();
				ChangeScene(scene);	// TitleScene�ɐ؂�ւ���
			}
		}
		break;
	}
	_fade->SetStep(step);	// ���݂̃X�e�b�v��ۑ�

}

/*
	@brief	SceneGameOver�̕`��
*/
void SceneGameOver::Draw() {
	// �w�i
	DrawGraph(0, 0, _cgBg, FALSE);
	// continue?
	DrawGraph(410, 100, _cgContinue, TRUE);
	// yes
	DrawGraph(YES_X_, YES_Y_, _cgYes[COLLOR_BLUE], TRUE);
	// no
	DrawGraph(NO_X_, NO_Y_, _cgNo[COLLOR_BLUE], TRUE);

	switch (nowSelect) {
	case OPTION_YES:
		// yes
		DrawGraph(YES_X_, YES_Y_, _cgYes[COLLOR_YELLOW], TRUE);
		break;
	case OPTION_NO:
		// no
		DrawGraph(NO_X_, NO_Y_, _cgNo[COLLOR_YELLOW], TRUE);
		break;
	}
}