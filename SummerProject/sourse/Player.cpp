// SFöú±(`æÍHi)

/*
	vC[ÉÖ·éðÜÆß½àÌ
*/

#include "DxLib.h"
#include "mymath.h"
#include "WinMain.h"
#include "SceneAction.h"
#include "framedata.h"
#include "motiondata.h"

/*
	@brief	vC[Ìú»
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

	// tXg[VGtFNgÌ[h
	// _Å(3b)Í\¦
	ef_frustration->Load("res/effect/frustration.png", 5, 4, 2, 180, 180);
	ef_frustration->SetWaitFrame(3);
	ef_frustration->SetLoop(9);
}

/*
	@brief	vC[Ì_[W
*/
void SceneAction::DamagePlayer() {
	// ³GACeðæ¾µÄ¢È¯êÎ_[Wðó¯é
	if(shouldGotBattery == 0 ) {
		_life--;
		_UIlife.Set(_life);
	}
	ef_frustration->SetStarting(true);	// tXg[VGtFNgÌ`æX^[gtO
}

/*
	@brief	vC[Ì®«
*/
void SceneAction::ProcessPlayer() {

	// Ú®OÌêðæÁÄ¨­
	int old_x = pl.x;
	int old_y = pl.y;

	// vC[Æ[OÌ½è»è
	HitCheckPlayerWall(old_x, old_y);

	// vC[ÆáQ¨Ì½è»è
	HitCheckPlayerObstacle();

	ef_frustration->Process();		// GtFNg (frustration)

	
	// speed§À
	if (pl.obstacleHit == TRUE) {
		// áQ¨ÉÔÂ©Á½çXs[hð0É·é
		pl.speed_x = 0;
	}
	else {
		// Xs[hª35ÈãÉÈçÈ¢æ¤É·é
		if (pl.speed_x >= 35) pl.speed_x = 35;
		// Xs[hª10ÈºÉÈçÈ¢æ¤É·é
		else if (pl.speed_x <= 10) pl.speed_x = 10;
	}

	// ÁèÌêÜÅÚ®
	if(pl.x <= DISTANCE_LIMIT && pl.obstacleHit == FALSE) { pl.x += pl.speed_x; }
	
	// L[üÍð»èµÄAålöðÚ®³¹é
	pl.lane = AddPlayerLane(pl.y + pl.hit_y);
	// nãÉ¢éÔÂ©ÁÄ¢È¢üÍótÉÚ®
	if(pl.stand == 1 && pl.obstacleHit == FALSE && playerMoveFlag == 1) {
		// 1[ÅÈ¯êÎãÉÚ®Å«é
		if(gTrg & PAD_INPUT_UP && pl.lane != 1) {
			playerCnt		= 0;
			start			= pl.y;
			end				= start - CHIP_H;
			playerMoveFlag	= 0;
		}
		// 4[ÅÈ¯êÎºÉÚ®Å«é
		if(gTrg & PAD_INPUT_DOWN && pl.lane != 4) { 
			playerCnt		= 0;
			start			= pl.y;
			end				= start + CHIP_H;
			playerMoveFlag	= 0;
		}
	}

	// vC[Ì[Ú®
	if(playerMoveFlag == 0) {
		pl.y = EasingLinear(playerCnt, start, end, frames);
	}
	// Ú®ÈÌÅAÌ[É­ÜÅìð§À·é
	if(playerCnt >= frames) {
		playerMoveFlag = 1;
	}
	// vC[ÌÚ®JEgðißé
	playerCnt++;

	// A é¢ÍB{^ÅWv
	if(gTrg & PAD_INPUT_4 && pl.stand == 1 && pl.obstacleHit == 0 && playerMoveFlag == 1)
	{
		if(shouldGotJet == 0) { pl.gravity = -17; }
	}
	else if(gTrg & PAD_INPUT_3 && pl.stand == 1 && pl.obstacleHit == 0 && playerMoveFlag == 1)
	{
		if(shouldGotJet == 0) { pl.gravity = -17; }
	}

	// Wv
	pl.gravity++;				// º~Xs[hðÁZ
	pl.high		+= pl.gravity;	// vC[Ì³ðº°é
	pl.stand	= 0;			// vC[ÌntOð0É·é

	// vC[ªnÊÉ¢éêAßèÜÈ¢æ¤É·é
	if(pl.high > 0) {
		pl.high		= 0;	// vC[Ì³ð0É·é
		pl.gravity	= 0;	// vC[Ìº~Xs[hð0É·é
		pl.stand	= 1;	// vC[ÌntOð1É·é
	}
}

/*
	@brief	vC[Ì`æ
*/
void SceneAction::DrawPlayer() {
	int i, x, y;	// XN[ðzèµ½Lx,yðüêé
	x = pl.x - gScrollX;
	y = pl.y - gScrollY + pl.high;

	// L`æ
	for(i = 0; i < CHARA_MAX; i++) {
		if(_gChara[i].type != CHARA_TYPE_NONE) {
			// LÌ[Vt[©çîñð¾é
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

	// GtFNg`æifrustrationj
	ef_frustration->SetXY(x - 20, y - 100);
	ef_frustration->Draw();

}

