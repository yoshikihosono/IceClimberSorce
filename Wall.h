#pragma once

/*最終更新：2020/8/30*/
/*ボーナスステージの壁のソース*/

class PlayScene;

static const int WallWidth = 100;
static const int WallHeight = 204;
static const int HalfHeight = 116;


class Wall
{
public:
	Wall(PlayScene* _scene);
	~Wall();
	void Update();
	void Draw();
	bool LeftWallCollision(int px, int py, int pw, int ph,int lwx,int lwy);
	bool RightWallCollision(int px, int py, int pw, int ph,int rwx,int rwy);
	int LeftX[7], LeftY[7];		//左の壁の座標
	int RightX[7], RightY[7];	//右の壁の座標	
private:
	PlayScene* scene;
	int image;		//壁のイメージ
	int Halfimage;	//半分の壁のイメージ
};
