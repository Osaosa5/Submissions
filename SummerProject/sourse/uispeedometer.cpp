// SFφϊ±

/*
	vC[Μ»έΜXs[hπ\¦·ιUI
*/

#include "DxLib.h"
#include "uispeedometer.h"

/*
	@brief	RXgN^
*/
UISpeedoMeter::UISpeedoMeter() {
	// ζΗέέ
	LoadDivGraph("res/UI/speedometer.png", 7, 7, 1, 200, 200, &_cgSpeedMeter[0]);
	// Οϊ»
	_speed		= 0;
	_drawSpeed	= 0;
}

/*
	@brief	fXgN^
*/
UISpeedoMeter::~UISpeedoMeter() {
	// ζν
	for (int i = 0; i < 7; i++) {
		DeleteGraph(_cgSpeedMeter[i]);
	}
}

/*
	@brief	Zb^[
	@param	speedF»έΜXs[h
*/
void	UISpeedoMeter::Set(int speed) {
	_speed = speed;
}

/*
	@brief	Qb^[
	@return	_speedF»έΜXs[h
*/
int		UISpeedoMeter::Get() {
	return _speed;
}

/*
	@brief	XV
	@param	speed		F»έΜXs[h
	@param	min			FXs[hΜΕ¬l
	@param	max			FXs[hΜΕεl
	@param	cangeAmount	FXs[hΜΟ»Κ
*/
void	UISpeedoMeter::Process(int speed, int min, int max, int cangeAmount) {
	// playerΜXs[h©η[^[Μlπίι
	// Xs[hͺ0ΘηΪ·θρ\¦
	if (speed == 0) { _speed = 0; }
	// »κΘOΘηXs[hΙΆ½Ϊ·θπ\¦
	else if(speed != 0){
		for (int i = 1; i < 7; i++) {
			// Xs[hͺΪ·θΜΕ¬lΘγΕεlΘΊΘηΪ·θπ\¦
			if (speed == cangeAmount * (i - 1) + min) {
				_speed = i;
				break;
			}
		}
	}
	// `ζΪ·θπίι
	_drawSpeed = _speed;
}

/*
	@brief	`ζ
*/
void	UISpeedoMeter::Draw() {
	// ²Χ½speedπ`ζ
	DrawGraph(20, 100, _cgSpeedMeter[_drawSpeed], TRUE);
}
