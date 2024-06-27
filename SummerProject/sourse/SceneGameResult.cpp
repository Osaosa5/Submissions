// �S���F����

/*
	���U���g����
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneGameResult.h"
#include "SceneGameEnding.h"

/*
	@brief	SceneGameResult�̃R���X�g���N�^
	@param	resultTime:�N���A�^�C��
*/
SceneGameResult::SceneGameResult (int resultTime) {
	// �Z�[�u�ǂݍ���
	_save = new save("save.txt", 5, 120000 - resultTime);
	// �摜�ǂݍ���
	_cgBg = LoadGraph("res/cgBg/result2.png");
	_cgRanking = LoadGraph("res/UI/ranking_hyou.png");
	_cgFade = LoadGraph("res/cgBg/fade.png");
	_cgRetry	= LoadGraph("res/UI/retry.png");
	_cgResult[0] = LoadGraph("res/UI/ui_rank_s.png");
	_cgResult[1] = LoadGraph("res/UI/ui_rank_a.png");
	_cgResult[2] = LoadGraph("res/UI/ui_rank_b.png");
	_cgResult[3] = LoadGraph("res/UI/ui_rank_c.png");
	// Yes or No
	_cgYes[COLLOR_BLUE] = LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE] = LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/No4.png");
	// bgm�ǂݍ���
	_bgmResult = LoadSoundMem("res/sound/Clear_Pallet.mp3");
	_seResult[0] = LoadSoundMem("res/sound/select.mp3");
	_seResult[1] = LoadSoundMem("res/sound/determination.mp3");

	// �ϐ��̏�����
	_rank = 0;
	// �t���O������
	_isRanking = FALSE;
	_isContinue = FALSE;
	// ��������N���A�^�C�����Z�b�g
	_resultTime = resultTime;
	// �I������������
	menu_Yes = OPTION_YES;
	menu_No = OPTION_NO;
	// �I�����̑���
	menu_Num = _OPTION_ALL_;
	// �I��
	nowSelect = menu_Yes;
	// �J���[�}�X�N�̃��Z�b�g
	_fade->ColorFadeIn(60);
	_save->Export("save.txt", 5);
}

/*
	@brief	SceneGameResult�̃f�X�g���N�^
*/
SceneGameResult::~SceneGameResult() {
	// �O���t�B�b�N���������ォ��폜����
	// �w�i�폜
	DeleteGraph(_cgBg);
	// ���g���C�폜
	DeleteGraph(_cgRetry);
	// �t�F�[�h�폜
	DeleteGraph(_cgFade);
	// �����L���O�폜
	DeleteGraph(_cgRanking);
	// �����N�폜
	for (int i = 0; i < 3; i++) {
		DeleteGraph(_cgResult[i]);
	}
	// �I�����폜
	for (int i = 0; i < 2; i++) {
		DeleteGraph(_cgYes[i]);
		DeleteGraph(_cgNo[i]);
		DeleteGraph(_seResult[i]);
	}
	// �������ɓǂ݂��񂾉��f�[�^���폜����
	// bgm�폜
	DeleteSoundMem(_bgmResult);
}

/*
	@brief	SceneGameResult�̏���
*/
void SceneGameResult::Process() {
	// ����step���擾
	int step = _fade->GetStep();
	// �X�e�b�v���Ƃ̏���
	switch (step) {
	case 0:
		// �N���A�^�C�����烉���N�����߂�
		if(_resultTime < 56000)	_rank = 1;
		if(_resultTime < 41000)	_rank = 2;
		if(_resultTime < 26000)	_rank = 3;
		// FI�J�n
		_fade->ColorFadeIn(10);
		PlaySoundMem(_bgmResult, DX_PLAYTYPE_LOOP);
		// ���̃X�e�b�v��
		step++;
		break;
	case 1:
		// �t�F�[�h�C���͏I���������H
		if (_fade->IsColorFade() == 0) {
			// B�L�[�Ŏ��̃X�e�b�v��
			if (gTrg & PAD_INPUT_4) {	
				step++;
			}
		}
		break;
	case 2:
		
		_isRanking = TRUE;
		// B�L�[�Ŏ��̃X�e�b�v��
		if (gTrg & PAD_INPUT_4) {	
			_isContinue = TRUE;
			step++;
		}
		break;
	case 3:
		// �I�������������
		if (gTrg & PAD_INPUT_RIGHT) {
			nowSelect = (nowSelect + 1) % menu_Num;
			PlaySoundMem(_seResult[0], DX_PLAYTYPE_BACK);
		}
		// �I��������グ��
		if (gTrg & PAD_INPUT_LEFT) {
			nowSelect = (nowSelect + (menu_Num - 1)) % menu_Num;
			PlaySoundMem(_seResult[0], DX_PLAYTYPE_BACK);
		}
		// �I�����̏���
		switch (nowSelect) {
			// yes��I�����Ă�����
		case OPTION_YES:
			// �ŏ������蒼��
			if (gTrg & PAD_INPUT_4) {	// A�L�[
				// ���艹
				PlaySoundMem(_seResult[1], DX_PLAYTYPE_BACK);
				// �t�F�[�h�A�E�g�J�n
				_fade->ColorFadeOut(0, 0, 0, 40);
				// ���g���C
				_isRetry = TRUE;
				step++;
			}
			break;
			// no��I�����Ă�����
		case OPTION_NO:
			// �Q�[���𑱂���
			if (gTrg & PAD_INPUT_4) {	// A�L�[
				// ���艹
				PlaySoundMem(_seResult[1], DX_PLAYTYPE_BACK);
				// �t�F�[�h�A�E�g�J�n
				_fade->ColorFadeOut(0, 0, 0, 40);
				// �G���f�B���O
				_isEnd = TRUE;
				step++;
			}
			break;
		}
		break;
	case 4:
		if(_fade->IsColorFade() == 0) {
			_isRanking = FALSE;
			if(_isRetry) {
				// SceneAction��ǂݍ��݂Ȃ���
				SceneBase* scene = new SceneAction(0);
				ChangeScene(scene);
				step = 0;
			}
			if(_isEnd) {
				// �V�[���؂�ւ�
				SceneBase* scene = new SceneGameEnding();
				ChangeScene(scene);
				step = 0;
			}
		}
		break;
	}
	_fade->SetStep(step);

}

/*
	@brief	SceneGameResult�̕`��
*/
void SceneGameResult::Draw() {
	// �w�i�`��
	DrawGraph(0, 0, _cgBg, FALSE);
	// �����N�`��
	DrawGraph(50, 100, _cgResult[_rank], TRUE);
	// �����L���O�`��
	if (_isRanking)
	{
		DrawGraph(0, 0, _cgFade, TRUE);
		DrawGraph(474, 239, _cgRanking, TRUE);
		_save->AscendingOrderDataDrawing(810, 250, 120, 100);
	}
	// retry
	if (_isContinue) {
		DrawGraph(0, 0, _cgFade, TRUE);
		// retry?
		DrawGraph(810, 200, _cgRetry, TRUE);
		// yes
		DrawGraph(YES_X, YES_Y, _cgYes[COLLOR_BLUE], TRUE);
		// no
		DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_BLUE], TRUE);
		// �I�����̏���
		switch (nowSelect) {
		case OPTION_YES:
			// yes
			DrawGraph(YES_X, YES_Y, _cgYes[COLLOR_YELLOW], TRUE);
			break;
		case OPTION_NO:
			// no
			DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_YELLOW], TRUE);
			break;
		}
	}
}