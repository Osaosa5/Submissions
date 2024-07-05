// 担当：尾﨑(描画処理は秋永)

/*
	プレイヤーに関する処理をまとめたもの
*/

#include "DxLib.h"
#include "mymath.h"
#include "WinMain.h"
#include "SceneAction.h"
#include "framedata.h"
#include "motiondata.h"

/*
	@brief	プレイヤーの初期化
*/
void SceneAction::InitPlayer() {
	pl.type				= 0;
	pl.x				= 60;				
	pl.y				= 450;
	pl.w				= 239;
	pl.h				= 239;
	pl.speed_x			= 0;
	pl.speed_y			= 5;
	pl.high				= 0;
	pl.gravity			= 0;
	pl.stand			= 0;
	pl.obstacle			= 0;
	pl.obstacleHit		= 0;
	pl.obstacleLimit	= 1200;
	pl.hit				= 0;
	pl.lane				= AddPlayerLane(pl.y + pl.hit_y);

	InitRect();
	
	playerMoveFlag	= 1;
	playerCnt		= 0;
	start			= 0;
	end				= 0;
	frames			= 8;

	playerSlopeFlag	= 1;

	invincibleTime	= 0;
	timeObstacle	= 0;

	// フラストレーションエフェクトのロード
	// 点滅中(3秒)は表示
	ef_frustration->Load("res/effect/frustration.png", 5, 4, 2, 180, 180);
	ef_frustration->SetWaitFrame(3);
	ef_frustration->SetLoop(9);
}

/*
	@brief	プレイヤーのダメージ処理
*/
void SceneAction::DamagePlayer() {
	// 無敵アイテムを取得していなければダメージを受ける
	if(shouldGotBattery == 0 ) {
		_life--;
		_UIlife.Set(_life);
	}
	ef_frustration->SetStarting(true);	// フラストレーションエフェクトの描画スタートフラグ
}

/*
	@brief	プレイヤーの動き
*/
void SceneAction::ProcessPlayer() {

	// 移動前の場所を取っておく
	int old_x = pl.x;
	int old_y = pl.y;

	// プレイヤーとレーン外の当たり判定
	HitCheckPlayerWall(old_x, old_y);

	// プレイヤーと障害物の当たり判定
	HitCheckPlayerObstacle();

	ef_frustration->Process();		// エフェクト処理 (frustration)

	
	// speed制限
	if (pl.obstacleHit == TRUE) {
		// 障害物にぶつかったらスピードを0にする
		pl.speed_x = 0;
	}
	else {
		// スピードが35以上にならないようにする
		if (pl.speed_x >= 35) pl.speed_x = 35;
		// スピードが10以下にならないようにする
		else if (pl.speed_x <= 10) pl.speed_x = 10;
	}

	// 特定の場所まで移動
	if(pl.x <= DISTANCE_LIMIT && pl.obstacleHit == FALSE) { pl.x += pl.speed_x; }
	
	// キー入力を判定して、主人公を移動させる
	pl.lane = AddPlayerLane(pl.y + pl.hit_y);
	// 地上にいる＆ぶつかっていない＆入力受付時に移動
	if(pl.stand == 1 && pl.obstacleHit == FALSE && playerMoveFlag == 1) {
		// 1レーンでなければ上に移動できる
		if(gTrg & PAD_INPUT_UP && pl.lane != 1) {
			playerCnt		= 0;
			start			= pl.y;
			end				= start - CHIP_H;
			playerMoveFlag	= 0;
		}
		// 4レーンでなければ下に移動できる
		if(gTrg & PAD_INPUT_DOWN && pl.lane != 4) { 
			playerCnt		= 0;
			start			= pl.y;
			end				= start + CHIP_H;
			playerMoveFlag	= 0;
		}
	}

	// プレイヤーのレーン移動
	if(playerMoveFlag == 0) {
		pl.y = EasingLinear(playerCnt, start, end, frames);
	}
	// 移動中なので、次のレーンに着くまで操作を制限する
	if(playerCnt >= frames) {
		playerMoveFlag = 1;
	}
	// プレイヤーの移動カウントを進める
	playerCnt++;

	// AあるいはBボタンでジャンプ
	if(gTrg & PAD_INPUT_4 && pl.stand == 1 && pl.obstacleHit == 0 && playerMoveFlag == 1)
	{
		if(shouldGotJet == 0) { pl.gravity = -17; }
	}
	else if(gTrg & PAD_INPUT_3 && pl.stand == 1 && pl.obstacleHit == 0 && playerMoveFlag == 1)
	{
		if(shouldGotJet == 0) { pl.gravity = -17; }
	}

	// ジャンプ処理
	pl.gravity++;				// 下降スピードを加算
	pl.high		+= pl.gravity;	// プレイヤーの高さを下げる
	pl.stand	= 0;			// プレイヤーの着地フラグを0にする

	// プレイヤーが地面にいる場合、めり込まないようにする
	if(pl.high > 0) {
		pl.high		= 0;	// プレイヤーの高さを0にする
		pl.gravity	= 0;	// プレイヤーの下降スピードを0にする
		pl.stand	= 1;	// プレイヤーの着地フラグを1にする
	}
}

/*
	@brief	プレイヤーの描画
*/
void SceneAction::DrawPlayer() {
	int i, x, y;	// スクロールを想定したキャラx,yを入れる
	x = pl.x - gScrollX;
	y = pl.y - gScrollY + pl.high;

	// キャラ描画
	for(i = 0; i < CHARA_MAX; i++) {
		if(_gChara[i].type != CHARA_TYPE_NONE) {
			// キャラのモーションフレームから情報を得る
			int motId = _gChara[i].motId;
			CHARA_MOTION_ITEM* item = tblMotion_chara[motId].item;
			int frameId = item[_gChara[i].motcnt].frameId;
			int _frameId = SearchFrame(frameId);
			int cgId = tblFrame_chara[_frameId].cgId;
			if(invincibleTime % 10 < 7) {
				DrawGraph(x, y, _cgPlayer[cgId], TRUE);
			}
		}
	}

	// エフェクト描画（frustration）
	ef_frustration->SetXY(x - 20, y - 100);
	ef_frustration->Draw();

}

