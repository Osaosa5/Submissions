// 担当：尾﨑

/*
	アイテムの処理に関する関数
*/

#include "DxLib.h"
#include "SceneAction.h"
#include "ItemData.h"

/*
	@brief	アイテムに関する変数の初期化
*/
void SceneAction::InitItem() {
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		_gItem[i].use = 1;
		_gItem[i].x = itemData[i].x;
		_gItem[i].y = itemData[i].y;
		_gItem[i].w = ITEM_WIDTH;
		_gItem[i].h = ITEM_HEIGHT;
		_gItem[i].lane = AddObjectLane(_gItem[i].y);
		_gItem[i].high = 20;
		_gItem[i].type = itemData[i].type;
		_gItem[i].stand = itemData[i].stand;
	}

	// フラグの初期化
	shouldGotBattery = 0;
	shouldGotHeart = 0;
	shouldGotJet = 0;
	// カウントの初期化
	batteryEffectStartTime = 0;
	// スピードアップ,ダウン文字表示の初期化
	drawCount = 0;

	// バリアエフェクトのロード 
	if(ef_barrier->Check() == false) 
	{
		ef_barrier->Load("res/effect/barrier.png", 30, 30, 1, 210, 210);
		ef_barrier->SetWaitFrame(0);
		ef_barrier->SetLoop(10);
	}

	// 回復エフェクトのロード
	ef_healing->Load("res/effect/healing.png", 30, 30, 1, 360, 180);
	ef_healing->SetWaitFrame(2);

	// 加速エフェクトのロード
	ef_firespark->Load("res/effect/blue_firespark.png", 30, 30, 1, 210, 70);
	ef_firespark->SetWaitFrame(0);
	ef_firespark->SetLoop(2);
}

/*
	@brief	アイテムに関するフラグを0にする
*/
void SceneAction::ProcessItemFlag() 
{
	// エフェクト（barrier）
	// バッテリー処理
	if(shouldGotBattery == 1) 
	{
		// 5秒立ったらフラグを0にする
		if(GetNowCount() - batteryEffectStartTime > 5000)
		{
			shouldGotBattery = 0;
		}
	}

	// 回復処理
	if(shouldGotHeart == 1) 
	{
		// HPが4未満であればHPが1回復する
		if(_UIlife.Get() < 4)
		{
			_life++;
			_UIlife.Set(_life);
		}
		shouldGotHeart = 0;
	}

	// 加速処理
	if(shouldGotJet == 1)
	{
		drawCount = MAX_SPEEDUP_COUNT;
		// プレイヤーのスピードを上げる
		pl.speed_x += 5;
		shouldGotJet = 0;
	}

	if (drawCount > 0) { drawCount--; }
}

/*
	@brief	アイテムの様々な処理をまとめたもの
*/
void SceneAction::ProcessItem()
{
	ProcessItemFlag();			// フラグ関係の処理

	HitCheckPlayerItem();		// プレイヤーとアイテムの処理

	ef_barrier->Process();		// エフェクト処理(barrier)
	ef_healing->Process();		// エフェクト処理(healing)
	ef_firespark->Process();	// エフェクト処理(firespark)
}

/*
	@brief	アイテムの描画処理
*/
void SceneAction::DrawItem() 
{
	int x, y;
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		x = _gItem[i].x * CHIP_W - gScrollX;
		switch(_gItem[i].stand) {
		case 0:		// 空中
			y = _gItem[i].y * CHIP_H - _gItem[i].high * 4 - gScrollY;
			break;

		case 1:		// 地面
			y = _gItem[i].y * CHIP_H - _gItem[i].high - gScrollY;
			break;
		}
		// useが1なら描画する
		if(_gItem[i].use == 1) {
			int yy = _gItem[i].y * CHIP_H;
			_shadow->DrawItem(x, yy);
			// typeによって描画するアイテムを変える
			if(_gItem[i].type == BATTERY) DrawGraph(x, y, _cgItem[ITEM_BATTERY], TRUE);
			if(_gItem[i].type == HEART) DrawGraph(x, y, _cgItem[ITEM_HEART], TRUE);
			if(_gItem[i].type == JET) DrawGraph(x, y, _cgItem[ITEM_JET], TRUE);
		}
	}

	int xx, yy;	// スクロールを想定したキャラx,yを入れる
	xx = pl.x - gScrollX;
	yy = pl.y - gScrollY + pl.high;

	// スピードアップの文字描画
	if (drawCount > 0) 
	{
		if(_UIspeedoMeter->Get() < 6) 
		{
			SetFontSize(32);
			DrawFormatString(xx + 50, yy - 20, GetColor(255, 0, 0), "スピードUP");
		}
	}
}

