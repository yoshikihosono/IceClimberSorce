#include "Whitebear.h"
#include "Player.h"
#include "DxLib.h"
#include "assert.h"
#include "PlayScene.h"
#include "Map.h"
#include "Seal.h"
#include "Knit picker.h"
#include "Wall.h"
#include "Cloud.h"
#include "Timer.h"
#include "Condor.h"
#include "Eggplant.h"
#include "Floor.h"
#include "app.h"

/*最終更新：2020/8/30*/
/*シロクマのソース*/

Whitebear::Whitebear(PlayScene * _scene)
{
	scene = _scene;
	image = LoadGraph("data\\texture\\Whitebare.png");
	x = 0;
	y = 0;
	RefY = 65;
	alive = false;
	action = false;
	rightward = true;
	AppearCount = 2100;
}

Whitebear::~Whitebear()
{
}

void Whitebear::Update()
{
	//ボーナスステージじゃなくて
	if (!scene->Getplayer()->BonusStage)
	{
		//生きてなくて
		if (!alive)
		{
			//プレイヤーのY値がアザラシ6体目の復帰位置より高くて
			if (scene->Getplayer()->y > scene->Getseal()->RefY[5])
			{
				//出現するまでのカウントが0未満なら
				if (AppearCount < 0)
				{
					y = RefY;	
					x = 0 - bearWidth;
					alive = true;
					rightward = true;
				}
			}
		}
		//生きてて
		else
		{
			//1マス先が地面で
			if (!scene->Getmap()->MapChip[150 - (33 - ((y + bearHeight) / 27))][(x + bearWidth) / 32] == 0)
			{
				//アクションしてなくて
				if (!action)
				{
					//右向きなら
					if (rightward)
					{
						x++;
						moveCount++;
						animCounter++;
					}
					//左向きなら
					else
					{
						x--;
						moveCount++;
						animCounter++;
					}
				}
				//アクションフラグがtrueなら
				else
				{
					moveCount++;

					/*疑似ジャンプ*/
					if (moveCount > 600 && moveCount < 605)
					{
						y--;
					}

					if (moveCount > 605 && moveCount < 610)
					{
						y++;
					}
					/*疑似ジャンプ*/

					/*画面内外の物すべてを下げる*/
					if (moveCount > 610)
					{
						/*マップ*/
						for (int y = MapY - 1; y > 6; y--)
						{
							for (int x = 0; x < MapX; x++)
							{
								scene->Getmap()->MapChip[y][x] = scene->Getmap()->MapChip[y - 8][x];
							}
						}
						/*マップ*/

						/*アザラシ*/
						for (int i = 0; i < 6; i++)
						{
							scene->Getseal()->y[i] += 216;
							scene->Getseal()->RefY[i] += 216;
							scene->Getseal()->iceY[i] += 216;
							/*壁*/
							scene->Getwall()->LeftY[i] += 216;
							scene->Getwall()->RightY[i] += 216;
							/*壁*/
						}
						/*アザラシ*/

						/*雲*/
						for (int i = 0; i < 2; i++)
						{
							scene->Getcloud()->y[i] += 216;
						}
						/*雲*/

						/*ナス*/
						for (int i = 0; i < 4; i++)
						{
							scene->Geteggplant()->y[i] += 216;
						}
						/*ナス*/

						/*背景のやつ*/
						for (int i = 0; i < 8; i++)
						{
							scene->Getfloor()->LeftY[i] += 216;
							scene->Getfloor()->RightY[i] += 216;
						}
						/*背景のやつ*/

						scene->Getplayer()->TempY += 216;		//プレイヤー
						scene->Getknitpicker()->RefY += 216;	//鳥
						scene->Getknitpicker()->y += 216;		//鳥
						y += 216;	//シロクマ自身
						scene->Getwall()->LeftY[6] += 216;	//ボーナスステージの壁
						scene->Getwall()->RightY[6] += 216;	//ボーナスステージの壁
						scene->Getcondor()->y += 216;	//コンドル
						scene->Gettimer()->y += 216;	//タイマー
						scene->Gettimer()->y2 += 216;	//タイマー2
						scene->Getplayer()->ScrollCount++;	//プレイヤーのスクロール回数を1増やす
						action = false;	//アクションフラグをfalseに
						moveCount = 620;	//移動用カウントを620に固定
						AppearCount = 2500;	//出現するまでのカウントを2500に
					}
					/*画面内外の物すべてを下げる*/
				}
			}
			//1マス先が地面じゃない
			else
			{
				if (!hit)
				{
					//右向きなら
					if (rightward)
					{
						rightward = false;
						x -= 10;
					}
					//左向きなら
					else
					{
						rightward = true;
					}
				}
				//殴られたら
				else
				{
					y++;
				}
			}
		}
	}
	//ボーナスステージなら
	else
	{
		alive = false;	//ころす
	}

	//左端に行ったら
	if (x < 0 - bearWidth)
	{
		//movecountが620以上なら
		if (moveCount > 620)
		{
			alive = false;	//ころす
		}
		else
		{
			x = 1024;	//右端に
		}
	}

	//右端にいて
	if (x > 1024)
	{
		//movecountが620以上なら
		if (moveCount > 620)
		{
			alive = false;	//ころす
		}
		else
		{
			x = 0 - bearWidth;	//左端に
		}
	}

	//movecountが600なら
	if (moveCount == 600)
	{
		action = true;	//ジャンプアクションをtrueに
	}

	AppearCount--;
}

void Whitebear::Draw()
{
	int tx;

	if (hit)
	{
		tx = 0;
		pattern = 1 * bearHeight;
	}
	else
	{
		tx = animCounter % 3 * bearWidth;
		pattern = 0 * bearHeight;
	}

	if (alive)
		DrawRectGraph(x, y, tx, pattern, bearWidth, bearHeight, image, true, rightward);
}

bool Whitebear::Collision(int px, int py, int pw, int ph, int sx, int sy, bool sHit)
{
	if (!sHit)
	{
		if (px > sx + width)
		{
			return false;
		}


		if (px + pw < sx)
		{
			return false;
		}

		if (py > sy + height)
		{
			return false;
		}

		if (py + ph < sy)
		{
			return false;
		}

		return true;

	}
	else
	{
		return false;
	}
}
