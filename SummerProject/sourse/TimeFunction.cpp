// �S���F����

/*
	����/�X�^�[�g�֌W�̊֐��̏������܂Ƃ߂�����
*/

#include "DxLib.h"
#include "WinMain.h"
#include "SceneAction.h"

/*
	@brief	�Q�[���X�^�[�g�O�����̏�����
*/
void SceneAction::InitStartPreprocessing() {
	// �X�^�[�g�t���O������
	gameStart				= 0;
	operationDescription	= 1;
	startSignal				= 0;
	startCnt				= -1;
}

/*
	@brief	�Q�[���X�^�[�g�O����
*/
void SceneAction::ProcessBeforeStart() {
	// �Q�[���X�^�[�g�@
	// B�{�^������������3�J�E���g�J�n
	if(gTrg & PAD_INPUT_4 && operationDescription == 1) {
		operationDescription = 0;
		startCnt = 250;
	}
	// �J�E���g��50�ɂȂ�����ustart�v��\��
	if(startCnt == 50)  startSignal = 1;
	// �J�E���g��1�ɂȂ�����ustart�v���\��
	if(startCnt == 1)	startSignal = 0;
	// �J�E���g��0�ɂȂ�����Q�[�����J�n����
	if(startCnt == 0) {
		gameStart = 1;
		gameStartTime = GetNowCount();
		pl.speed_x = 10;
		PlaySoundMem(_bgm[BGM_STAGE_ONE], DX_PLAYTYPE_LOOP);
	}
	// cnt�����炷
	if(startCnt != -1) { startCnt--; }
}

/*
	@brief	�Q�[���X�^�[�g�O�����̕`��
*/
void SceneAction::DrawStartPreprocessing() {
	// ��������̉摜��`��
	if(operationDescription == 1) {
		DrawGraph(0, 0, _cgOperationDescription, FALSE);
	}
	// 3�J�E���g�`��
	int num = 0;
	if(startCnt <= 230) num = NUMBER_ZERO;
	if(startCnt <= 170) num = NUMBER_ONE;
	if(startCnt <= 110)	num = NUMBER_TWO;
	if(startCnt <= 50)  num = -1;
	// �J�E���g�`��ʒu
	int cnt_x = (SCREEN_W / 2) - 150;
	int cnt_y = SCREEN_H / 2 - 150;
	// 0�͕`�悵�Ȃ�
	if(num > -1) {
		if((startCnt - 50) % 60 == 0) PlaySoundMem(_se[SE_CNT], DX_PLAYTYPE_BACK);
		DrawGraph(cnt_x, cnt_y, _cgCntNumber[num], TRUE);
	}
	// �ustart�v�`��ʒu
	int start_x = (SCREEN_W / 2) - 450;
	int start_y = SCREEN_H / 2 - 150;
	if(startSignal == 1) {
		if(startCnt == 49) PlaySoundMem(_se[SE_START], DX_PLAYTYPE_BACK);
		DrawGraph(start_x, start_y, _cgStart, TRUE);
	}
}

/*
	@brief	�������ԏ����̏�����
*/
void SceneAction::InitLimitTime() {
	// �������Ԃ��Z�b�g
	gameLimitTime	= 120000;	
	// �Q�[���X�^�[�g���Ԃ�������
	gameStartTime	= 0;
	// �Q�[���̌o�ߎ��Ԃ�������
	gameElapsedTime = 0;
	// �`��p�̐������Ԃ�������
	drawLimitTime	= 0;
}

/*
	@brief	�������ԏ���
*/
void SceneAction::ProcessLimitTime() {
	// �Q�[�����X�^�[�g���Ă����玞�Ԃ��v��
	if(gameStart == 1) {
		// �|�[�Y��ʂ��J�������Ԃ�ۑ�����ϐ��Ɍ��݂̎��Ԃ��擾
		oldTime			= GetNowCount();
		// �Q�[���̌o�ߎ��Ԃ��v��
		// ���݂̎��� - �Q�[���X�^�[�g����
		gameElapsedTime = GetNowCount() - gameStartTime;
	}
	// �`��p�̐������Ԃ��v�Z
	// �������� - �o�ߎ���
	drawLimitTime = gameLimitTime - gameElapsedTime;
}

/*
	@brief	�������Ԃ�`��
*/
void SceneAction::DrawLimitTime() {
	// ���݂̎��Ԃ�b�ɕϊ�
	int second		= drawLimitTime / 1000;
	// ���ɕϊ�
	int minutes		= second / 60;
	// �b�ɕϊ�(�\�̈�)
	int second_10	= second % 60 / 10;
	// �b�ɕϊ�(��̈�)
	int second_1	= second % 60 - second_10 * 10;
	// �~���b��`��
	int ms_10		= (drawLimitTime / 10) % 10;
	int ms_100		= (drawLimitTime / 100) % 10;

	// ���Ԃ�`�悷��ʒu
	int time_x = 780;
	int time_y = 45;
	int time_w = 48;

	// �������Ԃ̌��ɕ`�悷��{�b�N�X�̈ʒu
	int box_w = 430;
	int box_h = 110;
	int box_x = (SCREEN_W - box_w) / 2;
	int box_y = 30;

	// ��������̉摜��\�����Ă��Ȃ��Ƃ��ɁA�������Ԃ�`�悷��
	if(operationDescription == 0) {
		DrawGraph(box_x, box_y, _cgLimitTimeBox, TRUE);

		DrawGraph(time_x, time_y, _cgNumber[minutes], TRUE);

		DrawGraph(time_x + time_w, time_y, _cgNumber[NUMBER_KOLON], TRUE);

		DrawGraph(time_x + time_w * 2, time_y, _cgNumber[second_10], TRUE);

		DrawGraph(time_x + time_w * 3, time_y, _cgNumber[second_1], TRUE);

		DrawGraph(time_x + time_w * 4, time_y, _cgNumber[NUMBER_KOLON], TRUE);

		DrawGraph(time_x + time_w * 5, time_y, _cgNumber[ms_100], TRUE);

		DrawGraph(time_x + time_w * 6, time_y, _cgNumber[ms_10], TRUE);
	}
}