#include "ResultScene.h"
#include "DxLib.h"
#include "Player.h"
#include "PlayScene.h"

/*最終更新：2020/8/30*/
/*リザルト画面のソース*/

ResultScene::ResultScene(PlayScene* _scene)
{
	scene = _scene;
	Clearimage[0] = LoadGraph("data\\texture\\Clear.png");		//クリア画面のイメージ1枚目
	Clearimage[1] = LoadGraph("data\\texture\\Clear2.png");		//クリア画面のイメージ2枚目
	Clearimage[2] = LoadGraph("data\\texture\\Clear3.png");		//クリア画面のイメージ3枚目
	Clearimage[3] = LoadGraph("data\\texture\\Clear4.png");		//クリア画面のイメージ4枚目
	Clearimage[4] = LoadGraph("data\\texture\\Clear5.png");		//クリア画面のイメージ5枚目
	Failedimage[0] = LoadGraph("data\\texture\\Failed.png");	//失敗画面のイメージ1枚目
	Failedimage[1] = LoadGraph("data\\texture\\Failed2.png");	//失敗画面のイメージ2枚目
	Failedimage[2] = LoadGraph("data\\texture\\Failed3.png");	//失敗画面のイメージ3枚目
	Failedimage[3] = LoadGraph("data\\texture\\Failed4.png");	//失敗画面のイメージ4枚目
	Failedimage[4] = LoadGraph("data\\texture\\Failed5.png");	//失敗画面のイメージ5枚目
	Playerimage = LoadGraph("data\\texture\\Player4.png");		//プレイヤーのイメージ
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
	PlayerX = 100;	//プレイヤーの表示位置
	PlayerY = 200;	//プレイヤーの表示位置
	AnimCounter = 0;	//アニメーション用カウンター
	EggCounter = 0;		//ナスカウンター
	EggCounterOne = 0;	//ナスカウンターの1の位
	EggCounterTen = 0;	//ナスカウンターの10の位
	IceCounter = 0;		//破壊した氷用カウンター
	IceCounterOne = 0;	//破壊した氷用カウンターの1の位
	IceCounterTen = 0;	//破壊した氷用カウンターの10の位
	BirdCounter = 0;	//倒した鳥用カウンター
	BirdCounterOne = 0;	//倒した鳥用カウンターの1の位
	BirdCounterTen = 0;	//倒した鳥用カウンターの10の位
	BlockCounter = 0;	//破壊したブロック用カウンター
	BlockCounterOne = 0;//破壊したブロック用カウンターの1の位
	BlockCounterTen = 0;//破壊したブロック用カウンターの10の位
	HaveEgg = 0;	//プレイ画面でとったナスの数
	HaveIce = 0;	//プレイ画面で破壊した氷の数
	HaveBird = 0;	//プレイ画面で倒した鳥の数
	HaveBlock = 0;	//プレイ画面で破壊したブロックの数
	ScoreOne = 0;	//スコア1の位
	ScoreTen = 0;	//スコア10の位
	ScoreHun = 0;	//スコア100の位
	ScoreSau = 0;	//スコア1000の位
	ScoreTenSau = 0;//スコア10000の位
	ScoreHunSau = 0;//スコア100000の位
	EggCalculation = true;	//trueの間ナス分のスコア計算
	IceCalculation = false;	//trueの間氷分のスコア計算
	BirdCalculation = false;//trueの間鳥分のスコア計算
	BlockCaculation = false;//trueの間ブロック分のスコア計算
	score = 0;
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	//ボーナスステージをクリアか失敗したら
	if (scene->Getplayer()->Clear || scene->Getplayer()->Failed)
	{
		//クリアなら
		if (scene->Getplayer()->Clear)
		{
			if (ScoreSau == 0)
				ScoreSau = 3;
		}

		//ナスの計算
		if (EggCalculation)
		{
			//ナスを取った個数分計算
			if (EggCounter < HaveEgg)
			{
				WaitTimer(100);
				EggCounter++;
				EggCounterOne++;
				//繰り上がり処理
				if (EggCounterOne > 10)
				{
					EggCounterOne = 0;
					EggCounterTen++;
				}
				score += 300;

				for (int i = 0; i < 3; i++)
				{
					ScoreHun++;

					//繰り上がり処理
					if (ScoreHun > 9)
					{
						ScoreSau++;
						ScoreHun = 0;
					}
				}
			}
			else
			{
				//氷分の計算へ
				IceCalculation = true;
			}
		}

		//氷分のスコア計算
		if (IceCalculation)
		{
			//壊した氷分計算
			if (IceCounter < HaveIce)
			{
				WaitTimer(100);
				IceCounter++;
				IceCounterOne++;
				//繰り上がり処理
				if (IceCounterOne > 10)
				{
					IceCounterOne = 0;
					IceCounterTen++;
				}
				score += 400;

				for (int i = 0; i < 4; i++)
				{
					ScoreHun++;

					//繰り上がり処理
					if (ScoreHun > 9)
					{
						ScoreSau++;
						ScoreHun = 0;
					}
				}
			}
			else
			{
				//鳥のスコア計算へ
				BirdCalculation = true;
			}
		}

		//倒した鳥のスコア計算
		if (BirdCalculation)
		{
			//倒した鳥分計算
			if (BirdCounter < HaveBird)
			{
				WaitTimer(100);
				BirdCounter++;
				BirdCounterOne++;
				//繰り上がり処理
				if (BirdCounterOne > 10)
				{
					BirdCounterOne = 0;
					BirdCounterTen++;
				}
				score += 800;

				for (int i = 0; i < 8; i++)
				{
					ScoreHun++;

					//繰り上がり処理
					if (ScoreHun > 9)
					{
						ScoreSau++;
						ScoreHun = 0;
					}
				}
			}
			else
			{
				BlockCaculation = true;
			}
		}

		//壊したブロックのスコア計算
		if (BlockCaculation)
		{
			//壊したブロック分計算
			if (BlockCounter < HaveBlock)
			{
				WaitTimer(100);
				BlockCounter++;
				BlockCounterOne++;
				//繰り上がり処理
				if (BlockCounterOne >= 10)
				{
					BlockCounterOne = 0;
					BlockCounterTen++;
				}
				score += 10;
				ScoreTen++;
			}
		}

		//繰り上がり処理
		if (ScoreTen > 9)
		{
			ScoreHun++;
			ScoreTen = 0;
		}

		//繰り上がり処理
		if (ScoreHun > 9)
		{
			ScoreSau++;
			ScoreHun = 0;
		}

		//繰り上がり処理
		if (ScoreSau > 9)
		{
			ScoreTenSau++;
			ScoreSau = 0;
		}

		//繰り上がり処理
		if (ScoreTenSau > 9)
		{
			ScoreHunSau++;
			ScoreTenSau = 0;
		}
	}
}

void ResultScene::Draw()
{
	int tx;
	int pattern;

	//ボーナスステージをクリアか失敗したら
	if (scene->Getplayer()->Clear || scene->Getplayer()->Failed)
	{
		//クリアなら
		if (scene->Getplayer()->Clear)
		{
			DrawGraph(0, 0, Clearimage[0], false);
			AnimCounter++;
			tx = (AnimCounter / 16) % 2 * 92;
			pattern = 4 * 120;

			if (EggCalculation)
			{
				DrawGraph(0, 0, Clearimage[1], false);
				DrawGraph(370, 375, NumImage[EggCounterTen], false);
				DrawGraph(410, 375, NumImage[EggCounterOne], false);
			}

			if (IceCalculation)
			{
				DrawGraph(0, 0, Clearimage[2], false);
				DrawGraph(370, 375, NumImage[EggCounterTen], false);
				DrawGraph(410, 375, NumImage[EggCounterOne], false);
				DrawGraph(370, 438, NumImage[IceCounterTen], false);
				DrawGraph(410, 438, NumImage[IceCounterOne], false);
			}

			if (BirdCalculation)
			{
				DrawGraph(0, 0, Clearimage[3], false);
				DrawGraph(370, 375, NumImage[EggCounterTen], false);
				DrawGraph(410, 375, NumImage[EggCounterOne], false);
				DrawGraph(370, 438, NumImage[IceCounterTen], false);
				DrawGraph(410, 438, NumImage[IceCounterOne], false);
				DrawGraph(370, 501, NumImage[BirdCounterTen], false);
				DrawGraph(410, 501, NumImage[BirdCounterOne], false);
			}

			if (BlockCaculation)
			{
				DrawGraph(0, 0, Clearimage[4], false);
				DrawGraph(370, 375, NumImage[EggCounterTen], false);
				DrawGraph(410, 375, NumImage[EggCounterOne], false);
				DrawGraph(370, 438, NumImage[IceCounterTen], false);
				DrawGraph(410, 438, NumImage[IceCounterOne], false);
				DrawGraph(370, 501, NumImage[BirdCounterTen], false);
				DrawGraph(410, 501, NumImage[BirdCounterOne], false);
				DrawGraph(370, 564, NumImage[BlockCounterTen], false);
				DrawGraph(410, 564, NumImage[BlockCounterOne], false);
			}
		}

		//失敗したら
		if (scene->Getplayer()->Failed)
		{
			DrawGraph(0, 0, Failedimage[0], false);
			AnimCounter++;
			tx = (AnimCounter / 16) % 2 * 92;
			pattern = 3 * 120;

			if (IceCalculation)
			{
				DrawGraph(0, 0, Failedimage[2], false);
				DrawGraph(370, 375, NumImage[EggCounterTen], false);
				DrawGraph(410, 375, NumImage[EggCounterOne], false);
				DrawGraph(370, 438, NumImage[IceCounterTen], false);
				DrawGraph(410, 438, NumImage[IceCounterOne], false);
			}

			if (BirdCalculation)
			{
				DrawGraph(0, 0, Failedimage[3], false);
				DrawGraph(370, 375, NumImage[EggCounterTen], false);
				DrawGraph(410, 375, NumImage[EggCounterOne], false);
				DrawGraph(370, 438, NumImage[IceCounterTen], false);
				DrawGraph(410, 438, NumImage[IceCounterOne], false);
				DrawGraph(370, 501, NumImage[BirdCounterTen], false);
				DrawGraph(410, 501, NumImage[BirdCounterOne], false);
			}

			if (BlockCaculation)
			{
				DrawGraph(0, 0, Failedimage[4], false);
				DrawGraph(370, 375, NumImage[EggCounterTen], false);
				DrawGraph(410, 375, NumImage[EggCounterOne], false);
				DrawGraph(370, 438, NumImage[IceCounterTen], false);
				DrawGraph(410, 438, NumImage[IceCounterOne], false);
				DrawGraph(370, 501, NumImage[BirdCounterTen], false);
				DrawGraph(410, 501, NumImage[BirdCounterOne], false);
				DrawGraph(370, 564, NumImage[BlockCounterTen], false);
				DrawGraph(410, 564, NumImage[BlockCounterOne], false);
			}
		}

		DrawRectGraph(PlayerX, PlayerY, tx, pattern, 92, 120, Playerimage, true, false);
		DrawGraph(348, 722, NumImage[ScoreOne], false);
		DrawGraph(304, 722, NumImage[ScoreTen], false);
		DrawGraph(260, 722, NumImage[ScoreHun], false);
		DrawGraph(216, 722, NumImage[ScoreSau], false);
		DrawGraph(172, 722, NumImage[ScoreTenSau], false);
		DrawGraph(128, 722, NumImage[ScoreHunSau], false);
	}
}
