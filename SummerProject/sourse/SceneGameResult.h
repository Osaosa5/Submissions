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
	// �摜�n���h��
	int _cgBg;			// �w�i�摜
	int _cgResult[4];	// �����N�摜
	int _cgRanking;		// �����L���O�g
	int _cgFade;		// �����Â�
	int	_cgRetry;
	int	_cgYes[_COLLOR_ALL_];
	int	_cgNo[_COLLOR_ALL_];
	// ���֘A
	int _seResult[2];
	// ����
	int menu_Yes;		// yes
	int menu_No;		// no
	int menu_Num;		// ����
	// �t���O�E�ϐ�
	int nowSelect;		// �I��
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

