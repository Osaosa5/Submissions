#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "mymath.h"

class MapData 
{
public:
	MapData(int stageNumber);			// コンストラクタ
	virtual ~MapData();	// デストラクタ

	void	Draw(int scrollX, int scrollY);		// マップ描画

	// 当たり判定関連					// キャラとマップチップの当たり判定

	int		CheckHitMapChip(int x, int y);											// 指定位置のチップが当たり判定ありか？
	int		CheckHitChip(int chip_no);												// 指定のチップIDが当たり判定ありか？
	int		IsHitCharaMap(int hit_x, int hit_y, int hit_w, int hit_h, int number);	// キャラとマップチップの当たり判定処理

// マップチップ関連
#define	CHIPSIZE_W	120		 // チップの横サイズ
#define	CHIPSIZE_H	120		 // チップの縦サイズ
// マップデータ				 
#define	MAPSIZE_W	1020		 // マップの横サイズ
#define	MAPSIZE_H	9		 // マップの縦サイズ
	
// チップ数
#define CHIP_NUM	4

protected:
	int _gMapData[MAPSIZE_W * MAPSIZE_H];	// マップデータ格納変数
	int	_cgChip[CHIP_NUM];							// チップ画像ハンドル
	int _stageNumber;						// 現在のステージナンバー
};

