#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "scenebase.h"
#include "Fade.h"
#include "Effect.h"


// 他のcppでも使いたいグローバル変数は、ヘッダファイルでextern宣言する

// ゲーム情報
extern int gKey;			// キー入力の情報
extern int gTrg;			// トリガ入力の情報
extern int gRel;			// リリース入力の情報

void ChangeScene(SceneBase* scene);	// Sceneを変更する

void GameMain();	// gamemain.cpp に実体を記述

extern Fade* _fade;

