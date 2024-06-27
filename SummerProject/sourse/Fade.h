#pragma once

class Fade
{
public:
	Fade();		// �R���X�g���N�^
	~Fade();	// �f�X�g���N�^

	// // �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha=255�ɂ���j
	void ColorFadeOut(float colorR, float colorG, float colorB, float frames);
	// // �J���[�}�X�N�̎w��
	void ColorMask(float colorR, float colorG, float colorB, float colorA);
	// // ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha=0�ɂ���j
	void ColorFadeIn(float frames);
	// // �t�F�[�h�C���A�E�g�͏I���������H �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I��(�������͊J�n�O)
	int IsColorFade();

public:
	void MainProcess();
	void Draw();

public:
	int GetStep();
	void SetStep(int step);

protected:
	// �J���[�}�X�N�p
	float gColorMaskR, gColorMaskG, gColorMaskB, gColorMaskA;
	// �t�F�[�h�C���A�E�g�p
	float gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
	float gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
	float gFadeFrames, gFadeCnt;
	// switch�p
	int _step;
};

