#pragma once

/*最終更新：2020/8/30*/
/*アイテム：ナスのソース*/

class PlayScene;

static const int EggWidth = 40;
static const int EggHeight = 53;

class Eggplant
{
public:
	Eggplant(PlayScene* _scene);
	~Eggplant();
	void Draw();
	bool collision(int px,int py,int pw,int ph,int ex,int ey);
	int x[4], y[4];
	int exist[4];
private:
	int image;
	PlayScene* scene;
};