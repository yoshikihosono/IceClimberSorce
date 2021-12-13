#include "Condor.h"
#include "DxLib.h"

/*最終更新：2020/8/30*/
/*コンドルのソース*/

Condor::Condor(PlayScene * _scene)
{
	x = 1024;
	y = -2575;
	image = LoadGraph("data\\texture\\Condor.png");
	animcounter = 0;
}

Condor::~Condor()
{
}

void Condor::Update()
{
	x -= 5;
	animcounter++;

	if (x < 0 - CondorWidth)
	{
		x = 1024;
	}
}

void Condor::Draw()
{
	int tx;

	tx = (animcounter / 3) % 3 * CondorWidth;

	DrawRectGraph(x, y, tx, 0, CondorWidth, CondorHeight, image, true,false);
}

bool Condor::Collision(int px, int py, int pw, int ph)
{
	if (px > x + 46 + 20)
	{
		return false;
	}

	if (px + pw < x + 46)
	{
		return false;
	}

	if (py > y + CondorHeight)
	{
		return false;
	}



	if (py + ph < y + 53)
	{
		return false;
	}

	return true;
}
