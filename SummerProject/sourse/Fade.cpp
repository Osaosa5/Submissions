// 担当：尾﨑

/*
    フェード処理
*/

#include "Fade.h"
#include "mymath.h"
#include "DxLib.h"
#include "WinMain.h"

/*
	@brief	Fadeのコンストラクタ
*/
Fade::Fade() 
{
    // 初期化
    // カラーマスク用
    gColorMaskR = 0, gColorMaskG = 0, gColorMaskB = 0, gColorMaskA = 0;
    // フェードインアウト用
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
	@brief	Fadeのデストラクタ
*/
Fade::~Fade() 
{ 
    // 何もしない
}

/*
	@brief	カラーマスクの指定
	@param	colorR:赤
	@param	colorG:緑
	@param	colorB:青
	@param	colorA:アルファ
*/
void Fade::ColorMask(float colorR, float colorG, float colorB, float colorA) 
{
    gColorMaskR = colorR;
    gColorMaskG = colorG;
    gColorMaskB = colorB;
    gColorMaskA = colorA;
}

/*
	@brief	指定の色にフェードアウト（カラーマスク使用, alpha=255にする）
	@param	colorR:赤
	@param	colorG:緑
	@param	colorB:青
	@param	frames:フレーム数
*/
void Fade::ColorFadeOut(float colorR, float colorG, float colorB, float frames) 
{
    // フェード開始値
    gColorFadeStR = gColorMaskR;
    gColorFadeStG = gColorMaskG;
    gColorFadeStB = gColorMaskB;
    gColorFadeStA = 0;
    // フェード到達値
    gColorFadeEdR = colorR;
    gColorFadeEdG = colorG;
    gColorFadeEdB = colorB;
    gColorFadeEdA = 255;
    // フェードカウンタ
    gFadeFrames = frames;
    gFadeCnt    = 0;
}

/*
	@brief	現在のカラーマスクからフェードイン（カラーマスク使用, alpha=0にする）
	@param	frames:フレーム数
*/
void Fade::ColorFadeIn(float frames) 
{
    // フェード開始値
    if (IsColorFade() != 1) 
    {
        gColorFadeStR = gColorMaskR;
        gColorFadeStG = gColorMaskG;
        gColorFadeStB = gColorMaskB;
        gColorFadeStA = 255;
        // フェード到達値
        gColorFadeEdR = gColorMaskR;
        gColorFadeEdG = gColorMaskG;
        gColorFadeEdB = gColorMaskB;
        gColorFadeEdA = 0;
        // フェードカウンタ
        gFadeFrames = frames;
        gFadeCnt    = 0;
    }
}

/*
	@brief	フェードインアウトは終了したか？
	@return	1：フェード中
    @return 0：フェード終了(もしくは開始前)
*/
int Fade::IsColorFade() 
{
    if (gFadeCnt < gFadeFrames) return 1; 
    return 0;
}

/*
	@brief	メイン処理
*/
void Fade::MainProcess()
{
    // カラーマスクのフェードインアウト
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
	@brief	描画処理
*/
void Fade::Draw()
{
    // カラーマスク
    if (gColorMaskA > 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// 半透明モード
        DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(gColorMaskR, gColorMaskG, gColorMaskB), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, gColorMaskA);
    }
}

/*
	@brief	ステップの取得
    @return	ステップ
*/
int Fade::GetStep()
{
    return _step;
}

/*
	@brief	ステップの設定
    @param	step:ステップ
*/
void Fade::SetStep(int step) 
{
    _step = step;
}
