#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"
#include "mapdata.h"
#include "uilife.h"
#include "mymath.h"
#include "framedata.h"
#include "motiondata.h"
#include "fps.h"
#include "uispeedometer.h"
#include "Shadow.h"
#include "Effect.h"
#include "uiMileStone.h"

/////////////////////////////////////////////////////////////////////////////////////
// アニメーションパターン用定義
// 配列の番号は間を空けて余裕を持って設定しています
// プレイヤー
#define PLAYER_WALK					0					// 0	～	24枚
#define PLAYER_DAMAGE				30					// 30	～	24枚
#define PLAYER_JUMP_UP				60					// 60	～	12枚
#define PLAYER_JUMP_DOWN			90					// 90	～	12枚
#define PLAYER_MOVING_LEFT			120					// 120	～	 8枚
#define PLAYER_MOVING_RIGHT			150					// 150	～	 8枚
#define _PLAYER_ALL_				200					// 全パターン枚数

// アイテム
#define ITEM_BATTERY				0					// 0	～ 24枚
#define ITEM_HEART					30					// 30	～ 24枚
#define ITEM_JET					60					// 60	～ 24枚
#define _ITEM_ALL_					100					// 全パターン枚数

//エフェクト
#define EFFECT_BARRIER				0					// 0	～	30枚		// バリア（無敵中）
#define EFFECT_HEALING				40					// 40	～	30枚		// 回復
#define EFFECT_BLUE_FIRESPARK		80					// 80	～	30枚		// ジェットの火花(加速)
#define EFFECT_FRUSTRATION			120					// 120	～	 5枚		// フラストレーション（ダメージ受けた時）
#define _EFFECT_ALL_				200					// 全パターン枚数


// 効果音用定義
// 配列の番号は0～
#define SE_WALK						0					// 走行
#define	SE_DAMAGE					1					// ダメージ(コンテナに追突時)
#define SE_JUMP						2					// ジャンプ
#define SE_LANDING					3					// 着地
#define SE_GOAL						4					// ゴール
#define SE_CHOOSE					5					// ボタン選択
#define SE_DECISION					6					// ボタン決定
#define SE_CANCEL					7					// 選択キャンセル
#define SE_HEART					8					// ハート
#define SE_JET						9					// ジェット機
#define SE_RED_JET					10					// 赤ジェット機
#define SE_BATTERY					11					// 充電池
#define SE_CNT						12					// 3カウント
#define SE_START					13					// スタート
#define SE_SELECT					14					// 選択
#define SE_DETERMINATION			15					// 決定
#define	_SE_ALL_					20					// 全SE数


// BGM用定義
// 配列の番号は0～
#define BGM_TITLE					0					// タイトル画面
#define BGM_GAMEOVER				1					// ゲームオーバー画面
#define BGM_ENDING					2					// エンディング画面
#define BGM_STAGE_ONE				3					// ゲームプレイ画面(STAGE1)
#define BGM_SCENARIO				6					// シナリオ画面
#define BGM_RESULT					7					// リザルト画面
#define _BGM_ALL_					10					// 全BGM数

// 数フォント用定義
#define NUMBER_ZERO					0
#define NUMBER_ONE					1
#define NUMBER_TWO					2
#define NUMBER_THREE				3
#define NUMBER_FOUR					4
#define NUMBER_FIVE					5
#define NUMBER_SIX					6
#define NUMBER_SEVEN				7
#define NUMBER_EIGHT				8
#define NUMBER_NINE					9
#define NUMBER_KOLON				10
#define _NUMBER_ALL_				11

//////////////////////////////////////////////////////////////////////////////////////

class SceneAction : public SceneBase {
public:
	SceneAction(int stageNumber);					// コンストラクタ
	virtual ~SceneAction();							// デストラクタ

	void	Input() override;							// 入力
	void	Process() override;							// 計算
	void	Draw() override;							// 描画

protected:
	///////////////////////////////////////////////////////////////////////////////////////////////
	// ポーズ関係の関数
	///////////////////////////////////////////////////////////////////////////////////////////////
	void InitPouse();
	void ProcessPouse();
	void DrawPouse();
	///////////////////////////////////////////////////////////////////////////////////////////////
	// 時間関係の関数
	///////////////////////////////////////////////////////////////////////////////////////////////
	void InitStartPreprocessing();						// ゲームスタート前処理の初期化
	void ProcessBeforeStart();							// ゲームスタート前処理
	void DrawStartPreprocessing();						// ゲームスタート前処理の描画
	void InitLimitTime();
	void ProcessLimitTime();
	void DrawLimitTime();
	///////////////////////////////////////////////////////////////////////////////////////////////
	// 画面関係の関数
	///////////////////////////////////////////////////////////////////////////////////////////////
	void InitScreen();									// 画面関係の初期化
	void ProcessScreen();								// 画面処理
	void DrawScreen();									// 画面描画
	///////////////////////////////////////////////////////////////////////////////////////////////
	// モーション関係の関数
	///////////////////////////////////////////////////////////////////////////////////////////////
	void CharaChangeMotion(int charaIndex, int motion);	// モーション切り替えの処理
	int  SearchFrame(int frameId);						// フレームID検索
	void ProcessCharacter();
	///////////////////////////////////////////////////////////////////////////////////////////////
	//player//
	///////////////////////////////////////////////////////////////////////////////////////////////
	// player関係の関数	
	void InitPlayer();									// playerの初期化
	void ProcessPlayer();								// playerの動き
	void DrawPlayer();									// playerの描画
	void DamagePlayer();								// playerのダメージ処理
	int  AddPlayerLane(int y);							// playerのレーン追加処理
	///////////////////////////////////////////////////////////////////////////////////////////////
	// オブジェクト//
	///////////////////////////////////////////////////////////////////////////////////////////////
	int	 AddObjectLane(int y);							// オブジェクトのレーン追加処理
	// アイテム関係の関数									  
	void InitItem();									// アイテムの初期化
	void ProcessItem();									// アイテムの計算処理
	void DrawItem();									// アイテムの描画
	void ProcessItemFlag();								// アイテムのフラグ処理
	//////////////////////////////////////////////////////////////////////////////////////////////
	// 当たり判定関係の関数
	//////////////////////////////////////////////////////////////////////////////////////////////
	void InitRect();									// playerの当たり判定初期化
	void HitCheckPlayerWall(int old_x, int old_y);		// playerと壁の当たり判定処理
	void HitCheckPlayerObstacle();						// playerと障害物の当たり判定処理
	void HitCheckPlayerItem();							// playerとアイテムの当たり判定処理

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// 画面関係の変数
	//////////////////////////////////////////////////////////////////////////////////////////////
	// チップのサイズ
#define	CHIP_W		 (120)								// マップチップの横サイズ
#define	CHIP_H		 (120)								// マップチップの縦サイズ

	// マップスクロール用
	int gScrollX, gScrollY;

	// 画像データ	
	int _cgOperationDescription;						// 操作説明
	int _cgStart;										// ゲームスタート
	int _cgNumber[_NUMBER_ALL_];						// 数字
	int _cgCntNumber[3];								// 3カウント
	int _cgLimitTimeBox;								// 制限時間のボックス
	int _cgBg;											// 背景
	int _cgChip[4];										// チップ画像（配列）
	int _cgPlayer[_PLAYER_ALL_];						// プレイヤー
	int _cgItem[_ITEM_ALL_];							// アイテム
	int _cgShadow;										// 影
	int _cgFade;											// 暗い画像

	// ゲーム進行の停止をするなら1
	int	_gamePause = 0;
	// ポーズ関係
	// マクロ
#define OPTION_YES		0
#define OPTION_NO		1
#define _OPTION_ALL_	2

#define COLLOR_BLUE		0
#define COLLOR_YELLOW	1
#define _COLLOR_ALL_	2

#define YES_X			300
#define YES_Y			600
#define NO_X			1200
#define NO_Y			600

	// 画像ハンドル
	int		_cgRetry;
	int		_cgYes[_COLLOR_ALL_];
	int		_cgNo[_COLLOR_ALL_];

	// 項目
	int menu_Yes;										// yes
	int menu_No;										// no
	int menu_Num;										// 総数

	// フラグ・変数
	int nowSelect;										// 選択中
	bool pause;											// ポーズフラグ

	// ゲームスタート
	bool gameStart;										// ゲームスタートフラグ
	bool operationDescription;							// 説明書フラグ
	bool startSignal;									// スタート合図
	int	 startCnt;										// スタート前3カウント

	// 制限時間
	int gameLimitTime;									// 
	int gameStartTime;									// 
	int gameElapsedTime;								// 
	int drawLimitTime;									// 
	int oldTime;										// 	ポーズ画面を開いた瞬間の時間を記録する

	// 特殊演出
#define	STAGING_NONE		0							// なし
#define	STAGING_START		1							// start
#define	STAGING_GAMEOVER	2							// gameover
#define STAGING_GAMECLEAR	3							// gameclear
#define STAGING_FINISH		4							// finish

	int	_stagingProc = STAGING_NONE;

	//////////////////////////////////////////////////////////////////////////////////////////////
	// 音関係
	//////////////////////////////////////////////////////////////////////////////////////////////
	int _se[_SE_ALL_];									// 効果音セット
	int _bgm[_BGM_ALL_];								// BGMセット
	int _end;											// ゲームクリア前の演出

	//////////////////////////////////////////////////////////////////////////////////////////////
	// ゲーム情報
	//////////////////////////////////////////////////////////////////////////////////////////////
	int gKey;											// キー入力の情報
	int gTrg;											// トリガ入力の情報
	int gRel;											// リリース入力の情報

	//////////////////////////////////////////////////////////////////////////////////////////////
	// キャラクタ情報
	//////////////////////////////////////////////////////////////////////////////////////////////
	// キャラタイプ
#define	CHARA_TYPE_NONE		0							// キャラ無し（use=0的に使用）
#define	CHARA_TYPE_PLAYER	1							// プレイヤー

#define	CHARA_MAX			10							// キャラ数

	// プレイヤー情報 //
#define DISTANCE_LIMIT		120 * 1008					// ゴール座標


	struct PLAYER {										// player構造体	
		// player基本情報
		int		type;									// キャラタイプ
		int		x, y;									// 座標（チップ単位）
		int		w, h;									// playerの大きさ
		int		hit_x, hit_w, hit_y, hit_h;				// 当たり判定
		int		speed_x;								// x軸の移動スピード
		int		speed_y;								// y軸の移動スピード
		int		lane;									// レーン
		// ジャンプ処理関係
		int		high;									// 上昇量
		int		gravity;								// 重力加速度
		int		stand;									// ジャンプフラグ
		// 当たり判定フラグ
		bool	hit;									// 障害物ダメージヒットフラグ
		bool	obstacleHit;							// 障害物衝突フラグ
		int		obstacle;								// 障害物と衝突してからの経過時間
		int		obstacleLimit;							// 硬直時間
		// モーション関係
		int		motId;									// モーションID。 MOTION_xxxx_xxxxx
		int		motcnt;									// モーションカウンタ。0～
		int		animcnt;								// アニメーションカウンタ。0～
	}pl;

	int			invincibleTime;							// 無敵時間

	bool		playerMoveFlag;							// レーン移動フラグ
	bool		playerSlopeFlag;						// 左右の傾きフラグ

	int			playerCnt;								// playr用イージングカウント
	int			start;									// 移動開始位置
	int			end;									// 移動終着位置
	int			frames;									// 移動にかかるフレーム数

	struct PLAYER _gChara[CHARA_MAX] = 
{
	{	// プレイヤー
		// type,			x,	y,			 motId,						motcnt,			animcnt
		CHARA_TYPE_PLAYER,	240,240,   		 MOTION_WALK,				0,				0,
	},
};
	int timeObstacle;									// 障害物に当たった瞬間の時間


	// アイテムの情報 //	
#define ITEM_MAX 77										// アイテムの数

	// アイテム
	struct ITEM {
		// 基本情報
		int		use;									// この配列を使用するか（0:使用しない, 1:使用する）
		int		type;									// タイプ
		int		x, y;									// 座標
		int		w, h;									// 大きさ
		int		lane;									// レーン
		int		cgItem;									// 画像ハンドル
		// 高さの処理
		int		high;									// 上昇値
		int		stand;									// 着地フラグ
		// モーション関係
		int		motId;									// モーションID
		int		motcnt;									// モーションカウンタ
		int		animcnt;								// アニメーションカウンタ
	};

	struct ITEM _gItem[ITEM_MAX] = 
{
	{	// アイテム
		// type,	x,		y,			motId,				motcnt,		animcnt
		BATTERY,	120,120,    MOTION_BATTERY,				0,			0,
	},
	{
		// type,	x,		y,			motId,				motcnt,		animcnt
		HEART,		120,120,		MOTION_HEART,			0,			0,
	},
	{
		// type,	x,		y,			motId,				motcnt,		animcnt
		JET,		120,120,		MOTION_JET,				0,			0,
	},
};

	bool		shouldGotBattery;						// バッテリーをゲットしたか
	bool		shouldGotHeart;							// ハートをゲットしたか
	bool		shouldGotJet;							// ジェットをゲットしたか
						
	int			batteryEffectStartTime;					// バッテリー効果開始時間

#define MAX_SPEEDUP_COUNT			60					// スピードアップ表記の表示時間 

	int			drawCount;
	int			maxDrawCount;


	//////////////////////////////////////////////////////////////////////////////////////////////
	// クラス
	//////////////////////////////////////////////////////////////////////////////////////////////

	MapData*		_mapData;							// mapクラス
	UILife			_UIlife;							// ライフUIクラス
	UISpeedoMeter*  _UIspeedoMeter;						// speedometerのクラス
	Shadow*			_shadow;							// 影クラス
	uiMileStone*	_UImileStone;						// マイルストーン
	fps*			_fps;								// fpsクラス

	Effect*			ef_frustration;						// エフェクトクラス(フラストレーション)
	Effect*			ef_barrier; 						// エフェクトクラス(バリア)
	Effect*			ef_healing;;						// エフェクトクラス(回復)
	Effect*			ef_firespark;						// エフェクトクラス(青い火花)
	
	int				_life;								// playerのHP
	int				_score;								// playerのスコア

	int				drawingFlag;						// スピードアップの文字描画フラグ

	int				gameFlag_Over;
	int				gameFlag_TimeOver;
	int				gameFlag_Clear;

};
