#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない

// キャラクタ動作テーブル
struct CHARA_MOTION_ITEM 
{
	int		frameId;	// 表示したいフレームID
	int		frameCnt;	// 何フレーム表示するか
	int		mx, my;		// 表示中、1フレームあたり移動する値
};

// １モーションあたり、モーションアイテムをいくつまで書けるか
#define	CHARA_MOTION_ITEM_MAX			64
#define ITEM_MOTION_ITEM_MAX			64
#define EFFECT_MOTION_ITEM_MAX			64

// モーションアイテム用コマンド。frameId に指定して使う。frameIdと重複してはいけない
// コマンドはフレーム終了時に処理されるため、最初のフレームには指定できない仕様
#define	CHARA_MOTION_CMD_LOOP			1	// モーションをループする(frameCntにモーションindex指定)
#define	CHARA_MOTION_CMD_MOTION			2	// 別のモーションへ(frameCntにモーション番号指定)
#define CHARA_MOTION_CMD_MAINTENANCE	3	// モーションを維持する
#define	CHARA_MOTION_CMD_PLAYSE			4	// 効果音再生(frameCntにSE_xxxx)
#define CHARA_MOTION_CMD_PLAYSE_STOP	5	// 効果音停止
#define	CHARA_CMD_OBSTACLE_HIT			6	// コンテナフラグをオフ

struct CHARA_MOTION 
{
	CHARA_MOTION_ITEM	item[CHARA_MOTION_ITEM_MAX];
};

// モーション番号。0番からの通し番号であること
// プレイヤー
#define	MOTION_WALK						0
#define	MOTION_DAMAGE					1
#define	MOTION_JUMP_UP 					2
#define MOTION_JUMP_DOWN				3
#define MOTION_MOVING_LEFT				4
#define MOTION_MOVING_RIGHT				5
// アイテム
#define MOTION_BATTERY					10
#define MOTION_HEART					11
#define MOTION_JET						12

extern struct CHARA_MOTION tblMotion_chara[];
