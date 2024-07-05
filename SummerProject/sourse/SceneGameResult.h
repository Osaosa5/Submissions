#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"
#include "SceneAction.h"
#include "save.h"

class SceneGameResult : public SceneBase {
public:
	SceneGameResult(int resultTime);			// �R���X�g���N�^
	virtual ~SceneGameResult();	// �f�X�g���N�^

	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	// �}�N��
#define _CG_RESULT_ALL_ 4		// �����N�摜�̐�
#define _CG_OPTION_COLOR_NUM_ 2	// �I�����̐F�̐�

#define _SE_RESULT_NUM_		  2	// ���U���g�V�[���Ŏg�p����SE�̐�

	// �摜�n���h��
	int _cgBg;						// �w�i�摜
	int _cgResult[_CG_RESULT_ALL_];	// �����N�摜
	int _cgRanking;					// �����L���O�g
	int _cgFade;					// �����Â�
	int	_cgRetry;
	int	_cgYes[_CG_OPTION_COLOR_NUM_];
	int	_cgNo[_CG_OPTION_COLOR_NUM_];
	// ���֘A
	int _seResult[_SE_RESULT_NUM_];
	// ����
	int _menuYes;		// yes
	int _menuNo;		// no
	int _menuNum;		// ����
	// �t���O�E�ϐ�
	int _nowSelect;		// �I��
	bool _isContinue;	// �I����
	bool _isRetry;		// ���g���C�t���O
	bool _isEnd;		// �G���h�t���O
	// ���֘A
	int _bgmResult;		// BGM (���U���g���)
	// �����p    
	int _resultTime;	// �����N����p
	int _rank;			// �����N
	// �t���O
	bool _isRanking;
	// �N���X
	save* _save;
};

