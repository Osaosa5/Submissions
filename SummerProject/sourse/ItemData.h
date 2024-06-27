#pragma once
#define ITEM_WIDTH	120					 // アイテムの横サイズ
#define ITEM_HEIGHT 120					 // アイテムの縦サイズ

#define BATTERY		0					 // バッテリー
#define HEART		1					 // ハート(回復)
#define JET			2					 // ジェット

struct ITEMDATA 
{						 // アイテム構造体
	int x, y, stand, type;				 // 基本情報
};

extern struct ITEMDATA itemData[];		 // 宣言
