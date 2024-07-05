// �S���F����

/*
    �t�F�[�h����
*/

#include "Fade.h"
#include "mymath.h"
#include "DxLib.h"
#include "WinMain.h"

/*
	@brief	Fade�̃R���X�g���N�^
*/
Fade::Fade() 
{
    // ������
    // �J���[�}�X�N�p
    gColorMaskR = 0, gColorMaskG = 0, gColorMaskB = 0, gColorMaskA = 0;
    // �t�F�[�h�C���A�E�g�p
    gColorFadeStR   = 0;
    gColorFadeStG   = 0; 
    gColorFadeStB   = 0;
    gColorFadeStA   = 0;
    gColorFadeEdR   = 0;
    gColorFadeEdG   = 0;
    gColorFadeEdB   = 0;
    gColorFadeEdA   = 0;
    gFadeFrames     = 0;
    gFadeCnt        = 0;
    _step           = 0;
}

/*
	@brief	Fade�̃f�X�g���N�^
*/
Fade::~Fade() 
{ 
    // �������Ȃ�
}

/*
	@brief	�J���[�}�X�N�̎w��
	@param	colorR:��
	@param	colorG:��
	@param	colorB:��
	@param	colorA:�A���t�@
*/
void Fade::ColorMask(float colorR, float colorG, float colorB, float colorA) 
{
    gColorMaskR = colorR;
    gColorMaskG = colorG;
    gColorMaskB = colorB;
    gColorMaskA = colorA;
}

/*
	@brief	�w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha=255�ɂ���j
	@param	colorR:��
	@param	colorG:��
	@param	colorB:��
	@param	frames:�t���[����
*/
void Fade::ColorFadeOut(float colorR, float colorG, float colorB, float frames) 
{
    // �t�F�[�h�J�n�l
    gColorFadeStR = gColorMaskR;
    gColorFadeStG = gColorMaskG;
    gColorFadeStB = gColorMaskB;
    gColorFadeStA = 0;
    // �t�F�[�h���B�l
    gColorFadeEdR = colorR;
    gColorFadeEdG = colorG;
    gColorFadeEdB = colorB;
    gColorFadeEdA = 255;
    // �t�F�[�h�J�E���^
    gFadeFrames = frames;
    gFadeCnt    = 0;
}

/*
	@brief	���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha=0�ɂ���j
	@param	frames:�t���[����
*/
void Fade::ColorFadeIn(float frames) 
{
    // �t�F�[�h�J�n�l
    if (IsColorFade() != 1) 
    {
        gColorFadeStR = gColorMaskR;
        gColorFadeStG = gColorMaskG;
        gColorFadeStB = gColorMaskB;
        gColorFadeStA = 255;
        // �t�F�[�h���B�l
        gColorFadeEdR = gColorMaskR;
        gColorFadeEdG = gColorMaskG;
        gColorFadeEdB = gColorMaskB;
        gColorFadeEdA = 0;
        // �t�F�[�h�J�E���^
        gFadeFrames = frames;
        gFadeCnt    = 0;
    }
}

/*
	@brief	�t�F�[�h�C���A�E�g�͏I���������H
	@return	1�F�t�F�[�h��
    @return 0�F�t�F�[�h�I��(�������͊J�n�O)
*/
int Fade::IsColorFade() 
{
    if (gFadeCnt < gFadeFrames) return 1; 
    return 0;
}

/*
	@brief	���C������
*/
void Fade::MainProcess()
{
    // �J���[�}�X�N�̃t�F�[�h�C���A�E�g
    if (IsColorFade() != 0)
    {
        gFadeCnt++;
        gColorMaskR = EasingLinear(gFadeCnt, gColorFadeStR, gColorFadeEdR, gFadeFrames);
        gColorMaskG = EasingLinear(gFadeCnt, gColorFadeStG, gColorFadeEdG, gFadeFrames);
        gColorMaskB = EasingLinear(gFadeCnt, gColorFadeStB, gColorFadeEdB, gFadeFrames);
        gColorMaskA = EasingLinear(gFadeCnt, gColorFadeStA, gColorFadeEdA, gFadeFrames);
    }
}

/*
	@brief	�`�揈��
*/
void Fade::Draw()
{
    // �J���[�}�X�N
    if (gColorMaskA > 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// ���������[�h
        DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(gColorMaskR, gColorMaskG, gColorMaskB), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, gColorMaskA);
    }
}

/*
	@brief	�X�e�b�v�̎擾
    @return	�X�e�b�v
*/
int Fade::GetStep()
{
    return _step;
}

/*
	@brief	�X�e�b�v�̐ݒ�
    @param	step:�X�e�b�v
*/
void Fade::SetStep(int step) 
{
    _step = step;
}
