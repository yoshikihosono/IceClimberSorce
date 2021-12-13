#include "Player.h"
#include "DxLib.h"
#include "assert.h"
#include "PlayScene.h"
#include "Map.h"
#include "Seal.h"
#include "Knit picker.h"
#include "Whitebear.h"
#include "Wall.h"
#include "Cloud.h"
#include "Timer.h"
#include "Condor.h"
#include "Eggplant.h"
#include "Floor.h"
#include "app.h"
#include "ResultScene.h"

/*最終更新：2020/8/30*/
/*プレイヤーのソース*/

static const float G = 9.8f * 3.0f / 60.0f;


Player::Player(PlayScene* _scene)
{
	scene = _scene;
	image = LoadGraph("data\\texture\\Player4.png");	//プレイヤーの画像
	Lifeimage = LoadGraph("data\\texture\\Life.png");	//残機の画像
	GameOverimage = LoadGraph("data\\texture\\Gameover.png");	//ゲームオーバーのグラフ
	Life = 3;	//残機
	LifeX = 224;	//残機の表示位置
	LifeY = 80;		//残機の表示位置
	x = 400;	//自機の初期位置
	y = 700;	//自機の初期位置
	TempX = x;	//自機の一時的座標
	TempY = y;	//自機の一時的座標
	HummerX = x;	//ハンマーの座標
	HummerY = y;	//ハンマーの座標
	beforeJump = y;	//ジャンプ前の座標
	OverX = 100;	//ゲームオーバーの画像の座標
	OverY = 1000;	//ゲームオーバーの画像の座標
	velX = 0.0f;	//移動スピード
	velY = 0.0f;	//落下速度
	jumping = false;	//ジャンプフラグ
	PushJump = false;	//ジャンプボタンが押されたか
	RestTime = 0;	//無敵時間
	ScrollCount = 0;	//スクロールした回数
	BonusStage = false;	//ボーナスステージに入ったか
	Clear = false;	//ボーナスステージをクリアしたか
	Failed = false;	//ボーナスステージを失敗したか
	Scrolling = false;	//スクロールしてる途中か？
	RefY = 715;
	Accel = 0;
}

Player::~Player()
{
	DeleteGraph(image);
}

void Player::Update()
{
	if (!Clear && !Failed)
	{
		/*自機操作*/
		/*ジャンプ*/
		if (CheckHitKey(KEY_INPUT_Z) && PushJump == false && !Hit)
		{
			reverse = false;
			jumping = true;
			PushJump = true;
			beforeJump = y;
			Accel = 0;
		}
		/*ジャンプ*/
		/*ハンマー*/
		else if (CheckHitKey(KEY_INPUT_X) && PushJump == false && !Hit)
		{
			Attacking = true;
			animCounter++;
			velX = 0;
		}
		/*ハンマー*/
		/*右移動*/
		else if (CheckHitKey(KEY_INPUT_RIGHT) && !Hit)
		{
			//ジャンプしていないなら
			if (!PushJump)
			{
				animCounter++;
			}
			velX = 5;

			//氷の床なら
			if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) /  BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 9 ||
				scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) /  BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 10)
			{
				if (Accel < 7)
					Accel += 0.3;
			}
			Rightward = true;
		}
		/*右移動*/
		/*左移動*/
		else if (CheckHitKey(KEY_INPUT_LEFT) && !Hit)
		{
			//ジャンプしていないなら
			if (PushJump == false)
			{
				animCounter++;
			}
			velX = 5;

			//氷の床なら
			if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 9 ||
				scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 10)
			{
				if (Accel < 7)
					Accel += 0.3;
			}
			Rightward = false;
		}
		/*左移動*/
		//どちらでもない
		else
		{
			//敵にも当たっていない
			if (!Hit)
			{
				animCounter = 0;
			}

			velX = 0;
			pattern = 0 * 120;
			Attacking = false;
		}

		//攻撃用のキーが押されていないなら
		if (!CheckHitKey(KEY_INPUT_X))
		{
			Attacking = false;
		}
		/*自機操作*/

		/*落下*/
		if (!jumping)
		{
			velY += G;
		}
		/*落下*/

		/*移動*/
		//右向きのとき
		if (Rightward)
		{
			TempX += velX;
			if (Accel > 0)
			{
				TempX += Accel;
				Accel -= 0.1;
			}
		}
		else
		{
			TempX -= velX;

			if (Accel > 0)
			{
				TempX -= Accel;
				Accel -= 0.1;
			}
		}
		/*移動*/

		/*端まで行ったら反対から*/
		if (TempX > 1024)
		{
			TempX = -68;
		}
		if (TempX < -68)
		{
			TempX = 1024;
		}
		/*端まで行ったら反対から*/

		/*画面外に落ちたら*/
		if (TempY > 900)
		{
			if (BonusStage)
			{
				Failed = true;
			}
			else
			{
				if (Life > 0)
				{
					if (Hit)
					{
						RestTime = 60;
						TempX = 50;
						Life--;
						Hit = false;
					}
					TempY = RefY;
				}
				else if (Life <= 0)
				{
					if (OverY > 100)
					{
						OverY -= 5;
					}
				}
			}
		}
		/*画面外に落ちたら*/

		/*無敵時間*/
		if (RestTime > 0)
		{
			RestTime--;
		}

		if (Hit == true)
		{
			velX = 0;
			Accel = 0;
			animCounter++;
			TempY += 4;
		}
		/*無敵時間*/

		/*ジャンプ*/
		if (jumping == true)
		{
			if (TempY >= beforeJump - 220)
			{
				TempY -= 10;
			}
			else
			{
				jumping = false;
			}
		}
		/*ジャンプ*/


		/*ブロックとの当たり判定*/
		for (int i = 0; i < 7; i += 3)
		{
			/*敵に当たってなくて*/
			if (!Hit)
			{
				//足元の当たり判定
				if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 4 + i ||
					scene->Getmap()->MapChip[150 - (33 - ((TempY + 20 + PHeight) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 3 + i)	
				{
					if (reverse == false)
					{
						reverse = true;
						TempY -= velY;
					}

					/*スクロール*/
					if (ScrollCount < 6 || ScrollCount > 7)
					{
						if (TempY + 20 + PHeight < 410)
						{
							if (!Scrolling)
							{
								ScrollCount++;
								Scrolling = true;
							}
						}

						if (TempY + 20 + PHeight < 603)
						{
							if (Scrolling)
							{
								/*マップ*/
								for (int y = MapY - 1; y > 6; y--)
								{
									for (int x = 0; x < MapX; x++)
									{
										scene->Getmap()->MapChip[y][x] = scene->Getmap()->MapChip[y - 1][x];
									}
								}
								/*マップ*/

								/*アザラシ*/
								for (int i = 0; i < 6; i++)
								{
									scene->Getseal()->y[i] += BHeight;
									scene->Getseal()->RefY[i] += BHeight;
									scene->Getseal()->iceY[i] += BHeight;
									/*壁*/
									scene->Getwall()->LeftY[i] += BHeight;
									scene->Getwall()->RightY[i] += BHeight;
									/*壁*/
								}
								/*アザラシ*/

								for (int i = 0; i < 2; i++)
								{
									scene->Getcloud()->y[i] += BHeight;
								}

								for (int i = 0; i < 4; i++)
								{
									scene->Geteggplant()->y[i] += BHeight;
								}

								for (int i = 0; i < 8; i++)
								{
									scene->Getfloor()->LeftY[i] += BHeight;
									scene->Getfloor()->RightY[i] += BHeight;
								}

								TempY += BHeight;	//自機
								scene->Getknitpicker()->RefY += BHeight;	//鳥
								scene->Getknitpicker()->y += BHeight;		//鳥
								scene->Getwhitebear()->AppearCount = 2100;	//シロクマ
								scene->Getwhitebear()->moveCount = 620;	//シロクマ
								scene->Getwhitebear()->y += BHeight;
								scene->Getwall()->LeftY[6] += BHeight;
								scene->Getwall()->RightY[6] += BHeight;
								scene->Getcondor()->y += BHeight;
								scene->Gettimer()->y += BHeight;
								scene->Gettimer()->y2 += BHeight;
								RefY = 599;
							}
						}
						else
						{
							Scrolling = false;
						}
					}
					else if (ScrollCount == 6)
					{
						if (TempY + 20 + PHeight < 125)
						{
							ScrollCount++;
							BonusStage = true;
							Scrolling = true;
						}
					}
					else if (ScrollCount == 7)
					{
						if (TempY + 20 + PHeight < 819)
						{
							if (Scrolling)
							{
								/*マップ*/
								for (int y = MapY - 1; y > 6; y--)
								{
									for (int x = 0; x < MapX; x++)
									{
										scene->Getmap()->MapChip[y][x] = scene->Getmap()->MapChip[y - 1][x];
									}
								}
								/*マップ*/

								/*アザラシ*/
								for (int i = 0; i < 6; i++)
								{
									scene->Getseal()->alive[i] = false;
									scene->Getseal()->iceExist[i] = false;
									/*壁*/
									scene->Getwall()->LeftY[i] += BHeight;
									scene->Getwall()->RightY[i] += BHeight;
									/*壁*/
								}
								/*アザラシ*/

								/*雲*/
								for (int i = 0; i < 2; i++)
								{
									scene->Getcloud()->y[i] += BHeight;
								}
								/*雲*/

								/*ナス*/
								for (int i = 0; i < 4; i++)
								{
									scene->Geteggplant()->y[i] += BHeight;
								}
								/*ナス*/

								for (int i = 0; i < 8; i++)
								{
									scene->Getfloor()->LeftY[i] += BHeight;
									scene->Getfloor()->RightY[i] += BHeight;
								}

								TempY += BHeight;	//自機
								scene->Getknitpicker()->alive = false;	//鳥
								scene->Getwhitebear()->alive = false;	//シロクマ
								scene->Getwall()->LeftY[6] += BHeight;	//横のやつ	
								scene->Getwall()->RightY[6] += BHeight;	//横のやつ
								scene->Gettimer()->y += BHeight;	//タイマー
								scene->Gettimer()->y2 += BHeight;	//タイマー2
								scene->Getcondor()->y += BHeight;	//コンドル
								RefY = 599;	//リスポーン位置
							}
						}
						else
						{
							ScrollCount++;
							Scrolling = false;
						}
					}
					/*スクロール*/
					velY = 0;
					jumping = false;
					PushJump = false;
				}
				else
				{
					TempY += velY;
				}

				if (jumping)	//頭
				{

					if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 3 + i)	//頭
					{
						jumping = false;
					}

					if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 4 + i)	//頭
					{
						jumping = false;
						scene->Getresult()->HaveBlock++;
						/*ブロックを壊す*/
						scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] = 0;
						/*ブロックを壊す*/
					}

					if (scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] == 5 + i)	//頭
					{
						if (TempY < 10 + scene->Getmap()->MY[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth])
						{
							jumping = false;
							scene->Getresult()->HaveBlock++;
							scene->Getmap()->MapChip[150 - (33 - ((TempY + 20) / BHeight))][(TempX + 20 + (PWidth / 2)) / BWidth] = 0;
						}
					}
				}
			}
			/*敵に当たってなくて*/
		}
		/*ブロックとの当たり判定*/

		/*雲との当たり判定*/
		int cx[2] = { scene->Getcloud()->x[0],scene->Getcloud()->x[1] };
		int cy[2] = { scene->Getcloud()->y[0],scene->Getcloud()->y[1] };
		if (scene->Getcloud()->Collision(TempX + 20, TempY + 20, PWidth, PHeight, cx[0], cy[0]))
		{
			if (TempY + 20 - 1 < cy[0] + CloudHeight)
			{
				jumping = false;
			}

			if (TempY + 20 + PHeight < cy[0] + CloudHeight)
			{
				TempX++;
				PushJump = false;
				/*if (!velY == 0)
				{
					TempY -= velY;
				}*/
				if (reverse == false)
				{
					reverse = true;
					TempY -= velY;
				}
				velY = 0;
			}
		}

		if (scene->Getcloud()->Collision(TempX + 20, TempY + 20, PWidth, PHeight, cx[1], cy[1]))
		{
			if (TempY + 20 - 1 < cy[1] + CloudHeight)
			{
				jumping = false;
			}

			if (TempY + 20 + PHeight < cy[1] + CloudHeight)
			{
				TempX--;
				PushJump = false;
				/*if (!velY == 0)
				{
					TempY -= velY;
				}*/
				if (reverse == false)
				{
					reverse = true;
					TempY -= velY;
				}
				//velY = 0;
			}
		}
		/*雲との当たり判定*/

		/*コンドルの当たり判定*/
		if (scene->Getcondor()->Collision(TempX + 20, TempY + 20, PWidth, PHeight))
		{
			WaitTimer(5000);
			Clear = true;
			scene->Getresult()->score += 3000;
		}
		/*コンドルの当たり判定*/

		/*ナスとの当たり判定*/
		int ex[4], ey[4];
		if (BonusStage)
		{

			for (int i = 0; i < 4; i++)
			{
				ex[i] = scene->Geteggplant()->x[i];
				ey[i] = scene->Geteggplant()->y[i];
				if (scene->Geteggplant()->collision(TempX + 20, TempY + 20, PWidth, PHeight, ex[i], ey[i]))
				{
					if (scene->Geteggplant()->exist[i])
					{
						scene->Geteggplant()->exist[i] = false;
						scene->Getresult()->HaveEgg++;
					}
				}
			}
		}
		/*ナスとの当たり判定*/

		if (!BonusStage)
		{
			/*アザラシ?との当たり判定*/
			for (int i = 0; i < 6; i++)
			{
				int sx[6];
				int sy[6];
				bool sHit[6];

				sx[i] = scene->Getseal()->x[i];
				sy[i] = scene->Getseal()->y[i];
				sHit[i] = scene->Getseal()->Hit[i];
				/*ハンマーとアザラシ*/
				if (Attacking)
				{
					if (scene->Getseal()->Collision(HummerX, TempY, HummerWidth, 108, sx[i], sy[i], sHit[i]))
					{
						if (x > sx[i] && !scene->Getseal()->HummerLeft[i] && !scene->Getseal()->HummerRight[i])
						{
							scene->Getseal()->HummerRight[i] = true;
						}
						if (x < sx[i] && !scene->Getseal()->HummerLeft[i] && !scene->Getseal()->HummerRight[i])
						{
							scene->Getseal()->HummerLeft[i] = true;
						}

						scene->Getseal()->Hit[i] = true;
						sHit[i] = true;

					}
				}
				/*ハンマーとアザラシ*/

				/*ポポとアザラシ*/
				if (RestTime <= 0)
				{
					if (x > 128 && x + PWidth < 896)
					{
						if (scene->Getseal()->Collision(TempX + 20, TempY + 20, PWidth, PHeight, sx[i], sy[i], sHit[i]))
						{
							if (!Hit)
							{
								WaitTimer(500);
								Hit = true;
							}
						}
					}
				}
				/*ポポとアザラシ*/
			}
			/*アザラシ?との当たり判定*/

			/*ハンマーと鳥*/
			if (Attacking || jumping)
			{
				if (scene->Getknitpicker()->Collision(HummerX, HummerY, HummerWidth, HummerHeight))
				{
					scene->Getknitpicker()->Hit = true;
					scene->Getresult()->HaveBird++;
				}
			}
			/*ハンマーと鳥*/

			/*ポポと鳥*/
			if (scene->Getknitpicker()->Collision(TempX + 20, TempY + 20, PWidth, PHeight))
			{
				if (!Hit)
				{
					WaitTimer(500);
				}
				Hit = true;
			}
			/*ポポと鳥*/

			/*氷との当たり判定*/
			int ix[8], iy[8];
			bool iexist[8];
			for (int i = 0; i < 8; i++)
			{
				ix[i] = scene->Getseal()->iceX[i];
				iy[i] = scene->Getseal()->iceY[i];
				iexist[i] = scene->Getseal()->iceExist[i];

				if (scene->Getseal()->IceCollision(TempX + 20, TempY + 20, PWidth, PHeight, ix[i], iy[i], iexist[i]))
				{
					WaitTimer(1000);
					Hit = true;
				}

				if (scene->Getseal()->IceCollision(HummerX, HummerY, HummerWidth, HummerHeight, ix[i], iy[i], iexist[i]))
				{
					scene->Getseal()->iceExist[i] = false;
					scene->Getresult()->HaveIce++;
				}
			}
			/*氷との当たり判定*/
		}
		else
		{
			/*壁との当たり判定*/
			int lwx[7], rwx[7], lwy[7], rwy[7];
			for (int i = 0; i < 7; i++)
			{
				lwx[i] = scene->Getwall()->LeftX[i];
				rwx[i] = scene->Getwall()->RightX[i];
				lwy[i] = scene->Getwall()->LeftY[i];
				rwy[i] = scene->Getwall()->RightY[i];

				if (scene->Getwall()->LeftWallCollision(TempX + 20, TempY + 20, PWidth, PHeight, lwx[i], lwy[i]))
				{
					TempX += velX;
					Rightward = true;
				}

				if (scene->Getwall()->RightWallCollision(TempX + 20, TempY + 20, PWidth, PHeight, rwx[i], rwy[i]))
				{
					TempX -= velX;
					Rightward = false;
				}
			}
			/*壁との当たり判定*/
		}


		x = TempX;
		y = TempY;

		if (!jumping)	//ジャンプしてなかったら
		{
			HummerX = TempX + (40 * Rightward) + (width * Rightward);
			HummerY = TempY;
			HummerWidth = 20;
			HummerHeight = 108;
		}
		else //ジャンプしてたら
		{
			HummerX = TempX + 20;
			HummerY = TempY - 40;
			HummerWidth = 48;
			HummerHeight = 40;
		}
	}
}

void Player::Draw()
{
	int tx = 0;

	if (!Clear && !Failed)
	{
		if (Hit)
		{
			pattern = 5 * 120;
			tx = (animCounter / 2) % 4 * 92;
		}
		else if (PushJump)
		{
			pattern = 2 * 120;
			if (animCounter < 2)
			{
				animCounter++;
			}
			tx = animCounter % 2 * 92;
		}
		else if (Attacking)
		{
			pattern = 1 * 120;
			tx = ((animCounter / 6) % 3) * 92;
		}
		else
		{
			pattern = 0 * 120;
			tx = animCounter % 4 * 92;
		}

		if (RestTime % 2 == 0)
		{
			DrawRectGraph(x, y, tx, pattern, 92, 120, image, true, Rightward);
		}

		DrawGraph(OverX, OverY, GameOverimage, true);

		if (!BonusStage)
		{
			if (Life >= 1)
			{
				DrawGraph(LifeX, LifeY, Lifeimage, true);
			}

			if (Life >= 2)
			{
				DrawGraph(LifeX + 40, LifeY, Lifeimage, true);
			}

			if (Life >= 3)
			{
				DrawGraph(LifeX + 80, LifeY, Lifeimage, true);
			}
		}
	}
}
