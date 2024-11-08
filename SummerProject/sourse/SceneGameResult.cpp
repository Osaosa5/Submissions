// SFφϊ±

/*
	Ug
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneGameResult.h"
#include "SceneGameEnding.h"

/*
	@brief	SceneGameResultΜRXgN^
	@param	resultTime:NA^C
*/
SceneGameResult::SceneGameResult (int resultTime) {
	// Z[uΗέέ
	_save = new save("save.txt", 5, 120000 - resultTime);
	// ζΗέέ
	_cgBg			= LoadGraph("res/cgBg/result2.png");
	_cgRanking		= LoadGraph("res/UI/ranking_hyou.png");
	_cgFade			= LoadGraph("res/cgBg/fade.png");
	_cgRetry		= LoadGraph("res/UI/retry.png");
	_cgResult[0]	= LoadGraph("res/UI/ui_rank_s.png");
	_cgResult[1]	= LoadGraph("res/UI/ui_rank_a.png");
	_cgResult[2]	= LoadGraph("res/UI/ui_rank_b.png");
	_cgResult[3]	= LoadGraph("res/UI/ui_rank_c.png");
	// Yes or No
	_cgYes[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/No4.png");
	// bgmΗέέ
	_bgmResult		= LoadSoundMem("res/sound/Clear_Pallet.mp3");
	_seResult[0]	= LoadSoundMem("res/sound/select.mp3");
	_seResult[1]	= LoadSoundMem("res/sound/determination.mp3");

	// ΟΜϊ»
	_rank = 0;
	// tOϊ»
	_isRanking	= FALSE;
	_isContinue = FALSE;
	// ψ©ηNA^CπZbg
	_resultTime = resultTime;
	// Iππϊ»
	_menuYes	= OPTION_YES;
	_menuNo		= OPTION_NO;
	// IπΜ
	_menuNum	= _OPTION_ALL_;
	// Iπ
	_nowSelect	= _menuYes;
	// J[}XNΜZbg
	_fade->ColorFadeIn(60);
	_save->Export("save.txt", 5);
}

/*
	@brief	SceneGameResultΜfXgN^
*/
SceneGameResult::~SceneGameResult() {
	// OtBbNπγ©ην·ι
	// wiν
	DeleteGraph(_cgBg);
	// gCν
	DeleteGraph(_cgRetry);
	// tF[hν
	DeleteGraph(_cgFade);
	// LOν
	DeleteGraph(_cgRanking);
	// Nν
	for (int i = 0; i < _CG_RESULT_ALL_; i++) {
		DeleteGraph(_cgResult[i]);
	}
	// Iπν
	for (int i = 0; i < _CG_OPTION_COLOR_NUM_; i++) {
		DeleteGraph(_cgYes[i]);
		DeleteGraph(_cgNo[i]);
	}

	// ΙΗέ±ρΎΉf[^πν·ι
	// seν
	for (int i = 0; i < _SE_RESULT_NUM_; i++) {
		DeleteSoundMem(_seResult[i]);
	}
	// bgmν
	DeleteSoundMem(_bgmResult);
}

/*
	@brief	SceneGameResultΜ
*/
void SceneGameResult::Process() {
	// ‘ΜstepπζΎ
	int step = _fade->GetStep();
	// Xebv²ΖΜ
	switch (step) {
	case 0:
		// NA^C©ηNπίι
		if(_resultTime < 56000)	_rank = 1;
		if(_resultTime < 41000)	_rank = 2;
		if(_resultTime < 26000)	_rank = 3;
		// FIJn
		_fade->ColorFadeIn(10);
		PlaySoundMem(_bgmResult, DX_PLAYTYPE_LOOP);
		// ΜXebvΦ
		step++;
		break;
	case 1:
		// tF[hCΝIΉ΅½©H
		if (_fade->IsColorFade() == 0) {
			// BL[ΕΜXebvΦ
			if (gTrg & PAD_INPUT_4) {	
				step++;
			}
		}
		break;
	case 2:
		
		_isRanking = TRUE;
		// BL[ΕΜXebvΦ
		if (gTrg & PAD_INPUT_4) {	
			_isContinue = TRUE;
			step++;
		}
		break;
	case 3:
		// IππκΒΊ°ι
		if (gTrg & PAD_INPUT_RIGHT) {
			_nowSelect = (_nowSelect + 1) % _menuNum;
			PlaySoundMem(_seResult[0], DX_PLAYTYPE_BACK);
		}
		// IππκΒγ°ι
		if (gTrg & PAD_INPUT_LEFT) {
			_nowSelect = (_nowSelect + (_menuNum - 1)) % _menuNum;
			PlaySoundMem(_seResult[0], DX_PLAYTYPE_BACK);
		}
		// IπΜ
		switch (_nowSelect) {
			// yesπIπ΅Δ’½η
		case OPTION_YES:
			// Ε©ηβθΌ·
			if (gTrg & PAD_INPUT_4) {	// AL[
				// θΉ
				PlaySoundMem(_seResult[1], DX_PLAYTYPE_BACK);
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 40);
				// gC
				_isRetry = TRUE;
				step++;
			}
			break;
			// noπIπ΅Δ’½η
		case OPTION_NO:
			// Q[π±―ι
			if (gTrg & PAD_INPUT_4) {	// AL[
				// θΉ
				PlaySoundMem(_seResult[1], DX_PLAYTYPE_BACK);
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 40);
				// GfBO
				_isEnd = TRUE;
				step++;
			}
			break;
		}
		break;
	case 4:
		if(_fade->IsColorFade() == 0) {
			_isRanking = FALSE;
			if(_isRetry) {
				// SceneActionπΗέέΘ¨·
				SceneBase* scene = new SceneAction(0);
				ChangeScene(scene);
				step = 0;
			}
			if(_isEnd) {
				// V[ΨθΦ¦
				SceneBase* scene = new SceneGameEnding();
				ChangeScene(scene);
				step = 0;
			}
		}
		break;
	}
	_fade->SetStep(step);

}

/*
	@brief	SceneGameResultΜ`ζ
*/
void SceneGameResult::Draw() {
	// wi`ζ
	DrawGraph(0, 0, _cgBg, FALSE);
	// N`ζ
	DrawGraph(50, 100, _cgResult[_rank], TRUE);
	// LO`ζ
	if (_isRanking)
	{
		DrawGraph(0, 0,	_cgFade, TRUE);
		DrawGraph(474, 239, _cgRanking, TRUE);
		_save->AscendingOrderDataDrawing(810, 250, 120, 100);
	}
	// retry
	if (_isContinue) {
		DrawGraph(0, 0, _cgFade, TRUE);
		// retry?
		DrawGraph(810, 200,	_cgRetry, TRUE);
		// yes
		DrawGraph(YES_X, YES_Y,	_cgYes[COLLOR_BLUE], TRUE);
		// no
		DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_BLUE], TRUE);
		// IπΜ
		switch (_nowSelect) {
		case OPTION_YES:
			// yes
			DrawGraph(YES_X, YES_Y,	_cgYes[COLLOR_YELLOW], TRUE);
			break;
		case OPTION_NO:
			// no
			DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_YELLOW],	TRUE);
			break;
		}
	}
}