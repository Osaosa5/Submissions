// �S���F����

/*
    �t���[�����[�g�����肳����N���X
*/

#include "DxLib.h"
#include "fps.h"

/*
	@brief	fps�̃R���X�g���N�^
*/
fps::fps() 
{
	fps_count = 0;
	count0t = 0;
	for(int i = 0; i < FLAME; i++) 
    {
		f[i] = 0;
	}
	ave = 0;
}

/*
	@brief	fps�̃f�X�g���N�^
*/
fps::~fps()
{
    // �������Ȃ�
}

/*
	@brief	�t���[�����[�g���v�����āA60�t���[���ɂȂ�悤�ɑ҂�
*/
void fps::fps_wait() 
{
    int term, i, gnt;
    static int t = 0;
    if(fps_count == 0) 
    {   //60�t���[����1��ڂȂ�
        if(t == 0)//���S�ɍŏ��Ȃ�܂��Ȃ�
            term = 0;
        else//�O��L�^�������Ԃ����Ɍv�Z
            term = count0t + 1000 - GetNowCount();
    }
    else    //�҂ׂ�����=���݂���ׂ�����-���݂̎���
        term = (int)(count0t + fps_count * (1000.0 / FLAME)) - GetNowCount();

    if(term > 0)//�҂ׂ����Ԃ����҂�
        Sleep(term);

    gnt = GetNowCount();

    if(fps_count == 0)//60�t���[����1�x������
        count0t = gnt;
    f[fps_count] = gnt - t;//�P���������Ԃ��L�^
    t = gnt;
    //���όv�Z
    if(fps_count == FLAME - 1) 
    {
        ave = 0;
        for(i = 0; i < FLAME; i++)
            ave += f[i];
        ave /= FLAME;
    }
    fps_count = (++fps_count) % FLAME;
}

