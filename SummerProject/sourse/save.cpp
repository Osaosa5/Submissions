// SFφϊ±

/*
	Z[uf[^ΜΗέέA«έπs€
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "DxLib.h"
#include "save.h"

/*
	@brief	saveΜRXgN^
	@param	_FileName:t@CΌ
	@param	dataElementsCount:zρΜvf
	@param	playerTime:vC[ΜNA^C
*/
save::save(char const* _FileName, int dataElementsCount, int playerTime)
{	
	// FILE^\’Μ
	FILE* fp; 
	// ΗέρΎΆρπi[·ιΟ
	char str[N];	

	// t@CπJ­BΈs·ιΖNULLπΤ·B
	fp = fopen(_FileName, "r");  
	// t@CͺJ―Θ©Α½κ
	if(fp == NULL) { printfDx("%s file not open!\n", _FileName); }

	int i = 0;
	// t@C©ηκsΈΒΗέή
	while(fgets(str, N, fp) != NULL) {	
		// char^©ηint^ΦΟ··ι
		date[i].time = atoi(str);
		// f[^Μ^CvπOΙέθ
		date[i].type = TYPE_LOG;
		i++;
	}

	// t@CπΒΆι
	fclose(fp); 

	// vC[ΜNA^CπZbg
	date[dataElementsCount].type = TYPE_PLAYER;
	date[dataElementsCount].time = playerTime;

	// ou\[g@~
	int tmpTime = NULL; int tmpType = NULL;
	for(i = 0; i <= dataElementsCount; i++) {	
		for(int j = i + 1; j <= dataElementsCount; j++) {
			if(date[i].time > date[j].time) {
				// timeΜόκΦ¦
				tmpTime = date[i].time;	
				date[i].time = date[j].time;
				date[j].time = tmpTime;
				// typeΜόκΦ¦
				tmpType = date[i].type;	
				date[i].type = date[j].type;
				date[j].type = tmpType;
			}
		}
		date[i].x = 0; date[i].y = 0;
	}
	// sπέθ
	_drawLine = dataElementsCount;
}

/*
	@brief	saveΜfXgN^
*/
save::~save()
{	
	// fXgN^
}

/*
	@brief	eLXgΜoΝ
	@param	_FileName:t@CΌ
	@param	dataElementsCount:zρΜvf
*/
void save::Export(char const* _FileName, int dataElementsCount)
{
	// t@Cϊ»
	FILE* fp = 0;

	//	.txtt@Cπ«έΒ\ΕI[v
	fp = fopen(_FileName, "w");

	for (int i = 0; i < dataElementsCount; i++) {
		//u.txtvΙ date Μξρπ«ή
		fprintf(fp, "%d\n", date[i].time);
	}
	//	t@CπN[Y
	fclose(fp);
}

/*
	@brief	eLXgΜΗέέ
	@param	_FileName:t@CΌ
	@param	dataElementsCount:zρΜvf
*/
int save::Input(char const* _FileName, int dataElementsCount)	// dataElementsCount:zρ(s)
{
	// FILE^\’Μ
	FILE* fp; 
	char str[N];
	// t@CπJ­BΈs·ιΖNULLπΤ·B
	fp = fopen(_FileName, "r");  
	// t@CͺJ―Θ©Α½κ
	if(fp == NULL) {
		printfDx("%s file not open!\n", _FileName);
		return -1;
	}

	int i = 0;
	// t@C©ηκsΈΒΗέή
	while(fgets(str, N, fp) != NULL) {	
		// char^©ηint^ΦΟ··ι
		_date[i] = atoi(str);		
		i++;
	}
	// t@CπΒΆι
	fclose(fp); 
	// wθΜsπΤ·
	return _date[dataElementsCount];	
}

/*
	@brief	f[^Μ`ζ
	@param	pos_x:`ζ·ιxΐW
	@param	pos_y:`ζ·ιyΐW
	@param	width:ΆΜ
	@param	size:ΆΜTCY
*/
void save::AscendingOrderDataDrawing(int pos_x, int pos_y, int width, int size)
{
	int i, Cr;
	// `ζ·ιΆρΜTCYπέθ
	SetFontSize(size);
	// f[^Μ`ζ
	for(i = 0; i <= _drawLine; i++) {
		// 6sΪͺOΜκΝ`ζ΅Θ’
		if (i == _drawLine && date[i].type == TYPE_LOG) continue;
		// `ζ·ιΐWπέθ
		date[i].x = pos_x;
		date[i].y = pos_y + i * width;
		// NA^CπvZ΅Δ`ζ
		int time1 = date[i].time / 60000;
		int time2 = (date[i].time % 60000) / 10000;
		int time3 = ((date[i].time % 60000) / 1000) % 10;
		int time4 = ((date[i].time /10) % 100) / 10;
		int time5 = (date[i].time / 10) % 10;
		// OΝFΕ`ζ
		if(date[i].type == TYPE_LOG) Cr = GetColor(175, 223, 228); 	
		// vC[Ν©FΕ`ζ
		if(date[i].type == TYPE_PLAYER)  Cr = GetColor(255, 255, 102); 
		// NA^CΜ`ζ
		DrawFormatString(date[i].x, date[i].y, Cr,"%d:%d%d:%d%d", time1, time2, time3, time4, time5);
	}
}
