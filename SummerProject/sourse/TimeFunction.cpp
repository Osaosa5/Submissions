// 担当：尾﨑

/*
	時間/スタート関係の関数の処理をまとめたもの
*/

#include "DxLib.h"
#include "WinMain.h"
#include "SceneAction.h"

/*
	@brief	ゲームスタート前処理の初期化
*/
void SceneAction::InitStartPreprocessing() {
	// スタートフラグ初期化
	gameStart				= 0;
	operationDescription	= 1;
	startSignal				= 0;
	startCnt				= -1;
}

/*
	@brief	ゲームスタート前処理
*/
void SceneAction::ProcessBeforeStart() {
	// ゲームスタート　
	// Bボタンを押したら3カウント開始
	if(gTrg & PAD_INPUT_4 && operationDescription == 1) {
		operationDescription = 0;
		startCnt = 250;
	}
	// カウントが50になったら「start」を表示
	if(startCnt == 50)  startSignal = 1;
	// カウントが1になったら「start」を非表示
	if(startCnt == 1)	startSignal = 0;
	// カウントが0になったらゲームを開始する
	if(startCnt == 0) {
		gameStart = 1;
		gameStartTime = GetNowCount();
		pl.speed_x = 10;
		PlaySoundMem(_bgm[BGM_STAGE_ONE], DX_PLAYTYPE_LOOP);
	}
	// cntを減らす
	if(startCnt != -1) { startCnt--; }
}

/*
	@brief	ゲームスタート前処理の描画
*/
void SceneAction::DrawStartPreprocessing() {
	// 操作説明の画像を描画
	if(operationDescription == 1) {
		DrawGraph(0, 0, _cgOperationDescription, FALSE);
	}
	// 3カウント描画
	int num = 0;
	if(startCnt <= 230) num = NUMBER_ZERO;
	if(startCnt <= 170) num = NUMBER_ONE;
	if(startCnt <= 110)	num = NUMBER_TWO;
	if(startCnt <= 50)  num = -1;
	// カウント描画位置
	int cnt_x = (SCREEN_W / 2) - 150;
	int cnt_y = SCREEN_H / 2 - 150;
	// 0は描画しない
	if(num > -1) {
		if((startCnt - 50) % 60 == 0) PlaySoundMem(_se[SE_CNT], DX_PLAYTYPE_BACK);
		DrawGraph(cnt_x, cnt_y, _cgCntNumber[num], TRUE);
	}
	// 「start」描画位置
	int start_x = (SCREEN_W / 2) - 450;
	int start_y = SCREEN_H / 2 - 150;
	if(startSignal == 1) {
		if(startCnt == 49) PlaySoundMem(_se[SE_START], DX_PLAYTYPE_BACK);
		DrawGraph(start_x, start_y, _cgStart, TRUE);
	}
}

/*
	@brief	制限時間処理の初期化
*/
void SceneAction::InitLimitTime() {
	// 制限時間をセット
	gameLimitTime	= 120000;	
	// ゲームスタート時間を初期化
	gameStartTime	= 0;
	// ゲームの経過時間を初期化
	gameElapsedTime = 0;
	// 描画用の制限時間を初期化
	drawLimitTime	= 0;
}

/*
	@brief	制限時間処理
*/
void SceneAction::ProcessLimitTime() {
	// ゲームがスタートしていたら時間を計測
	if(gameStart == 1) {
		// ポーズ画面を開いた時間を保存する変数に現在の時間を取得
		oldTime			= GetNowCount();
		// ゲームの経過時間を計測
		// 現在の時間 - ゲームスタート時間
		gameElapsedTime = GetNowCount() - gameStartTime;
	}
	// 描画用の制限時間を計算
	// 制限時間 - 経過時間
	drawLimitTime = gameLimitTime - gameElapsedTime;
}

/*
	@brief	制限時間を描画
*/
void SceneAction::DrawLimitTime() {
	// 現在の時間を秒に変換
	int second		= drawLimitTime / 1000;
	// 分に変換
	int minutes		= second / 60;
	// 秒に変換(十の位)
	int second_10	= second % 60 / 10;
	// 秒に変換(一の位)
	int second_1	= second % 60 - second_10 * 10;
	// ミリ秒を描画
	int ms_10		= (drawLimitTime / 10) % 10;
	int ms_100		= (drawLimitTime / 100) % 10;

	// 時間を描画する位置
	int time_x = 780;
	int time_y = 45;
	int time_w = 48;

	// 制限時間の後ろに描画するボックスの位置
	int box_w = 430;
	int box_h = 110;
	int box_x = (SCREEN_W - box_w) / 2;
	int box_y = 30;

	// 操作説明の画像を表示していないときに、制限時間を描画する
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