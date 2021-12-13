#pragma once

/*最終更新：2020/8/30*/
/*アザラシのソース*/

class PlayScene;

static const int width = 32;
static const int height = 31;
static const int MaxSeal = 6;

static const int iceWidth = 30;
static const int iceHeight = 36;

class Seal
{
public:
	Seal(PlayScene* _scene);
	~Seal();
	void Update();
	void Draw();
	bool Collision(int px, int py, int pw, int ph, int sx, int sy, bool sHit);
	bool IceCollision(int px, int py, int pw, int ph, int ix, int iy,int iexist);
private:
	PlayScene* scene;
	int image;	//アザラシのイメージ用変数
	int iceimage;	//氷のイメージ用変数
	int pattern[MaxSeal];		//アニメーションY軸用カウンター
	int animCounter[MaxSeal];	//アニメーションX軸用カウンター
	int spawn;
public:
	int x[MaxSeal], y[MaxSeal];	//アザラシの座標
	int RefY[MaxSeal];	//アザラシが復帰するときに使うY
	int iceX[MaxSeal], iceY[MaxSeal];	//氷の座標
	bool iceExist[MaxSeal];	//氷が存在してたらtrue
	bool rightward[MaxSeal];	//左向いてたらtrue
	bool alive[MaxSeal];	//生きてたらtrue
	bool Hit[MaxSeal];	//ハンマーに殴られたらtrue
	bool HummerRight[MaxSeal];	//ハンマーに右から殴られたらtrue
	bool HummerLeft[MaxSeal];	//ハンマーに左から殴られたらtrue
	bool FindHole[MaxSeal];	//穴を発見したらtrue
	bool Falling[MaxSeal];	//落下中ならtrue
	int Count[MaxSeal];	//出現するときのカウンター
};