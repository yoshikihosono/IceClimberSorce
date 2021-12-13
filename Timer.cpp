#include "Timer.h"
#include "DxLib.h"
#include "PlayScene.h"
#include "Player.h"
#include "ResultScene.h"

/*最終更新：2020/8/30*/
/*ボーナスステージのタイマーのソース*/

Timer::Timer(PlayScene* _scene)
{
	image = LoadGraph("data\\texture\\Time.png");		//枠組
	NumImage[0] = LoadGraph("data\\texture\\0.png");	//0のイメージ
	NumImage[1] = LoadGraph("data\\texture\\1.png");	//1のイメージ
	NumImage[2] = LoadGraph("data\\texture\\2.png");	//2のイメージ
	NumImage[3] = LoadGraph("data\\texture\\3.png");	//3のイメージ
	NumImage[4] = LoadGraph("data\\texture\\4.png");	//4のイメージ
	NumImage[5] = LoadGraph("data\\texture\\5.png");	//5のイメージ
	NumImage[6] = LoadGraph("data\\texture\\6.png");	//6のイメージ
	NumImage[7] = LoadGraph("data\\texture\\7.png");	//7のイメージ
	NumImage[8] = LoadGraph("data\\texture\\8.png");	//8のイメージ
	NumImage[9] = LoadGraph("data\\texture\\9.png");	//9のイメージ
	x = 80;		//タイマーのX座標
	y = -1585;	//タイマーのY座標
	y2 = -2500;	//タイマーのY座標2
	time = 1200;	//時間
	one = 0;	//時間の1の位
	ten = 0;	//時間の10の位
	hun = 4;	//時間の100の位
	scene = _scene;
}

Timer::~Timer()
{

}

void Timer::Update()
{

	//ボーナスステージ中なら
	if (scene->Getplayer()->BonusStage && !scene->Getplayer()->Clear && !scene->Getplayer()->Failed)
	{
		one--;	//1の位をへらす
	}

	//1の位が0未満になったら
	if (one < 0)
	{
		one = 99;	//1の位を99に
		ten--;		//１０の位を1へらす
	}

	//10の位が0未満になったら
	if (ten < 0)
	{
		ten = 9;	//10の位を9に
		hun--;		//100の位を1へらす
	}

	//全部0になったら
	if (hun == 0 && ten == 0 && one == 0)
	{
		scene->Getplayer()->Failed = true;	//失敗フラグをtrueに
	}
}

void Timer::Draw()
{
	int tx = 0;
	int pattern = 0;

	DrawGraph(x, y, image, false);
	DrawRectGraph(x + 15, y + 50, tx, pattern, 43, 37, NumImage[hun], false, false);
	DrawRectGraph(x + 53, y + 50, tx, pattern, 43, 37, NumImage[ten], false, false);
	DrawRectGraph(x + 113, y + 50, tx, pattern, 43, 37, NumImage[one / 10], false, false);

	DrawGraph(x, y2, image, false);
	DrawRectGraph(x + 15, y2 + 50, tx, pattern, 43, 37, NumImage[hun], false, false);
	DrawRectGraph(x + 53, y2 + 50, tx, pattern, 43, 37, NumImage[ten], false, false);
	DrawRectGraph(x + 113, y2 + 50, tx, pattern, 43, 37, NumImage[one / 10], false, false);
}
