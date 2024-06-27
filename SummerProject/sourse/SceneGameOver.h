#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"

class SceneGameOver : public SceneBase {
public:
	SceneGameOver();			// �R���X�g���N�^
	virtual ~SceneGameOver();	// �f�X�g���N�^

	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	// ����
#define OPTION_YES		0
#define OPTION_NO		1
#define _OPTION_ALL_	2
	// �F
#define COLLOR_BLUE		0
#define COLLOR_YELLOW	1
#define _COLLOR_ALL_	2
	// ���W
#define YES_X_			300
#define YES_Y_			400
#define NO_X_			300
#define NO_Y_			700
	// ��
#define SE_SELECT_			0
#define	SE_DETERMINATION_	1
#define _SE_ALL_			2

	// �摜�n���h��
	int		_cgBg;			// �w�i�摜
	int		_cgContinue;
	int		_cgYes[_COLLOR_ALL_];
	int		_cgNo[_COLLOR_ALL_];
	// bgm/se�n���h��
	int		bgm_gameover;	// BGM (�Q�[���I�[�o�[���)
	int		se[_SE_ALL_];

	struct OPTION {
		int menu_Yes, menu_No, menu_Num;
	}option;

	int nowSelect;		// �I��
	bool retry;			// ���g���C�t���O
	bool end;			// �G���h�t���O
};
