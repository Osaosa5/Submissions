#pragma once

class save {
public:
	save(char const* _FileName, int dataElementsCount, int playerTime);				// コンストラクタ
	~save();			// デストラクタ

	void	Export(char const* _FileName, int _date);	// テキストの出力
	int		Input(char const* _FileName, int dataElementsCount);		// テキストの読み込み
	void	AscendingOrderDataDrawing(int pos_x, int pos_y, int width, int size);

protected:
#define N 256					// 1行の最大文字数(バイト数)
#define ARRAY_NUMBER	1000	// 配列の数
#define DRAW_LINE		10

// データタイプ
#define TYPE_LOG		0
#define TYPE_PLAYER	1

protected:
	int	_date[ARRAY_NUMBER];	// 変換後のデータを格納する
	int _drawLine;				// 描画行数

	struct DATE {
		int type;	// タイプ
		int time;	// クリアタイム
		int x, y;	// 座標
	} date[DRAW_LINE];
};


