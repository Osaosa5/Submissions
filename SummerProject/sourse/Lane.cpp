// SFφϊ±

/*
	Q[V[Μ[ΙΦ·ιΦ
	vC[Μ[πΚuΐW+½θ»θΕίΔ΅άΑ½½ίΙA
	ACepΜΦπΚΕμι±ΖΙΘΑΔ΅ά’ά΅½B
*/

#include "SceneAction.h"

/*
	@brief	vC[Μ[ΟX
	@param	yFvC[ΜYΐW
*/
int SceneAction::AddPlayerLane(int y) 
{
	// playerΜyΐWΙ`bvΜε«³π©―ι
	int searchLane = y / CHIP_H;
	if(searchLane == 4) return 1;
	if(searchLane == 5) return 2;
	if(searchLane == 6) return 3;
	if(searchLane == 7) return 4;
	return 0;
}

// 
/*
	@brief	IuWFNgΜ[ΟX
	@param	yFIuWFNgΜYΐW
*/
int SceneAction::AddObjectLane(int y) 
{
	int searchLane = y;
	if(searchLane == 9) return 1;
	if(searchLane == 10) return 2;
	if(searchLane == 11) return 3;
	if(searchLane == 12) return 4;
	return 0;
}
