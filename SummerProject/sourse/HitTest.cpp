// 担当：尾﨑

/*
	当たり判定に関する関数
*/

#include "DxLib.h"
#include "SceneAction.h"

/*
	@brief	当たり判定(矩形)の初期化
*/
void SceneAction::InitRect() 
{
	pl.hit_x = 80;
	pl.hit_y = 150;
	pl.hit_w = 159;
	pl.hit_h = 79;
}

/*
	@brief	プレイヤーと壁の当たり判定
	@param	old_x：移動前のプレイヤーのX座標
	@param	old_y：移動前のプレイヤーのY座標
*/
void SceneAction::HitCheckPlayerWall(int old_x, int old_y) 
{
	int left = pl.x + pl.hit_x;
	int up = pl.y + pl.hit_y;
	int right = pl.hit_w - 1;
	int down = pl.hit_h - 1;
	if(_mapData->IsHitCharaMap(left, up, right, down, 1) == 1) 
	{
		pl.y = old_y;
	}
}

/*
	@brief	プレイヤーと障害物の当たり判定
*/
void SceneAction::HitCheckPlayerObstacle() 
{
	// playerの当たり判定を作る
	int x = pl.x + pl.hit_x + 120;
	int y = pl.y + pl.hit_y;
	int w = pl.hit_w - 121;
	int h = pl.hit_h - 1;
	// 地上にいるか？
	if (pl.stand == 1) 
	{
		// 障害物に当たっている且つ、バッテリー（無敵）を取得していないか
		if (_mapData->IsHitCharaMap(x, y, w, h, 3) == 1 && shouldGotBattery == 0) 
		{
			// 被弾直後ではないか？
			if (invincibleTime == 0) 
			{
				// 障害物に当たった
				pl.obstacleHit = 1;
				// ダメージ処理
				DamagePlayer();
				// 被弾後の無敵時間をセット
				invincibleTime = 180;
			}
			// playerのスピードをリセット
			pl.speed_x = 10;
		}
	}
	// 被弾後の無敵時間が発生していたら
	if (invincibleTime != 0) 
	{
		invincibleTime--;
	}
}

/*
	@brief	プレイヤーとアイテムの当たり判定
*/
void SceneAction::HitCheckPlayerItem() 
{
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		// playerの当たり判定矩形を作る
		int x = pl.x + pl.hit_x - gScrollX - 60;
		int y = pl.y + pl.hit_y - pl.high - gScrollY;
		int w = pl.hit_w - 1;
		int h = pl.hit_h - 1;
		// アイテムの当たり判定矩形を作る
		int item_x = _gItem[i].x * CHIP_W - gScrollX;
		int item_y = _gItem[i].y * CHIP_H - _gItem[i].high - gScrollY;
		int item_w = _gItem[i].w;
		int item_h = _gItem[i].h;
		// playerはアイテムが当たったか？
		if(IsHitBox(x, y, w, h, item_x, item_y, item_w, item_h) == 1) 
		{	
			// お互い地上にいるか、アイテムは表示されているか
			if(pl.stand == _gItem[i].stand && _gItem[i].use == 1)
			{
				// アイテムの種類によって処理が変わる
				switch(_gItem[i].type) 
				{
				case BATTERY:	// 充電池(バリア)
					shouldGotBattery = 1;	// フラグをONにする
					PlaySoundMem(_se[SE_BATTERY], DX_PLAYTYPE_BACK);	// seを再生
					batteryEffectStartTime = GetNowCount();	// アイテムを取得した時間を記録する
					ef_barrier->SetStarting(true);	// バリアエフェクト描画スタートフラグ
					break;
				case HEART:	// ハート(回復)
					shouldGotHeart = 1;	// フラグをONにする
					PlaySoundMem(_se[SE_HEART], DX_PLAYTYPE_BACK);	// seを再生
					ef_healing->SetStarting(true);	// 回復エフェクト描画スタートフラグ
					break;
				case JET:	// ジェット(加速)
					shouldGotJet = 1;	// フラグをONにする
					PlaySoundMem(_se[SE_JET], DX_PLAYTYPE_BACK);	// seを再生
					ef_firespark->SetStarting(true);  // 加速エフェクト描画スタートフラグ
					break;
				}
				_gItem[i].use = 0;	// 取得したアイテムを非表示にする
			}
		}
	}
}
