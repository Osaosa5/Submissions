// 担当：尾﨑

/*
	ゲームオーバー処理
*/

#include "DxLib.h"
#include "GameMain.h"
#include "SceneGameOver.h"
#include "SceneGameTitle.h"
#include "SceneAction.h"

/*
	@brief	SceneGameOverのコンストラクタ
*/
SceneGameOver::SceneGameOver() {
	// 背景
	_cgBg = LoadGraph("res/cgBg/gameover.png");

	// continue?
	_cgContinue = LoadGraph("res/UI/gameover/continue2.png");

	// Yes or No
	_cgYes[COLLOR_BLUE] = LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE] = LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW] = LoadGraph("res/UI/gameover/No4.png");

	// bgm
	bgm_gameover = LoadSoundMem("res/sound/間.mp3");
	// se
	se[SE_SELECT_] = LoadSoundMem("res/sound/select.mp3");						// 選択音
	se[SE_DETERMINATION_] = LoadSoundMem("res/sound/determination.mp3");		// 決定音
	
	// 選択肢を初期化
	option.menu_Yes = OPTION_YES;
	option.menu_No	= OPTION_NO;
	
	// 選択肢の総数
	option.menu_Num = _OPTION_ALL_;

	// 選択中
	nowSelect = option.menu_Yes;

	// フラグ初期化
	retry = FALSE;
	end = FALSE;
}

/*
	@brief	SceneGameOverのデストラクタ
*/
SceneGameOver::~SceneGameOver() {
	// グラフィックをメモリ上から削除する
	// 背景削除
	DeleteGraph(_cgBg);
	// continue削除
	DeleteGraph(_cgContinue);
	// 項目削除
	for (int i = 0; i < _OPTION_ALL_; i++) {
		DeleteGraph(_cgYes[i]);
		DeleteGraph(_cgNo[i]);
	}
	// メモリに読みこんだ音データを削除する
	// bgm削除
	DeleteSoundMem(bgm_gameover);
	// se削除
	for (int i = 0; i < _SE_ALL_; i++) {
		DeleteGraph(se[i]);
	}
}

/*
	@brief	SceneGameOverの処理
*/
void SceneGameOver::Process() {
	// 画面処理
	int step = _fade->GetStep();	// 現在のステップを取得
	switch (step) {
	case 0:
		_fade->ColorFadeIn(60);	// 60fでFI
		PlaySoundMem(bgm_gameover, DX_PLAYTYPE_LOOP);	// bgmを再生
		step++;	// 次のステップへ
		break;
	case 1:
		if (_fade->IsColorFade() == 0) {	// FIは終了したか？
			// フェードイン終了
			step++;	// 次のステップへ
		}
		break;
	case 2:
		// メイン処理
		
		// 選択肢を一つ下げる
		if (gTrg & PAD_INPUT_DOWN) {	// 下に入力した？
			nowSelect = (nowSelect + 1) % option.menu_Num;	// 下の選択肢を選ぶ
			PlaySoundMem(se[SE_SELECT_], DX_PLAYTYPE_BACK);	// 選択音
		}
		// 選択肢を一つ上げる
		if (gTrg & PAD_INPUT_UP) {	// 上に入力した？
			nowSelect = (nowSelect + (option.menu_Num - 1)) % option.menu_Num;	// 上の選択肢を選ぶ
			PlaySoundMem(se[SE_SELECT_], DX_PLAYTYPE_BACK);	// 選択音
		}
		switch (nowSelect) {	// 何を選択しているか
		case OPTION_YES:	// Yesを選択している場合
			if (gTrg & PAD_INPUT_4) {	// Aキー
				PlaySoundMem(se[SE_DETERMINATION_], DX_PLAYTYPE_BACK);	// 選択音
				// フラグオン
				retry = TRUE;
				// フェードアウト開始
				_fade->ColorFadeOut(0, 0, 0, 60);
				step++;	// 次のステップへ
			}
			break;
		case OPTION_NO:	// Noを選択している場合
			if (gTrg & PAD_INPUT_4) {	// Aキー
				PlaySoundMem(se[SE_DETERMINATION_], DX_PLAYTYPE_BACK);	// 選択音
				// フラグオン
				end = TRUE;
				// フェードアウト開始
				_fade->ColorFadeOut(0, 0, 0, 60);
				step++;	// 次のステップへ
			}
			break;
		}
		break;
	case 3:
		if (_fade->IsColorFade() == 0) {	// FOは終了したか？
			// step初期化
			step = 0;
			// フェードアウト終了
			if (retry == TRUE) {
				SceneBase* scene = new SceneAction(0);
				ChangeScene(scene);	// ActionSceneに切り替える
			}
			if (end == TRUE) {
				SceneBase* scene = new SceneGameTitle();
				ChangeScene(scene);	// TitleSceneに切り替える
			}
		}
		break;
	}
	_fade->SetStep(step);	// 現在のステップを保存

}

/*
	@brief	SceneGameOverの描画
*/
void SceneGameOver::Draw() {
	// 背景
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