#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"

class SceneGameEnding : public SceneBase {
public:
	SceneGameEnding();			// �R���X�g���N�^
	virtual ~SceneGameEnding();	// �f�X�g���N�^

	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	// �摜�n���h��
	int		_cgBg;		// �w�i�摜
	// ���y�n���h��
	int		bgm_ending;	// BGM (�G���f�B���O���)

	// �t���O
	bool	ed;		// ed�t���O
	bool	end;	// end�t���O
};