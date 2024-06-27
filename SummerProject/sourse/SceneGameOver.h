#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"

class SceneGameOver : public SceneBase {
public:
	SceneGameOver();			// コンストラクタ
	virtual ~SceneGameOver();	// デストラクタ

	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
	// 項目
#define OPTION_YES		0
#define OPTION_NO		1
#define _OPTION_ALL_	2
	// 色
#define COLLOR_BLUE		0
#define COLLOR_YELLOW	1
#define _COLLOR_ALL_	2
	// 座標
#define YES_X_			300
#define YES_Y_			400
#define NO_X_			300
#define NO_Y_			700
	// 音
#define SE_SELECT_			0
#define	SE_DETERMINATION_	1
#define _SE_ALL_			2

	// 画像ハンドル
	int		_cgBg;			// 背景画像
	int		_cgContinue;
	int		_cgYes[_COLLOR_ALL_];
	int		_cgNo[_COLLOR_ALL_];
	// bgm/seハンドル
	int		bgm_gameover;	// BGM (ゲームオーバー画面)
	int		se[_SE_ALL_];

	struct OPTION {
		int menu_Yes, menu_No, menu_Num;
	}option;

	int nowSelect;		// 選択中
	bool retry;			// リトライフラグ
	bool end;			// エンドフラグ
};
