#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenebase.h"
#include "SceneGameTitle.h"
#include "SceneGameOver.h"
#include "Effect.h"

//
// 定数・構造体定義
//


//
// グローバル変数宣言
//

// ゲーム情報
int gKey;			// キー入力の情報
int gTrg;			// トリガ入力の情報
int gRel;			// リリース入力の情報


// Sceneポインタ
SceneBase* gScene;					// ポインタなのでnewするまで実体は無い

// Sceneの切り替え用
SceneBase* gNewScene;				// NULL以外がセットされていたら、シーンを切り替える

Fade* _fade;


// Sceneを変更する
void ChangeScene(SceneBase* scene) 
{
	gNewScene = scene;		// 次のシーンをセット
}


// アプリの初期化
// 起動時に1回だけ実行される
void AppInit() 
{
	gNewScene = NULL;		// 次のシーンを初期化する
	gScene = new SceneGameTitle();		// Sceneの実体を作る
	_fade = new Fade();
}


// アプリの解放
// 終了時に1回だけ実行される
void AppRelease() 
{
	delete gScene;				// Sceneを削除する
	delete _fade;
}



//
// フレーム処理。1フレームに1回ずつ実行される
//

// フレーム処理：入力
void FrameInput() 
{
	// キー入力、トリガ入力、リリース入力を得る
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// キー入力を取得
	gTrg = (gKey ^ keyold) & gKey;
	gRel = (gKey ^ keyold) & ~gKey;

	// Sceneの入力呼び出し
	gScene->Input();

}

// フレーム処理：計算
void FrameProcess() 
{
	// Sceneの計算呼び出し
	gScene->Process();

	_fade->MainProcess();
}

// フレーム処理：描画
void FrameDraw() 
{
	ClearDrawScreen();						// 画面を初期化する

	// Sceneの描画呼び出し
	gScene->Draw();

	_fade->Draw();

	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}


void GameMain()
{
	AppInit();	// 初期化

	// 1フレームループを組む ----------------------------------------------------------
	while(ProcessMessage() == 0)		// プログラムが終了するまでループ
	{
		// シーンを切り替えるか？
		if(gNewScene != NULL) 
		{
			delete gScene;		// 今のシーンを削除する
			gScene = gNewScene;	// 受け取ったシーンをポインタセット
			gNewScene = NULL;	// 次のシーンを初期化する
		}

		FrameInput();	// 入力
		FrameProcess();	// 計算
		FrameDraw();	// 描画
	}

	AppRelease();	// 解放
}
