// SFφϊ±

/*
	vC[ΜHPπ\¦·ιUI
*/

#include "DxLib.h"
#include "uilife.h"

/*
	@brief	RXgN^
*/
UILife::UILife() {
	// ζΜΗέέ
	_cgHeart_loss	= LoadGraph("res/UI/heart-black.png");
	_cgHeart		= LoadGraph("res/UI/heart.png");
	_cgDie			= LoadGraph("res/effect/about_to_die.png");
	// ϊ»
	_UIlife		= 0;
	_lifeCnt	= 0;
}

/*
	@brief	fXgN^
*/
UILife::~UILife() {
	// ζΜν
	DeleteGraph(_cgHeart_loss);
	DeleteGraph(_cgHeart);
}

/*
	@brief	Zb^[
	@param	lifeFHP
*/
void	UILife::Set(int life) {
	_UIlife = life;
}

/*
	@brief	Xn[gZb^[
	@return	_UIlifeF»έΜHP
*/
int		UILife::Get() {
	return _UIlife;
}

/*
	@brief	XV
*/
void	UILife::Process() {
	// Ctͺ1ΜΙ_Ε
	if (_UIlife == 1) _lifeCnt++;
	// Ctͺ1΄ΜΝ_Ε΅Θ’
	else _lifeCnt = 0;
}

// `ζ
void	UILife::Draw() {

	// Ctͺ1ΜΝζΚͺΤ­Θι
	if (_UIlife == 1) DrawGraph(0, 0, _cgDie, TRUE);
	// ζπ`ζ·ιξΐW
	int base_x = 40, base_y = 25;

	// n[gΜTCY
	int heart_w		= 84, heart_h = 70;
	int heart_one	= 1;		// ΠΖΒΜn[gΕlifeπ’­Β\»·ι©

	// lifeπn[gΕ`ζ
	int x, y, w;
	x = 0; y = 0; w = 80;			// n[gΖn[gΜXL}
	int life = _UIlife;
	for (int i = 0; i < 320; i += w) {
		// ’n[gπ`ζ
		DrawGraph(base_x + i, base_y, _cgHeart_loss, TRUE);
	}
	while(life > 0) {
		// _lifeCntπ60ΕΑ½]θͺ30’ΜΙn[gπ`ζ
		if (_lifeCnt % 60 < 30) {
			DrawGraph(base_x + x, base_y + y, _cgHeart, TRUE);
		}
		life -= heart_one;	// n[gΠΖΒͺCtπΈη·
		x += w;	// Μn[gΚuΦ
	}
}
