#pragma once

class fps {
public:
	fps();
	~fps();

	void fps_wait();
protected:
	//fps
#define FLAME 60

//fps�̃J�E���^�A60�t���[����1���ƂȂ鎞�����L�^����ϐ�
	int fps_count, count0t;
	//���ς��v�Z���邽��60���1�����Ԃ��L�^
	int f[FLAME];
	//����fps
	double ave;
};

