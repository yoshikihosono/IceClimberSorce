#pragma once

/*最終更新：2020/8/30*/
/*ボーナスステージのタイマーのソース*/

class PlayScene;

class Timer
{
public:
	Timer(PlayScene* _scene);
	~Timer();
	void Update();
	void Draw();
	int time;
	int x, y, y2;
	PlayScene* scene;
private:
	int image;	//タイマーの枠
	int NumImage[10];	//数字のイメージ
	int one;	//1の位用
	int ten;	//10の位用
	int hun;	//100の位用
};