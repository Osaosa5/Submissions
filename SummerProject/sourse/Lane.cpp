// 担当：尾﨑

/*
	ゲームシーンのレーンに関する関数
	プレイヤーのレーンを位置座標+当たり判定で決めてしまったために、
	アイテム用の関数を別で作ることになってしまいました。
*/

#include "SceneAction.h"

/*
	@brief	プレイヤーのレーン変更
	@param	y：プレイヤーのY座標
*/
int SceneAction::AddPlayerLane(int y) 
{
	// playerのy座標にチップの大きさをかける
	int searchLane = y / CHIP_H;
	if(searchLane == 4) return 1;
	if(searchLane == 5) return 2;
	if(searchLane == 6) return 3;
	if(searchLane == 7) return 4;
	return 0;
}

// 
/*
	@brief	オブジェクトのレーン変更
	@param	y：オブジェクトのY座標
*/
int SceneAction::AddObjectLane(int y) 
{
	int searchLane = y;
	if(searchLane == 9) return 1;
	if(searchLane == 10) return 2;
	if(searchLane == 11) return 3;
	if(searchLane == 12) return 4;
	return 0;
}
