// 担当：尾﨑

/*
	背景やスクロールなどの画面関係の処理をまとめたもの
*/

#include "DxLib.h"
#include "WinMain.h"
#include "SceneAction.h"

/*
	@brief	画面関係の初期化
*/
void SceneAction::InitScreen()
{
	// スクロールの初期化
	gScrollX = 0;
	gScrollY = 0;
}

/*
	@brief	スクロールの処理
*/
void SceneAction::ProcessScreen()
{
	// 画面の左側にプレイヤーが来るようにする
	gScrollX = pl.x - SCREEN_W / 8;
	gScrollY = pl.y - SCREEN_H / 8;

	// スクロールをマップデータ外までやらないように制限
	if (gScrollX < 0) { gScrollX = 0; }
	if (gScrollX + SCREEN_W >= MAPSIZE_W * CHIP_W) { gScrollX = MAPSIZE_W * CHIP_W - SCREEN_W; }
	if (gScrollY < 0) { gScrollY = 0; }
	if (gScrollY + SCREEN_H >= MAPSIZE_H * CHIP_H) { gScrollY = MAPSIZE_H * CHIP_H - SCREEN_H; }

}

/*
	@brief	背景描画
*/
void SceneAction::DrawScreen()
{
	for (int i = 0; i < 122400; i += 1920)
	{
		DrawGraph(i - gScrollX, 0, _cgBg, FALSE);
	}
}