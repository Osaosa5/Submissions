#pragma once
#define ITEM_WIDTH	120					 // �A�C�e���̉��T�C�Y
#define ITEM_HEIGHT 120					 // �A�C�e���̏c�T�C�Y

#define BATTERY		0					 // �o�b�e���[
#define HEART		1					 // �n�[�g(��)
#define JET			2					 // �W�F�b�g

struct ITEMDATA 
{						 // �A�C�e���\����
	int x, y, stand, type;				 // ��{���
};

extern struct ITEMDATA itemData[];		 // �錾
