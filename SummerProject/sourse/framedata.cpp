#include "SceneAction.h"
#include "framedata.h"


// フレームテーブル
struct CHARA_FRAME tblFrame_chara[] = 
{
	// プレイヤー
	// frameIdは重複しないこと
	// frameId,	cgId,							cx,cy,		w,h,	
	// 走り
	{	1000,	PLAYER_WALK + 0,							60,450,		240, 240	 },
	{	1001,	PLAYER_WALK + 1,							60,450,		240, 240	 },
	{	1002,	PLAYER_WALK + 2,							60,450,		240, 240	 },
	{	1003,	PLAYER_WALK + 3,							60,450,		240, 240	 },
	{	1004,	PLAYER_WALK + 4,							60,450,		240, 240	 },
	{	1005,	PLAYER_WALK + 5,							60,450,		240, 240	 },
	{	1006,	PLAYER_WALK + 6,							60,450,		240, 240	 },
	{	1007,	PLAYER_WALK + 7,							60,450,		240, 240	 },
	{	1008,	PLAYER_WALK + 8,							60,450,		240, 240	 },
	{	1009,	PLAYER_WALK + 9,							60,450,		240, 240	 },
	{	1010,	PLAYER_WALK + 10,							60,450,		240, 240	 },
	{	1011,	PLAYER_WALK + 11,							60,450,		240, 240	 },
	{	1012,	PLAYER_WALK + 12,							60,450,		240, 240	 },
	{	1013,	PLAYER_WALK + 13,							60,450,		240, 240	 },
	{	1014,	PLAYER_WALK + 14,							60,450,		240, 240	 },
	{	1015,	PLAYER_WALK + 15,							60,450,		240, 240	 },
	{	1016,	PLAYER_WALK + 16,							60,450,		240, 240	 },
	{	1017,	PLAYER_WALK + 17,							60,450,		240, 240	 },
	{	1018,	PLAYER_WALK + 18,							60,450,		240, 240	 },
	{	1019,	PLAYER_WALK + 19,							60,450,		240, 240	 },
	{	1020,	PLAYER_WALK + 20,							60,450,		240, 240	 },
	{	1021,	PLAYER_WALK + 21,							60,450,		240, 240	 },
	{	1022,	PLAYER_WALK + 22,							60,450,		240, 240	 },
	{	1023,	PLAYER_WALK + 23,							60,450,		240, 240	 },

	// ダメージ											
	{	1100,	PLAYER_DAMAGE + 0,						60,450,		240, 240,	 },
	{	1101,	PLAYER_DAMAGE + 1,						60,450,		240, 240,	 },
	{	1102,	PLAYER_DAMAGE + 2,						60,450,		240, 240,	 },
	{	1103,	PLAYER_DAMAGE + 3,						60,450,		240, 240,	 },
	{	1104,	PLAYER_DAMAGE + 4,						60,450,		240, 240,	 },
	{	1105,	PLAYER_DAMAGE + 5,						60,450,		240, 240,	 },
	{	1106,	PLAYER_DAMAGE + 6,						60,450,		240, 240,	 },
	{	1107,	PLAYER_DAMAGE + 7,						60,450,		240, 240,	 },
	{	1108,	PLAYER_DAMAGE + 8,						60,450,		240, 240,	 },
	{	1109,	PLAYER_DAMAGE + 9,						60,450,		240, 240,	 },
	{	1110,	PLAYER_DAMAGE + 10,					60,450,		240, 240,	 },
	{	1111,	PLAYER_DAMAGE + 11,					60,450,		240, 240,	 },
	{	1112,	PLAYER_DAMAGE + 12,					60,450,		240, 240,	 },
	{	1113,	PLAYER_DAMAGE + 13,					60,450,		240, 240,	 },
	{	1114,	PLAYER_DAMAGE + 14,					60,450,		240, 240,	 },
	{	1115,	PLAYER_DAMAGE + 15,					60,450,		240, 240,	 },
	{	1116,	PLAYER_DAMAGE + 16,					60,450,		240, 240,	 },
	{	1117,	PLAYER_DAMAGE + 17,					60,450,		240, 240,	 },
	{	1118,	PLAYER_DAMAGE + 18,					60,450,		240, 240,	 },
	{	1119,	PLAYER_DAMAGE + 19,					60,450,		240, 240,	 },
	{	1120,	PLAYER_DAMAGE + 20,					60,450,		240, 240,	 },
	{	1121,	PLAYER_DAMAGE + 21,					60,450,		240, 240,	 },
	{	1122,	PLAYER_DAMAGE + 22,					60,450,		240, 240,	 },
	{	1123,	PLAYER_DAMAGE + 23,					60,450,		240, 240,	 },

	// ジャンプ	(上昇)							   	
	{	1200,	PLAYER_JUMP_UP + 0,						60,450,		240, 240,	 },
	{	1201,	PLAYER_JUMP_UP + 1,						60,450,		240, 240,	 },
	{	1202,	PLAYER_JUMP_UP + 2,						60,450,		240, 240,	 },
	{	1203,	PLAYER_JUMP_UP + 3,						60,450,		240, 240,	 },
	{	1204,	PLAYER_JUMP_UP + 4,						60,450,		240, 240,	 },
	{	1205,	PLAYER_JUMP_UP + 5,						60,450,		240, 240,	 },
	{	1206,	PLAYER_JUMP_UP + 6,						60,450,		240, 240,	 },
	{	1207,	PLAYER_JUMP_UP + 7,						60,450,		240, 240,	 },
	{	1208,	PLAYER_JUMP_UP + 8,						60,450,		240, 240,	 },
	{	1209,	PLAYER_JUMP_UP + 9,						60,450,		240, 240,	 },
	{	1210,	PLAYER_JUMP_UP + 10, 					60,450,		240, 240,	 },
	{	1211,	PLAYER_JUMP_UP + 11, 					60,450,		240, 240,	 },

	// ジャンプ(下降)							
	{	1300,	PLAYER_JUMP_DOWN + 0,				60,450,		240, 240,	 },
	{	1301,	PLAYER_JUMP_DOWN + 1,				60,450,		240, 240,	 },
	{	1302,	PLAYER_JUMP_DOWN + 2,				60,450,		240, 240,	 },
	{	1303,	PLAYER_JUMP_DOWN + 3,				60,450,		240, 240,	 },
	{	1304,	PLAYER_JUMP_DOWN + 4,				60,450,		240, 240,	 },
	{	1305,	PLAYER_JUMP_DOWN + 5,				60,450,		240, 240,	 },
	{	1306,	PLAYER_JUMP_DOWN + 6,				60,450,		240, 240,	 },
	{	1307,	PLAYER_JUMP_DOWN + 7,				60,450,		240, 240,	 },
	{	1308,	PLAYER_JUMP_DOWN + 8,				60,450,		240, 240,	 },
	{	1309,	PLAYER_JUMP_DOWN + 9,				60,450,		240, 240,	 },
	{	1310,	PLAYER_JUMP_DOWN + 10,			60,450,		240, 240,	 },
	{	1311,	PLAYER_JUMP_DOWN + 11,				60,450,		240, 240,	 },

	//	レーン移動中(左)
	{	1403,	PLAYER_MOVING_LEFT + 3,			60,450,		240, 240,	 },
	{	1402,	PLAYER_MOVING_LEFT + 2,				60,450,		240, 240,	 },
	{	1401,	PLAYER_MOVING_LEFT + 1,				60,450,		240, 240,	 },
	{	1404,	PLAYER_MOVING_LEFT + 4,			60,450,		240, 240,	 },
	{	1405,	PLAYER_MOVING_LEFT + 5,			60,450,		240, 240,	 },
	{	1406,	PLAYER_MOVING_LEFT + 6,			60,450,		240, 240,	 },
	{	1400,	PLAYER_MOVING_LEFT + 0,				60,450,		240, 240,	 },
	{	1407,	PLAYER_MOVING_LEFT + 7,			60,450,		240, 240,	 },

	//	レーン移動中(右)
	{	1500,	PLAYER_MOVING_RIGHT + 0,			60,450,		240, 240,	 },
	{	1501,	PLAYER_MOVING_RIGHT + 1,			60,450,		240, 240,	 },
	{	1502,	PLAYER_MOVING_RIGHT + 2,			60,450,		240, 240,	 },
	{	1503,	PLAYER_MOVING_RIGHT + 3,			60,450,		240, 240,	 },
	{	1504,	PLAYER_MOVING_RIGHT + 4,			60,450,		240, 240,	 },
	{	1505,	PLAYER_MOVING_RIGHT + 5,			60,450,		240, 240,	 },
	{	1506,	PLAYER_MOVING_RIGHT + 6,			60,450,		240, 240,	 },
	{	1507,	PLAYER_MOVING_RIGHT + 7,			60,450,		240, 240,	 },

	
	// フレーム終端
	{	-1	},		// frameId = -1を終端とする
};

