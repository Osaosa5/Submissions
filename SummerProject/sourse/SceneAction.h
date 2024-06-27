#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"
#include "mapdata.h"
#include "uilife.h"
#include "mymath.h"
#include "framedata.h"
#include "motiondata.h"
#include "fps.h"
#include "uispeedometer.h"
#include "Shadow.h"
#include "Effect.h"
#include "uiMileStone.h"

/////////////////////////////////////////////////////////////////////////////////////
// �A�j���[�V�����p�^�[���p��`
// �z��̔ԍ��͊Ԃ��󂯂ė]�T�������Đݒ肵�Ă��܂�
// �v���C���[
#define PLAYER_WALK					0					// 0	�`	24��
#define PLAYER_DAMAGE				30					// 30	�`	24��
#define PLAYER_JUMP_UP				60					// 60	�`	12��
#define PLAYER_JUMP_DOWN			90					// 90	�`	12��
#define PLAYER_MOVING_LEFT			120					// 120	�`	 8��
#define PLAYER_MOVING_RIGHT			150					// 150	�`	 8��
#define _PLAYER_ALL_				200					// �S�p�^�[������

// �A�C�e��
#define ITEM_BATTERY				0					// 0	�` 24��
#define ITEM_HEART					30					// 30	�` 24��
#define ITEM_JET					60					// 60	�` 24��
#define _ITEM_ALL_					100					// �S�p�^�[������

//�G�t�F�N�g
#define EFFECT_BARRIER				0					// 0	�`	30��		// �o���A�i���G���j
#define EFFECT_HEALING				40					// 40	�`	30��		// ��
#define EFFECT_BLUE_FIRESPARK		80					// 80	�`	30��		// �W�F�b�g�̉Ή�(����)
#define EFFECT_FRUSTRATION			120					// 120	�`	 5��		// �t���X�g���[�V�����i�_���[�W�󂯂����j
#define _EFFECT_ALL_				200					// �S�p�^�[������


// ���ʉ��p��`
// �z��̔ԍ���0�`
#define SE_WALK						0					// ���s
#define	SE_DAMAGE					1					// �_���[�W(�R���e�i�ɒǓˎ�)
#define SE_JUMP						2					// �W�����v
#define SE_LANDING					3					// ���n
#define SE_GOAL						4					// �S�[��
#define SE_CHOOSE					5					// �{�^���I��
#define SE_DECISION					6					// �{�^������
#define SE_CANCEL					7					// �I���L�����Z��
#define SE_HEART					8					// �n�[�g
#define SE_JET						9					// �W�F�b�g�@
#define SE_RED_JET					10					// �ԃW�F�b�g�@
#define SE_BATTERY					11					// �[�d�r
#define SE_CNT						12					// 3�J�E���g
#define SE_START					13					// �X�^�[�g
#define SE_SELECT					14					// �I��
#define SE_DETERMINATION			15					// ����
#define	_SE_ALL_					20					// �SSE��


// BGM�p��`
// �z��̔ԍ���0�`
#define BGM_TITLE					0					// �^�C�g�����
#define BGM_GAMEOVER				1					// �Q�[���I�[�o�[���
#define BGM_ENDING					2					// �G���f�B���O���
#define BGM_STAGE_ONE				3					// �Q�[���v���C���(STAGE1)
#define BGM_SCENARIO				6					// �V�i���I���
#define BGM_RESULT					7					// ���U���g���
#define _BGM_ALL_					10					// �SBGM��

// ���t�H���g�p��`
#define NUMBER_ZERO					0
#define NUMBER_ONE					1
#define NUMBER_TWO					2
#define NUMBER_THREE				3
#define NUMBER_FOUR					4
#define NUMBER_FIVE					5
#define NUMBER_SIX					6
#define NUMBER_SEVEN				7
#define NUMBER_EIGHT				8
#define NUMBER_NINE					9
#define NUMBER_KOLON				10
#define _NUMBER_ALL_				11

//////////////////////////////////////////////////////////////////////////////////////

class SceneAction : public SceneBase {
public:
	SceneAction(int stageNumber);					// �R���X�g���N�^
	virtual ~SceneAction();							// �f�X�g���N�^

	void	Input() override;							// ����
	void	Process() override;							// �v�Z
	void	Draw() override;							// �`��

protected:
	///////////////////////////////////////////////////////////////////////////////////////////////
	// �|�[�Y�֌W�̊֐�
	///////////////////////////////////////////////////////////////////////////////////////////////
	void InitPouse();
	void ProcessPouse();
	void DrawPouse();
	///////////////////////////////////////////////////////////////////////////////////////////////
	// ���Ԋ֌W�̊֐�
	///////////////////////////////////////////////////////////////////////////////////////////////
	void InitStartPreprocessing();						// �Q�[���X�^�[�g�O�����̏�����
	void ProcessBeforeStart();							// �Q�[���X�^�[�g�O����
	void DrawStartPreprocessing();						// �Q�[���X�^�[�g�O�����̕`��
	void InitLimitTime();
	void ProcessLimitTime();
	void DrawLimitTime();
	///////////////////////////////////////////////////////////////////////////////////////////////
	// ��ʊ֌W�̊֐�
	///////////////////////////////////////////////////////////////////////////////////////////////
	void InitScreen();									// ��ʊ֌W�̏�����
	void ProcessScreen();								// ��ʏ���
	void DrawScreen();									// ��ʕ`��
	///////////////////////////////////////////////////////////////////////////////////////////////
	// ���[�V�����֌W�̊֐�
	///////////////////////////////////////////////////////////////////////////////////////////////
	void CharaChangeMotion(int charaIndex, int motion);	// ���[�V�����؂�ւ��̏���
	int  SearchFrame(int frameId);						// �t���[��ID����
	void ProcessCharacter();
	///////////////////////////////////////////////////////////////////////////////////////////////
	//player//
	///////////////////////////////////////////////////////////////////////////////////////////////
	// player�֌W�̊֐�	
	void InitPlayer();									// player�̏�����
	void ProcessPlayer();								// player�̓���
	void DrawPlayer();									// player�̕`��
	void DamagePlayer();								// player�̃_���[�W����
	int  AddPlayerLane(int y);							// player�̃��[���ǉ�����
	///////////////////////////////////////////////////////////////////////////////////////////////
	// �I�u�W�F�N�g//
	///////////////////////////////////////////////////////////////////////////////////////////////
	int	 AddObjectLane(int y);							// �I�u�W�F�N�g�̃��[���ǉ�����
	// �A�C�e���֌W�̊֐�									  
	void InitItem();									// �A�C�e���̏�����
	void ProcessItem();									// �A�C�e���̌v�Z����
	void DrawItem();									// �A�C�e���̕`��
	void ProcessItemFlag();								// �A�C�e���̃t���O����
	//////////////////////////////////////////////////////////////////////////////////////////////
	// �����蔻��֌W�̊֐�
	//////////////////////////////////////////////////////////////////////////////////////////////
	void InitRect();									// player�̓����蔻�菉����
	void HitCheckPlayerWall(int old_x, int old_y);		// player�ƕǂ̓����蔻�菈��
	void HitCheckPlayerObstacle();						// player�Ə�Q���̓����蔻�菈��
	void HitCheckPlayerItem();							// player�ƃA�C�e���̓����蔻�菈��

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// ��ʊ֌W�̕ϐ�
	//////////////////////////////////////////////////////////////////////////////////////////////
	// �`�b�v�̃T�C�Y
#define	CHIP_W		 (120)								// �}�b�v�`�b�v�̉��T�C�Y
#define	CHIP_H		 (120)								// �}�b�v�`�b�v�̏c�T�C�Y

	// �}�b�v�X�N���[���p
	int gScrollX, gScrollY;

	// �摜�f�[�^	
	int _cgOperationDescription;						// �������
	int _cgStart;										// �Q�[���X�^�[�g
	int _cgNumber[_NUMBER_ALL_];						// ����
	int _cgCntNumber[3];								// 3�J�E���g
	int _cgLimitTimeBox;								// �������Ԃ̃{�b�N�X
	int _cgBg;											// �w�i
	int _cgChip[4];										// �`�b�v�摜�i�z��j
	int _cgPlayer[_PLAYER_ALL_];						// �v���C���[
	int _cgItem[_ITEM_ALL_];							// �A�C�e��
	int _cgShadow;										// �e
	int _cgFade;											// �Â��摜

	// �Q�[���i�s�̒�~������Ȃ�1
	int	_gamePause = 0;
	// �|�[�Y�֌W
	// �}�N��
#define OPTION_YES		0
#define OPTION_NO		1
#define _OPTION_ALL_	2

#define COLLOR_BLUE		0
#define COLLOR_YELLOW	1
#define _COLLOR_ALL_	2

#define YES_X			300
#define YES_Y			600
#define NO_X			1200
#define NO_Y			600

	// �摜�n���h��
	int		_cgRetry;
	int		_cgYes[_COLLOR_ALL_];
	int		_cgNo[_COLLOR_ALL_];

	// ����
	int menu_Yes;										// yes
	int menu_No;										// no
	int menu_Num;										// ����

	// �t���O�E�ϐ�
	int nowSelect;										// �I��
	bool pause;											// �|�[�Y�t���O

	// �Q�[���X�^�[�g
	bool gameStart;										// �Q�[���X�^�[�g�t���O
	bool operationDescription;							// �������t���O
	bool startSignal;									// �X�^�[�g���}
	int	 startCnt;										// �X�^�[�g�O3�J�E���g

	// ��������
	int gameLimitTime;									// 
	int gameStartTime;									// 
	int gameElapsedTime;								// 
	int drawLimitTime;									// 
	int oldTime;										// 	�|�[�Y��ʂ��J�����u�Ԃ̎��Ԃ��L�^����

	// ���ꉉ�o
#define	STAGING_NONE		0							// �Ȃ�
#define	STAGING_START		1							// start
#define	STAGING_GAMEOVER	2							// gameover
#define STAGING_GAMECLEAR	3							// gameclear
#define STAGING_FINISH		4							// finish

	int	_stagingProc = STAGING_NONE;

	//////////////////////////////////////////////////////////////////////////////////////////////
	// ���֌W
	//////////////////////////////////////////////////////////////////////////////////////////////
	int _se[_SE_ALL_];									// ���ʉ��Z�b�g
	int _bgm[_BGM_ALL_];								// BGM�Z�b�g
	int _end;											// �Q�[���N���A�O�̉��o

	//////////////////////////////////////////////////////////////////////////////////////////////
	// �Q�[�����
	//////////////////////////////////////////////////////////////////////////////////////////////
	int gKey;											// �L�[���͂̏��
	int gTrg;											// �g���K���͂̏��
	int gRel;											// �����[�X���͂̏��

	//////////////////////////////////////////////////////////////////////////////////////////////
	// �L�����N�^���
	//////////////////////////////////////////////////////////////////////////////////////////////
	// �L�����^�C�v
#define	CHARA_TYPE_NONE		0							// �L���������iuse=0�I�Ɏg�p�j
#define	CHARA_TYPE_PLAYER	1							// �v���C���[

#define	CHARA_MAX			10							// �L������

	// �v���C���[��� //
#define DISTANCE_LIMIT		120 * 1008					// �S�[�����W


	struct PLAYER {										// player�\����	
		// player��{���
		int		type;									// �L�����^�C�v
		int		x, y;									// ���W�i�`�b�v�P�ʁj
		int		w, h;									// player�̑傫��
		int		hit_x, hit_w, hit_y, hit_h;				// �����蔻��
		int		speed_x;								// x���̈ړ��X�s�[�h
		int		speed_y;								// y���̈ړ��X�s�[�h
		int		lane;									// ���[��
		// �W�����v�����֌W
		int		high;									// �㏸��
		int		gravity;								// �d�͉����x
		int		stand;									// �W�����v�t���O
		// �����蔻��t���O
		bool	hit;									// ��Q���_���[�W�q�b�g�t���O
		bool	obstacleHit;							// ��Q���Փ˃t���O
		int		obstacle;								// ��Q���ƏՓ˂��Ă���̌o�ߎ���
		int		obstacleLimit;							// �d������
		// ���[�V�����֌W
		int		motId;									// ���[�V����ID�B MOTION_xxxx_xxxxx
		int		motcnt;									// ���[�V�����J�E���^�B0�`
		int		animcnt;								// �A�j���[�V�����J�E���^�B0�`
	}pl;

	int			invincibleTime;							// ���G����

	bool		playerMoveFlag;							// ���[���ړ��t���O
	bool		playerSlopeFlag;						// ���E�̌X���t���O

	int			playerCnt;								// playr�p�C�[�W���O�J�E���g
	int			start;									// �ړ��J�n�ʒu
	int			end;									// �ړ��I���ʒu
	int			frames;									// �ړ��ɂ�����t���[����

	struct PLAYER _gChara[CHARA_MAX] = 
{
	{	// �v���C���[
		// type,			x,	y,			 motId,						motcnt,			animcnt
		CHARA_TYPE_PLAYER,	240,240,   		 MOTION_WALK,				0,				0,
	},
};
	int timeObstacle;									// ��Q���ɓ��������u�Ԃ̎���


	// �A�C�e���̏�� //	
#define ITEM_MAX 77										// �A�C�e���̐�

	// �A�C�e��
	struct ITEM {
		// ��{���
		int		use;									// ���̔z����g�p���邩�i0:�g�p���Ȃ�, 1:�g�p����j
		int		type;									// �^�C�v
		int		x, y;									// ���W
		int		w, h;									// �傫��
		int		lane;									// ���[��
		int		cgItem;									// �摜�n���h��
		// �����̏���
		int		high;									// �㏸�l
		int		stand;									// ���n�t���O
		// ���[�V�����֌W
		int		motId;									// ���[�V����ID
		int		motcnt;									// ���[�V�����J�E���^
		int		animcnt;								// �A�j���[�V�����J�E���^
	};

	struct ITEM _gItem[ITEM_MAX] = 
{
	{	// �A�C�e��
		// type,	x,		y,			motId,				motcnt,		animcnt
		BATTERY,	120,120,    MOTION_BATTERY,				0,			0,
	},
	{
		// type,	x,		y,			motId,				motcnt,		animcnt
		HEART,		120,120,		MOTION_HEART,			0,			0,
	},
	{
		// type,	x,		y,			motId,				motcnt,		animcnt
		JET,		120,120,		MOTION_JET,				0,			0,
	},
};

	bool		shouldGotBattery;						// �o�b�e���[���Q�b�g������
	bool		shouldGotHeart;							// �n�[�g���Q�b�g������
	bool		shouldGotJet;							// �W�F�b�g���Q�b�g������
						
	int			batteryEffectStartTime;					// �o�b�e���[���ʊJ�n����

#define MAX_SPEEDUP_COUNT			60					// �X�s�[�h�A�b�v�\�L�̕\������ 

	int			drawCount;
	int			maxDrawCount;


	//////////////////////////////////////////////////////////////////////////////////////////////
	// �N���X
	//////////////////////////////////////////////////////////////////////////////////////////////

	MapData*		_mapData;							// map�N���X
	UILife			_UIlife;							// ���C�tUI�N���X
	UISpeedoMeter*  _UIspeedoMeter;						// speedometer�̃N���X
	Shadow*			_shadow;							// �e�N���X
	uiMileStone*	_UImileStone;						// �}�C���X�g�[��
	fps*			_fps;								// fps�N���X

	Effect*			ef_frustration;						// �G�t�F�N�g�N���X(�t���X�g���[�V����)
	Effect*			ef_barrier; 						// �G�t�F�N�g�N���X(�o���A)
	Effect*			ef_healing;;						// �G�t�F�N�g�N���X(��)
	Effect*			ef_firespark;						// �G�t�F�N�g�N���X(���Ή�)
	
	int				_life;								// player��HP
	int				_score;								// player�̃X�R�A

	int				drawingFlag;						// �X�s�[�h�A�b�v�̕����`��t���O

	int				gameFlag_Over;
	int				gameFlag_TimeOver;
	int				gameFlag_Clear;

};
