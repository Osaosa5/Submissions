#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenebase.h"
#include "SceneGameTitle.h"
#include "SceneGameOver.h"
#include "Effect.h"

//
// �萔�E�\���̒�`
//


//
// �O���[�o���ϐ��錾
//

// �Q�[�����
int gKey;			// �L�[���͂̏��
int gTrg;			// �g���K���͂̏��
int gRel;			// �����[�X���͂̏��


// Scene�|�C���^
SceneBase* gScene;					// �|�C���^�Ȃ̂�new����܂Ŏ��͖̂���

// Scene�̐؂�ւ��p
SceneBase* gNewScene;				// NULL�ȊO���Z�b�g����Ă�����A�V�[����؂�ւ���

Fade* _fade;


// Scene��ύX����
void ChangeScene(SceneBase* scene) 
{
	gNewScene = scene;		// ���̃V�[�����Z�b�g
}


// �A�v���̏�����
// �N������1�񂾂����s�����
void AppInit() 
{
	gNewScene = NULL;		// ���̃V�[��������������
	gScene = new SceneGameTitle();		// Scene�̎��̂����
	_fade = new Fade();
}


// �A�v���̉��
// �I������1�񂾂����s�����
void AppRelease() 
{
	delete gScene;				// Scene���폜����
	delete _fade;
}



//
// �t���[�������B1�t���[����1�񂸂��s�����
//

// �t���[�������F����
void FrameInput() 
{
	// �L�[���́A�g���K���́A�����[�X���͂𓾂�
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �L�[���͂��擾
	gTrg = (gKey ^ keyold) & gKey;
	gRel = (gKey ^ keyold) & ~gKey;

	// Scene�̓��͌Ăяo��
	gScene->Input();

}

// �t���[�������F�v�Z
void FrameProcess() 
{
	// Scene�̌v�Z�Ăяo��
	gScene->Process();

	_fade->MainProcess();
}

// �t���[�������F�`��
void FrameDraw() 
{
	ClearDrawScreen();						// ��ʂ�����������

	// Scene�̕`��Ăяo��
	gScene->Draw();

	_fade->Draw();

	ScreenFlip();							// ����ʂ̓��e��\��ʂɔ��f������
}


void GameMain()
{
	AppInit();	// ������

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while(ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		// �V�[����؂�ւ��邩�H
		if(gNewScene != NULL) 
		{
			delete gScene;		// ���̃V�[�����폜����
			gScene = gNewScene;	// �󂯎�����V�[�����|�C���^�Z�b�g
			gNewScene = NULL;	// ���̃V�[��������������
		}

		FrameInput();	// ����
		FrameProcess();	// �v�Z
		FrameDraw();	// �`��
	}

	AppRelease();	// ���
}
