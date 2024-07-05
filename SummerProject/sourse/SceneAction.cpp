// 担当：尾﨑

/*
	ゲームのメイン処理
*/

#include "DxLib.h"
#include "winmain.h"
#include "GameMain.h"
#include "scenegameover.h"
#include "sceneaction.h"
#include "scenegameresult.h"
#include "Effect.h"

/*
	@brief	SceneActionのコンストラクタ
	@param	stageNumber:ステージ番号
*/
SceneAction::SceneAction(int stageNumber) {

	// キャラ画像配列の初期化
	for(int i = 0; i < _PLAYER_ALL_; i++) {
		_cgPlayer[i] = -1;
	}
	// 画像の読み込み
	_cgBg					= LoadGraph("res/cgBg/cgBg.png");					// 背景
	_cgOperationDescription = LoadGraph("res/cgBg/sousahouhou.png");			// 操作説明画像
	_cgStart				= LoadGraph("res/UI/go-04.png");					// start
	_cgLimitTimeBox			= LoadGraph("res/UI/timeframe-02.png");				// 制限時間の後ろのボックス(枠組み)
	_cgFade					= LoadGraph("res/cgBg/fade.png");					// 暗い画像
	_cgRetry				= LoadGraph("res/UI/retry.png");					// retry?
	// Yes or No
	_cgYes[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/No4.png");

	// プレイヤー画像読み込み
	LoadDivGraph("res/motion/bike_run_nogatoling_00000_sheet.png", 24, 4, 6, 240, 240, &_cgPlayer[PLAYER_WALK]);
	LoadDivGraph("res/motion/bike_crash_new_00000_sheet.png", 24, 4, 6, 240, 240, &_cgPlayer[PLAYER_DAMAGE]);
	LoadDivGraph("res/motion/bike_jump_new_00000_sheet.png", 12, 4, 3, 240, 240, &_cgPlayer[PLAYER_JUMP_UP]);
	LoadDivGraph("res/motion/bike_jump_new_00012_sheet.png", 12, 4, 3, 240, 240, &_cgPlayer[PLAYER_JUMP_DOWN]);
	LoadDivGraph("res/motion/player_moving_left_left.png", 8, 4, 2, 240, 240, &_cgPlayer[PLAYER_MOVING_LEFT]);
	LoadDivGraph("res/motion/player_moving_right_right.png", 8, 4, 2, 240, 240, &_cgPlayer[PLAYER_MOVING_RIGHT]);
	// アイテム画像読み込み
	LoadDivGraph("res/UI/item_battery.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_BATTERY]);
	LoadDivGraph("res/UI/item_heart.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_HEART]);
	LoadDivGraph("res/UI/stageitem1_jet.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_JET]);

	// 数字画像読み込み
	LoadDivGraph("res/UI/number_ui_sheet.png", 11, 11, 1, 48, 72, &_cgNumber[0]);
	LoadDivGraph("res/UI/3cnt_sheet.png", 3, 3, 1, 300, 300, &_cgCntNumber[0]);


	// 効果音の読み込み
	for(int i = 0; i < _SE_ALL_; i++) {
		_se[i] = -1;
	}
	_se[SE_WALK]			= LoadSoundMem("res/sound/bike.mp3");						// エンジン音
	_se[SE_DAMAGE]			= LoadSoundMem("res/sound/damage.wav");						// 衝突音
	_se[SE_JUMP]			= LoadSoundMem("res/sound/SE_jetjump.wav");					// ジャンプ音
	_se[SE_LANDING]			= LoadSoundMem("res/sound/SE_landing.wav");					// 着地
	_se[SE_GOAL]			= LoadSoundMem("res/sound/choice.mp3");						// ゴール音
	_se[SE_CHOOSE]			= LoadSoundMem("res/sound/choice.mp3");						// ボタン選択音	
	_se[SE_DECISION]		= LoadSoundMem("res/sound/waterslash.mp3");					// ボタン決定音
	_se[SE_CANCEL]			= LoadSoundMem("res/sound/destruction.mp3");				// 選択キャンセル音
	_se[SE_JET]				= LoadSoundMem("res/sound/kasoku.mp3");						// ジェット獲得音
	_se[SE_RED_JET]			= LoadSoundMem("res/sound/kira.mp3");						// ジェット（赤）獲得音
	_se[SE_HEART]			= LoadSoundMem("res/sound/heal.mp3");						// ハート獲得音
	_se[SE_BATTERY]			= LoadSoundMem("res/sound/barrier.mp3");					// バッテリー獲得音
	_se[SE_CNT]				= LoadSoundMem("res/sound/cnt.mp3");						// カウントダウン音
	_se[SE_START]			= LoadSoundMem("res/sound/start.mp3");						// ゲームスタート音
	_se[SE_SELECT]			= LoadSoundMem("res/sound/select.mp3");						// 選択音
	_se[SE_DETERMINATION]	= LoadSoundMem("res/sound/determination.mp3");				// 決定音

	_bgm[BGM_STAGE_ONE]		= LoadSoundMem("res/sound/CrazyHill.mp3");					// ステージ１のBGM

	_mapData				= new MapData(stageNumber);		
															
	_fps					= new fps();					
															
	_UIspeedoMeter			= new UISpeedoMeter();			
															
	_shadow					= new Shadow();					
															
	_UImileStone			= new uiMileStone();			
															
	ef_barrier				= new Effect();					
	ef_healing				= new Effect();					
	ef_firespark			= new Effect();					
	ef_frustration			= new Effect();					

	// ポーズ画面の初期化
	InitPouse();

	// 画面処理の初期化
	InitScreen();

	// 制限時間処理の初期化
	InitLimitTime();

	// アイテム処理の初期化
	InitItem();

	// プレイヤー処理の初期化
	InitPlayer();

	// ゲーム開始前の処理の初期化
	InitStartPreprocessing();

	// 体力の初期化
	_life = 4;
	_UIlife.Set(_life);

	// ゲームスタートフラグ
	drawingFlag	= 1;

	// ゲームフラグ
	// ゲームオーバーフラグ　体力が0になった時
	gameFlag_Over		= 0;
	// ゲームオーバーフラグ　タイムオーバー
	gameFlag_TimeOver	= 0;
	// ゲームクリアフラグ
	gameFlag_Clear		= 0;
	// ポーズ画面フラグ
	pause				= 0;
}

/*
	@brief	SceneActionのデストラクタ
*/
SceneAction::~SceneAction() {
	// グラフィックをメモリ上から削除する
	// 背景
	DeleteGraph(_cgBg);

	// アイテム
	for(int i = 0; i < _ITEM_ALL_; i++) {
		if(_cgItem[i] != -1) {
			DeleteGraph(_cgItem[i]);
		}
	}

	// プレイヤー
	for(int i = 0; i < _PLAYER_ALL_; i++) {
		if(_cgPlayer[i] != -1) {
			DeleteGraph(_cgPlayer[i]);
		}
	}

	// 数字
	for(int i = 0; i < _NUMBER_ALL_; i++) {
		if(_cgNumber[i] != -1) {
			DeleteGraph(_cgNumber[i]);
		}
	}

	// メモリに読みこんだ音データを削除する
	// 効果音
	for(int i = 0; i < _SE_ALL_; i++) {
		if(_se[i] != -1) {
			DeleteSoundMem(_se[i]);
		}
	}

	// BGM
	for(int i = 0; i < _BGM_ALL_; i++) {
		if(_bgm[i] != -1) {
			DeleteSoundMem(_bgm[i]);
		}
	}

	// UI関係
	_mapData->~MapData();
	_UIlife.~UILife();
	_UIspeedoMeter->~UISpeedoMeter();
	_UImileStone->~uiMileStone();

	// エフェクト関係
	ef_barrier->~Effect();
	ef_healing->~Effect();
	ef_firespark->~Effect();
	ef_frustration->~Effect();
}

/*
	@brief	SceneActionの入力情報の処理
*/
void SceneAction::Input() {
	// 何もしない
	// キーの入力、トリガ入力を得る
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// キー入力を取得
	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	gTrg = (gKey ^ keyold) & gKey;
	// キーのリリース情報生成（離した瞬間しか反応しないキー情報）
	gRel = (gKey ^ keyold) & ~gKey;
}

/*
	@brief	SceneActionの処理
*/
void SceneAction::Process() {
	// ポーズのフラグが立っていないとき
	if (pause == 0) {
		// スタート前の処理
		ProcessBeforeStart();
		// 制限時間の処理
		ProcessLimitTime();
		// スピードメーターの処理
		_UIspeedoMeter->Process(pl.speed_x, 10, 35, 5);
		// マイルストーンの処理
		_UImileStone->Process(pl.x, 60, DISTANCE_LIMIT);
		// ゲームスタートフラグが立っているとき
		if (gameStart == 1) {
			_UIlife.Process();  // ハートUIの処理

			ProcessCharacter();

			ProcessItem();		// アイテムの処理

			ProcessPlayer();	// playerの処理

			ProcessScreen();	// スクリーンの処理
		}
		// ポーズの処理
		ProcessPouse();
		// フレームレートの処理
		_fps->fps_wait();

		{
			// フェード処理の段階の取得
			int step = _fade->GetStep();
			switch (step) {
			case 0: // フェードイン
				_fade->ColorFadeIn(10);
				step++;
				break;
			case 1:	// フェードインが終了しているか
				if (_fade->IsColorFade() == 0) {
					// フェードイン終了
					step++;
				}
				break;
			case 2:
				// ゲームオーバー
				if (_UIlife.Get() == 0) {
					gameFlag_Over = 1;
				}
				if (drawLimitTime < 0) {
					gameFlag_TimeOver = 1;
				}

				// ゲームクリア
				if (_UIlife.Get() != 0 && pl.x >= DISTANCE_LIMIT) {
					// クリアSE
					PlaySoundMem(_se[SE_GOAL], DX_PLAYTYPE_BACK);
					if (CheckSoundMem(_bgm[BGM_STAGE_ONE]) == 1) {
						StopSoundMem(_bgm[BGM_STAGE_ONE]);
					}
					// ゴールムービー
					if (gameFlag_Clear == 0) {
						PlayMovie("res/staging/clear.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
						gameFlag_Clear = 1;
						drawingFlag = 0;
						WaitTimer(1000);
					}
					// ゲームフラグoff
					gameStart = 0;
				}
				// 通常処理
				// タイムオーバーに限りC.O
				if (gameFlag_TimeOver == 1) {
					SceneBase* scene = new SceneGameOver();
					ChangeScene(scene);
				}
				if (gameFlag_Over == 1) {
					// フェードアウト開始
					_fade->ColorFadeOut(0, 0, 0, 60);
					step++;
				}
				if (gameFlag_Clear == 1) {
					step++;
				}
				break;
			case 3:
				if (_fade->IsColorFade() != 1) {
					// step初期化
					step = 0;
					// フェードアウト終了
					// ゲームオーバー
					if (gameFlag_Over == 1) {
						// ゲームオーバー画面へ
						SceneBase* scene = new SceneGameOver();
						ChangeScene(scene);
					}
					// ゲームクリア
					if (gameFlag_Clear == 1) {
						// ゲームクリア画面へ
						SceneBase* scene = new SceneGameResult(drawLimitTime);
						ChangeScene(scene);
					}
				}
				break;
			}
			// 現在のフェード処理の段階のセット
			_fade->SetStep(step);
		}
	}
}

/*
	@brief	SceneActionの描画
*/
void SceneAction::Draw() {
	// 描画フラグが立っているとき
	if (drawingFlag == 1) {
		// 背景の描画
		DrawScreen();
		// 操作説明画面が表示されていない時
		if (operationDescription == 0) {
			// マップ描画
			_mapData->Draw(gScrollX, 0);
			// 補助線描画
			for (int i = 4; i < 9; i++) {
				int y, w;
				y = i * CHIP_H;
				w = SCREEN_W;
				DrawLine(0, y, w, y, GetColor(255, 255, 255));
			}
			// マイルストーン描画
			_UImileStone->Draw();
			// 体力の描画
			_UIlife.Draw();
			// プレイヤーの影の描画
			_shadow->DrawPlayer(pl.x, pl.y, gScrollX);
			// スピードメーターの描画
			_UIspeedoMeter->Draw();
			// アイテム描画
			DrawItem();
			// プレイヤー描画
			DrawPlayer();

			int xx, yy;	// スクロールを想定したキャラx,yを入れる
			xx = pl.x - gScrollX;
			yy = pl.y - gScrollY + pl.high;

			// エフェクト描画（barrier）
			ef_barrier->SetXY(xx + 50, yy + 45);
			ef_barrier->Draw();

			// エフェクト描画（healing）
			ef_healing->SetXY(xx - 5, yy + 90);
			ef_healing->Draw();

			// エフェクト描画（blue_firespark）
			ef_firespark->SetXY(xx - 160, yy + 170);
			ef_firespark->Draw();
			// 制限時間の描画
			DrawLimitTime();
		}
		// ゲーム開始前の描画
		DrawStartPreprocessing();
		// ポーズ画面の描画
		DrawPouse();
	}
}

