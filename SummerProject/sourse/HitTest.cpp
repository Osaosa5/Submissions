// �S���F����

/*
	�����蔻��Ɋւ���֐�
*/

#include "DxLib.h"
#include "SceneAction.h"

/*
	@brief	�����蔻��(��`)�̏�����
*/
void SceneAction::InitRect() 
{
	pl.hit_x = 80;
	pl.hit_y = 150;
	pl.hit_w = 159;
	pl.hit_h = 79;
}

/*
	@brief	�v���C���[�ƕǂ̓����蔻��
	@param	old_x�F�ړ��O�̃v���C���[��X���W
	@param	old_y�F�ړ��O�̃v���C���[��Y���W
*/
void SceneAction::HitCheckPlayerWall(int old_x, int old_y) 
{
	int left = pl.x + pl.hit_x;
	int up = pl.y + pl.hit_y;
	int right = pl.hit_w - 1;
	int down = pl.hit_h - 1;
	if(_mapData->IsHitCharaMap(left, up, right, down, 1) == 1) 
	{
		pl.y = old_y;
	}
}

/*
	@brief	�v���C���[�Ə�Q���̓����蔻��
*/
void SceneAction::HitCheckPlayerObstacle() 
{
	// player�̓����蔻������
	int x = pl.x + pl.hit_x + 120;
	int y = pl.y + pl.hit_y;
	int w = pl.hit_w - 121;
	int h = pl.hit_h - 1;
	// �n��ɂ��邩�H
	if (pl.stand == 1) 
	{
		// ��Q���ɓ������Ă��銎�A�o�b�e���[�i���G�j���擾���Ă��Ȃ���
		if (_mapData->IsHitCharaMap(x, y, w, h, 3) == 1 && shouldGotBattery == 0) 
		{
			// ��e����ł͂Ȃ����H
			if (invincibleTime == 0) 
			{
				// ��Q���ɓ�������
				pl.obstacleHit = 1;
				// �_���[�W����
				DamagePlayer();
				// ��e��̖��G���Ԃ��Z�b�g
				invincibleTime = 180;
			}
			// player�̃X�s�[�h�����Z�b�g
			pl.speed_x = 10;
		}
	}
	// ��e��̖��G���Ԃ��������Ă�����
	if (invincibleTime != 0) 
	{
		invincibleTime--;
	}
}

/*
	@brief	�v���C���[�ƃA�C�e���̓����蔻��
*/
void SceneAction::HitCheckPlayerItem() 
{
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		// player�̓����蔻���`�����
		int x = pl.x + pl.hit_x - gScrollX - 60;
		int y = pl.y + pl.hit_y - pl.high - gScrollY;
		int w = pl.hit_w - 1;
		int h = pl.hit_h - 1;
		// �A�C�e���̓����蔻���`�����
		int item_x = _gItem[i].x * CHIP_W - gScrollX;
		int item_y = _gItem[i].y * CHIP_H - _gItem[i].high - gScrollY;
		int item_w = _gItem[i].w;
		int item_h = _gItem[i].h;
		// player�̓A�C�e���������������H
		if(IsHitBox(x, y, w, h, item_x, item_y, item_w, item_h) == 1) 
		{	
			// ���݂��n��ɂ��邩�A�A�C�e���͕\������Ă��邩
			if(pl.stand == _gItem[i].stand && _gItem[i].use == 1)
			{
				// �A�C�e���̎�ނɂ���ď������ς��
				switch(_gItem[i].type) 
				{
				case BATTERY:	// �[�d�r(�o���A)
					shouldGotBattery = 1;	// �t���O��ON�ɂ���
					PlaySoundMem(_se[SE_BATTERY], DX_PLAYTYPE_BACK);	// se���Đ�
					batteryEffectStartTime = GetNowCount();	// �A�C�e�����擾�������Ԃ��L�^����
					ef_barrier->SetStarting(true);	// �o���A�G�t�F�N�g�`��X�^�[�g�t���O
					break;
				case HEART:	// �n�[�g(��)
					shouldGotHeart = 1;	// �t���O��ON�ɂ���
					PlaySoundMem(_se[SE_HEART], DX_PLAYTYPE_BACK);	// se���Đ�
					ef_healing->SetStarting(true);	// �񕜃G�t�F�N�g�`��X�^�[�g�t���O
					break;
				case JET:	// �W�F�b�g(����)
					shouldGotJet = 1;	// �t���O��ON�ɂ���
					PlaySoundMem(_se[SE_JET], DX_PLAYTYPE_BACK);	// se���Đ�
					ef_firespark->SetStarting(true);  // �����G�t�F�N�g�`��X�^�[�g�t���O
					break;
				}
				_gItem[i].use = 0;	// �擾�����A�C�e�����\���ɂ���
			}
		}
	}
}
