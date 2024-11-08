// SFöú±

/*
	½è»èÉÖ·éÖ
*/

#include "DxLib.h"
#include "SceneAction.h"

/*
	@brief	½è»è(é`)Ìú»
*/
void SceneAction::InitRect() 
{
	pl.hit_x = 80;
	pl.hit_y = 150;
	pl.hit_w = 159;
	pl.hit_h = 79;
}

/*
	@brief	vC[ÆÇÌ½è»è
	@param	old_xFÚ®OÌvC[ÌXÀW
	@param	old_yFÚ®OÌvC[ÌYÀW
*/
void SceneAction::HitCheckPlayerWall(int old_x, int old_y) 
{
	int left	= pl.x + pl.hit_x;
	int up		= pl.y + pl.hit_y;
	int right	= pl.hit_w - 1;
	int down	= pl.hit_h - 1;
	if(_mapData->IsHitCharaMap(left, up, right, down, 1) == 1) 
	{
		pl.y = old_y;
	}
}

/*
	@brief	vC[ÆáQ¨Ì½è»è
*/
void SceneAction::HitCheckPlayerObstacle() 
{
	// playerÌ½è»èðìé
	int x = pl.x + pl.hit_x + 120;
	int y = pl.y + pl.hit_y;
	int w = pl.hit_w - 121;
	int h = pl.hit_h - 1;
	// nãÉ¢é©H
	if (pl.stand == 1) 
	{
		// áQ¨É½ÁÄ¢éÂAobe[i³Gjðæ¾µÄ¢È¢©
		if (_mapData->IsHitCharaMap(x, y, w, h, 3) == 1 && shouldGotBattery == 0) 
		{
			// íe¼ãÅÍÈ¢©H
			if (invincibleTime == 0) 
			{
				// áQ¨É½Á½
				pl.obstacleHit = 1;
				// _[W
				DamagePlayer();
				// íeãÌ³GÔðZbg
				invincibleTime = 180;
			}
			// playerÌXs[hðZbg
			pl.speed_x = 10;
		}
	}
	// íeãÌ³GÔª­¶µÄ¢½ç
	if (invincibleTime != 0) 
	{
		invincibleTime--;
	}
}

/*
	@brief	vC[ÆACeÌ½è»è
*/
void SceneAction::HitCheckPlayerItem() 
{
	for(int i = 0; i < ITEM_MAX; i++) 
	{
		// playerÌ½è»èé`ðìé
		int x = pl.x + pl.hit_x - gScrollX - 60;
		int y = pl.y + pl.hit_y - pl.high - gScrollY;
		int w = pl.hit_w - 1;
		int h = pl.hit_h - 1;
		// ACeÌ½è»èé`ðìé
		int item_x = _gItem[i].x * CHIP_W - gScrollX;
		int item_y = _gItem[i].y * CHIP_H - _gItem[i].high - gScrollY;
		int item_w = _gItem[i].w;
		int item_h = _gItem[i].h;
		// playerÍACeª½Á½©H
		if(IsHitBox(x, y, w, h, item_x, item_y, item_w, item_h) == 1) 
		{	
			// ¨Ý¢nãÉ¢é©AACeÍ\¦³êÄ¢é©
			if(pl.stand == _gItem[i].stand && _gItem[i].use == 1)
			{
				// ACeÌíÞÉæÁÄªÏíé
				switch(_gItem[i].type) 
				{
				case BATTERY:	// [dr(oA)
					shouldGotBattery = 1;	// tOðONÉ·é
					PlaySoundMem(_se[SE_BATTERY], DX_PLAYTYPE_BACK);	// seðÄ¶
					batteryEffectStartTime = GetNowCount();	// ACeðæ¾µ½ÔðL^·é
					ef_barrier->SetStarting(true);	// oAGtFNg`æX^[gtO
					break;
				case HEART:	// n[g(ñ)
					shouldGotHeart = 1;	// tOðONÉ·é
					PlaySoundMem(_se[SE_HEART], DX_PLAYTYPE_BACK);	// seðÄ¶
					ef_healing->SetStarting(true);	// ñGtFNg`æX^[gtO
					break;
				case JET:	// WFbg(Á¬)
					shouldGotJet = 1;	// tOðONÉ·é
					PlaySoundMem(_se[SE_JET], DX_PLAYTYPE_BACK);	// seðÄ¶
					ef_firespark->SetStarting(true);  // Á¬GtFNg`æX^[gtO
					break;
				}
				_gItem[i].use = 0;	// æ¾µ½ACeðñ\¦É·é
			}
		}
	}
}
