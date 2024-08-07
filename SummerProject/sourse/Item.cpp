// SFφϊ±

/*
	ACeΜΙΦ·ιΦ
*/

#include "DxLib.h"
#include "SceneAction.h"
#include "ItemData.h"

/*
	@brief	ACeΙΦ·ιΟΜϊ»
*/
void SceneAction::InitItem() {
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		_gItem[i].use	= 1;
		_gItem[i].x		= itemData[i].x;
		_gItem[i].y		= itemData[i].y;
		_gItem[i].w		= ITEM_WIDTH;
		_gItem[i].h		= ITEM_HEIGHT;
		_gItem[i].lane	= AddObjectLane(_gItem[i].y);
		_gItem[i].high	= 20;
		_gItem[i].type	= itemData[i].type;
		_gItem[i].stand = itemData[i].stand;
	}

	// tOΜϊ»
	shouldGotBattery	= 0;
	shouldGotHeart		= 0;
	shouldGotJet		= 0;
	// JEgΜϊ»
	batteryEffectStartTime = 0;
	// Xs[hAbv,_EΆ\¦Μϊ»
	drawCount = 0;

	// oAGtFNgΜ[h 
	if(ef_barrier->Check() == false) 
	{
		ef_barrier->Load("res/effect/barrier.png", 30, 30, 1, 210, 210);
		ef_barrier->SetWaitFrame(0);
		ef_barrier->SetLoop(10);
	}

	// ρGtFNgΜ[h
	ef_healing->Load("res/effect/healing.png", 30, 30, 1, 360, 180);
	ef_healing->SetWaitFrame(2);

	// Α¬GtFNgΜ[h
	ef_firespark->Load("res/effect/blue_firespark.png", 30, 30, 1, 210, 70);
	ef_firespark->SetWaitFrame(0);
	ef_firespark->SetLoop(2);
}

/*
	@brief	ACeΙΦ·ιtOπ0Ι·ι
*/
void SceneAction::ProcessItemFlag() 
{
	// GtFNgibarrierj
	// obe[
	if(shouldGotBattery == 1) 
	{
		// 5b§Α½ηtOπ0Ι·ι
		if(GetNowCount() - batteryEffectStartTime > 5000)
		{
			shouldGotBattery = 0;
		}
	}

	// ρ
	if(shouldGotHeart == 1) 
	{
		// HPͺ4’Ε κΞHPͺ1ρ·ι
		if(_UIlife.Get() < 4)
		{
			_life++;
			_UIlife.Set(_life);
		}
		shouldGotHeart = 0;
	}

	// Α¬
	if(shouldGotJet == 1)
	{
		drawCount = MAX_SPEEDUP_COUNT;
		// vC[ΜXs[hπγ°ι
		pl.speed_x += 5;
		shouldGotJet = 0;
	}

	if (drawCount > 0) { drawCount--; }
}

/*
	@brief	ACeΜlXΘπάΖί½ΰΜ
*/
void SceneAction::ProcessItem()
{
	ProcessItemFlag();			// tOΦWΜ

	HitCheckPlayerItem();		// vC[ΖACeΜ

	ef_barrier->Process();		// GtFNg(barrier)
	ef_healing->Process();		// GtFNg(healing)
	ef_firespark->Process();	// GtFNg(firespark)
}

/*
	@brief	ACeΜ`ζ
*/
void SceneAction::DrawItem() 
{
	int x, y;
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		x = _gItem[i].x * CHIP_W - gScrollX;
		switch(_gItem[i].stand) {
		case 0:		// σ
			y = _gItem[i].y * CHIP_H - _gItem[i].high * 4 - gScrollY;
			break;

		case 1:		// nΚ
			y = _gItem[i].y * CHIP_H - _gItem[i].high - gScrollY;
			break;
		}
		// useͺ1Θη`ζ·ι
		if(_gItem[i].use == 1) {
			int yy = _gItem[i].y * CHIP_H;
			_shadow->DrawItem(x, yy);
			// typeΙζΑΔ`ζ·ιACeπΟ¦ι
			if(_gItem[i].type == BATTERY)	DrawGraph(x, y, _cgItem[ITEM_BATTERY], TRUE);
			if(_gItem[i].type == HEART)		DrawGraph(x, y, _cgItem[ITEM_HEART], TRUE);
			if(_gItem[i].type == JET)		DrawGraph(x, y, _cgItem[ITEM_JET], TRUE);
		}
	}

	int xx, yy;	// XN[πzθ΅½Lx,yπόκι
	xx = pl.x - gScrollX;
	yy = pl.y - gScrollY + pl.high;

	// Xs[hAbvΜΆ`ζ
	if (drawCount > 0) 
	{
		if(_UIspeedoMeter->Get() < 6) 
		{
			SetFontSize(32);
			DrawFormatString(xx + 50, yy - 20, GetColor(255, 0, 0), "Xs[hUP");
		}
	}
}

