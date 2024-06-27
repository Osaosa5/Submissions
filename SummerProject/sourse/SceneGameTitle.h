#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"

class SceneGameTitle : public SceneBase {
public:
	SceneGameTitle();			// �R���X�g���N�^
	virtual ~SceneGameTitle();	// �f�X�g���N�^

	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	// �摜�n���h��
	int		_cgSchool;	// �w�Z���S
	int		_cgLogo;	// �`�[�����S
	int		_cgBg;		// �w�i�摜
	int		_cgStart;	// �X�^�[�g�{�^��
	// ���y�n���h��
	int		bgm_title;	// BGM (�^�C�g�����)

	// �t���O
	bool	school;		// �w�Z���S�t���O
	bool	logo;		// �`�[�����S�t���O
	bool	op;			// �I�[�v�j���O�t���O
	bool	start;		// �X�^�[�g�t���O

	// time�֌W
#define	LATENCY		2000			// �ҋ@����

	int		instrumentationStart;	// �v���J�n
	int		latency;				// �ҋ@����
};

