#pragma once

/*最終更新：2020/8/30*/
/*コンドルのソース*/

class PlayScene;

static const int CondorWidth = 112;
static const int CondorHeight = 59;

class Condor
{
public:
	Condor(PlayScene* _scene);
	~Condor();
	void Update();
	void Draw();
	bool Collision(int px,int py, int pw,int ph);
	int x, y;
private:
	int image;
	int animcounter;
};