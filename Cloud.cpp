#include "Cloud.h"
#include "DxLib.h"
#include "PlayScene.h"
#include "Player.h"

/*最終更新：2020/8/30*/
/*雲のソース*/

Cloud::Cloud(PlayScene * _scene)
{
	x[0] = 0 - CloudWidth;
	x[1] = 1024;
	y[0] = -1167;
	y[1] = -1610;
	image = LoadGraph("data\\texture\\Cloud.png");
}

Cloud::~Cloud()
{
}

void Cloud::Update()
{
		x[0]++;
		x[1]--;

		if (x[0] > 1024)
		{
			x[0] = 0;
		}

		if (x[1] < 0 - CloudWidth)
		{
			x[1] = 1024;
		}
}

void Cloud::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(x[i], y[i], image, true);
	}
}

bool Cloud::Collision(int px, int py, int pw, int ph, int cx, int cy)
{
	if (px > cx + CloudWidth)
	{
		return false;
	}

	if (px + pw < cx)
	{
		return false;
	}

	if (py > cy + CloudHeight)
	{
		return false;
	}

	if (py + ph < cy)
	{
		return false;
	}

	return true;
}
