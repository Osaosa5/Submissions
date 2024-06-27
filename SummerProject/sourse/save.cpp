// 担当：尾﨑

/*
	セーブデータの読み込み、書き込みを行う
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "DxLib.h"
#include "save.h"

/*
	@brief	saveのコンストラクタ
	@param	_FileName:ファイル名
	@param	dataElementsCount:配列の要素数
	@param	playerTime:プレイヤーのクリアタイム
*/
save::save(char const* _FileName, int dataElementsCount, int playerTime)
{	
	// FILE型構造体
	FILE* fp; 
	// 読み込んだ文字列を格納する変数
	char str[N];	

	// ファイルを開く。失敗するとNULLを返す。
	fp = fopen(_FileName, "r");  
	// ファイルが開けなかった場合
	if(fp == NULL) { printfDx("%s file not open!\n", _FileName); }

	int i = 0;
	// ファイルから一行ずつ読み込む
	while(fgets(str, N, fp) != NULL) {	
		// char型からint型へ変換する
		date[i].time = atoi(str);
		// データのタイプをログに設定
		date[i].type = TYPE_LOG;
		i++;
	}

	// ファイルを閉じる
	fclose(fp); 

	// プレイヤーのクリアタイムをセット
	date[dataElementsCount].type = TYPE_PLAYER;
	date[dataElementsCount].time = playerTime;

	// バブルソート　降順
	int tmpTime = NULL; int tmpType = NULL;
	for(i = 0; i <= dataElementsCount; i++) {	
		for(int j = i + 1; j <= dataElementsCount; j++) {
			if(date[i].time > date[j].time) {
				// timeの入れ替え
				tmpTime = date[i].time;	
				date[i].time = date[j].time;
				date[j].time = tmpTime;
				// typeの入れ替え
				tmpType = date[i].type;	
				date[i].type = date[j].type;
				date[j].type = tmpType;
			}
		}
		date[i].x = 0; date[i].y = 0;
	}
	// 行数を設定
	_drawLine = dataElementsCount;
}

/*
	@brief	saveのデストラクタ
*/
save::~save()
{	
	// デストラクタ
}

/*
	@brief	テキストの出力
	@param	_FileName:ファイル名
	@param	dataElementsCount:配列の要素数
*/
void save::Export(char const* _FileName, int dataElementsCount)
{
	// ファイル初期化
	FILE* fp = 0;

	//	.txtファイルを書き込み可能でオープン
	fp = fopen(_FileName, "w");

	for (int i = 0; i < dataElementsCount; i++) {
		//「.txt」に date の情報を書き込む
		fprintf(fp, "%d\n", date[i].time);
	}
	//	ファイルをクローズ
	fclose(fp);
}

/*
	@brief	テキストの読み込み
	@param	_FileName:ファイル名
	@param	dataElementsCount:配列の要素数
*/
int save::Input(char const* _FileName, int dataElementsCount)	// dataElementsCount:配列(行)
{
	// FILE型構造体
	FILE* fp; 
	char str[N];
	// ファイルを開く。失敗するとNULLを返す。
	fp = fopen(_FileName, "r");  
	// ファイルが開けなかった場合
	if(fp == NULL) {
		printfDx("%s file not open!\n", _FileName);
		return -1;
	}

	int i = 0;
	// ファイルから一行ずつ読み込む
	while(fgets(str, N, fp) != NULL) {	
		// char型からint型へ変換する
		_date[i] = atoi(str);		
		i++;
	}
	// ファイルを閉じる
	fclose(fp); 
	// 指定の行数を返す
	return _date[dataElementsCount];	
}

/*
	@brief	データの描画
	@param	pos_x:描画するx座標
	@param	pos_y:描画するy座標
	@param	width:文字の幅
	@param	size:文字のサイズ
*/
void save::AscendingOrderDataDrawing(int pos_x, int pos_y, int width, int size)
{
	int i, Cr;
	// 描画する文字列のサイズを設定
	SetFontSize(size);
	// データの描画
	for(i = 0; i <= _drawLine; i++) {
		// 6行目がログの場合は描画しない
		if (i == _drawLine && date[i].type == TYPE_LOG) continue;
		// 描画する座標を設定
		date[i].x = pos_x;
		date[i].y = pos_y + i * width;
		// クリアタイムを計算して描画
		int time1 = date[i].time / 60000;
		int time2 = (date[i].time % 60000) / 10000;
		int time3 = ((date[i].time % 60000) / 1000) % 10;
		int time4 = ((date[i].time /10) % 100) / 10;
		int time5 = (date[i].time / 10) % 10;
		// ログは水色で描画
		if(date[i].type == TYPE_LOG) Cr = GetColor(175, 223, 228); 	
		// プレイヤーは黄色で描画
		if(date[i].type == TYPE_PLAYER)  Cr = GetColor(255, 255, 102); 
		// クリアタイムの描画
		DrawFormatString(date[i].x, date[i].y, Cr,"%d:%d%d:%d%d", time1, time2, time3, time4, time5);
	}
}
