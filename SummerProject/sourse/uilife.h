#pragma once

class UILife {
public:
	UILife();							// �R���g���N�^
	virtual ~UILife();					// �f�X�g���N�^
										
	void	Process();					// �v�Z
	void	Draw();						// �`��
	void	Set(int life);				// �Z�b�^�[
	void	SetHeart(int life_loss);	// ���X�n�[�g�Z�b�^�[
	int		Get();						// �Q�b�^�[

private:
	int		_cgHeart_loss;				// ���X�n�[�g�`��n���h��
	int		_cgHeart;					// �n�[�g�`��n���h��
	int		_cgDie;						// die���o�n���h��

	int		_UIlife;					// �n�[�g�ێ��ϐ�
	int		_UIlife_loss;				// ���X�n�[�g�ێ��ϐ�

	int		_lifeCnt;
};