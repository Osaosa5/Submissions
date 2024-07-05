// 担当：尾﨑

/*
	プレイヤーが現在ステージのどこにいるかを表示するUI
*/

#include "uiMileStone.h"
#include "DxLib.h"

/*
	@brief	コンストラクタ
*/
uiMileStone::uiMileStone() { 
	// 画像読み込み
	_cgPlayerPosDisplay	= LoadGraph("res/UI/UI_Face.png");
	_cgMileStone		= LoadGraph("res/UI/location.png");
	// 座標設定
	_mileStone_x		= 265;
	_mileStone_y		= 980;
	_playerPosDisplay_x	= 0;
	_playerPosDisplay_y	= _mileStone_y;
	// 処理用変数初期化
	_mapDistance	= 0;
	_ranRate		= 0;
	_uiMapDistance	= 1264;
}

/*
	@brief	デストラクタ
*/
uiMileStone::~uiMileStone() { 
	// 画像削除
	DeleteGraph(_cgPlayerPosDisplay);
	DeleteGraph(_cgMileStone);
}

/*
	@brief	更新
	@param	x		：プレイヤーの走行距離
	@param	start	：コースのスタート地点
	@param	end		：コースのゴール地点
*/
void uiMileStone::Process(int x, int start, int end) {
	// コースの走行距離
	_mapDistance		= end - start;
	// プレイヤーの走った割合
	_ranRate			= x / _mapDistance;
	// プレイヤーの走った割合をUIに反映させる
	_playerPosDisplay_x = _ranRate * _uiMapDistance + _mileStone_x;
}

/*
	@brief	描画
*/
void uiMileStone::Draw() {
	// マイルストーンの描画
	DrawGraph(_mileStone_x, _mileStone_y + 10, _cgMileStone, TRUE);
	// プレイヤー走行位置
	DrawGraph(_playerPosDisplay_x, _playerPosDisplay_y, _cgPlayerPosDisplay, TRUE);
}