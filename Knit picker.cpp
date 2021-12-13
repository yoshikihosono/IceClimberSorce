#include "Knit picker.h"
#include "DxLib.h"
#include "time.h"
#include "assert.h"

/*最終更新：2020/8/30*/
/*鳥のソース*/

Knitpicker::Knitpicker(PlayScene * _scene)
{
	image = LoadGraph("data\\texture\\Knitpicker.png");
	RefY = -320;
	x = 0.0f;
	y = RefY;
	alive = false;
	Hit = false;
	Count = 30;
	MoveCounter = 0;
	animCounter = 0;
	spawn = 0;
}

Knitpicker::~Knitpicker()
{
}

void Knitpicker::Update()
{
	srand((unsigned int)time(NULL));

	if (RefY > 0)
	{
		if (!alive)
		{
			if (Count <= 0)
			{
				spawn = rand() % 2;	//左右どっちから出るか決めます
				x = 1024 * spawn;
				y = RefY;
				MoveCounter = 0;
				Hit = false;
				alive = true;	//生きさせます
				if (spawn == 0)		//生まれた場所で右向きかどうか設定するで
				{
					rightward = true;
				}
				else
				{
					rightward = false;
				}
			}
		}
		else
		{
			if (!Hit)	//殴られてなくて
			{
				if (spawn == 0)	//右向きなら
				{
					/*移動制御*/
					if (MoveCounter < 150 || MoveCounter > 170 && MoveCounter < 190 || MoveCounter > 840)
					{
						y += 1.25f;
					}

					if (MoveCounter > 150 && MoveCounter < 170)
					{
						y -= 0.75;
					}

					if (MoveCounter > 190 && MoveCounter < 400)
					{
						y += 0.5;
					}

					if (MoveCounter > 400 && MoveCounter < 620)
					{
						y -= 0.5;
					}

					if (MoveCounter > 650 && MoveCounter < 840)
					{
						y -= 1.25f;
					}

					if (MoveCounter < 150 || MoveCounter > 180 && MoveCounter < 620)
					{
						x += 1.5f;
					}

					if (MoveCounter > 670)
					{
						x -= 2.0f;
					}

					if (MoveCounter == 620)
					{
						rightward = false;
					}

					if (MoveCounter == 1000)
					{
						MoveCounter = 150;
						rightward = true;
					/*移動制御*/
					}


					animCounter++;
					MoveCounter++;
				}
				else if(spawn == 1)	//左向きなら
				{
					/*移動制御*/
					if (MoveCounter < 150 || MoveCounter > 170 && MoveCounter < 190 || MoveCounter > 840)
					{
						y += 1.25f;
					}

					if (MoveCounter > 150 && MoveCounter < 170)
					{
						y -= 0.75;
					}

					if (MoveCounter > 190 && MoveCounter < 400)
					{
						y += 0.5;
					}

					if (MoveCounter > 400 && MoveCounter < 620)
					{
						y -= 0.5;
					}

					if (MoveCounter > 650 && MoveCounter < 840)
					{
						y -= 1.25f;
					}

					if (MoveCounter < 150 || MoveCounter > 180 && MoveCounter < 620)
					{
						x -= 1.5f;
					}

					if (MoveCounter > 670)
					{
						x += 2.0f;
					}

					if (MoveCounter == 620)
					{
						rightward = true;
					}

					if (MoveCounter == 1000)
					{
						MoveCounter = 150;
						rightward = false;
					}
					/*移動制御*/


					animCounter++;
					MoveCounter++;
				}

			}
			else
			{
				y += 3;
			}
		}
	}

	if (y > 900)
	{
		alive = false;
		Count = 300;
	}

	Count--;
}

//描画
void Knitpicker::Draw()
{
	int tx;

	if (Hit)	//殴られたら
	{
		tx = 0 * 60;
		pattern = 1 * 60;
	}
	else
	{
		tx = (animCounter / 6) % 2 * 60;
		pattern = 0;
	}


	if (alive)	//生きているなら
		DrawRectGraph(x, y, tx, pattern, 60, 60, image, true, rightward);
}

//当たり判定
bool Knitpicker::Collision(int px, int py, int pw, int ph)
{
	if (!Hit)
	{
		if (px > x + Knitwidth)
		{
			return false;
		}


		if (px + pw < x)
		{
			return false;
		}

		if (py > y + Knitheight)
		{
			return false;
		}

		if (py + ph < y)
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
