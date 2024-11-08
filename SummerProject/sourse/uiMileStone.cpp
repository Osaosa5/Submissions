// SFöú±

/*
	vC[ª»ÝXe[WÌÇ±É¢é©ð\¦·éUI
*/

#include "uiMileStone.h"
#include "DxLib.h"

/*
	@brief	RXgN^
*/
uiMileStone::uiMileStone() { 
	// æÇÝÝ
	_cgPlayerPosDisplay	= LoadGraph("res/UI/UI_Face.png");
	_cgMileStone		= LoadGraph("res/UI/location.png");
	// ÀWÝè
	_mileStone_x		= 265;
	_mileStone_y		= 980;
	_playerPosDisplay_x	= 0;
	_playerPosDisplay_y	= _mileStone_y;
	// pÏú»
	_mapDistance	= 0;
	_ranRate		= 0;
	_uiMapDistance	= 1264;
}

/*
	@brief	fXgN^
*/
uiMileStone::~uiMileStone() { 
	// æí
	DeleteGraph(_cgPlayerPosDisplay);
	DeleteGraph(_cgMileStone);
}

/*
	@brief	XV
	@param	x		FvC[Ìs£
	@param	start	FR[XÌX^[gn_
	@param	end		FR[XÌS[n_
*/
void uiMileStone::Process(int x, int start, int end) {
	// R[XÌs£
	_mapDistance		= end - start;
	// vC[ÌÁ½
	_ranRate			= x / _mapDistance;
	// vC[ÌÁ½ðUIÉ½f³¹é
	_playerPosDisplay_x = _ranRate * _uiMapDistance + _mileStone_x;
}

/*
	@brief	`æ
*/
void uiMileStone::Draw() {
	// }CXg[Ì`æ
	DrawGraph(_mileStone_x, _mileStone_y + 10, _cgMileStone, TRUE);
	// vC[sÊu
	DrawGraph(_playerPosDisplay_x, _playerPosDisplay_y, _cgPlayerPosDisplay, TRUE);
}