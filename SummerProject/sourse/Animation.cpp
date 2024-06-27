#include "DxLib.h"
#include "SceneAction.h"

// tblFrame[] �̔z��ԍ����AframeId�Œ��ׂ�
int SceneAction::SearchFrame(int frameId) 
{
	int n = 0;
	while(tblFrame_chara[n].frameId != -1) 
	{
		if(tblFrame_chara[n].frameId == frameId) 
		{
			// ���������B[n]���z��ԍ�
			return n;
		}
		n++;
	}
	// ������Ȃ������i�{�����Ă͂����Ȃ��j
	return -1;
}

// �L�����̃��[�V�����ύX�w��
void SceneAction::CharaChangeMotion(int charaIndex, int motion) 
{
	if(_gChara[charaIndex].motId != motion) 
	{
		_gChara[charaIndex].motId = motion;
		_gChara[charaIndex].motcnt = 0;
		_gChara[charaIndex].animcnt = 0;
	}
}

void SceneAction::ProcessCharacter() 
{
	int i;
	for(i = 0; i < CHARA_MAX; i++) 
	{

		if(_gChara[i].type != CHARA_TYPE_NONE) 
		{
			//
			// ���ʏ����i�O�j
			//

			int motChg = -1;		// ���[�V������ύX����ꍇ�A�����Ɏw�肷��

			int x = pl.x + pl.hit_x;
			int y = pl.y * pl.hit_y;
			int w = pl.hit_w - 1;
			int h = pl.hit_h - 1;

			//
			// �^�C�v�ʌʏ���
			//

			switch(_gChara[i].type) 
			{
			case CHARA_TYPE_PLAYER:
			{	// �v���C���[
				// ���݂̃��[�V�����ɂ���đ���𕪂���
				switch(_gChara[i].motId) 
				{
				case MOTION_WALK:
				{	// ���s
					motChg = MOTION_WALK;

					if((gTrg & PAD_INPUT_3 || gTrg & PAD_INPUT_4) && gameStart == 1)	 // 3,4 = C,A�L�[
					{	
						motChg = MOTION_JUMP_UP;
					}

					int x = pl.x + pl.hit_x;
					int y = pl.y + pl.hit_y;
					int w = pl.hit_w - 1;
					int h = pl.hit_h - 1;
					if(pl.stand == 1) 
					{
						if(pl.obstacleHit == 1) 
						{
							motChg = MOTION_DAMAGE;		// �_���[�W���[�V����
						}
					}
					if (playerSlopeFlag == 1) 
					{
						if (gTrg & PAD_INPUT_UP && gameStart == 1) 
						{
							motChg = MOTION_MOVING_LEFT;
						}
						if (gTrg & PAD_INPUT_DOWN && gameStart == 1) 
						{
							motChg = MOTION_MOVING_RIGHT;
						}
					}
					break;
				}

				case MOTION_MOVING_LEFT:
				{	// ��i��l�����猩�č��j�Ɉړ���
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// �_���[�W���[�V����
					}
					if(playerMoveFlag == 1) 
					{
						motChg = MOTION_WALK;
					}
					break;
				}

				case MOTION_MOVING_RIGHT:
				{	//	���i��l�����猩�ĉE�j�Ɉړ���
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// �_���[�W���[�V����
					}
					//playerSlopeFlag
					if(playerMoveFlag == 1) 
					{
						motChg = MOTION_WALK;
					}
					break;
				}

				case MOTION_JUMP_UP:
				{	// �W�����v�㏸��
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// �_���[�W���[�V����
					}
					if(pl.gravity >= 0) 
					{
						motChg = MOTION_JUMP_DOWN;
					}
					break;
				}
				case MOTION_JUMP_DOWN:
				{	// �W�����v���~��
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// �_���[�W���[�V����
					}
					if(pl.stand != 0) 
					{
						//PlaySoundMem(_se[SE_LANDING], DX_PLAYTYPE_BACK);
						if (pl.speed_x > 10) 
						{
							pl.speed_x -= 5;
						}
						motChg = MOTION_WALK;
					}
					break;
				}
				}
				break;
			}
			}


			//
			// ���ʏ����i��j
			//

			// ���[�V�����͕ύX����Ȃ����H
			if(motChg == -1 || motChg == _gChara[i].motId) 
			{
				// ���[�V�������ړ�
				// mx,my�Ɉړ��l�𓾂�
				int mx, my;
				mx = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].mx;
				my = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].my;

				// �ړ����Ă݂�B�܂������蔻��͂��Ă��Ȃ�
				_gChara[i].x += mx;
				_gChara[i].y += my;

				// ���̃��[�V�����̂܂܂Ȃ̂ŁA�J�E���^��i�߂�
				_gChara[i].animcnt++;

				// ���[�V�����̍��̃t���[���͏I���������H
				if(tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt <= _gChara[i].animcnt) 
				{
					// ���̃t���[����
					_gChara[i].motcnt++;
					_gChara[i].animcnt = 0;

					// ���̃t���[���̓R�}���h���H
					// �R�}���h�������A���ŏ����ł���悤�ɁA���[�v�������Ă���
					int loop = 1;
					while(loop == 1) 
					{
						// �R�}���h����
						switch(tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameId) 
						{
						case CHARA_MOTION_CMD_LOOP:
						{	// ���[�V���������[�v������
							int motionIndex = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							_gChara[i].motcnt = 0;
							break;
						}
						case CHARA_MOTION_CMD_MOTION:
						{	// �ʂ̃��[�V������(frameCnt�̓��[�V����ID)
							int motionId = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							CharaChangeMotion(i, motionId);
							loop = 0;	// ���[�v�I��
							break;
						}
						case CHARA_MOTION_CMD_MAINTENANCE:
						{	// ���[�V�����̕ێ�
							loop = 1;
							break;
						}
						case CHARA_MOTION_CMD_PLAYSE:
						{	// ���ʉ��Đ�(frameCnt��SE_xxxx)
							int seId = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							PlaySoundMem(_se[seId], DX_PLAYTYPE_BACK, TRUE);
							_gChara[i].motcnt++;
							break;
						}
						case CHARA_MOTION_CMD_PLAYSE_STOP:
						{	// ���ʉ���~
							int seId = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							StopSoundMem(_se[seId]);
							_gChara[i].motcnt++;
							break;
						}
						case CHARA_CMD_OBSTACLE_HIT:
						{	// ��Q���Փ˃t���O���I�t�ɂ���
							pl.obstacleHit = 0;
						}

						default:
						{	// �R�}���h����Ȃ������̂Ń��[�v�I��
							loop = 0;
						}
						}
					}
				}
			}

			// ���[�V�����͕ύX����邩�H
			if(
				motChg != -1 && motChg != _gChara[i].motId) 
			{
				// ���ƕʂ̃��[�V�����ɕύX
				CharaChangeMotion(i, motChg);
			}
		}
	}
}