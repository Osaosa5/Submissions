#pragma once

class UISpeedoMeter {
public:
	UISpeedoMeter();						// コントラクタ
	virtual ~UISpeedoMeter();			// デストラクタ

	void	Process(int speed, int min, int max, int cangeAmount);					// 計算
	void	Draw();						// 描画
	void	Set(int speedmeter);	// スピードセッター
	int		Get();						// ゲッター

private:
	int		_cgSpeedMeter[7];				// スピードメーター画像描画ハンドル
	int		_speed;
	int		_drawSpeed;
};