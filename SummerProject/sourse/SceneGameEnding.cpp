// SFöú±

/*
	Q[ÌGfBO
*/

#include "DxLib.h"
#include "gamemain.h"
#include "SceneGameEnding.h"
#include "SceneGameTitle.h"

/*
	@brief	SceneGameEndingÌRXgN^
*/
SceneGameEnding::SceneGameEnding() {
	// æÇÝÝ
	_cgBg		= LoadGraph("res/cgBg/ending.png");
	// ¹yÇÝÝ
	bgm_ending	= LoadSoundMem("res/sound/Anxious.mp3");

	// tOú»
	ed	= FALSE;
	end = FALSE;
}

/*
	@brief	SceneGameEndingÌfXgN^
*/
SceneGameEnding::~SceneGameEnding() {
	// OtBbNðã©çí·é
	// wií
	DeleteGraph(_cgBg);

	// ÉÇÝ±ñ¾¹f[^ðí·é
	// GfBOí
	DeleteSoundMem(bgm_ending);
}

/*
	@brief	SceneGameEndingÌ
*/
void SceneGameEnding::Process() {
	// ¡Ìstepðæ¾
	int step = _fade->GetStep();
	switch (step) {
	case 0:
		// FIJn
		_fade->ColorFadeIn(1);
		// ÌXebvÖ
		step++;
		break;
	case 1:
		// tF[hCÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// ®æÄ¶
			ed = TRUE;
			// ÌXebvÖ
			step++;
		}
		break;
	case 2:
		// b{^Å®æXLbv
		if (gTrg & PAD_INPUT_4) {
			ed = FALSE;
		}
		if (ed == FALSE) {
			// GhæÊ`æ
			end = TRUE;
			// ÌXebvÖ
			step++;
		}
		break;
	case 3:
		// bgmÄ¶
		PlaySoundMem(bgm_ending, DX_PLAYTYPE_LOOP);
		// FIJn
		_fade->ColorFadeIn(0);
		// ÌXebvÖ
		step++;
		break;
	case 4:
		// Êí
		if (gTrg & PAD_INPUT_4) {
			// tF[hAEgJn
			_fade->ColorFadeOut(0, 0, 0, 30);
			// ÌXebvÖ
			step++;
		}
		break;
	case 5:
		// tF[hAEgÍI¹µ½©H
		if (_fade->IsColorFade() == 0) {
			// stepú»
			step = 0;
			// tF[hAEgI¹
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
		}
		break;
	}
	_fade->SetStep(step);
}

/*
	@brief	SceneGameEndingÌ`æ
*/
void SceneGameEnding::Draw() {
	// edªTRUEÈçÄ¶
	if (ed == TRUE) {
		PlayMovie("res/staging/ed.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		// ®æí
		ed = FALSE;
	}
	// endªTRUEÈç`æ
	if (end == TRUE) {
		DrawGraph(0, 0, _cgBg, FALSE);
	}
}