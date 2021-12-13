#pragma once

/*最終更新：2020/8/30*/
/*鳥のソース*/

class PlayScene;

static const int Knitwidth = 60;
static const int Knitheight = 60;

class Knitpicker
{
public:
	Knitpicker(PlayScene* _scene);
	~Knitpicker();
	void Update();
	void Draw();
	bool Collision(int px, int py, int pw, int ph);	//当たり判定
private:
	int image;	//画像ハンドラ
	int animCounter;	//X軸アニメーション用カウンター
	int pattern;		//アニメーションY軸用カウンター
public:
	bool alive;	//生きてたらtrue
	float x, y;	//鳥の座標
	int RefY;	//復活するときに参照する座標
	int MoveCounter;	//移動を管理するカウンター
	int Count;	//復活するまでの時間
	int spawn;	//生まれる位置
	bool Hit;	//ハンマーに殴られたらtrue
	bool rightward;	//右向いてたらtrue
};
