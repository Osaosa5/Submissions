#pragma once

class UILife {
public:
	UILife();							// コントラクタ
	virtual ~UILife();					// デストラクタ
										
	void	Process();					// 計算
	void	Draw();						// 描画
	void	Set(int life);				// セッター
	void	SetHeart(int life_loss);	// ロスハートセッター
	int		Get();						// ゲッター

private:
	int		_cgHeart_loss;				// ロスハート描画ハンドル
	int		_cgHeart;					// ハート描画ハンドル
	int		_cgDie;						// die演出ハンドル

	int		_UIlife;					// ハート保持変数
	int		_UIlife_loss;				// ロスハート保持変数

	int		_lifeCnt;
};