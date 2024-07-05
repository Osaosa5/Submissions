// �S���F����

/*
	�|�[�Y��ʂɊւ���֐�
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneAction.h"

/*
	@brief	�|�[�Y��ʂɊւ���ϐ��̏�����
*/
void SceneAction::InitPouse() {
	// �I������������
	menu_Yes	= OPTION_YES;
	menu_No		= OPTION_NO;

	// �I�����̑���
	menu_Num	= _OPTION_ALL_;

	// �I��
	nowSelect	= menu_Yes;

	oldTime		= 0;
}

/*
	@brief	�|�[�Y��ʂ̏���
*/
void SceneAction::ProcessPouse() {
	// �Q�[�����J�n���Ă��邩�H
	if (gameStart == 1) {
		// start�{�^�����������Ƃ��A
		// �|�[�Y��ʂ��J���Ă��Ȃ���΃|�[�Y��ʂ��J��
		if (gTrg & PAD_INPUT_12) {
			if (pause == 0) { pause = 1; }
		}
		// �|�[�Y��ʂ��J���Ă���Ƃ��̏���
		if(pause == 1) {
			// �I�������������
			if(gTrg & PAD_INPUT_RIGHT) {
				nowSelect = (nowSelect + 1) % menu_Num;
				PlaySoundMem(_se[SE_SELECT], DX_PLAYTYPE_BACK);
			}
			// �I��������グ��
			if(gTrg & PAD_INPUT_LEFT) {
				nowSelect = (nowSelect + (menu_Num - 1)) % menu_Num;
				PlaySoundMem(_se[SE_SELECT], DX_PLAYTYPE_BACK);
			}
			// �I�����̏���
			switch(nowSelect) {
				// yes��I�����Ă�����
			case OPTION_YES:
				// �ŏ������蒼��
				if(gTrg & PAD_INPUT_4) {	// A�L�[
					// ���艹
					PlaySoundMem(_se[SE_DETERMINATION], DX_PLAYTYPE_BACK);
					// SceneAction��ǂݍ��݂Ȃ���
					SceneBase* scene = new SceneAction(0);
					ChangeScene(scene);
				}
				break;

				// no��I�����Ă�����
			case OPTION_NO:
				// �Q�[���𑱂���
				if(gTrg & PAD_INPUT_4) {	// A�L�[
					// ���艹
					PlaySoundMem(_se[SE_DETERMINATION], DX_PLAYTYPE_BACK);
					// �t���O�I�t
					pause = FALSE;
					int difference = GetNowCount() - oldTime;
					gameStartTime += difference;
					int ac = 0;
				}
				break;
			}
		}
	}

	
}

/*
	@brief	�|�[�Y��ʂ̕`��
*/
void SceneAction::DrawPouse() {
	// pause�t���O���I���̎��ɕ`�悷��
	if (pause == 1) {
		// fade
		DrawGraph(0, 0, _cgFade, TRUE);
		// retry?
		DrawGraph(810, 200, _cgRetry, TRUE);
		// yes
		DrawGraph(YES_X, YES_Y, _cgYes[COLLOR_BLUE], TRUE);
		// no
		DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_BLUE], TRUE);

		// �I�����̏���
		// �ǂ��炪�I�΂�Ă��邩�ŏ������ς��
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