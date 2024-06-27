#pragma once

class Shadow{
public:
	Shadow();	// コンストラクタ
	~Shadow();	// デストラクタ

	void DrawPlayer(int x, int y, int scroll_x);
	void DrawItem(int x, int y);

protected:
	int cgShadowPlayer;
	int cgShadowItem;
};


