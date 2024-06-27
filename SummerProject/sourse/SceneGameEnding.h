#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"

class SceneGameEnding : public SceneBase {
public:
	SceneGameEnding();			// コンストラクタ
	virtual ~SceneGameEnding();	// デストラクタ

	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
	// 画像ハンドル
	int		_cgBg;		// 背景画像
	// 音楽ハンドル
	int		bgm_ending;	// BGM (エンディング画面)

	// フラグ
	bool	ed;		// edフラグ
	bool	end;	// endフラグ
};