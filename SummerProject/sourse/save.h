#pragma once

class save {
public:
	save(char const* _FileName, int dataElementsCount, int playerTime);				// �R���X�g���N�^
	~save();			// �f�X�g���N�^

	void	Export(char const* _FileName, int _date);	// �e�L�X�g�̏o��
	int		Input(char const* _FileName, int dataElementsCount);		// �e�L�X�g�̓ǂݍ���
	void	AscendingOrderDataDrawing(int pos_x, int pos_y, int width, int size);

protected:
#define N 256					// 1�s�̍ő啶����(�o�C�g��)
#define ARRAY_NUMBER	1000	// �z��̐�
#define DRAW_LINE		10

// �f�[�^�^�C�v
#define TYPE_LOG		0
#define TYPE_PLAYER	1

protected:
	int	_date[ARRAY_NUMBER];	// �ϊ���̃f�[�^���i�[����
	int _drawLine;				// �`��s��

	struct DATE {
		int type;	// �^�C�v
		int time;	// �N���A�^�C��
		int x, y;	// ���W
	} date[DRAW_LINE];
};


