// SFφϊ±

/*
	Q[ΜC
*/

#include "DxLib.h"
#include "winmain.h"
#include "GameMain.h"
#include "scenegameover.h"
#include "sceneaction.h"
#include "scenegameresult.h"
#include "Effect.h"

/*
	@brief	SceneActionΜRXgN^
	@param	stageNumber:Xe[WΤ
*/
SceneAction::SceneAction(int stageNumber) {

	// LζzρΜϊ»
	for(int i = 0; i < _PLAYER_ALL_; i++) {
		_cgPlayer[i] = -1;
	}
	// ζΜΗέέ
	_cgBg					= LoadGraph("res/cgBg/cgBg.png");					// wi
	_cgOperationDescription = LoadGraph("res/cgBg/sousahouhou.png");			// μΰΎζ
	_cgStart				= LoadGraph("res/UI/go-04.png");					// start
	_cgLimitTimeBox			= LoadGraph("res/UI/timeframe-02.png");				// §ΐΤΜγλΜ{bNX(ggέ)
	_cgFade					= LoadGraph("res/cgBg/fade.png");					// Γ’ζ
	_cgRetry				= LoadGraph("res/UI/retry.png");					// retry?
	// Yes or No
	_cgYes[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/No4.png");

	// vC[ζΗέέ
	LoadDivGraph("res/motion/bike_run_nogatoling_00000_sheet.png", 24, 4, 6, 240, 240, &_cgPlayer[PLAYER_WALK]);
	LoadDivGraph("res/motion/bike_crash_new_00000_sheet.png", 24, 4, 6, 240, 240, &_cgPlayer[PLAYER_DAMAGE]);
	LoadDivGraph("res/motion/bike_jump_new_00000_sheet.png", 12, 4, 3, 240, 240, &_cgPlayer[PLAYER_JUMP_UP]);
	LoadDivGraph("res/motion/bike_jump_new_00012_sheet.png", 12, 4, 3, 240, 240, &_cgPlayer[PLAYER_JUMP_DOWN]);
	LoadDivGraph("res/motion/player_moving_left_left.png", 8, 4, 2, 240, 240, &_cgPlayer[PLAYER_MOVING_LEFT]);
	LoadDivGraph("res/motion/player_moving_right_right.png", 8, 4, 2, 240, 240, &_cgPlayer[PLAYER_MOVING_RIGHT]);
	// ACeζΗέέ
	LoadDivGraph("res/UI/item_battery.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_BATTERY]);
	LoadDivGraph("res/UI/item_heart.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_HEART]);
	LoadDivGraph("res/UI/stageitem1_jet.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_JET]);

	// ζΗέέ
	LoadDivGraph("res/UI/number_ui_sheet.png", 11, 11, 1, 48, 72, &_cgNumber[0]);
	LoadDivGraph("res/UI/3cnt_sheet.png", 3, 3, 1, 300, 300, &_cgCntNumber[0]);


	// ψΚΉΜΗέέ
	for(int i = 0; i < _SE_ALL_; i++) {
		_se[i] = -1;
	}
	_se[SE_WALK]			= LoadSoundMem("res/sound/bike.mp3");						// GWΉ
	_se[SE_DAMAGE]			= LoadSoundMem("res/sound/damage.wav");						// ΥΛΉ
	_se[SE_JUMP]			= LoadSoundMem("res/sound/SE_jetjump.wav");					// WvΉ
	_se[SE_LANDING]			= LoadSoundMem("res/sound/SE_landing.wav");					// n
	_se[SE_GOAL]			= LoadSoundMem("res/sound/choice.mp3");						// S[Ή
	_se[SE_CHOOSE]			= LoadSoundMem("res/sound/choice.mp3");						// {^IπΉ	
	_se[SE_DECISION]		= LoadSoundMem("res/sound/waterslash.mp3");					// {^θΉ
	_se[SE_CANCEL]			= LoadSoundMem("res/sound/destruction.mp3");				// IπLZΉ
	_se[SE_JET]				= LoadSoundMem("res/sound/kasoku.mp3");						// WFbglΎΉ
	_se[SE_RED_JET]			= LoadSoundMem("res/sound/kira.mp3");						// WFbgiΤjlΎΉ
	_se[SE_HEART]			= LoadSoundMem("res/sound/heal.mp3");						// n[glΎΉ
	_se[SE_BATTERY]			= LoadSoundMem("res/sound/barrier.mp3");					// obe[lΎΉ
	_se[SE_CNT]				= LoadSoundMem("res/sound/cnt.mp3");						// JEg_EΉ
	_se[SE_START]			= LoadSoundMem("res/sound/start.mp3");						// Q[X^[gΉ
	_se[SE_SELECT]			= LoadSoundMem("res/sound/select.mp3");						// IπΉ
	_se[SE_DETERMINATION]	= LoadSoundMem("res/sound/determination.mp3");				// θΉ

	_bgm[BGM_STAGE_ONE]		= LoadSoundMem("res/sound/CrazyHill.mp3");					// Xe[WPΜBGM

	_mapData				= new MapData(stageNumber);		
															
	_fps					= new fps();					
															
	_UIspeedoMeter			= new UISpeedoMeter();			
															
	_shadow					= new Shadow();					
															
	_UImileStone			= new uiMileStone();			
															
	ef_barrier				= new Effect();					
	ef_healing				= new Effect();					
	ef_firespark			= new Effect();					
	ef_frustration			= new Effect();					

	// |[YζΚΜϊ»
	InitPouse();

	// ζΚΜϊ»
	InitScreen();

	// §ΐΤΜϊ»
	InitLimitTime();

	// ACeΜϊ»
	InitItem();

	// vC[Μϊ»
	InitPlayer();

	// Q[JnOΜΜϊ»
	InitStartPreprocessing();

	// ΜΝΜϊ»
	_life = 4;
	_UIlife.Set(_life);

	// Q[X^[gtO
	drawingFlag	= 1;

	// Q[tO
	// Q[I[o[tO@ΜΝͺ0ΙΘΑ½
	gameFlag_Over		= 0;
	// Q[I[o[tO@^CI[o[
	gameFlag_TimeOver	= 0;
	// Q[NAtO
	gameFlag_Clear		= 0;
	// |[YζΚtO
	pause				= 0;
}

/*
	@brief	SceneActionΜfXgN^
*/
SceneAction::~SceneAction() {
	// OtBbNπγ©ην·ι
	DeleteGraph(_cgBg);
	DeleteGraph(_cgOperationDescription);
	DeleteGraph(_cgStart);
	DeleteGraph(_cgLimitTimeBox);
	DeleteGraph(_cgFade);
	DeleteGraph(_cgRetry);

	// |[YζΚΜIπ
	for (int i = 0; i < _COLLOR_ALL_; i++) {
		DeleteGraph(_cgYes[i]);
		DeleteGraph(_cgNo[i]);
	}			   

	// ACe
	for(int i = 0; i < _ITEM_ALL_; i++) {
		if(_cgItem[i] != -1) {
			DeleteGraph(_cgItem[i]);
		}
	}

	// vC[
	for(int i = 0; i < _PLAYER_ALL_; i++) {
		if(_cgPlayer[i] != -1) {
			DeleteGraph(_cgPlayer[i]);
		}
	}

	// 
	for(int i = 0; i < _NUMBER_ALL_; i++) {
		if(_cgNumber[i] != -1) {
			DeleteGraph(_cgNumber[i]);
		}
	}
	// 3JEg
	for (int i = 0; i < 3; i++) {
		DeleteGraph(_cgCntNumber[i]);
	}

	// ΙΗέ±ρΎΉf[^πν·ι
	// ψΚΉ
	for(int i = 0; i < _SE_ALL_; i++) {
		if(_se[i] != -1) {
			DeleteSoundMem(_se[i]);
		}
	}

	// BGM
	for(int i = 0; i < _BGM_ALL_; i++) {
		if(_bgm[i] != -1) {
			DeleteSoundMem(_bgm[i]);
		}
	}

	// UIΦW
	_mapData->~MapData();
	_UIlife.~UILife();
	_UIspeedoMeter->~UISpeedoMeter();
	_UImileStone->~uiMileStone();

	// GtFNgΦW
	ef_barrier->~Effect();
	ef_healing->~Effect();
	ef_firespark->~Effect();
	ef_frustration->~Effect();

	delete _mapData;
	delete _fps;
	delete _UIspeedoMeter;
	delete _shadow;
	delete _UImileStone;
	delete ef_barrier;
	delete ef_healing;
	delete ef_firespark;
	delete ef_frustration;
}

/*
	@brief	SceneActionΜόΝξρΜ
*/
void SceneAction::Input() {
	// ½ΰ΅Θ’
	// L[ΜόΝAgKόΝπΎι
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// L[όΝπζΎ
	// L[ΜgKξρΆ¬i΅½uΤ΅©½΅Θ’L[ξρj
	gTrg = (gKey ^ keyold) & gKey;
	// L[Μ[XξρΆ¬i£΅½uΤ΅©½΅Θ’L[ξρj
	gRel = (gKey ^ keyold) & ~gKey;
}

/*
	@brief	SceneActionΜ
*/
void SceneAction::Process() {
	// |[YΜtOͺ§ΑΔ’Θ’Ζ«
	if (pause == 0) {
		// X^[gOΜ
		ProcessBeforeStart();
		// §ΐΤΜ
		ProcessLimitTime();
		// Xs[h[^[Μ
		_UIspeedoMeter->Process(pl.speed_x, 10, 35, 5);
		// }CXg[Μ
		_UImileStone->Process(pl.x, 60, DISTANCE_LIMIT);
		// Q[X^[gtOͺ§ΑΔ’ιΖ«
		if (gameStart == 1) {
			_UIlife.Process();  // n[gUIΜ

			ProcessCharacter();

			ProcessItem();		// ACeΜ

			ProcessPlayer();	// playerΜ

			ProcessScreen();	// XN[Μ
		}
	}

	// |[YΜ
	ProcessPouse();
	// t[[gΜ
	_fps->fps_wait();

	{
		// tF[hΜiKΜζΎ
		int step = _fade->GetStep();
		switch (step) {
		case 0: // tF[hC
			_fade->ColorFadeIn(10);
			step++;
			break;
		case 1:	// tF[hCͺIΉ΅Δ’ι©
			if (_fade->IsColorFade() == 0) {
				// tF[hCIΉ
				step++;
			}
			break;
		case 2:
			// Q[I[o[
			if (_UIlife.Get() == 0) {
				gameFlag_Over = 1;
			}
			if (drawLimitTime < 0) {
				gameFlag_TimeOver = 1;
			}

			// Q[NA
			if (_UIlife.Get() != 0 && pl.x >= DISTANCE_LIMIT) {
				// NASE
				PlaySoundMem(_se[SE_GOAL], DX_PLAYTYPE_BACK);
				if (CheckSoundMem(_bgm[BGM_STAGE_ONE]) == 1) {
					StopSoundMem(_bgm[BGM_STAGE_ONE]);
				}
				// S[[r[
				if (gameFlag_Clear == 0) {
					PlayMovie("res/staging/clear.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
					gameFlag_Clear = 1;
					drawingFlag = 0;
					WaitTimer(1000);
				}
				// Q[tOoff
				gameStart = 0;
			}
			// Κν
			// ^CI[o[ΙΐθC.O
			if (gameFlag_TimeOver == 1) {
				SceneBase* scene = new SceneGameOver();
				ChangeScene(scene);
			}
			if (gameFlag_Over == 1) {
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 60);
				step++;
			}
			if (gameFlag_Clear == 1) {
				step++;
			}
			break;
		case 3:
			if (_fade->IsColorFade() != 1) {
				// stepϊ»
				step = 0;
				// tF[hAEgIΉ
				// Q[I[o[
				if (gameFlag_Over == 1) {
					// Q[I[o[ζΚΦ
					SceneBase* scene = new SceneGameOver();
					ChangeScene(scene);
				}
				// Q[NA
				if (gameFlag_Clear == 1) {
					// Q[NAζΚΦ
					SceneBase* scene = new SceneGameResult(drawLimitTime);
					ChangeScene(scene);
				}
			}
			break;
		}
		// »έΜtF[hΜiKΜZbg
		_fade->SetStep(step);
	}
	
}

/*
	@brief	SceneActionΜ`ζ
*/
void SceneAction::Draw() {
	// `ζtOͺ§ΑΔ’ιΖ«
	if (drawingFlag == 1) {
		// wiΜ`ζ
		DrawScreen();
		// μΰΎζΚͺ\¦³κΔ’Θ’
		if (operationDescription == 0) {
			// }bv`ζ
			_mapData->Draw(gScrollX, 0);
			// βό`ζ
			for (int i = 4; i < 9; i++) {
				int y, w;
				y = i * CHIP_H;
				w = SCREEN_W;
				DrawLine(0, y, w, y, GetColor(255, 255, 255));
			}
			// }CXg[`ζ
			_UImileStone->Draw();
			// ΜΝΜ`ζ
			_UIlife.Draw();
			// vC[ΜeΜ`ζ
			_shadow->DrawPlayer(pl.x, pl.y, gScrollX);
			// Xs[h[^[Μ`ζ
			_UIspeedoMeter->Draw();
			// ACe`ζ
			DrawItem();
			// vC[`ζ
			DrawPlayer();

			int xx, yy;	// XN[πzθ΅½Lx,yπόκι
			xx = pl.x - gScrollX;
			yy = pl.y - gScrollY + pl.high;

			// GtFNg`ζibarrierj
			ef_barrier->SetXY(xx + 50, yy + 45);
			ef_barrier->Draw();

			// GtFNg`ζihealingj
			ef_healing->SetXY(xx - 5, yy + 90);
			ef_healing->Draw();

			// GtFNg`ζiblue_firesparkj
			ef_firespark->SetXY(xx - 160, yy + 170);
			ef_firespark->Draw();
			// §ΐΤΜ`ζ
			DrawLimitTime();
		}
		// Q[JnOΜ`ζ
		DrawStartPreprocessing();
		// |[YζΚΜ`ζ
		DrawPouse();
	}
}

