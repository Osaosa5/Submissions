#pragma once

class Fade
{
public:
	Fade();		// コンストラクタ
	~Fade();	// デストラクタ

	// // 指定の色にフェードアウト（カラーマスク使用, alpha=255にする）
	void ColorFadeOut(float colorR, float colorG, float colorB, float frames);
	// // カラーマスクの指定
	void ColorMask(float colorR, float colorG, float colorB, float colorA);
	// // 現在のカラーマスクからフェードイン（カラーマスク使用, alpha=0にする）
	void ColorFadeIn(float frames);
	// // フェードインアウトは終了したか？ 戻り値: 1 = フェード中, 0 = フェード終了(もしくは開始前)
	int IsColorFade();

public:
	void MainProcess();
	void Draw();

public:
	int GetStep();
	void SetStep(int step);

protected:
	// カラーマスク用
	float gColorMaskR, gColorMaskG, gColorMaskB, gColorMaskA;
	// フェードインアウト用
	float gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
	float gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
	float gFadeFrames, gFadeCnt;
	// switch用
	int _step;
};

