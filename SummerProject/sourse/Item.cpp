// �S���F����

/*
	�A�C�e���̏����Ɋւ���֐�
*/

#include "DxLib.h"
#include "SceneAction.h"
#include "ItemData.h"

/*
	@brief	�A�C�e���Ɋւ���ϐ��̏�����
*/
void SceneAction::InitItem() {
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		_gItem[i].use = 1;
		_gItem[i].x = itemData[i].x;
		_gItem[i].y = itemData[i].y;
		_gItem[i].w = ITEM_WIDTH;
		_gItem[i].h = ITEM_HEIGHT;
		_gItem[i].lane = AddObjectLane(_gItem[i].y);
		_gItem[i].high = 20;
		_gItem[i].type = itemData[i].type;
		_gItem[i].stand = itemData[i].stand;
	}

	// �t���O�̏�����
	shouldGotBattery = 0;
	shouldGotHeart = 0;
	shouldGotJet = 0;
	// �J�E���g�̏�����
	batteryEffectStartTime = 0;
	// �X�s�[�h�A�b�v,�_�E�������\���̏�����
	drawCount = 0;

	// �o���A�G�t�F�N�g�̃��[�h 
	if(ef_barrier->Check() == false) 
	{
		ef_barrier->Load("res/effect/barrier.png", 30, 30, 1, 210, 210);
		ef_barrier->SetWaitFrame(0);
		ef_barrier->SetLoop(10);
	}

	// �񕜃G�t�F�N�g�̃��[�h
	ef_healing->Load("res/effect/healing.png", 30, 30, 1, 360, 180);
	ef_healing->SetWaitFrame(2);

	// �����G�t�F�N�g�̃��[�h
	ef_firespark->Load("res/effect/blue_firespark.png", 30, 30, 1, 210, 70);
	ef_firespark->SetWaitFrame(0);
	ef_firespark->SetLoop(2);
}

/*
	@brief	�A�C�e���Ɋւ���t���O��0�ɂ���
*/
void SceneAction::ProcessItemFlag() 
{
	// �G�t�F�N�g�ibarrier�j
	// �o�b�e���[����
	if(shouldGotBattery == 1) 
	{
		// 5�b��������t���O��0�ɂ���
		if(GetNowCount() - batteryEffectStartTime > 5000)
		{
			shouldGotBattery = 0;
		}
	}

	// �񕜏���
	if(shouldGotHeart == 1) 
	{
		// HP��4�����ł����HP��1�񕜂���
		if(_UIlife.Get() < 4)
		{
			_life++;
			_UIlife.Set(_life);
		}
		shouldGotHeart = 0;
	}

	// ��������
	if(shouldGotJet == 1)
	{
		drawCount = MAX_SPEEDUP_COUNT;
		// �v���C���[�̃X�s�[�h���グ��
		pl.speed_x += 5;
		shouldGotJet = 0;
	}

	if (drawCount > 0) { drawCount--; }
}

/*
	@brief	�A�C�e���̗l�X�ȏ������܂Ƃ߂�����
*/
void SceneAction::ProcessItem()
{
	ProcessItemFlag();			// �t���O�֌W�̏���

	HitCheckPlayerItem();		// �v���C���[�ƃA�C�e���̏���

	ef_barrier->Process();		// �G�t�F�N�g����(barrier)
	ef_healing->Process();		// �G�t�F�N�g����(healing)
	ef_firespark->Process();	// �G�t�F�N�g����(firespark)
}

/*
	@brief	�A�C�e���̕`�揈��
*/
void SceneAction::DrawItem() 
{
	int x, y;
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		x = _gItem[i].x * CHIP_W - gScrollX;
		switch(_gItem[i].stand) {
		case 0:		// ��
			y = _gItem[i].y * CHIP_H - _gItem[i].high * 4 - gScrollY;
			break;

		case 1:		// �n��
			y = _gItem[i].y * CHIP_H - _gItem[i].high - gScrollY;
			break;
		}
		// use��1�Ȃ�`�悷��
		if(_gItem[i].use == 1) {
			int yy = _gItem[i].y * CHIP_H;
			_shadow->DrawItem(x, yy);
			// type�ɂ���ĕ`�悷��A�C�e����ς���
			if(_gItem[i].type == BATTERY) DrawGraph(x, y, _cgItem[ITEM_BATTERY], TRUE);
			if(_gItem[i].type == HEART) DrawGraph(x, y, _cgItem[ITEM_HEART], TRUE);
			if(_gItem[i].type == JET) DrawGraph(x, y, _cgItem[ITEM_JET], TRUE);
		}
	}

	int xx, yy;	// �X�N���[����z�肵���L����x,y������
	xx = pl.x - gScrollX;
	yy = pl.y - gScrollY + pl.high;

	// �X�s�[�h�A�b�v�̕����`��
	if (drawCount > 0) 
	{
		if(_UIspeedoMeter->Get() < 6) 
		{
			SetFontSize(32);
			DrawFormatString(xx + 50, yy - 20, GetColor(255, 0, 0), "�X�s�[�hUP");
		}
	}
}

