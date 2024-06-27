// ’S“–FH‰i

#include "DxLib.h"
#include "Effect.h"

Effect::Effect() 
{
	x = -1;
	y = -1;

	loop = 0;
	loopCnt = 0;

	waitframe = 0;
	waitframeCnt = 0;

	handles = NULL;
	handlenum = 0;
	nowhandle = 0;

	startflag = false;

}

Effect::~Effect() 
{
	if(handles != NULL)
	{
		delete handles;
		handles = NULL;
	}
}

bool Effect::Load(const char* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize) 
{
	handles = new int[AllNum];
	handlenum = AllNum;

	int result = LoadDivGraph(FileName, AllNum, XNum, YNum, XSize, YSize, handles);

	if (-1 == result) 
	{
		return false;
	}
	
	return true;
}
bool Effect::Check() 
{
	if (handles != NULL && handlenum > 0 && x > 0 && y > 0 && startflag == true ) 
	{
		return true;
	}
	return false;
}

void Effect::Process() 
{
	if (Check() == false) 
	{
		return;
	}
	waitframeCnt++;
	if (waitframeCnt > waitframe) 
	{
		waitframeCnt = 0;
		nowhandle++;
		if(nowhandle >= handlenum)
		{
			if (loop == 0) 
			{
				startflag = false;
			}
			else 
			{
				nowhandle = 0;
				loopCnt++;
				if (loopCnt >= loop)
				{
					startflag = false;
				}
			}
		}
	}
}

void Effect::Draw() 
{
	if (Check() == false) 
	{
		return;
	}
	DrawGraph(x, y, handles[nowhandle], TRUE);
}

