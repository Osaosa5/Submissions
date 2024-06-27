#pragma once

class uiMileStone {
public:
		uiMileStone();
		~uiMileStone();

	void Process(int x, int start, int end);
	void Draw();
protected:
	// 画像ハンドル
	int _cgMileStone;						// マイルストーンの画像
	int _cgPlayerPosDisplay;			// プレイヤーの走行位置の画像
	// 座標
	float _mileStone_x;					// マイルストーンのx座標
	float _mileStone_y;					// マイルストーンのy座標
	float _playerPosDisplay_x;		// 走行位置のx座標
	float _playerPosDisplay_y;		// 走行位置のy座標
	// 処理用
	float _mapDistance;					// マップの距離
	float _ranRate;							// どの程度走ったかの割合
	float _uiMapDistance;				// UIマップの距離
};




