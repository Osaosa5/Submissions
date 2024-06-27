// 担当：尾﨑

/*
	リザルト処理
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneGameResult.h"
#include "SceneGameEnding.h"

/*
	@brief	SceneGameResultのコンストラクタ
	@param	resultTime:クリアタイム
*/
SceneGameResult::SceneGameResult (int resultTime) {
	// セーブ読み込み
	_save = new save("save.txt", 5, 120000 - resultTime);
	// 画像読み込み
	_cgBg = LoadGraph("res/cgBg/result2.png");
	_cgRanking = LoadGraph("res/UI/ranking_hyou.png");
	_cgFade = LoadGraph("res/cgBg/fade.png");
	_cgRetry	= LoadGraph("res/UI/retry.png");
	_cgResult[0] = LoadGraph("res/UI/ui_rank_s.png");
	_cgResult[1] = LoadGraph("res/UI/ui_rank_a.png");
	_cgResult[2] = LoadGraph("res/UI/ui_rank_b.png");
	_cgResult[3] = LoadGraph("res/UI/ui_rank_c.png");
	// Yes or No
	_cgYes[COLLOR_BLUE] = LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE] = LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/No4.png");
	// bgm読み込み
	_bgmResult = LoadSoundMem("res/sound/Clear_Pallet.mp3");
	_seResult[0] = LoadSoundMem("res/sound/select.mp3");
	_seResult[1] = LoadSoundMem("res/sound/determination.mp3");

	// 変数の初期化
	_rank = 0;
	// フラグ初期化
	_isRanking = FALSE;
	_isContinue = FALSE;
	// 引数からクリアタイムをセット
	_resultTime = resultTime;
	// 選択肢を初期化
	menu_Yes = OPTION_YES;
	menu_No = OPTION_NO;
	// 選択肢の総数
	menu_Num = _OPTION_ALL_;
	// 選択中
	nowSelect = menu_Yes;
	// カラーマスクのリセット
	_fade->ColorFadeIn(60);
	_save->Export("save.txt", 5);
}

/*
	@brief	SceneGameResultのデストラクタ
*/
SceneGameResult::~SceneGameResult() {
	// グラフィックをメモリ上から削除する
	// 背景削除
	DeleteGraph(_cgBg);
	// リトライ削除
	DeleteGraph(_cgRetry);
	// フェード削除
	DeleteGraph(_cgFade);
	// ランキング削除
	DeleteGraph(_cgRanking);
	// ランク削除
	for (int i = 0; i < 3; i++) {
		DeleteGraph(_cgResult[i]);
	}
	// 選択肢削除
	for (int i = 0; i < 2; i++) {
		DeleteGraph(_cgYes[i]);
		DeleteGraph(_cgNo[i]);
		DeleteGraph(_seResult[i]);
	}
	// メモリに読みこんだ音データを削除する
	// bgm削除
	DeleteSoundMem(_bgmResult);
}

/*
	@brief	SceneGameResultの処理
*/
void SceneGameResult::Process() {
	// 今のstepを取得
	int step = _fade->GetStep();
	// ステップごとの処理
	switch (step) {
	case 0:
		// クリアタイムからランクを決める
		if(_resultTime < 56000)	_rank = 1;
		if(_resultTime < 41000)	_rank = 2;
		if(_resultTime < 26000)	_rank = 3;
		// FI開始
		_fade->ColorFadeIn(10);
		PlaySoundMem(_bgmResult, DX_PLAYTYPE_LOOP);
		// 次のステップへ
		step++;
		break;
	case 1:
		// フェードインは終了したか？
		if (_fade->IsColorFade() == 0) {
			// Bキーで次のステップへ
			if (gTrg & PAD_INPUT_4) {	
				step++;
			}
		}
		break;
	case 2:
		
		_isRanking = TRUE;
		// Bキーで次のステップへ
		if (gTrg & PAD_INPUT_4) {	
			_isContinue = TRUE;
			step++;
		}
		break;
	case 3:
		// 選択肢を一つ下げる
		if (gTrg & PAD_INPUT_RIGHT) {
			nowSelect = (nowSelect + 1) % menu_Num;
			PlaySoundMem(_seResult[0], DX_PLAYTYPE_BACK);
		}
		// 選択肢を一つ上げる
		if (gTrg & PAD_INPUT_LEFT) {
			nowSelect = (nowSelect + (menu_Num - 1)) % menu_Num;
			PlaySoundMem(_seResult[0], DX_PLAYTYPE_BACK);
		}
		// 選択肢の処理
		switch (nowSelect) {
			// yesを選択していたら
		case OPTION_YES:
			// 最初からやり直す
			if (gTrg & PAD_INPUT_4) {	// Aキー
				// 決定音
				PlaySoundMem(_seResult[1], DX_PLAYTYPE_BACK);
				// フェードアウト開始
				_fade->ColorFadeOut(0, 0, 0, 40);
				// リトライ
				_isRetry = TRUE;
				step++;
			}
			break;
			// noを選択していたら
		case OPTION_NO:
			// ゲームを続ける
			if (gTrg & PAD_INPUT_4) {	// Aキー
				// 決定音
				PlaySoundMem(_seResult[1], DX_PLAYTYPE_BACK);
				// フェードアウト開始
				_fade->ColorFadeOut(0, 0, 0, 40);
				// エンディング
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
				// SceneActionを読み込みなおす
				SceneBase* scene = new SceneAction(0);
				ChangeScene(scene);
				step = 0;
			}
			if(_isEnd) {
				// シーン切り替え
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
	@brief	SceneGameResultの描画
*/
void SceneGameResult::Draw() {
	// 背景描画
	DrawGraph(0, 0, _cgBg, FALSE);
	// ランク描画
	DrawGraph(50, 100, _cgResult[_rank], TRUE);
	// ランキング描画
	if (_isRanking)
	{
		DrawGraph(0, 0, _cgFade, TRUE);
		DrawGraph(474, 239, _cgRanking, TRUE);
		_save->AscendingOrderDataDrawing(810, 250, 120, 100);
	}
	// retry
	if (_isContinue) {
		DrawGraph(0, 0, _cgFade, TRUE);
		// retry?
		DrawGraph(810, 200, _cgRetry, TRUE);
		// yes
		DrawGraph(YES_X, YES_Y, _cgYes[COLLOR_BLUE], TRUE);
		// no
		DrawGraph(NO_X, NO_Y, _cgNo[COLLOR_BLUE], TRUE);
		// 選択肢の処理
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