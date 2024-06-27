#pragma once

class Effect 
{
public:
	Effect();																																					// �R���X�g���N�^
	virtual ~Effect();																																		// �f�X�g���N�^
	bool	Load(const char* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize);						// �摜�ǂݍ���
	void	Process();																																		// �v�Z
	void	Draw();																																				// �`��
	void	SetWaitFrame(float wait) { waitframe = wait; }																					// ���t���[���ł܂킷��
	void	SetStarting(bool start) { startflag = start; waitframeCnt = 0; nowhandle = 0; loopCnt = 0; }			// �`��X�^�[�g�t���O
	void	SetXY(int x, int y) { this->x = x; this->y = y; }																					// �`��ʒu
	void	SetLoop(int loop) { this->loop = loop; };																							// ���[�v
	bool	Check();																								// �`�F�b�N
protected:
	int x;
	int y;

	int loop;
	int loopCnt;

	int waitframe;		// 
	int waitframeCnt;	// 

	int* handles;		// 
	int handlenum;		// 
	int nowhandle;		// 

	bool startflag;		// �`��X�^�[�g�t���O

	

};
