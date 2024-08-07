// SFφϊ±

/*
	|[YζΚΙΦ·ιΦ
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneAction.h"

/*
	@brief	|[YζΚΙΦ·ιΟΜϊ»
*/
void SceneAction::InitPouse() {
	// Iππϊ»
	menu_Yes	= OPTION_YES;
	menu_No		= OPTION_NO;

	// IπΜ
	menu_Num	= _OPTION_ALL_;

	// Iπ
	nowSelect	= menu_Yes;

	oldTime		= 0;
}

/*
	@brief	|[YζΚΜ
*/
void SceneAction::ProcessPouse() {
	// Q[πJn΅Δ’ι©H
	if (gameStart == 1) {
		// start{^π΅½Ζ«A
		// |[YζΚπJ’Δ’Θ―κΞ|[YζΚπJ­
		if (gTrg & PAD_INPUT_12) {
			if (pause == 0) { pause = 1; }
		}
		// |[YζΚͺJ’Δ’ιΖ«Μ
		if(pause == 1) {
			// IππκΒΊ°ι
			if(gTrg & PAD_INPUT_RIGHT) {
				nowSelect = (nowSelect + 1) % menu_Num;
				PlaySoundMem(_se[SE_SELECT], DX_PLAYTYPE_BACK);
			}
			// IππκΒγ°ι
			if(gTrg & PAD_INPUT_LEFT) {
				nowSelect = (nowSelect + (menu_Num - 1)) % menu_Num;
				PlaySoundMem(_se[SE_SELECT], DX_PLAYTYPE_BACK);
			}
			// IπΜ
			switch(nowSelect) {
				// yesπIπ΅Δ’½η
			case OPTION_YES:
				// Ε©ηβθΌ·
				if(gTrg & PAD_INPUT_4) {	// AL[
					// θΉ
					PlaySoundMem(_se[SE_DETERMINATION], DX_PLAYTYPE_BACK);
					// SceneActionπΗέέΘ¨·
					SceneBase* scene = new SceneAction(0);
					ChangeScene(scene);
				}
				break;

				// noπIπ΅Δ’½η
			case OPTION_NO:
				// Q[π±―ι
				if(gTrg & PAD_INPUT_4) {	// AL[
					// θΉ
					PlaySoundMem(_se[SE_DETERMINATION], DX_PLAYTYPE_BACK);
					// tOIt
					pause = FALSE;
					int difference = GetNowCount() - oldTime;
					gameStartTime += difference;
					int ac = 0;
				}
				break;
			}
		}
	}

	
}

/*
	@brief	|[YζΚΜ`ζ
*/
void SceneAction::DrawPouse() {
	// pausetOͺIΜΙ`ζ·ι
	if (pause == 1) {
		// fade
		DrawGraph(0, 0, _cgFade, TRUE);
		// retry?
		DrawGraph(810, 200, _cgRetry, TRUE);
		// yes
		DrawGraph(YES_X, YES_Y, _cgYes[COLLOR_BLUE], TRUE);
		// no
		DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_BLUE], TRUE);

		// IπΜ
		// ΗΏηͺIΞκΔ’ι©ΕͺΟνι
		switch (nowSelect) {
		case OPTION_YES:
			// yes
			DrawGraph(YES_X, YES_Y, _cgYes[COLLOR_YELLOW], TRUE);
			break;
		case OPTION_NO:
			// no
			DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_YELLOW], TRUE);
			break;
		}
	}
}