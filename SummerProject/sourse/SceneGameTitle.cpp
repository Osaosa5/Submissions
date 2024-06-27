// 担当：尾﨑

/*
	タイトル処理
*/

#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "SceneGameTitle.h"
#include "SceneAction.h"

/*
	@brief	SceneGameTitleのコンストラクタ
*/
SceneGameTitle::SceneGameTitle() {
	// 画像読み込み
	_cgSchool	= LoadGraph("res/UI/AMG-LOGO.png");
	_cgLogo		= LoadGraph("res/UI/team_logo.png");
	_cgBg		= LoadGraph("res/cgBg/title.png");
	_cgStart	= LoadGraph("res/UI/ui_press_start_button.png");
	// 音楽読み込み
	bgm_title	= LoadSoundMem("res/sound/Electric_Highway.mp3");

	// フラグ初期化
	school = FALSE;
	logo = FALSE;
	op = FALSE;
	start = FALSE;

	// time関係初期化
	instrumentationStart = 0;
	latency = 0;
}

/*
	@brief	SceneGameTitleのデストラクタ
*/
SceneGameTitle::~SceneGameTitle() {
	DeleteGraph(_cgSchool);
	DeleteGraph(_cgLogo);
	DeleteGraph(_cgBg);
	DeleteSoundMem(bgm_title);
}

/*
	@brief	SceneGameTitleの処理
*/
void SceneGameTitle::Process() {
	// 今のstepを取得
	int step = _fade->GetStep();
	// stepで処理を変える
	switch (step) {
	case 0:
		// 計測開始
		instrumentationStart = GetNowCount();
		// 学校ロゴ描画
		school = TRUE;
		// FI開始
		_fade->ColorFadeIn(50);
		// 次のステップへ
		step++;
		break;
	case 1:
		// フェードインは終了したか？
		if (_fade->IsColorFade() == 0) {
			// 2秒経ったか？
			if (GetNowCount() - instrumentationStart > LATENCY) {
				// フェードアウト開始
				_fade->ColorFadeOut(0, 0, 0, 60);
				// 次のステップへ
				step++;
			}
		}
		break;
	case 2:
		// フェードアウトは終了したか？
		if (_fade->IsColorFade() == 0) {
			// 学校ロゴ削除
			school = FALSE;
			// 計測開始
			instrumentationStart = GetNowCount();
			// チームロゴ描画
			logo = TRUE;
			// FI開始
			_fade->ColorFadeIn(50);
			// 次のステップへ
			step++;
		}
		break;
	case 3:
		// フェードインは終了したか？
		if (_fade->IsColorFade() == 0) {
			// 2秒経ったか？
			if (GetNowCount() - instrumentationStart > LATENCY) {
				// フェードアウト開始
				_fade->ColorFadeOut(0, 0, 0, 40);
				// 次のステップへ
				step++;
			}
		}
		break;
	case 4:
		// フェードアウトは終了したか？
		if (_fade->IsColorFade() == 0) {
			// チームロゴ削除
			logo = FALSE;
			// 次のステップへ
			step++;
		}
		break;
	case 5:
		// 動画再生
		op = TRUE;
		// 次のステップへ
		step++;
		break;
	case 6:
		// bボタンで動画スキップ
		if (gTrg & PAD_INPUT_4) {
			op = FALSE;
		}
		if (op == FALSE) {
			// フェードアウト開始
			_fade->ColorFadeOut(0, 0, 0, 40);
			// 次のステップへ
			step++;
		}
		break;
	case 7:
		// フェードアウトは終了したか？
		if (_fade->IsColorFade() == 0) {
			// スタート画面描画
			start = TRUE;
			// FI開始
			_fade->ColorFadeIn(60);
			// bgm再生
			PlaySoundMem(bgm_title, DX_PLAYTYPE_LOOP);
			// 次のステップへ
			step++;
		}
		break;
	case 8:
		// フェードインは終了したか？
		if (_fade->IsColorFade() == 0) {
			// シーン切り替え処理
			if (gTrg & PAD_INPUT_12 || gTrg & PAD_INPUT_10) {
				// フェードアウト開始
				_fade->ColorFadeOut(0, 0, 0, 10);
				// 次のステップへ
				step++;
			}
		}
		break;
	case 9:
		// フェードアウトは終了したか？
		if (_fade->IsColorFade() == 0) {
			// スタート画面削除
			start = FALSE;
			// step初期化
			step = NULL;
			// フェードアウト終了
			SceneBase* scene = new SceneAction(0);
			ChangeScene(scene);
		}
		break;
	}
	_fade->SetStep(step);
}

/*
	@brief	SceneGameTitleの描画
*/
void SceneGameTitle::Draw() {
	// schoolがTRUEなら描画
	if (school == TRUE) {
		int x = SCREEN_W / 2 - 640;
		int y = SCREEN_H / 2 - 84;
		DrawGraph(x, y, _cgSchool, TRUE);
	}
	// logoがTRUEなら描画
	if (logo == TRUE) {
		DrawGraph(0, 0, _cgLogo, TRUE);
	}
	// opがTRUEなら再生
	if (op == TRUE) {
		PlayMovie("res/staging/OP.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		// 動画削除
		op = FALSE;
	}
	// startがTRUEなら描画
	if (start == TRUE) {
		// 背景描画
		DrawGraph(0, 0, _cgBg, FALSE);
		int start_w = 500;
		int start_h = 150;
		int x = (SCREEN_W - start_w) / 2 - 15;
		int y = (SCREEN_H + start_h * 3) / 2 - 35;
		// スタートボタン描画
		DrawGraph(x, y, _cgStart, TRUE);	
	}
}