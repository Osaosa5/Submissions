// 担当：尾﨑

/*
	プレイヤーのHPを表示するUI
*/

#include "DxLib.h"
#include "uilife.h"

/*
	@brief	コンストラクタ
*/
UILife::UILife() {
	// 画像の読み込み
	_cgHeart_loss = LoadGraph("res/UI/heart-black.png");
	_cgHeart = LoadGraph("res/UI/heart.png");
	_cgDie = LoadGraph("res/effect/about_to_die.png");
	// 初期化
	_UIlife = 0;
	_lifeCnt = 0;
}

/*
	@brief	デストラクタ
*/
UILife::~UILife() {
	// 画像の削除
	DeleteGraph(_cgHeart_loss);
	DeleteGraph(_cgHeart);
}

/*
	@brief	セッター
	@param	life：HP
*/
void	UILife::Set(int life) {
	_UIlife = life;
}

/*
	@brief	ロスハートセッター
	@return	_UIlife：現在のHP
*/
int		UILife::Get() {
	return _UIlife;
}

/*
	@brief	更新
*/
void	UILife::Process() {
	// ライフが1の時に点滅
	if (_UIlife == 1) _lifeCnt++;
	// ライフが1超の時は点滅しない
	else _lifeCnt = 0;
}

// 描画
void	UILife::Draw() {

	// ライフが1の時は画面が赤くなる
	if (_UIlife == 1) DrawGraph(0, 0, _cgDie, TRUE);
	// 画像を描画する基準座標
	int base_x = 40, base_y = 25;

	// ハートのサイズ
	int heart_w = 84, heart_h = 70;
	int heart_one = 1;		// ひとつのハートでlifeをいくつ表現するか

	// lifeをハートで描画
	int x, y, w;
	x = 0; y = 0;
	w = 80;			// ハートとハートのスキマ
	int life = _UIlife;
	for (int i = 0; i < 320; i += w) {
		// 黒いハートを描画
		DrawGraph(base_x + i, base_y, _cgHeart_loss, TRUE);
	}
	while(life > 0) {
		// _lifeCntを60で割った余りが30未満の時にハートを描画
		if (_lifeCnt % 60 < 30) {
			DrawGraph(base_x + x, base_y + y, _cgHeart, TRUE);
		}
		life -= heart_one;	// ハートひとつ分ライフを減らす
		x += w;	// 次のハート位置へ
	}
}
