#include "Map.h"
#include "DxLib.h"
#include "PlayScene.h"
#include "Player.h"

/*最終更新：2020/8/30*/
//マップのソース

Map::Map(PlayScene * _scene)
{
	LoadDivGraph("data\\texture\\MapChip4.png", 12, 3, 4, BWidth, BHeight, image);

	for (int y = 0; y < MapY; y++)
	{
		for (int x = 0; x < MapX; x++)
		{
			MX[y][x] = x * BWidth;
			MY[y][x] = 900 - ((MapY - y) * BHeight);
		}
	}
}

Map::~Map()
{
}

void Map::Update()
{
	for (int y = 0; y < MapY; y++)
	{
		for (int x = 0; x < MapX; x++)
		{
			if (MY[y][x] > 900)
			{
				MapChip[y][x] = 0;
			}
		}
	}
}

void Map::Draw()
{

	for (int y = 0; y < MapY; y++)
	{
		for (int x = 0; x < MapX; x++)
		{
			DrawGraph(MX[y][x], MY[y][x], image[MapChip[y][x]], true);
		}
	}

}
