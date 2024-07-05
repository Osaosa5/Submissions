// 担当：尾﨑

/*
	ポーズ画面に関する関数
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneAction.h"

/*
	@brief	ポーズ画面に関する変数の初期化
*/
void SceneAction::InitPouse() {
	// 選択肢を初期化
	menu_Yes	= OPTION_YES;
	menu_No		= OPTION_NO;

	// 選択肢の総数
	menu_Num	= _OPTION_ALL_;

	// 選択中
	nowSelect	= menu_Yes;

	oldTime		= 0;
}

/*
	@brief	ポーズ画面の処理
*/
void SceneAction::ProcessPouse() {
	// ゲームを開始しているか？
	if (gameStart == 1) {
		// startボタンを押したとき、
		// ポーズ画面を開いていなければポーズ画面を開く
		if (gTrg & PAD_INPUT_12) {
			if (pause == 0) { pause = 1; }
		}
		// ポーズ画面が開いているときの処理
		if(pause == 1) {
			// 選択肢を一つ下げる
			if(gTrg & PAD_INPUT_RIGHT) {
				nowSelect = (nowSelect + 1) % menu_Num;
				PlaySoundMem(_se[SE_SELECT], DX_PLAYTYPE_BACK);
			}
			// 選択肢を一つ上げる
			if(gTrg & PAD_INPUT_LEFT) {
				nowSelect = (nowSelect + (menu_Num - 1)) % menu_Num;
				PlaySoundMem(_se[SE_SELECT], DX_PLAYTYPE_BACK);
			}
			// 選択肢の処理
			switch(nowSelect) {
				// yesを選択していたら
			case OPTION_YES:
				// 最初からやり直す
				if(gTrg & PAD_INPUT_4) {	// Aキー
					// 決定音
					PlaySoundMem(_se[SE_DETERMINATION], DX_PLAYTYPE_BACK);
					// SceneActionを読み込みなおす
					SceneBase* scene = new SceneAction(0);
					ChangeScene(scene);
				}
				break;

				// noを選択していたら
			case OPTION_NO:
				// ゲームを続ける
				if(gTrg & PAD_INPUT_4) {	// Aキー
					// 決定音
					PlaySoundMem(_se[SE_DETERMINATION], DX_PLAYTYPE_BACK);
					// フラグオフ
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
	@brief	ポーズ画面の描画
*/
void SceneAction::DrawPouse() {
	// pauseフラグがオンの時に描画する
	if (pause == 1) {
		// fade
		DrawGraph(0, 0, _cgFade, TRUE);
		// retry?
		DrawGraph(810, 200, _cgRetry, TRUE);
		// yes
		DrawGraph(YES_X, YES_Y, _cgYes[COLLOR_BLUE], TRUE);
		// no
		DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_BLUE], TRUE);

		// 選択肢の処理
		// どちらが選ばれているかで処理が変わる
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