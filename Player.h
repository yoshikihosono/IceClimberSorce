#pragma once

/*最終更新：2020/8/30*/
/*プレイヤーのソース*/

class PlayScene;
class App;

static const int PWidth = 48;	//プレイヤーの横幅
static const int PHeight = 80;	//プレイヤーの高さ

class Player {
public:
	Player(PlayScene* _scene);
	~Player();
	void Update();
	void Draw();
	int x, y;	//キャラの座標
	int TempX, TempY;	//キャラの一時的座標
	int ScrollCount;	//スクロール用カウント
	bool BonusStage;	//ボーナスステージだったらtrue
	bool Clear;			//クリアしたらtrue
	bool Failed;		//ボーナスステージを失敗したらtrue
	bool Scrolling;		//スクロールしてたらtrue
	int RefY;			//復帰用のY値
	bool Hit;	//敵に当たったらtrue
private:
	float Accel;	//Xの加速度
	int image;	//画像のハンドラ
	int Life;	//残機
	int LifeX, LifeY;	//残機の座標
	int Lifeimage;	//残機の画像
	int beforeJump;		//ジャンプ前のY座標
	float velX, velY;	//速度
	int HummerX;	//ハンマーのX値
	int HummerY;	//ハンマーのY値
	int HummerWidth;	//ハンマーの横幅
	int HummerHeight;	//ハンマーの高さ
	PlayScene* scene;
	int pattern;		//アニメーションY軸用カウンター
	int animCounter;	//アニメーションX軸用カウンター
	bool Rightward;	//右向いてたらtrue
	bool jumping;	//ジャンプしてたらtrue
	bool PushJump;	//Spaceを押してたらtrue
	bool Attacking;	//攻撃してたらtrue
	int RestTime;	//復活してからの無敵時間
	int GameOverimage;	//ゲームオーバーイメージ
	int OverX, OverY;	//ゲームオーバーイメージの座標
	bool reverse = false;
};
