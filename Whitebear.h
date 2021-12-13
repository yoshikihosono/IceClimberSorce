#pragma once

/*最終更新：2020/8/30*/
/*シロクマのソース*/

class PlayScene;

static const int bearHeight = 106;
static const int bearWidth = 57;

class Whitebear
{
public:
	Whitebear(PlayScene* _scene);
	~Whitebear();
	void Update();
	void Draw();
	bool Collision(int px, int py, int pw, int ph, int sx, int sy, bool sHit);
	int x, y;	//座標
	int AppearCount;	//出現するまでのカウント
	int moveCount;	//移動している間カウントする
	bool alive;	//生きてたらtrue
	int RefY;	//生まれる時に参照する値
private:
	PlayScene* scene;
	int image;			//シロクマイメージ用変数
	bool rightward;		//右向いてたらtrue
	bool hit;			//殴られたらtrue
	bool action;		//ジャンプアクションしたらtrue
	int pattern;		//アニメーションY軸用カウンター
	int animCounter;	//アニメーションX軸用カウンター
};