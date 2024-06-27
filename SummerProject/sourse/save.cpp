// �S���F����

/*
	�Z�[�u�f�[�^�̓ǂݍ��݁A�������݂��s��
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "DxLib.h"
#include "save.h"

/*
	@brief	save�̃R���X�g���N�^
	@param	_FileName:�t�@�C����
	@param	dataElementsCount:�z��̗v�f��
	@param	playerTime:�v���C���[�̃N���A�^�C��
*/
save::save(char const* _FileName, int dataElementsCount, int playerTime)
{	
	// FILE�^�\����
	FILE* fp; 
	// �ǂݍ��񂾕�������i�[����ϐ�
	char str[N];	

	// �t�@�C�����J���B���s�����NULL��Ԃ��B
	fp = fopen(_FileName, "r");  
	// �t�@�C�����J���Ȃ������ꍇ
	if(fp == NULL) { printfDx("%s file not open!\n", _FileName); }

	int i = 0;
	// �t�@�C�������s���ǂݍ���
	while(fgets(str, N, fp) != NULL) {	
		// char�^����int�^�֕ϊ�����
		date[i].time = atoi(str);
		// �f�[�^�̃^�C�v�����O�ɐݒ�
		date[i].type = TYPE_LOG;
		i++;
	}

	// �t�@�C�������
	fclose(fp); 

	// �v���C���[�̃N���A�^�C�����Z�b�g
	date[dataElementsCount].type = TYPE_PLAYER;
	date[dataElementsCount].time = playerTime;

	// �o�u���\�[�g�@�~��
	int tmpTime = NULL; int tmpType = NULL;
	for(i = 0; i <= dataElementsCount; i++) {	
		for(int j = i + 1; j <= dataElementsCount; j++) {
			if(date[i].time > date[j].time) {
				// time�̓���ւ�
				tmpTime = date[i].time;	
				date[i].time = date[j].time;
				date[j].time = tmpTime;
				// type�̓���ւ�
				tmpType = date[i].type;	
				date[i].type = date[j].type;
				date[j].type = tmpType;
			}
		}
		date[i].x = 0; date[i].y = 0;
	}
	// �s����ݒ�
	_drawLine = dataElementsCount;
}

/*
	@brief	save�̃f�X�g���N�^
*/
save::~save()
{	
	// �f�X�g���N�^
}

/*
	@brief	�e�L�X�g�̏o��
	@param	_FileName:�t�@�C����
	@param	dataElementsCount:�z��̗v�f��
*/
void save::Export(char const* _FileName, int dataElementsCount)
{
	// �t�@�C��������
	FILE* fp = 0;

	//	.txt�t�@�C�����������݉\�ŃI�[�v��
	fp = fopen(_FileName, "w");

	for (int i = 0; i < dataElementsCount; i++) {
		//�u.txt�v�� date �̏�����������
		fprintf(fp, "%d\n", date[i].time);
	}
	//	�t�@�C�����N���[�Y
	fclose(fp);
}

/*
	@brief	�e�L�X�g�̓ǂݍ���
	@param	_FileName:�t�@�C����
	@param	dataElementsCount:�z��̗v�f��
*/
int save::Input(char const* _FileName, int dataElementsCount)	// dataElementsCount:�z��(�s)
{
	// FILE�^�\����
	FILE* fp; 
	char str[N];
	// �t�@�C�����J���B���s�����NULL��Ԃ��B
	fp = fopen(_FileName, "r");  
	// �t�@�C�����J���Ȃ������ꍇ
	if(fp == NULL) {
		printfDx("%s file not open!\n", _FileName);
		return -1;
	}

	int i = 0;
	// �t�@�C�������s���ǂݍ���
	while(fgets(str, N, fp) != NULL) {	
		// char�^����int�^�֕ϊ�����
		_date[i] = atoi(str);		
		i++;
	}
	// �t�@�C�������
	fclose(fp); 
	// �w��̍s����Ԃ�
	return _date[dataElementsCount];	
}

/*
	@brief	�f�[�^�̕`��
	@param	pos_x:�`�悷��x���W
	@param	pos_y:�`�悷��y���W
	@param	width:�����̕�
	@param	size:�����̃T�C�Y
*/
void save::AscendingOrderDataDrawing(int pos_x, int pos_y, int width, int size)
{
	int i, Cr;
	// �`�悷�镶����̃T�C�Y��ݒ�
	SetFontSize(size);
	// �f�[�^�̕`��
	for(i = 0; i <= _drawLine; i++) {
		// 6�s�ڂ����O�̏ꍇ�͕`�悵�Ȃ�
		if (i == _drawLine && date[i].type == TYPE_LOG) continue;
		// �`�悷����W��ݒ�
		date[i].x = pos_x;
		date[i].y = pos_y + i * width;
		// �N���A�^�C�����v�Z���ĕ`��
		int time1 = date[i].time / 60000;
		int time2 = (date[i].time % 60000) / 10000;
		int time3 = ((date[i].time % 60000) / 1000) % 10;
		int time4 = ((date[i].time /10) % 100) / 10;
		int time5 = (date[i].time / 10) % 10;
		// ���O�͐��F�ŕ`��
		if(date[i].type == TYPE_LOG) Cr = GetColor(175, 223, 228); 	
		// �v���C���[�͉��F�ŕ`��
		if(date[i].type == TYPE_PLAYER)  Cr = GetColor(255, 255, 102); 
		// �N���A�^�C���̕`��
		DrawFormatString(date[i].x, date[i].y, Cr,"%d:%d%d:%d%d", time1, time2, time3, time4, time5);
	}
}
