#pragma once

class Shadow{
public:
	Shadow();	// �R���X�g���N�^
	~Shadow();	// �f�X�g���N�^

	void DrawPlayer(int x, int y, int scroll_x);
	void DrawItem(int x, int y);

protected:
	int cgShadowPlayer;
	int cgShadowItem;
};


