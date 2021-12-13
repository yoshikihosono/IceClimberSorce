#include "Seal.h"
#include "DxLib.h"
#include "PlayScene.h"
#include "Map.h"
#include "time.h"
#include "Player.h"

/*最終更新：2020/8/30*/
/*アザラシのソース*/

Seal::Seal(PlayScene * _scene)
{
	scene = _scene;
	image = LoadGraph("data\\texture\\Seal2.png");
	iceimage = LoadGraph("data\\texture\\Ice.png");

	for (int i = 0; i < MaxSeal; i++)
	{
		pattern[i] = 0;
		RefY[i] = 760 - i * 432;
		y[i] = RefY[i];
		x[i] = 50;
		iceY[i] = 0;
		iceX[i] = 0;
		rightward[i] = false;
		alive[i] = false;
		Hit[i] = false;
		HummerRight[i] = false;
		HummerLeft[i] = false;
		FindHole[i] = false;
		iceExist[i] = false;
		Count[i] = 30;
	}

	RefY[3] = -320;
	RefY[4] = -536;
	RefY[5] = -750;

}

Seal::~Seal()
{
}

void Seal::Update()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MaxSeal; i++)
	{
		if (!scene->Getplayer()->BonusStage)	//ボーナスステージじゃなくて
		{
			if (RefY[i] > 0)	//画面内に居て
			{
				if (!alive[i])	//生きてなくて
				{
					if (Count[i] < 0)	//カウントが0より小さいなら
					{
						spawn = rand() % 2;	//左右どっちから出るか決めます
						x[i] = 50 + (spawn * 900);
						y[i] = RefY[i];
						if (spawn == 0)		//生まれた場所で右向きかどうか設定するで
						{
							rightward[i] = true;
						}
						else
						{
							rightward[i] = false;
						}
						alive[i] = true;	//生きさせます
					}
				}
				else		//生きてて
				{
					if (!Hit[i])	//殴られてなくて
					{
						if (rightward[i])	//右向きなら
						{
							if (!scene->Getmap()->MapChip[150 - (32 - ((y[i] + height) / 27))][(x[i] + width) / 32] == 0)
							{
								if (FindHole[i] || iceExist[i])
								{
									x[i] += 2;
									animCounter[i] += 2;
								}
								else
								{
									x[i]++;
									animCounter[i]++;
								}

							}

						}
						else
						{
							if (!scene->Getmap()->MapChip[150 - (32 - ((y[i] + height) / 27))][(x[i] + width) / 32] == 0)
							{
								if (FindHole[i] || iceExist[i])
								{
									x[i] -= 2;
									animCounter[i] += 2;
								}
								else
								{
									x[i]--;
									animCounter[i]++;
								}

							}
						}
					}
					else
					{
						if (!Falling[i])
						{
							if (HummerRight[i])
							{
								x[i] -= 2;
							}

							if (HummerLeft[i])
							{
								x[i] += 2;
							}
						}
						animCounter[i]++;

					}
				}

				/*ハンマーで殴られた後に穴を見つけたら*/
				if (scene->Getmap()->MapChip[150 - (32 - ((y[i] + height) / 27))][(x[i] + width) / 32] == 0)
				{
					y[i] += 5;
					Falling[i] = true;
					Hit[i] = true;
					HummerRight[i] = true;
					HummerLeft[i] = false;
				}
				else
				{
					Falling[i] = false;
				}
				/*ハンマーで殴られた後に穴を見つけたら*/

				/*穴を発見するやつ*/
				if (rightward[i])
				{
					if (scene->Getmap()->MapChip[150 - (32 - ((y[i] + height + 1) / 27))][(x[i] + width + 1) / 32] == 0)	//進んだ1マス先が0なら
					{
						if (!FindHole[i] || Hit[i])
						{
							rightward[i] = false;
							FindHole[i] = true;
						}
					}
				}
				else
				{
					if (scene->Getmap()->MapChip[150 - (32 - ((y[i] + height + 1) / 27))][(x[i] - 1) / 32] == 0)
					{
						if (!FindHole[i] || Hit[i])
						{
							rightward[i] = true;
							FindHole[i] = true;
						}
					}
				}
				/*穴を発見するやつ*/
			}
		}
		else
		{
			alive[i] = false;
		}

		Count[i]--;

		/*端っこまでいったら*/
		if (x[i] < 0)
		{
			if (Falling[i] || Hit[i])
			{
				Count[i] = 120;
				alive[i] = false;
				FindHole[i] = false;
				Falling[i] = false;
				HummerLeft[i] = false;
				HummerRight[i] = false;
				Hit[i] = false;
			}
			else if (FindHole[i])
			{
				rightward[i] = true;
				iceExist[i] = true;
				FindHole[i] = false;
				iceY[i] = y[i] + 25;
				iceX[i] = x[i] + width + iceWidth;
			}
			else
			{
				x[i] = 1024;
			}
		}

		if (x[i] > 1024)
		{
			if (Falling[i] || Hit[i])
			{
				alive[i] = false;
				Count[i] = 120;
				FindHole[i] = false;
				Falling[i] = false;
				HummerLeft[i] = false;
				HummerRight[i] = false;
				Hit[i] = false;
			}
			else if (FindHole[i])
			{
				rightward[i] = false;
				iceExist[i] = true;
				FindHole[i] = false;
				iceY[i] = y[i] + 25;
				iceX[i] = x[i] - iceWidth + 3;
			}
			else
			{
				x[i] = 0;
			}
		}
		/*端っこまでいったら*/

		/*氷関係*/
		if (iceExist[i])
		{
			if (rightward[i])
			{
				iceX[i] += 2;


				if (scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] + iceWidth + 1) / 32] == 0)	//進んだ1マス先が0なら
				{
					if (i == 0)
					{
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] + iceWidth + 1) / 32] = 4;
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][((iceX[i] + iceWidth + 1) / 32) + 1] = 4;
						iceExist[i] = false;
					}

					if (i == 1 || i == 2)
					{
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] + iceWidth + 1) / 32] = 7;
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][((iceX[i] + iceWidth + 1) / 32) + 1] = 7;
						iceExist[i] = false;
					}

					if (i == 3 || i == 4 || i == 5)
					{
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] + iceWidth + 1) / 32] = 10;
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][((iceX[i] + iceWidth + 1) / 32) + 1] = 10;
						iceExist[i] = false;
					}
				}
			}
			else
			{
				iceX[i] -= 2;

				if (scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] - 1) / 32] == 0)	//進んだ1マス先が0なら
				{
					if (i == 0)
					{
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] - 1) / 32] = 4;
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][((iceX[i] - 1) / 32) - 1] = 4;
						iceExist[i] = false;
					}

					if (i == 1 || i == 2)
					{
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] - 1) / 32] = 7;
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][((iceX[i] - 1) / 32) - 1] = 7;
						iceExist[i] = false;
					}

					if (i == 3 || i == 4 || i == 5)
					{
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][(iceX[i] - 1) / 32] = 10;
						scene->Getmap()->MapChip[150 - (33 - ((iceY[i] + iceHeight + 1) / 27))][((iceX[i] - 1) / 32) - 1] = 10;
						iceExist[i] = false;
					}
				}
			}
		}
		/*氷関係*/
	}
}

void Seal::Draw()
{
	int tx[MaxSeal] = { 0,0,0,0,0,0 };

	for (int i = 0; i < MaxSeal; i++)
	{
		if (Hit[i])
		{
			tx[i] = 0;
			pattern[i] = 1 * 60;
			rightward[i] = (animCounter[i] / 12) % 2;
		}
		else
		{
			tx[i] = (animCounter[i] / 6) % 3 * 60;
			pattern[i] = 0 * 60;
		}

		if (alive[i])
			DrawRectGraph(x[i], y[i], tx[i], pattern[i], 60, 59, image, true, rightward[i]);

		if (iceExist[i])
			DrawGraph(iceX[i], iceY[i], iceimage, true);
	}
}

bool Seal::Collision(int px, int py, int pw, int ph, int sx, int sy, bool sHit)
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

bool Seal::IceCollision(int px, int py, int pw, int ph, int ix, int iy,int iexist)
{
	if (iexist)
	{
		if(px > ix + iceWidth)
		{
			return false;
		}


		if (px + pw < ix)
		{
			return false;
		}

		if (py > iy + iceHeight)
		{
			return false;
		}

		if (py + ph < iy)
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
