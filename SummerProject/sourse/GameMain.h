#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "scenebase.h"
#include "Fade.h"
#include "Effect.h"


// ����cpp�ł��g�������O���[�o���ϐ��́A�w�b�_�t�@�C����extern�錾����

// �Q�[�����
extern int gKey;			// �L�[���͂̏��
extern int gTrg;			// �g���K���͂̏��
extern int gRel;			// �����[�X���͂̏��

void ChangeScene(SceneBase* scene);	// Scene��ύX����

void GameMain();	// gamemain.cpp �Ɏ��̂��L�q

extern Fade* _fade;

