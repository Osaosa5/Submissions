#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"
#include "SceneAction.h"
#include "save.h"

class SceneGameResult : public SceneBase {
public:
	SceneGameResult(int resultTime);			// コンストラクタ
	virtual ~SceneGameResult();	// デストラクタ

	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
	// 画像ハンドル
	int _cgBg;			// 背景画像
	int _cgResult[4];	// ランク画像
	int _cgRanking;		// ランキング枠
	int _cgFade;		// 薄く暗く
	int	_cgRetry;
	int	_cgYes[_COLLOR_ALL_];
	int	_cgNo[_COLLOR_ALL_];
	// 音関連
	int _seResult[2];
	// 項目
	int menu_Yes;		// yes
	int menu_No;		// no
	int menu_Num;		// 総数
	// フラグ・変数
	int nowSelect;		// 選択中
	bool _isContinue;	// 選択肢
	bool _isRetry;		// リトライフラグ
	bool _isEnd;		// エンドフラグ
	// 音関連
	int _bgmResult;		// BGM (リザルト画面)
	// 処理用    
	int _resultTime;	// ランク判定用
	int _rank;			// ランク
	// フラグ
	bool _isRanking;
	// クラス
	save* _save;
};

