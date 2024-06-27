// 担当：尾﨑

/*
	プレイヤーの現在のスピードを表示するUI
*/

#include "DxLib.h"
#include "uispeedometer.h"

/*
	@brief	コンストラクタ
*/
UISpeedoMeter::UISpeedoMeter() {
	// 画像読み込み
	LoadDivGraph("res/UI/speedometer.png", 7, 7, 1, 200, 200, &_cgSpeedMeter[0]);
	// 変数初期化
	_speed = 0;
	_drawSpeed = 0;
}

/*
	@brief	デストラクタ
*/
UISpeedoMeter::~UISpeedoMeter() {
	// 画像削除
	for (int i = 0; i < 7; i++) {
		DeleteGraph(_cgSpeedMeter[i]);
	}
}

/*
	@brief	セッター
	@param	speed：現在のスピード
*/
void	UISpeedoMeter::Set(int speed) {
	_speed = speed;
}

/*
	@brief	ゲッター
	@return	_speed：現在のスピード
*/
int		UISpeedoMeter::Get() {
	return _speed;
}

/*
	@brief	更新
	@param	speed		：現在のスピード
	@param	min			：スピードの最小値
	@param	max			：スピードの最大値
	@param	cangeAmount	：スピードの変化量
*/
void	UISpeedoMeter::Process(int speed, int min, int max, int cangeAmount) {
	// playerのスピードからメーターの数値を決める
	// スピードが0なら目盛り非表示
	if (speed == 0) { _speed = 0; }
	// それ以外ならスピードに応じた目盛りを表示
	else if(speed != 0){
		for (int i = 1; i < 7; i++) {
			// スピードが目盛りの最小値以上最大値以下なら目盛りを表示
			if (speed == cangeAmount * (i - 1) + min) {
				_speed = i;
				break;
			}
		}
	}
	// 描画目盛りを決める
	_drawSpeed = _speed;
}

/*
	@brief	描画
*/
void	UISpeedoMeter::Draw() {
	// 調べたspeedを描画
	DrawGraph(20, 100, _cgSpeedMeter[_drawSpeed], TRUE);
}
