#include "sceneaction.h"
#include "framedata.h"
#include "motiondata.h"


struct CHARA_MOTION tblMotion_chara[] =
{	// �v���C���[
	{	// MOTION_WALK
		{	// fId, fCnt, mx,my,
			{ 1000, 3, 0, 0 },
			{ 1001, 3, 0, 0 },
			{ 1002, 3, 0, 0 },
			{ 1003, 3, 0, 0 },
			{ 1004, 3, 0, 0 },
			{ 1005, 3, 0, 0 },
			{ 1006, 3, 0, 0 },
			{ 1007, 3, 0, 0 },
			{ 1008, 3, 0, 0 },
			{ 1009, 3, 0, 0 },
			{ 1010, 3, 0, 0 },
			{ 1011, 3, 0, 0 },
			{ 1012, 3, 0, 0 },
			{ 1013, 3, 0, 0 },
			{ 1014, 3, 0, 0 },
			{ 1015, 3, 0, 0 },
			{ 1016, 3, 0, 0 },
			{ 1017, 3, 0, 0 },
			{ 1018, 3, 0, 0 },
			{ 1019, 3, 0, 0 },
			{ 1020, 3, 0, 0 },
			{ 1021, 3, 0, 0 },
			{ 1022, 3, 0, 0 },
			{ 1023, 3, 0, 0 },
			{ CHARA_MOTION_CMD_LOOP, 0 },
		},
	},
	{	// MOTION_DAMAGE
		{	// fId, fCnt, mx,my,
			{ 1100, 3, 0, 0 },
			{ CHARA_MOTION_CMD_PLAYSE, SE_DAMAGE },
			{ 1101, 3, 0, 0 },
			{ 1102, 3, 0, 0 },
			{ 1103, 3, 0, 0 },
			{ 1104, 3, 0, 0 },
			{ 1105, 3, 0, 0 },
			{ 1106, 3, 0, 0 },
			{ 1107, 3, 0, 0 },
			{ 1108, 3, 0, 0 },
			{ 1109, 3, 0, 0 },
			{ 1110, 3, 0, 0 },
			{ 1111, 3, 0, 0 },
			{ 1112, 3, 0, 0 },
			{ 1113, 3, 0, 0 },
			{ 1114, 3, 0, 0 },
			{ 1115, 3, 0, 0 },
			{ 1116, 3, 0, 0 },
			{ 1117, 3, 0, 0 },
			{ 1118, 3, 0, 0 },
			{ 1119, 3, 0, 0 },
			{ 1120, 3, 0, 0 },
			{ 1121, 3, 0, 0 },
			{ 1122, 3, 0, 0 },
			{ 1123, 3, 0, 0 },
			{ CHARA_CMD_OBSTACLE_HIT},
			{ CHARA_MOTION_CMD_MOTION, MOTION_WALK },
		},
	},
	{	// MOTION_JUMP_UP
		{	// fId, fCnt, mx,my,
			{ 1200, 3, 0, 0 },
			{ CHARA_MOTION_CMD_PLAYSE, SE_JUMP },
			{ 1201, 3, 0, 0 },
			{ 1202, 3, 0, 0 },
			{ CHARA_MOTION_CMD_PLAYSE_STOP, SE_JUMP },
			{ 1203, 3, 0, 0 },
			{ 1204, 3, 0, 0 },
			{ 1205, 3, 0, 0 },
			{ 1206, 3, 0, 0 },
			{ 1207, 3, 0, 0 },
			{ 1208, 3, 0, 0 },
			{ 1209, 3, 0, 0 },
			{ 1210, 3, 0, 0 },
			{ 1211, 3, 0, 0 },
			{ CHARA_MOTION_CMD_MOTION, MOTION_WALK },
		},
	},
	{	// MOTION_JUMP_DOWN
		{	// fId, fCnt, mx,my,
			{ 1300, 3, 0, 0 },
			{ 1301, 3, 0, 0 },
			{ 1302, 3, 0, 0 },
			{ 1303, 3, 0, 0 },
			{ 1304, 3, 0, 0 },
			{ 1305, 3, 0, 0 },
			{ 1306, 3, 0, 0 },
			{ 1307, 3, 0, 0 },
			{ 1308, 3, 0, 0 },
			{ 1309, 3, 0, 0 },
			{ 1310, 3, 0, 0 },
			{ 1311, 3, 0, 0 },
			{ CHARA_MOTION_CMD_MOTION, MOTION_WALK },
		},
	},
	{	// MOTION_MOVING_LEFT
		{	// fId, fCnt, mx,my,
			{ 1400, 1, 0, 0 },
			{ 1401, 1, 0, 0 },
			{ 1402, 1, 0, 0 },
			{ 1403, 1, 0, 0 },
			{ 1404, 1, 0, 0 },
			{ 1405, 1, 0, 0 },
			{ 1406, 1, 0, 0 },
			{ 1407, 1, 0, 0 },
			{ CHARA_MOTION_CMD_LOOP, 0 },
		},
	},
	{	// MOTION_MOVING_RIGHT
		{	// fId, fCnt, mx,my,
			{ 1500,1, 0, 0 },
			{ 1501,1, 0, 0 },
			{ 1502,1, 0, 0 },
			{ 1503,1, 0, 0 },
			{ 1504,1, 0, 0 },
			{ 1505,1, 0, 0 },
			{ 1506,1, 0, 0 },
			{ 1507,1, 0, 0 },
			{ CHARA_MOTION_CMD_LOOP, 0 },
		},
	},
};
