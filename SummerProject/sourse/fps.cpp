// SFöú±

/*
    t[[gðÀè³¹éNX
*/

#include "DxLib.h"
#include "fps.h"

/*
	@brief	fpsÌRXgN^
*/
fps::fps() 
{
	fps_count = 0;
	count0t = 0;
	for(int i = 0; i < FLAME; i++) 
    {
		f[i] = 0;
	}
	ave = 0;
}

/*
	@brief	fpsÌfXgN^
*/
fps::~fps()
{
    // ½àµÈ¢
}

/*
	@brief	t[[gðvªµÄA60t[ÉÈéæ¤ÉÒÂ
*/
void fps::fps_wait() 
{
    int term, i, gnt;
    static int t = 0;
    if(fps_count == 0) 
    {   //60t[Ì1ñÚÈç
        if(t == 0)//®SÉÅÈçÜ½È¢
            term = 0;
        else//OñL^µ½Ôð³ÉvZ
            term = count0t + 1000 - GetNowCount();
    }
    else    //ÒÂ×«Ô=»Ý é×«-»ÝÌ
        term = (int)(count0t + fps_count * (1000.0 / FLAME)) - GetNowCount();

    if(term > 0)//ÒÂ×«Ô¾¯ÒÂ
        Sleep(term);

    gnt = GetNowCount();

    if(fps_count == 0)//60t[É1xîðìé
        count0t = gnt;
    f[fps_count] = gnt - t;//Püµ½ÔðL^
    t = gnt;
    //½ÏvZ
    if(fps_count == FLAME - 1) 
    {
        ave = 0;
        for(i = 0; i < FLAME; i++)
            ave += f[i];
        ave /= FLAME;
    }
    fps_count = (++fps_count) % FLAME;
}

