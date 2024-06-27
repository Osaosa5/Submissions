#pragma once

class Effect 
{
public:
	Effect();																																					// コンストラクタ
	virtual ~Effect();																																		// デストラクタ
	bool	Load(const char* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize);						// 画像読み込み
	void	Process();																																		// 計算
	void	Draw();																																				// 描画
	void	SetWaitFrame(float wait) { waitframe = wait; }																					// 何フレームでまわすか
	void	SetStarting(bool start) { startflag = start; waitframeCnt = 0; nowhandle = 0; loopCnt = 0; }			// 描画スタートフラグ
	void	SetXY(int x, int y) { this->x = x; this->y = y; }																					// 描画位置
	void	SetLoop(int loop) { this->loop = loop; };																							// ループ
	bool	Check();																								// チェック
protected:
	int x;
	int y;

	int loop;
	int loopCnt;

	int waitframe;		// 
	int waitframeCnt;	// 

	int* handles;		// 
	int handlenum;		// 
	int nowhandle;		// 

	bool startflag;		// 描画スタートフラグ

	

};
