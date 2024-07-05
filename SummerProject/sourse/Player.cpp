// �S���F����(�`�揈���͏H�i)

/*
	�v���C���[�Ɋւ��鏈�����܂Ƃ߂�����
*/

#include "DxLib.h"
#include "mymath.h"
#include "WinMain.h"
#include "SceneAction.h"
#include "framedata.h"
#include "motiondata.h"

/*
	@brief	�v���C���[�̏�����
*/
void SceneAction::InitPlayer() {
	pl.type				= 0;
	pl.x				= 60;				
	pl.y				= 450;
	pl.w				= 239;
	pl.h				= 239;
	pl.speed_x			= 0;
	pl.speed_y			= 5;
	pl.high				= 0;
	pl.gravity			= 0;
	pl.stand			= 0;
	pl.obstacle			= 0;
	pl.obstacleHit		= 0;
	pl.obstacleLimit	= 1200;
	pl.hit				= 0;
	pl.lane				= AddPlayerLane(pl.y + pl.hit_y);

	InitRect();
	
	playerMoveFlag	= 1;
	playerCnt		= 0;
	start			= 0;
	end				= 0;
	frames			= 8;

	playerSlopeFlag	= 1;

	invincibleTime	= 0;
	timeObstacle	= 0;

	// �t���X�g���[�V�����G�t�F�N�g�̃��[�h
	// �_�Œ�(3�b)�͕\��
	ef_frustration->Load("res/effect/frustration.png", 5, 4, 2, 180, 180);
	ef_frustration->SetWaitFrame(3);
	ef_frustration->SetLoop(9);
}

/*
	@brief	�v���C���[�̃_���[�W����
*/
void SceneAction::DamagePlayer() {
	// ���G�A�C�e�����擾���Ă��Ȃ���΃_���[�W���󂯂�
	if(shouldGotBattery == 0 ) {
		_life--;
		_UIlife.Set(_life);
	}
	ef_frustration->SetStarting(true);	// �t���X�g���[�V�����G�t�F�N�g�̕`��X�^�[�g�t���O
}

/*
	@brief	�v���C���[�̓���
*/
void SceneAction::ProcessPlayer() {

	// �ړ��O�̏ꏊ������Ă���
	int old_x = pl.x;
	int old_y = pl.y;

	// �v���C���[�ƃ��[���O�̓����蔻��
	HitCheckPlayerWall(old_x, old_y);

	// �v���C���[�Ə�Q���̓����蔻��
	HitCheckPlayerObstacle();

	ef_frustration->Process();		// �G�t�F�N�g���� (frustration)

	
	// speed����
	if (pl.obstacleHit == TRUE) {
		// ��Q���ɂԂ�������X�s�[�h��0�ɂ���
		pl.speed_x = 0;
	}
	else {
		// �X�s�[�h��35�ȏ�ɂȂ�Ȃ��悤�ɂ���
		if (pl.speed_x >= 35) pl.speed_x = 35;
		// �X�s�[�h��10�ȉ��ɂȂ�Ȃ��悤�ɂ���
		else if (pl.speed_x <= 10) pl.speed_x = 10;
	}

	// ����̏ꏊ�܂ňړ�
	if(pl.x <= DISTANCE_LIMIT && pl.obstacleHit == FALSE) { pl.x += pl.speed_x; }
	
	// �L�[���͂𔻒肵�āA��l�����ړ�������
	pl.lane = AddPlayerLane(pl.y + pl.hit_y);
	// �n��ɂ��違�Ԃ����Ă��Ȃ������͎�t���Ɉړ�
	if(pl.stand == 1 && pl.obstacleHit == FALSE && playerMoveFlag == 1) {
		// 1���[���łȂ���Ώ�Ɉړ��ł���
		if(gTrg & PAD_INPUT_UP && pl.lane != 1) {
			playerCnt		= 0;
			start			= pl.y;
			end				= start - CHIP_H;
			playerMoveFlag	= 0;
		}
		// 4���[���łȂ���Ή��Ɉړ��ł���
		if(gTrg & PAD_INPUT_DOWN && pl.lane != 4) { 
			playerCnt		= 0;
			start			= pl.y;
			end				= start + CHIP_H;
			playerMoveFlag	= 0;
		}
	}

	// �v���C���[�̃��[���ړ�
	if(playerMoveFlag == 0) {
		pl.y = EasingLinear(playerCnt, start, end, frames);
	}
	// �ړ����Ȃ̂ŁA���̃��[���ɒ����܂ő���𐧌�����
	if(playerCnt >= frames) {
		playerMoveFlag = 1;
	}
	// �v���C���[�̈ړ��J�E���g��i�߂�
	playerCnt++;

	// A���邢��B�{�^���ŃW�����v
	if(gTrg & PAD_INPUT_4 && pl.stand == 1 && pl.obstacleHit == 0 && playerMoveFlag == 1)
	{
		if(shouldGotJet == 0) { pl.gravity = -17; }
	}
	else if(gTrg & PAD_INPUT_3 && pl.stand == 1 && pl.obstacleHit == 0 && playerMoveFlag == 1)
	{
		if(shouldGotJet == 0) { pl.gravity = -17; }
	}

	// �W�����v����
	pl.gravity++;				// ���~�X�s�[�h�����Z
	pl.high		+= pl.gravity;	// �v���C���[�̍�����������
	pl.stand	= 0;			// �v���C���[�̒��n�t���O��0�ɂ���

	// �v���C���[���n�ʂɂ���ꍇ�A�߂荞�܂Ȃ��悤�ɂ���
	if(pl.high > 0) {
		pl.high		= 0;	// �v���C���[�̍�����0�ɂ���
		pl.gravity	= 0;	// �v���C���[�̉��~�X�s�[�h��0�ɂ���
		pl.stand	= 1;	// �v���C���[�̒��n�t���O��1�ɂ���
	}
}

/*
	@brief	�v���C���[�̕`��
*/
void SceneAction::DrawPlayer() {
	int i, x, y;	// �X�N���[����z�肵���L����x,y������
	x = pl.x - gScrollX;
	y = pl.y - gScrollY + pl.high;

	// �L�����`��
	for(i = 0; i < CHARA_MAX; i++) {
		if(_gChara[i].type != CHARA_TYPE_NONE) {
			// �L�����̃��[�V�����t���[��������𓾂�
			int motId = _gChara[i].motId;
			CHARA_MOTION_ITEM* item = tblMotion_chara[motId].item;
			int frameId = item[_gChara[i].motcnt].frameId;
			int _frameId = SearchFrame(frameId);
			int cgId = tblFrame_chara[_frameId].cgId;
			if(invincibleTime % 10 < 7) {
				DrawGraph(x, y, _cgPlayer[cgId], TRUE);
			}
		}
	}

	// �G�t�F�N�g�`��ifrustration�j
	ef_frustration->SetXY(x - 20, y - 100);
	ef_frustration->Draw();

}

