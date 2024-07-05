// 担当：尾﨑

/*
	ゲームのエンディング処理
*/

#include "DxLib.h"
#include "gamemain.h"
#include "SceneGameEnding.h"
#include "SceneGameTitle.h"

/*
	@brief	SceneGameEndingのコンストラクタ
*/
SceneGameEnding::SceneGameEnding() {
	// 画像読み込み
	_cgBg		= LoadGraph("res/cgBg/ending.png");
	// 音楽読み込み
	bgm_ending	= LoadSoundMem("res/sound/Anxious.mp3");

	// フラグ初期化
	ed	= FALSE;
	end = FALSE;
}

/*
	@brief	SceneGameEndingのデストラクタ
*/
SceneGameEnding::~SceneGameEnding() {
	// グラフィックをメモリ上から削除する
	// 背景削除
	DeleteGraph(_cgBg);

	// メモリに読みこんだ音データを削除する
	// エンディング削除
	DeleteSoundMem(bgm_ending);
}

/*
	@brief	SceneGameEndingの処理
*/
void SceneGameEnding::Process() {
	// 今のstepを取得
	int step = _fade->GetStep();
	switch (step) {
	case 0:
		// FI開始
		_fade->ColorFadeIn(1);
		// 次のステップへ
		step++;
		break;
	case 1:
		// フェードインは終了したか？
		if (_fade->IsColorFade() == 0) {
			// 動画再生
			ed = TRUE;
			// 次のステップへ
			step++;
		}
		break;
	case 2:
		// bボタンで動画スキップ
		if (gTrg & PAD_INPUT_4) {
			ed = FALSE;
		}
		if (ed == FALSE) {
			// エンド画面描画
			end = TRUE;
			// 次のステップへ
			step++;
		}
		break;
	case 3:
		// bgm再生
		PlaySoundMem(bgm_ending, DX_PLAYTYPE_LOOP);
		// FI開始
		_fade->ColorFadeIn(0);
		// 次のステップへ
		step++;
		break;
	case 4:
		// 通常処理
		if (gTrg & PAD_INPUT_4) {
			// フェードアウト開始
			_fade->ColorFadeOut(0, 0, 0, 30);
			// 次のステップへ
			step++;
		}
		break;
	case 5:
		// フェードアウトは終了したか？
		if (_fade->IsColorFade() == 0) {
			// step初期化
			step = 0;
			// フェードアウト終了
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
		}
		break;
	}
	_fade->SetStep(step);
}

/*
	@brief	SceneGameEndingの描画
*/
void SceneGameEnding::Draw() {
	// edがTRUEなら再生
	if (ed == TRUE) {
		PlayMovie("res/staging/ed.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		// 動画削除
		ed = FALSE;
	}
	// endがTRUEなら描画
	if (end == TRUE) {
		DrawGraph(0, 0, _cgBg, FALSE);
	}
}