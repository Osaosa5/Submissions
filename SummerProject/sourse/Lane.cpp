// �S���F����

/*
	�Q�[���V�[���̃��[���Ɋւ���֐�
	�v���C���[�̃��[�����ʒu���W+�����蔻��Ō��߂Ă��܂������߂ɁA
	�A�C�e���p�̊֐���ʂō�邱�ƂɂȂ��Ă��܂��܂����B
*/

#include "SceneAction.h"

/*
	@brief	�v���C���[�̃��[���ύX
	@param	y�F�v���C���[��Y���W
*/
int SceneAction::AddPlayerLane(int y) 
{
	// player��y���W�Ƀ`�b�v�̑傫����������
	int searchLane = y / CHIP_H;
	if(searchLane == 4) return 1;
	if(searchLane == 5) return 2;
	if(searchLane == 6) return 3;
	if(searchLane == 7) return 4;
	return 0;
}

// 
/*
	@brief	�I�u�W�F�N�g�̃��[���ύX
	@param	y�F�I�u�W�F�N�g��Y���W
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
