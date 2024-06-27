#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "ItemData.h"

// キャラクタフレーム構造体
// 1枚のフレームに関する設定
struct CHARA_FRAME 
{
	int		frameId;	// フレームID。固有の番号を振る
	int		cgId;		// 使用画像番号 cgChara[]
	int		cx, cy;		// 画像の基点。
	int		w, h;		// 画像サイズ
};

struct ITEM_FRAME 
{
	int		frameId;	// フレームID。固有の番号を振る
	int		cgId;		// 使用画像番号 cgChara[]
	int		cx, cy;		// 画像の基点。
	int		w, h;		// 画像サイズ
};

struct EFFECT_FRAME
{
	int		frameId;	// フレームID。固有の番号を振る
	int		cgId;		// 使用画像番号 cgChara[]
	int		cx, cy;		// 画像の基点。
	int		w, h;		// 画像サイズ
};

extern struct CHARA_FRAME tblFrame_chara[];

extern struct ITEM_FRAME tblFrame_item[];

extern struct EFFECT_FRAME tblFrame_effect[];


