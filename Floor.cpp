#include "Floor.h"
#include "DxLib.h"

/*最終更新：2020/8/30*/
/*背景の横にある数字書いてある壁*/

Floor::Floor(PlayScene* _scene)
{
	for (int i = 0; i < 8; i++)
	{
		LeftY[i] = 630 - (216 * i);
		RightY[i] = 630 - (216 * i);
	}
	LeftX = 0;
	RightX = 1024 - 189;
	Leftimage = LoadGraph("data\\texture\\Floorleft.png");
	Rightimage = LoadGraph("data\\texture\\Flooright.png");
}

Floor::~Floor()
{
}

void Floor::Update()
{
}

void Floor::Draw()
{
	for (int i = 0; i < 8; i++)
	{
		DrawRectGraph(LeftX, LeftY[i], 0, 189 * i, 192, 189, Leftimage, true, false);
		DrawRectGraph(RightX, RightY[i], 0, 189 * i, 192, 189, Rightimage, true, false);
	}
}
