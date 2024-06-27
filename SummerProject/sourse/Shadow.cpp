// 担当：尾﨑

/*
	背景やスクロールなどの画面関係の処理をまとめたもの
*/

#include "Shadow.h"
#include "DxLib.h"

/*
	@brief	背景描画
*/
Shadow::Shadow() {
	// 画像読み込み
	cgShadowPlayer = LoadGraph("res/UI/kage_240_120.png");
	cgShadowItem = LoadGraph("res/UI/kage_120_120.png");
}

/*
	@brief	デストラクタ
*/
Shadow::~Shadow() {
	DeleteGraph(cgShadowPlayer);
	DeleteGraph(cgShadowItem);
}

/*
	@brief	プレイヤーの影を描画
	@param	x:プレイヤーのx座標
	@param	y:プレイヤーのy座標
	@param	scroll_x:スクロール量
*/
void Shadow::DrawPlayer(int x, int y, int scroll_x) {
	// 座標
	int _x = x - scroll_x;
	int _y = y;
	DrawGraph(_x, _y, cgShadowPlayer, TRUE);

}

/*
	@brief	アイテムの影を描画
	@param	x:アイテムのx座標
	@param	y:アイテムのy座標
*/
void Shadow::DrawItem(int x, int y) {
	int _x = x;
	int _y = y;
	DrawGraph(_x, _y, cgShadowItem, TRUE);
}
