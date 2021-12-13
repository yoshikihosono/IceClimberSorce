#include "Wall.h"
#include "PlayScene.h"
#include "Map.h"
#include "DxLib.h"

/*最終更新：2020/8/30*/
/*ボーナスステージの壁のソース*/

Wall::Wall(PlayScene* _scene)
{
	scene = _scene;
	for (int i = 0; i < 6; i++)
	{
		LeftX[i] = 0 + (BWidth * i);
		LeftY[i] = -1059 - (WallHeight * i);
		RightX[i] = 1024 - WallWidth - (BWidth * i);
		RightY[i] = -1059 - (WallHeight * i);
	}
	
	LeftX[6] = 0 + (BWidth * 6);
	LeftY[6] = LeftY[5] - HalfHeight;
	RightX[6] = 1024 - WallWidth - (BWidth * 6);
	RightY[6] = RightY[5] - HalfHeight;

	image = LoadGraph("data\\texture\\Wall.png");
	Halfimage = LoadGraph("data\\texture\\Halfwall.png");
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
	for (int i = 0; i < 6; i++)
	{
		DrawGraph(LeftX[i], LeftY[i], image, true);
		DrawGraph(RightX[i], RightY[i], image, true);
	}
	DrawGraph(LeftX[6], LeftY[6], Halfimage, true);
	DrawGraph(RightX[6], RightY[6], Halfimage, true);
}

bool Wall::LeftWallCollision(int px, int py, int pw, int ph, int lwx, int lwy)
{
	if (px > lwx + WallWidth)
	{
		return false;
	}


	if (px + pw < lwx)
	{
		return false;
	}

	if (py > lwy + WallHeight)
	{
		return false;
	}



	if (py + ph < lwy)
	{
		return false;
	}

	return true;
}

bool Wall::RightWallCollision(int px, int py, int pw, int ph, int rwx, int rwy)
{
	if (px > rwx + WallWidth)
	{
		return false;
	}


	if (px + pw < rwx)
	{
		return false;
	}

	if (py > rwy + WallHeight)
	{
		return false;
	}



	if (py + ph < rwy)
	{
		return false;
	}

	return true;
}
