#pragma once

class fps {
public:
	fps();
	~fps();

	void fps_wait();
protected:
	//fps
#define FLAME 60

//fpsのカウンタ、60フレームに1回基準となる時刻を記録する変数
	int fps_count, count0t;
	//平均を計算するため60回の1周時間を記録
	int f[FLAME];
	//平均fps
	double ave;
};

