#pragma once

/*最終更新：2020/8/30*/
/*背景の横にある数字書いてある壁*/

class PlayScene;

class Floor
{
public:
	Floor(PlayScene* _scene);
	~Floor();
	void Update();
	void Draw();
	int LeftX, LeftY[8];
	int RightX, RightY[8];
private:
	int Leftimage;
	int Rightimage;
};