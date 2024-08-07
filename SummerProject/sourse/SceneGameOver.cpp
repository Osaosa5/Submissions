// SFφϊ±

/*
	Q[I[o[
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneGameOver.h"
#include "SceneGameTitle.h"
#include "SceneAction.h"

/*
	@brief	SceneGameOverΜRXgN^
*/
SceneGameOver::SceneGameOver() {
	// wi
	_cgBg = LoadGraph("res/cgBg/gameover.png");

	// continue?
	_cgContinue = LoadGraph("res/UI/gameover/continue2.png");

	// Yes or No
	_cgYes[COLLOR_BLUE] = LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE] = LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/No4.png");

	// bgm
	bgm_gameover = LoadSoundMem("res/sound/Τ.mp3");
	// se
	se[SE_SELECT_] = LoadSoundMem("res/sound/select.mp3");						// IπΉ
	se[SE_DETERMINATION_] = LoadSoundMem("res/sound/determination.mp3");		// θΉ
	
	// Iππϊ»
	option.menu_Yes = OPTION_YES;
	option.menu_No	= OPTION_NO;
	
	// IπΜ
	option.menu_Num = _OPTION_ALL_;

	// Iπ
	nowSelect = option.menu_Yes;

	// tOϊ»
	retry = FALSE;
	end = FALSE;
}

/*
	@brief	SceneGameOverΜfXgN^
*/
SceneGameOver::~SceneGameOver() {
	// OtBbNπγ©ην·ι
	// wiν
	DeleteGraph(_cgBg);
	// continueν
	DeleteGraph(_cgContinue);
	// Ϊν
	for (int i = 0; i < _OPTION_ALL_; i++) {
		DeleteGraph(_cgYes[i]);
		DeleteGraph(_cgNo[i]);
	}
	// ΙΗέ±ρΎΉf[^πν·ι
	// bgmν
	DeleteSoundMem(bgm_gameover);
	// seν
	for (int i = 0; i < _SE_ALL_; i++) {
		DeleteGraph(se[i]);
	}
}

/*
	@brief	SceneGameOverΜ
*/
void SceneGameOver::Process() {
	// ζΚ
	int step = _fade->GetStep();	// »έΜXebvπζΎ
	switch (step) {
	case 0:
		_fade->ColorFadeIn(60);	// 60fΕFI
		PlaySoundMem(bgm_gameover, DX_PLAYTYPE_LOOP);	// bgmπΔΆ
		step++;	// ΜXebvΦ
		break;
	case 1:
		if (_fade->IsColorFade() == 0) {	// FIΝIΉ΅½©H
			// tF[hCIΉ
			step++;	// ΜXebvΦ
		}
		break;
	case 2:
		// C
		
		// IππκΒΊ°ι
		if (gTrg & PAD_INPUT_DOWN) {	// ΊΙόΝ΅½H
			nowSelect = (nowSelect + 1) % option.menu_Num;	// ΊΜIππIΤ
			PlaySoundMem(se[SE_SELECT_], DX_PLAYTYPE_BACK);	// IπΉ
		}
		// IππκΒγ°ι
		if (gTrg & PAD_INPUT_UP) {	// γΙόΝ΅½H
			nowSelect = (nowSelect + (option.menu_Num - 1)) % option.menu_Num;	// γΜIππIΤ
			PlaySoundMem(se[SE_SELECT_], DX_PLAYTYPE_BACK);	// IπΉ
		}
		switch (nowSelect) {	// ½πIπ΅Δ’ι©
		case OPTION_YES:	// YesπIπ΅Δ’ικ
			if (gTrg & PAD_INPUT_4) {	// AL[
				PlaySoundMem(se[SE_DETERMINATION_], DX_PLAYTYPE_BACK);	// IπΉ
				// tOI
				retry = TRUE;
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 60);
				step++;	// ΜXebvΦ
			}
			break;
		case OPTION_NO:	// NoπIπ΅Δ’ικ
			if (gTrg & PAD_INPUT_4) {	// AL[
				PlaySoundMem(se[SE_DETERMINATION_], DX_PLAYTYPE_BACK);	// IπΉ
				// tOI
				end = TRUE;
				// tF[hAEgJn
				_fade->ColorFadeOut(0, 0, 0, 60);
				step++;	// ΜXebvΦ
			}
			break;
		}
		break;
	case 3:
		if (_fade->IsColorFade() == 0) {	// FOΝIΉ΅½©H
			// stepϊ»
			step = 0;
			// tF[hAEgIΉ
			if (retry == TRUE) {
				SceneBase* scene = new SceneAction(0);
				ChangeScene(scene);	// ActionSceneΙΨθΦ¦ι
			}
			if (end == TRUE) {
				SceneBase* scene = new SceneGameTitle();
				ChangeScene(scene);	// TitleSceneΙΨθΦ¦ι
			}
		}
		break;
	}
	_fade->SetStep(step);	// »έΜXebvπΫΆ

}

/*
	@brief	SceneGameOverΜ`ζ
*/
void SceneGameOver::Draw() {
	// wi
	DrawGraph(0, 0, _cgBg, FALSE);
	// continue?
	DrawGraph(410, 100, _cgContinue, TRUE);
	// yes
	DrawGraph(YES_X_, YES_Y_, _cgYes[COLLOR_BLUE], TRUE);
	// no
	DrawGraph(NO_X_, NO_Y_, _cgNo[COLLOR_BLUE], TRUE);

	switch (nowSelect) {
	case OPTION_YES:
		// yes
		DrawGraph(YES_X_, YES_Y_, _cgYes[COLLOR_YELLOW], TRUE);
		break;
	case OPTION_NO:
		// no
		DrawGraph(NO_X_, NO_Y_, _cgNo[COLLOR_YELLOW], TRUE);
		break;
	}
}