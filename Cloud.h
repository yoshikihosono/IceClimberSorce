#pragma once

/*最終更新：2020/8/30*/
/*雲のソース*/

class PlayScene;

static const int CloudWidth = 149;
static const int CloudHeight = 32;

class Cloud
{
public:
	Cloud(PlayScene* _scene);
	~Cloud();
	void Update();
	void Draw();
	bool Collision(int px, int py, int pw, int ph, int cx, int cy);
	int x[2], y[2];
private:
	int image;
	PlayScene* scene;
};