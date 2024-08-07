// SFφϊ±

/*
	Τ/X^[gΦWΜΦΜπάΖί½ΰΜ
*/

#include "DxLib.h"
#include "WinMain.h"
#include "SceneAction.h"

/*
	@brief	Q[X^[gOΜϊ»
*/
void SceneAction::InitStartPreprocessing() {
	// X^[gtOϊ»
	gameStart				= 0;
	operationDescription	= 1;
	startSignal				= 0;
	startCnt				= -1;
}

/*
	@brief	Q[X^[gO
*/
void SceneAction::ProcessBeforeStart() {
	// Q[X^[g@
	// B{^π΅½η3JEgJn
	if(gTrg & PAD_INPUT_4 && operationDescription == 1) {
		operationDescription = 0;
		startCnt = 250;
	}
	// JEgͺ50ΙΘΑ½ηustartvπ\¦
	if(startCnt == 50)  startSignal = 1;
	// JEgͺ1ΙΘΑ½ηustartvπρ\¦
	if(startCnt == 1)	startSignal = 0;
	// JEgͺ0ΙΘΑ½ηQ[πJn·ι
	if(startCnt == 0) {
		gameStart = 1;
		gameStartTime = GetNowCount();
		pl.speed_x = 10;
		PlaySoundMem(_bgm[BGM_STAGE_ONE], DX_PLAYTYPE_LOOP);
	}
	// cntπΈη·
	if(startCnt != -1) { startCnt--; }
}

/*
	@brief	Q[X^[gOΜ`ζ
*/
void SceneAction::DrawStartPreprocessing() {
	// μΰΎΜζπ`ζ
	if(operationDescription == 1) {
		DrawGraph(0, 0, _cgOperationDescription, FALSE);
	}
	// 3JEg`ζ
	int num = 0;
	if(startCnt <= 230) num = NUMBER_ZERO;
	if(startCnt <= 170) num = NUMBER_ONE;
	if(startCnt <= 110)	num = NUMBER_TWO;
	if(startCnt <= 50)  num = -1;
	// JEg`ζΚu
	int cnt_x = (SCREEN_W / 2) - 150;
	int cnt_y = SCREEN_H / 2 - 150;
	// 0Ν`ζ΅Θ’
	if(num > -1) {
		if((startCnt - 50) % 60 == 0) PlaySoundMem(_se[SE_CNT], DX_PLAYTYPE_BACK);
		DrawGraph(cnt_x, cnt_y, _cgCntNumber[num], TRUE);
	}
	// ustartv`ζΚu
	int start_x = (SCREEN_W / 2) - 450;
	int start_y = SCREEN_H / 2 - 150;
	if(startSignal == 1) {
		if(startCnt == 49) PlaySoundMem(_se[SE_START], DX_PLAYTYPE_BACK);
		DrawGraph(start_x, start_y, _cgStart, TRUE);
	}
}

/*
	@brief	§ΐΤΜϊ»
*/
void SceneAction::InitLimitTime() {
	// §ΐΤπZbg
	gameLimitTime	= 120000;	
	// Q[X^[gΤπϊ»
	gameStartTime	= 0;
	// Q[ΜoίΤπϊ»
	gameElapsedTime = 0;
	// `ζpΜ§ΐΤπϊ»
	drawLimitTime	= 0;
}

/*
	@brief	§ΐΤ
*/
void SceneAction::ProcessLimitTime() {
	// Q[ͺX^[g΅Δ’½ηΤπvͺ
	if(gameStart == 1) {
		// |[YζΚπJ’½ΤπΫΆ·ιΟΙ»έΜΤπζΎ
		oldTime			= GetNowCount();
		// Q[ΜoίΤπvͺ
		// »έΜΤ - Q[X^[gΤ
		gameElapsedTime = GetNowCount() - gameStartTime;
	}
	// `ζpΜ§ΐΤπvZ
	// §ΐΤ - oίΤ
	drawLimitTime = gameLimitTime - gameElapsedTime;
}

/*
	@brief	§ΐΤπ`ζ
*/
void SceneAction::DrawLimitTime() {
	// »έΜΤπbΙΟ·
	int second		= drawLimitTime / 1000;
	// ͺΙΟ·
	int minutes		= second / 60;
	// bΙΟ·(\ΜΚ)
	int second_10	= second % 60 / 10;
	// bΙΟ·(κΜΚ)
	int second_1	= second % 60 - second_10 * 10;
	// ~bπ`ζ
	int ms_10		= (drawLimitTime / 10) % 10;
	int ms_100		= (drawLimitTime / 100) % 10;

	// Τπ`ζ·ιΚu
	int time_x = 780;
	int time_y = 45;
	int time_w = 48;

	// §ΐΤΜγλΙ`ζ·ι{bNXΜΚu
	int box_w = 430;
	int box_h = 110;
	int box_x = (SCREEN_W - box_w) / 2;
	int box_y = 30;

	// μΰΎΜζπ\¦΅Δ’Θ’Ζ«ΙA§ΐΤπ`ζ·ι
	if(operationDescription == 0) {
		DrawGraph(box_x, box_y, _cgLimitTimeBox, TRUE);

		DrawGraph(time_x, time_y, _cgNumber[minutes], TRUE);

		DrawGraph(time_x + time_w, time_y, _cgNumber[NUMBER_KOLON], TRUE);

		DrawGraph(time_x + time_w * 2, time_y, _cgNumber[second_10], TRUE);

		DrawGraph(time_x + time_w * 3, time_y, _cgNumber[second_1], TRUE);

		DrawGraph(time_x + time_w * 4, time_y, _cgNumber[NUMBER_KOLON], TRUE);

		DrawGraph(time_x + time_w * 5, time_y, _cgNumber[ms_100], TRUE);

		DrawGraph(time_x + time_w * 6, time_y, _cgNumber[ms_10], TRUE);
	}
}