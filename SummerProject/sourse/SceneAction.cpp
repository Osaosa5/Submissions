// �S���F����

/*
	�Q�[���̃��C������
*/

#include "DxLib.h"
#include "winmain.h"
#include "GameMain.h"
#include "scenegameover.h"
#include "sceneaction.h"
#include "scenegameresult.h"
#include "Effect.h"

/*
	@brief	SceneAction�̃R���X�g���N�^
	@param	stageNumber:�X�e�[�W�ԍ�
*/
SceneAction::SceneAction(int stageNumber) {

	// �L�����摜�z��̏�����
	for(int i = 0; i < _PLAYER_ALL_; i++) {
		_cgPlayer[i] = -1;
	}
	// �摜�̓ǂݍ���
	_cgBg					= LoadGraph("res/cgBg/cgBg.png");					// �w�i
	_cgOperationDescription = LoadGraph("res/cgBg/sousahouhou.png");			// ��������摜
	_cgStart				= LoadGraph("res/UI/go-04.png");					// start
	_cgLimitTimeBox			= LoadGraph("res/UI/timeframe-02.png");				// �������Ԃ̌��̃{�b�N�X(�g�g��)
	_cgFade					= LoadGraph("res/cgBg/fade.png");					// �Â��摜
	_cgRetry				= LoadGraph("res/UI/retry.png");					// retry?
	// Yes or No
	_cgYes[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/yes3.png");
	_cgYes[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/yes4.png");
	_cgNo[COLLOR_BLUE]		= LoadGraph("res/UI/gameover/No3.png");
	_cgNo[COLLOR_YELLOW]	= LoadGraph("res/UI/gameover/No4.png");

	// �v���C���[�摜�ǂݍ���
	LoadDivGraph("res/motion/bike_run_nogatoling_00000_sheet.png", 24, 4, 6, 240, 240, &_cgPlayer[PLAYER_WALK]);
	LoadDivGraph("res/motion/bike_crash_new_00000_sheet.png", 24, 4, 6, 240, 240, &_cgPlayer[PLAYER_DAMAGE]);
	LoadDivGraph("res/motion/bike_jump_new_00000_sheet.png", 12, 4, 3, 240, 240, &_cgPlayer[PLAYER_JUMP_UP]);
	LoadDivGraph("res/motion/bike_jump_new_00012_sheet.png", 12, 4, 3, 240, 240, &_cgPlayer[PLAYER_JUMP_DOWN]);
	LoadDivGraph("res/motion/player_moving_left_left.png", 8, 4, 2, 240, 240, &_cgPlayer[PLAYER_MOVING_LEFT]);
	LoadDivGraph("res/motion/player_moving_right_right.png", 8, 4, 2, 240, 240, &_cgPlayer[PLAYER_MOVING_RIGHT]);
	// �A�C�e���摜�ǂݍ���
	LoadDivGraph("res/UI/item_battery.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_BATTERY]);
	LoadDivGraph("res/UI/item_heart.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_HEART]);
	LoadDivGraph("res/UI/stageitem1_jet.png", 24, 8, 3, 120, 120, &_cgItem[ITEM_JET]);

	// �����摜�ǂݍ���
	LoadDivGraph("res/UI/number_ui_sheet.png", 11, 11, 1, 48, 72, &_cgNumber[0]);
	LoadDivGraph("res/UI/3cnt_sheet.png", 3, 3, 1, 300, 300, &_cgCntNumber[0]);


	// ���ʉ��̓ǂݍ���
	for(int i = 0; i < _SE_ALL_; i++) {
		_se[i] = -1;
	}
	_se[SE_WALK]			= LoadSoundMem("res/sound/bike.mp3");						// �G���W����
	_se[SE_DAMAGE]			= LoadSoundMem("res/sound/damage.wav");						// �Փˉ�
	_se[SE_JUMP]			= LoadSoundMem("res/sound/SE_jetjump.wav");					// �W�����v��
	_se[SE_LANDING]			= LoadSoundMem("res/sound/SE_landing.wav");					// ���n
	_se[SE_GOAL]			= LoadSoundMem("res/sound/choice.mp3");						// �S�[����
	_se[SE_CHOOSE]			= LoadSoundMem("res/sound/choice.mp3");						// �{�^���I����	
	_se[SE_DECISION]		= LoadSoundMem("res/sound/waterslash.mp3");					// �{�^�����艹
	_se[SE_CANCEL]			= LoadSoundMem("res/sound/destruction.mp3");				// �I���L�����Z����
	_se[SE_JET]				= LoadSoundMem("res/sound/kasoku.mp3");						// �W�F�b�g�l����
	_se[SE_RED_JET]			= LoadSoundMem("res/sound/kira.mp3");						// �W�F�b�g�i�ԁj�l����
	_se[SE_HEART]			= LoadSoundMem("res/sound/heal.mp3");						// �n�[�g�l����
	_se[SE_BATTERY]			= LoadSoundMem("res/sound/barrier.mp3");					// �o�b�e���[�l����
	_se[SE_CNT]				= LoadSoundMem("res/sound/cnt.mp3");						// �J�E���g�_�E����
	_se[SE_START]			= LoadSoundMem("res/sound/start.mp3");						// �Q�[���X�^�[�g��
	_se[SE_SELECT]			= LoadSoundMem("res/sound/select.mp3");						// �I����
	_se[SE_DETERMINATION]	= LoadSoundMem("res/sound/determination.mp3");				// ���艹

	_bgm[BGM_STAGE_ONE]		= LoadSoundMem("res/sound/CrazyHill.mp3");					// �X�e�[�W�P��BGM

	_mapData				= new MapData(stageNumber);		
															
	_fps					= new fps();					
															
	_UIspeedoMeter			= new UISpeedoMeter();			
															
	_shadow					= new Shadow();					
															
	_UImileStone			= new uiMileStone();			
															
	ef_barrier				= new Effect();					
	ef_healing				= new Effect();					
	ef_firespark			= new Effect();					
	ef_frustration			= new Effect();					

	// �|�[�Y��ʂ̏�����
	InitPouse();

	// ��ʏ����̏�����
	InitScreen();

	// �������ԏ����̏�����
	InitLimitTime();

	// �A�C�e�������̏�����
	InitItem();

	// �v���C���[�����̏�����
	InitPlayer();

	// �Q�[���J�n�O�̏����̏�����
	InitStartPreprocessing();

	// �̗͂̏�����
	_life = 4;
	_UIlife.Set(_life);

	// �Q�[���X�^�[�g�t���O
	drawingFlag	= 1;

	// �Q�[���t���O
	// �Q�[���I�[�o�[�t���O�@�̗͂�0�ɂȂ�����
	gameFlag_Over		= 0;
	// �Q�[���I�[�o�[�t���O�@�^�C���I�[�o�[
	gameFlag_TimeOver	= 0;
	// �Q�[���N���A�t���O
	gameFlag_Clear		= 0;
	// �|�[�Y��ʃt���O
	pause				= 0;
}

/*
	@brief	SceneAction�̃f�X�g���N�^
*/
SceneAction::~SceneAction() {
	// �O���t�B�b�N���������ォ��폜����
	// �w�i
	DeleteGraph(_cgBg);

	// �A�C�e��
	for(int i = 0; i < _ITEM_ALL_; i++) {
		if(_cgItem[i] != -1) {
			DeleteGraph(_cgItem[i]);
		}
	}

	// �v���C���[
	for(int i = 0; i < _PLAYER_ALL_; i++) {
		if(_cgPlayer[i] != -1) {
			DeleteGraph(_cgPlayer[i]);
		}
	}

	// ����
	for(int i = 0; i < _NUMBER_ALL_; i++) {
		if(_cgNumber[i] != -1) {
			DeleteGraph(_cgNumber[i]);
		}
	}

	// �������ɓǂ݂��񂾉��f�[�^���폜����
	// ���ʉ�
	for(int i = 0; i < _SE_ALL_; i++) {
		if(_se[i] != -1) {
			DeleteSoundMem(_se[i]);
		}
	}

	// BGM
	for(int i = 0; i < _BGM_ALL_; i++) {
		if(_bgm[i] != -1) {
			DeleteSoundMem(_bgm[i]);
		}
	}

	// UI�֌W
	_mapData->~MapData();
	_UIlife.~UILife();
	_UIspeedoMeter->~UISpeedoMeter();
	_UImileStone->~uiMileStone();

	// �G�t�F�N�g�֌W
	ef_barrier->~Effect();
	ef_healing->~Effect();
	ef_firespark->~Effect();
	ef_frustration->~Effect();
}

/*
	@brief	SceneAction�̓��͏��̏���
*/
void SceneAction::Input() {
	// �������Ȃ�
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �L�[���͂��擾
	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	gTrg = (gKey ^ keyold) & gKey;
	// �L�[�̃����[�X��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	gRel = (gKey ^ keyold) & ~gKey;
}

/*
	@brief	SceneAction�̏���
*/
void SceneAction::Process() {
	// �|�[�Y�̃t���O�������Ă��Ȃ��Ƃ�
	if (pause == 0) {
		// �X�^�[�g�O�̏���
		ProcessBeforeStart();
		// �������Ԃ̏���
		ProcessLimitTime();
		// �X�s�[�h���[�^�[�̏���
		_UIspeedoMeter->Process(pl.speed_x, 10, 35, 5);
		// �}�C���X�g�[���̏���
		_UImileStone->Process(pl.x, 60, DISTANCE_LIMIT);
		// �Q�[���X�^�[�g�t���O�������Ă���Ƃ�
		if (gameStart == 1) {
			_UIlife.Process();  // �n�[�gUI�̏���

			ProcessCharacter();

			ProcessItem();		// �A�C�e���̏���

			ProcessPlayer();	// player�̏���

			ProcessScreen();	// �X�N���[���̏���
		}
		// �|�[�Y�̏���
		ProcessPouse();
		// �t���[�����[�g�̏���
		_fps->fps_wait();

		{
			// �t�F�[�h�����̒i�K�̎擾
			int step = _fade->GetStep();
			switch (step) {
			case 0: // �t�F�[�h�C��
				_fade->ColorFadeIn(10);
				step++;
				break;
			case 1:	// �t�F�[�h�C�����I�����Ă��邩
				if (_fade->IsColorFade() == 0) {
					// �t�F�[�h�C���I��
					step++;
				}
				break;
			case 2:
				// �Q�[���I�[�o�[
				if (_UIlife.Get() == 0) {
					gameFlag_Over = 1;
				}
				if (drawLimitTime < 0) {
					gameFlag_TimeOver = 1;
				}

				// �Q�[���N���A
				if (_UIlife.Get() != 0 && pl.x >= DISTANCE_LIMIT) {
					// �N���ASE
					PlaySoundMem(_se[SE_GOAL], DX_PLAYTYPE_BACK);
					if (CheckSoundMem(_bgm[BGM_STAGE_ONE]) == 1) {
						StopSoundMem(_bgm[BGM_STAGE_ONE]);
					}
					// �S�[�����[�r�[
					if (gameFlag_Clear == 0) {
						PlayMovie("res/staging/clear.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
						gameFlag_Clear = 1;
						drawingFlag = 0;
						WaitTimer(1000);
					}
					// �Q�[���t���Ooff
					gameStart = 0;
				}
				// �ʏ폈��
				// �^�C���I�[�o�[�Ɍ���C.O
				if (gameFlag_TimeOver == 1) {
					SceneBase* scene = new SceneGameOver();
					ChangeScene(scene);
				}
				if (gameFlag_Over == 1) {
					// �t�F�[�h�A�E�g�J�n
					_fade->ColorFadeOut(0, 0, 0, 60);
					step++;
				}
				if (gameFlag_Clear == 1) {
					step++;
				}
				break;
			case 3:
				if (_fade->IsColorFade() != 1) {
					// step������
					step = 0;
					// �t�F�[�h�A�E�g�I��
					// �Q�[���I�[�o�[
					if (gameFlag_Over == 1) {
						// �Q�[���I�[�o�[��ʂ�
						SceneBase* scene = new SceneGameOver();
						ChangeScene(scene);
					}
					// �Q�[���N���A
					if (gameFlag_Clear == 1) {
						// �Q�[���N���A��ʂ�
						SceneBase* scene = new SceneGameResult(drawLimitTime);
						ChangeScene(scene);
					}
				}
				break;
			}
			// ���݂̃t�F�[�h�����̒i�K�̃Z�b�g
			_fade->SetStep(step);
		}
	}
}

/*
	@brief	SceneAction�̕`��
*/
void SceneAction::Draw() {
	// �`��t���O�������Ă���Ƃ�
	if (drawingFlag == 1) {
		// �w�i�̕`��
		DrawScreen();
		// ���������ʂ��\������Ă��Ȃ���
		if (operationDescription == 0) {
			// �}�b�v�`��
			_mapData->Draw(gScrollX, 0);
			// �⏕���`��
			for (int i = 4; i < 9; i++) {
				int y, w;
				y = i * CHIP_H;
				w = SCREEN_W;
				DrawLine(0, y, w, y, GetColor(255, 255, 255));
			}
			// �}�C���X�g�[���`��
			_UImileStone->Draw();
			// �̗͂̕`��
			_UIlife.Draw();
			// �v���C���[�̉e�̕`��
			_shadow->DrawPlayer(pl.x, pl.y, gScrollX);
			// �X�s�[�h���[�^�[�̕`��
			_UIspeedoMeter->Draw();
			// �A�C�e���`��
			DrawItem();
			// �v���C���[�`��
			DrawPlayer();

			int xx, yy;	// �X�N���[����z�肵���L����x,y������
			xx = pl.x - gScrollX;
			yy = pl.y - gScrollY + pl.high;

			// �G�t�F�N�g�`��ibarrier�j
			ef_barrier->SetXY(xx + 50, yy + 45);
			ef_barrier->Draw();

			// �G�t�F�N�g�`��ihealing�j
			ef_healing->SetXY(xx - 5, yy + 90);
			ef_healing->Draw();

			// �G�t�F�N�g�`��iblue_firespark�j
			ef_firespark->SetXY(xx - 160, yy + 170);
			ef_firespark->Draw();
			// �������Ԃ̕`��
			DrawLimitTime();
		}
		// �Q�[���J�n�O�̕`��
		DrawStartPreprocessing();
		// �|�[�Y��ʂ̕`��
		DrawPouse();
	}
}

