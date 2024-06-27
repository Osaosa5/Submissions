#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"

class SceneGameTitle : public SceneBase {
public:
	SceneGameTitle();			// コンストラクタ
	virtual ~SceneGameTitle();	// デストラクタ

	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
	// 画像ハンドル
	int		_cgSchool;	// 学校ロゴ
	int		_cgLogo;	// チームロゴ
	int		_cgBg;		// 背景画像
	int		_cgStart;	// スタートボタン
	// 音楽ハンドル
	int		bgm_title;	// BGM (タイトル画面)

	// フラグ
	bool	school;		// 学校ロゴフラグ
	bool	logo;		// チームロゴフラグ
	bool	op;			// オープニングフラグ
	bool	start;		// スタートフラグ

	// time関係
#define	LATENCY		2000			// 待機時間

	int		instrumentationStart;	// 計測開始
	int		latency;				// 待機時間
};

