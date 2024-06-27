#pragma once

class UISpeedoMeter {
public:
	UISpeedoMeter();						// �R���g���N�^
	virtual ~UISpeedoMeter();			// �f�X�g���N�^

	void	Process(int speed, int min, int max, int cangeAmount);					// �v�Z
	void	Draw();						// �`��
	void	Set(int speedmeter);	// �X�s�[�h�Z�b�^�[
	int		Get();						// �Q�b�^�[

private:
	int		_cgSpeedMeter[7];				// �X�s�[�h���[�^�[�摜�`��n���h��
	int		_speed;
	int		_drawSpeed;
};