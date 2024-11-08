// SFöú±

/*
	^Cg
*/

#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "SceneGameTitle.h"
#include "SceneAction.h"

/*
	@brief	SceneGameTitleÌRXgN^
*/
SceneGameTitle::SceneGameTitle() {
	// æÇÝÝ
	_cgSchool	= LoadGraph("res/UI/AMG-LOGO.png");
	_cgLogo		= LoadGraph("res/UI/team_logo.png");
	_cgBg		= LoadGraph("res/cgBg/title.png");
	_cgStart	= LoadGraph("res/UI/ui_press_start_button.png");
	// ¹yÇÝÝ
	bgm_title	= LoadSoundMem("res/sound/Electric_Highway.mp3");

	// tOú»
	school = FALSE;
	logo = FALSE;
	op = FALSE;
	start = FALSE;

	// timeÖWú»
	instrumentationStart = 0;
	latency = 0;
}

/*
	@brief	SceneGameTitleÌfXgN^
*/
SceneGameTitle::~SceneGameTitle() {
	DeleteGraph(_cgSchool);
	DeleteGraph(_cgLogo);
	DeleteGraph(_cgBg);
	DeleteGraph(_cgStart);
	DeleteSoundMem(bgm_title);
}

/*
	@brief	SceneGameTitleÌ
*/
void SceneGameTitle::Process() {
	// ¡Ìstepðæ¾
	int step = _fade->GetStep();
	// stepÅðÏ¦é
	switch (step) {
	case 0:
		// vªJn
		instrumentationStart = GetNowCount();
		// wZS`æ
		school = TRUE;
		// FIJn
		_fade->ColorFadeIn(50);
		// ÌXebvÖ
		step++;
		break;
	case 1:
		// tF[hCÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// 2boÁ½©H
			if (GetNowCount() - instrumentationStart > LATENCY) {
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 60);
				// ÌXebvÖ
				step++;
			}
		}
		break;
	case 2:
		// tF[hAEgÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// wZSí
			school = FALSE;
			// vªJn
			instrumentationStart = GetNowCount();
			// `[S`æ
			logo = TRUE;
			// FIJn
			_fade->ColorFadeIn(50);
			// ÌXebvÖ
			step++;
		}
		break;
	case 3:
		// tF[hCÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// 2boÁ½©H
			if (GetNowCount() - instrumentationStart > LATENCY) {
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 40);
				// ÌXebvÖ
				step++;
			}
		}
		break;
	case 4:
		// tF[hAEgÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// `[Sí
			logo = FALSE;
			// ÌXebvÖ
			step++;
		}
		break;
	case 5:
		// ®æÄ¶
		op = TRUE;
		// ÌXebvÖ
		step++;
		break;
	case 6:
		// b{^Å®æXLbv
		if (gTrg & PAD_INPUT_4) {
			op = FALSE;
		}
		if (op == FALSE) {
			// tF[hAEgJn
			_fade->ColorFadeOut(0, 0, 0, 40);
			// ÌXebvÖ
			step++;
		}
		break;
	case 7:
		// tF[hAEgÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// X^[gæÊ`æ
			start = TRUE;
			// FIJn
			_fade->ColorFadeIn(60);
			// bgmÄ¶
			PlaySoundMem(bgm_title, DX_PLAYTYPE_LOOP);
			// ÌXebvÖ
			step++;
		}
		break;
	case 8:
		// tF[hCÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// V[ØèÖ¦
			if (gTrg & PAD_INPUT_12 || gTrg & PAD_INPUT_10) {
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 10);
				// ÌXebvÖ
				step++;
			}
		}
		break;
	case 9:
		// tF[hAEgÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// X^[gæÊí
			start = FALSE;
			// stepú»
			step = NULL;
			// tF[hAEgI¹
			SceneBase* scene = new SceneAction(0);
			ChangeScene(scene);
		}
		break;
	}
	_fade->SetStep(step);
}

/*
	@brief	SceneGameTitleÌ`æ
*/
void SceneGameTitle::Draw() {
	// schoolªTRUEÈç`æ
	if (school == TRUE) {
		int x = SCREEN_W / 2 - 640;
		int y = SCREEN_H / 2 - 84;
		DrawGraph(x, y, _cgSchool, TRUE);
	}
	// logoªTRUEÈç`æ
	if (logo == TRUE) {
		DrawGraph(0, 0, _cgLogo, TRUE);
	}
	// opªTRUEÈçÄ¶
	if (op == TRUE) {
		PlayMovie("res/staging/OP.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		// ®æí
		op = FALSE;
	}
	// startªTRUEÈç`æ
	if (start == TRUE) {
		// wi`æ
		DrawGraph(0, 0, _cgBg, FALSE);
		int start_w = 500;
		int start_h = 150;
		int x = (SCREEN_W - start_w) / 2 - 15;
		int y = (SCREEN_H + start_h * 3) / 2 - 35;
		// X^[g{^`æ
		DrawGraph(x, y, _cgStart, TRUE);	
	}
}