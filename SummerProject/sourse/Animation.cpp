#include "DxLib.h"
#include "SceneAction.h"

// tblFrame[] の配列番号を、frameIdで調べる
int SceneAction::SearchFrame(int frameId) 
{
	int n = 0;
	while(tblFrame_chara[n].frameId != -1) 
	{
		if(tblFrame_chara[n].frameId == frameId) 
		{
			// 見つかった。[n]が配列番号
			return n;
		}
		n++;
	}
	// 見つからなかった（本来来てはいけない）
	return -1;
}

// キャラのモーション変更指示
void SceneAction::CharaChangeMotion(int charaIndex, int motion) 
{
	if(_gChara[charaIndex].motId != motion) 
	{
		_gChara[charaIndex].motId = motion;
		_gChara[charaIndex].motcnt = 0;
		_gChara[charaIndex].animcnt = 0;
	}
}

void SceneAction::ProcessCharacter() 
{
	int i;
	for(i = 0; i < CHARA_MAX; i++) 
	{

		if(_gChara[i].type != CHARA_TYPE_NONE) 
		{
			//
			// 共通処理（前）
			//

			int motChg = -1;		// モーションを変更する場合、ここに指定する

			int x = pl.x + pl.hit_x;
			int y = pl.y * pl.hit_y;
			int w = pl.hit_w - 1;
			int h = pl.hit_h - 1;

			//
			// タイプ別個別処理
			//

			switch(_gChara[i].type) 
			{
			case CHARA_TYPE_PLAYER:
			{	// プレイヤー
				// 現在のモーションによって操作を分ける
				switch(_gChara[i].motId) 
				{
				case MOTION_WALK:
				{	// 走行
					motChg = MOTION_WALK;

					if((gTrg & PAD_INPUT_3 || gTrg & PAD_INPUT_4) && gameStart == 1)	 // 3,4 = C,Aキー
					{	
						motChg = MOTION_JUMP_UP;
					}

					int x = pl.x + pl.hit_x;
					int y = pl.y + pl.hit_y;
					int w = pl.hit_w - 1;
					int h = pl.hit_h - 1;
					if(pl.stand == 1) 
					{
						if(pl.obstacleHit == 1) 
						{
							motChg = MOTION_DAMAGE;		// ダメージモーション
						}
					}
					if (playerSlopeFlag == 1) 
					{
						if (gTrg & PAD_INPUT_UP && gameStart == 1) 
						{
							motChg = MOTION_MOVING_LEFT;
						}
						if (gTrg & PAD_INPUT_DOWN && gameStart == 1) 
						{
							motChg = MOTION_MOVING_RIGHT;
						}
					}
					break;
				}

				case MOTION_MOVING_LEFT:
				{	// 上（主人公から見て左）に移動中
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// ダメージモーション
					}
					if(playerMoveFlag == 1) 
					{
						motChg = MOTION_WALK;
					}
					break;
				}

				case MOTION_MOVING_RIGHT:
				{	//	下（主人公から見て右）に移動中
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// ダメージモーション
					}
					//playerSlopeFlag
					if(playerMoveFlag == 1) 
					{
						motChg = MOTION_WALK;
					}
					break;
				}

				case MOTION_JUMP_UP:
				{	// ジャンプ上昇中
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// ダメージモーション
					}
					if(pl.gravity >= 0) 
					{
						motChg = MOTION_JUMP_DOWN;
					}
					break;
				}
				case MOTION_JUMP_DOWN:
				{	// ジャンプ下降中
					if (pl.obstacleHit == 1) 
					{
						motChg = MOTION_DAMAGE;		// ダメージモーション
					}
					if(pl.stand != 0) 
					{
						//PlaySoundMem(_se[SE_LANDING], DX_PLAYTYPE_BACK);
						if (pl.speed_x > 10) 
						{
							pl.speed_x -= 5;
						}
						motChg = MOTION_WALK;
					}
					break;
				}
				}
				break;
			}
			}


			//
			// 共通処理（後）
			//

			// モーションは変更されないか？
			if(motChg == -1 || motChg == _gChara[i].motId) 
			{
				// モーション分移動
				// mx,myに移動値を得る
				int mx, my;
				mx = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].mx;
				my = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].my;

				// 移動してみる。まだ当たり判定はしていない
				_gChara[i].x += mx;
				_gChara[i].y += my;

				// 今のモーションのままなので、カウンタを進める
				_gChara[i].animcnt++;

				// モーションの今のフレームは終了したか？
				if(tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt <= _gChara[i].animcnt) 
				{
					// 次のフレームへ
					_gChara[i].motcnt++;
					_gChara[i].animcnt = 0;

					// 次のフレームはコマンドか？
					// コマンドが複数連続で処理できるように、ループをさせておく
					int loop = 1;
					while(loop == 1) 
					{
						// コマンド分岐
						switch(tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameId) 
						{
						case CHARA_MOTION_CMD_LOOP:
						{	// モーションをループさせる
							int motionIndex = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							_gChara[i].motcnt = 0;
							break;
						}
						case CHARA_MOTION_CMD_MOTION:
						{	// 別のモーションへ(frameCntはモーションID)
							int motionId = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							CharaChangeMotion(i, motionId);
							loop = 0;	// ループ終了
							break;
						}
						case CHARA_MOTION_CMD_MAINTENANCE:
						{	// モーションの保持
							loop = 1;
							break;
						}
						case CHARA_MOTION_CMD_PLAYSE:
						{	// 効果音再生(frameCntにSE_xxxx)
							int seId = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							PlaySoundMem(_se[seId], DX_PLAYTYPE_BACK, TRUE);
							_gChara[i].motcnt++;
							break;
						}
						case CHARA_MOTION_CMD_PLAYSE_STOP:
						{	// 効果音停止
							int seId = tblMotion_chara[_gChara[i].motId].item[_gChara[i].motcnt].frameCnt;
							StopSoundMem(_se[seId]);
							_gChara[i].motcnt++;
							break;
						}
						case CHARA_CMD_OBSTACLE_HIT:
						{	// 障害物衝突フラグをオフにする
							pl.obstacleHit = 0;
						}

						default:
						{	// コマンドじゃなかったのでループ終了
							loop = 0;
						}
						}
					}
				}
			}

			// モーションは変更されるか？
			if(
				motChg != -1 && motChg != _gChara[i].motId) 
			{
				// 今と別のモーションに変更
				CharaChangeMotion(i, motChg);
			}
		}
	}
}