#pragma once

class uiMileStone {
public:
		uiMileStone();
		~uiMileStone();

	void Process(int x, int start, int end);
	void Draw();
protected:
	// �摜�n���h��
	int _cgMileStone;						// �}�C���X�g�[���̉摜
	int _cgPlayerPosDisplay;			// �v���C���[�̑��s�ʒu�̉摜
	// ���W
	float _mileStone_x;					// �}�C���X�g�[����x���W
	float _mileStone_y;					// �}�C���X�g�[����y���W
	float _playerPosDisplay_x;		// ���s�ʒu��x���W
	float _playerPosDisplay_y;		// ���s�ʒu��y���W
	// �����p
	float _mapDistance;					// �}�b�v�̋���
	float _ranRate;							// �ǂ̒��x���������̊���
	float _uiMapDistance;				// UI�}�b�v�̋���
};




