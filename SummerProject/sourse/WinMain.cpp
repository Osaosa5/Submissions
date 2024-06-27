#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include <time.h>


// �v���O������WinMain ����n�܂�܂�
int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ������ -------------------------------------------------------------------------
	// �c�w���C�u��������������
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// ��ʂ̉𑜓x����1280�~�c720�A1�h�b�g������32�r�b�g�Ɏw�肷��
	ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	if(DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return -1;
	}
	
	SetMouseDispFlag(FALSE);			// �}�E�X��\����Ԃɂ���
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g
	srand((unsigned)time(NULL));		// �����̏�����

	// �Q�[�����C��
	GameMain();


	// ��� ---------------------------------------------------------------------------
	DxLib_End();		// �c�w���C�u�����g�p�̏I������

	// �I��
	return 0;
}