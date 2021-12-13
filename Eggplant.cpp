#include "Eggplant.h"
#include "DxLib.h"
#include "PlayScene.h"
#include "Player.h"

/*最終更新：2020/8/30*/
/*アイテム：ナスのソース*/

Eggplant::Eggplant(PlayScene* _scene)
{
	scene = _scene;
	x[0] = 197;
	x[1] = 768;
	x[2] = 640;
	x[3] = 384;
	y[0] = -1070;
	y[1] = -1070;
	y[2] = -1392;
	y[3] = -1557;
	image = LoadGraph("data\\texture\\eggplant.png");
	for (int i = 0; i < 4; i++)
	{
		exist[i] = true;
	}
}

Eggplant::~Eggplant()
{
}

void Eggplant::Draw()
{
	if (scene->Getplayer()->BonusStage)
	{
		for (int i = 0; i < 4; i++)
		{
			if (scene->Getplayer()->BonusStage)
			{
				if (exist[i])
					DrawGraph(x[i], y[i], image, true);
			}
		}
	}
}

bool Eggplant::collision(int px, int py, int pw, int ph, int ex, int ey)
{
	if (px > ex + EggWidth)
	{
		return false;
	}

	if (px + pw < ex)
	{
		return false;
	}

	if (py > ey + EggHeight)
	{
		return false;
	}

	if (py + ph < ey)
	{
		return false;
	}

	return true;
}
