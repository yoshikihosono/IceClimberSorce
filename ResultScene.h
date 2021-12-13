#pragma once

/*最終更新：2020/8/30*/
/*リザルト画面のソース*/

class PlayScene;

class ResultScene
{
public:
	ResultScene(PlayScene* _scene);
	~ResultScene();
	void Update();
	void Draw();
	int score;	//スコア用変数
	int HaveEgg;	//プレイヤーがプレイ中に取ったナス用の変数
	int HaveIce;	//プレイヤーがプレイ中に壊した氷用の変数
	int HaveBird;	//プレイヤーがプレイ中に倒した鳥用の変数
	int HaveBlock;	//プレイヤーがプレイ中に壊したブロック用の変数
private:
	PlayScene* scene;
	int Clearimage[5];	//クリア画面のイメージ用変数
	int Failedimage[5];	//失敗画面のイメージ用変数
	int Playerimage, PlayerX, PlayerY;	//プレイヤーイメージ用変数
	int AnimCounter;	//プレイヤーのアニメーション用変数
	int EggCounter;			//ナスカウンター
	int EggCounterOne;		//ナスカウンターの1の位
	int EggCounterTen;		//ナスカウンターの10の位
	int IceCounter;			//破壊した氷用カウンター
	int IceCounterOne;		//破壊した氷用カウンターの1の位
	int IceCounterTen;		//破壊した氷用カウンターの10の位
	int BirdCounter;		//倒した鳥用カウンター
	int BirdCounterOne;		//倒した鳥用カウンターの1の位
	int BirdCounterTen;		//倒した鳥用カウンターの10の位
	int BlockCounter;		//破壊したブロック用カウンター
	int BlockCounterOne;	//破壊したブロック用カウンターの1の位
	int BlockCounterTen;	//破壊したブロック用カウンターの10の位
	bool EggCalculation;	//プレイ画面でとったナスの数
	bool IceCalculation;	//プレイ画面で破壊した氷の数
	bool BirdCalculation;	//プレイ画面で倒した鳥の数
	bool BlockCaculation;	//プレイ画面で破壊したブロックの数
	int ScoreOne;			//スコア1の位
	int ScoreTen;			//スコア10の位
	int ScoreHun;			//スコア100の位
	int ScoreSau;			//スコア1000の位
	int ScoreTenSau;		//スコア10000の位
	int ScoreHunSau;		//スコア100000の位
	int NumImage[10];		//数字のイメージ用変数
};