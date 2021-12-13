#include "ResultScene.h"
#include "DxLib.h"
#include "Player.h"
#include "PlayScene.h"

/*�ŏI�X�V�F2020/8/30*/
/*���U���g��ʂ̃\�[�X*/

ResultScene::ResultScene(PlayScene* _scene)
{
	scene = _scene;
	Clearimage[0] = LoadGraph("data\\texture\\Clear.png");		//�N���A��ʂ̃C���[�W1����
	Clearimage[1] = LoadGraph("data\\texture\\Clear2.png");		//�N���A��ʂ̃C���[�W2����
	Clearimage[2] = LoadGraph("data\\texture\\Clear3.png");		//�N���A��ʂ̃C���[�W3����
	Clearimage[3] = LoadGraph("data\\texture\\Clear4.png");		//�N���A��ʂ̃C���[�W4����
	Clearimage[4] = LoadGraph("data\\texture\\Clear5.png");		//�N���A��ʂ̃C���[�W5����
	Failedimage[0] = LoadGraph("data\\texture\\Failed.png");	//���s��ʂ̃C���[�W1����
	Failedimage[1] = LoadGraph("data\\texture\\Failed2.png");	//���s��ʂ̃C���[�W2����
	Failedimage[2] = LoadGraph("data\\texture\\Failed3.png");	//���s��ʂ̃C���[�W3����
	Failedimage[3] = LoadGraph("data\\texture\\Failed4.png");	//���s��ʂ̃C���[�W4����
	Failedimage[4] = LoadGraph("data\\texture\\Failed5.png");	//���s��ʂ̃C���[�W5����
	Playerimage = LoadGraph("data\\texture\\Player4.png");		//�v���C���[�̃C���[�W
	NumImage[0] = LoadGraph("data\\texture\\0.png");	//0�̃C���[�W
	NumImage[1] = LoadGraph("data\\texture\\1.png");	//1�̃C���[�W
	NumImage[2] = LoadGraph("data\\texture\\2.png");	//2�̃C���[�W
	NumImage[3] = LoadGraph("data\\texture\\3.png");	//3�̃C���[�W
	NumImage[4] = LoadGraph("data\\texture\\4.png");	//4�̃C���[�W
	NumImage[5] = LoadGraph("data\\texture\\5.png");	//5�̃C���[�W
	NumImage[6] = LoadGraph("data\\texture\\6.png");	//6�̃C���[�W
	NumImage[7] = LoadGraph("data\\texture\\7.png");	//7�̃C���[�W
	NumImage[8] = LoadGraph("data\\texture\\8.png");	//8�̃C���[�W
	NumImage[9] = LoadGraph("data\\texture\\9.png");	//9�̃C���[�W
	PlayerX = 100;	//�v���C���[�̕\���ʒu
	PlayerY = 200;	//�v���C���[�̕\���ʒu
	AnimCounter = 0;	//�A�j���[�V�����p�J�E���^�[
	EggCounter = 0;		//�i�X�J�E���^�[
	EggCounterOne = 0;	//�i�X�J�E���^�[��1�̈�
	EggCounterTen = 0;	//�i�X�J�E���^�[��10�̈�
	IceCounter = 0;		//�j�󂵂��X�p�J�E���^�[
	IceCounterOne = 0;	//�j�󂵂��X�p�J�E���^�[��1�̈�
	IceCounterTen = 0;	//�j�󂵂��X�p�J�E���^�[��10�̈�
	BirdCounter = 0;	//�|�������p�J�E���^�[
	BirdCounterOne = 0;	//�|�������p�J�E���^�[��1�̈�
	BirdCounterTen = 0;	//�|�������p�J�E���^�[��10�̈�
	BlockCounter = 0;	//�j�󂵂��u���b�N�p�J�E���^�[
	BlockCounterOne = 0;//�j�󂵂��u���b�N�p�J�E���^�[��1�̈�
	BlockCounterTen = 0;//�j�󂵂��u���b�N�p�J�E���^�[��10�̈�
	HaveEgg = 0;	//�v���C��ʂłƂ����i�X�̐�
	HaveIce = 0;	//�v���C��ʂŔj�󂵂��X�̐�
	HaveBird = 0;	//�v���C��ʂœ|�������̐�
	HaveBlock = 0;	//�v���C��ʂŔj�󂵂��u���b�N�̐�
	ScoreOne = 0;	//�X�R�A1�̈�
	ScoreTen = 0;	//�X�R�A10�̈�
	ScoreHun = 0;	//�X�R�A100�̈�
	ScoreSau = 0;	//�X�R�A1000�̈�
	ScoreTenSau = 0;//�X�R�A10000�̈�
	ScoreHunSau = 0;//�X�R�A100000�̈�
	EggCalculation = true;	//true�̊ԃi�X���̃X�R�A�v�Z
	IceCalculation = false;	//true�̊ԕX���̃X�R�A�v�Z
	BirdCalculation = false;//true�̊Ԓ����̃X�R�A�v�Z
	BlockCaculation = false;//true�̊ԃu���b�N���̃X�R�A�v�Z
	score = 0;
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	//�{�[�i�X�X�e�[�W���N���A�����s������
	if (scene->Getplayer()->Clear || scene->Getplayer()->Failed)
	{
		//�N���A�Ȃ�
		if (scene->Getplayer()->Clear)
		{
			if (ScoreSau == 0)
				ScoreSau = 3;
		}

		//�i�X�̌v�Z
		if (EggCalculation)
		{
			//�i�X������������v�Z
			if (EggCounter < HaveEgg)
			{
				WaitTimer(100);
				EggCounter++;
				EggCounterOne++;
				//�J��オ�菈��
				if (EggCounterOne > 10)
				{
					EggCounterOne = 0;
					EggCounterTen++;
				}
				score += 300;

				for (int i = 0; i < 3; i++)
				{
					ScoreHun++;

					//�J��オ�菈��
					if (ScoreHun > 9)
					{
						ScoreSau++;
						ScoreHun = 0;
					}
				}
			}
			else
			{
				//�X���̌v�Z��
				IceCalculation = true;
			}
		}

		//�X���̃X�R�A�v�Z
		if (IceCalculation)
		{
			//�󂵂��X���v�Z
			if (IceCounter < HaveIce)
			{
				WaitTimer(100);
				IceCounter++;
				IceCounterOne++;
				//�J��オ�菈��
				if (IceCounterOne > 10)
				{
					IceCounterOne = 0;
					IceCounterTen++;
				}
				score += 400;

				for (int i = 0; i < 4; i++)
				{
					ScoreHun++;

					//�J��オ�菈��
					if (ScoreHun > 9)
					{
						ScoreSau++;
						ScoreHun = 0;
					}
				}
			}
			else
			{
				//���̃X�R�A�v�Z��
				BirdCalculation = true;
			}
		}

		//�|�������̃X�R�A�v�Z
		if (BirdCalculation)
		{
			//�|���������v�Z
			if (BirdCounter < HaveBird)
			{
				WaitTimer(100);
				BirdCounter++;
				BirdCounterOne++;
				//�J��オ�菈��
				if (BirdCounterOne > 10)
				{
					BirdCounterOne = 0;
					BirdCounterTen++;
				}
				score += 800;

				for (int i = 0; i < 8; i++)
				{
					ScoreHun++;

					//�J��オ�菈��
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

		//�󂵂��u���b�N�̃X�R�A�v�Z
		if (BlockCaculation)
		{
			//�󂵂��u���b�N���v�Z
			if (BlockCounter < HaveBlock)
			{
				WaitTimer(100);
				BlockCounter++;
				BlockCounterOne++;
				//�J��オ�菈��
				if (BlockCounterOne >= 10)
				{
					BlockCounterOne = 0;
					BlockCounterTen++;
				}
				score += 10;
				ScoreTen++;
			}
		}

		//�J��オ�菈��
		if (ScoreTen > 9)
		{
			ScoreHun++;
			ScoreTen = 0;
		}

		//�J��オ�菈��
		if (ScoreHun > 9)
		{
			ScoreSau++;
			ScoreHun = 0;
		}

		//�J��オ�菈��
		if (ScoreSau > 9)
		{
			ScoreTenSau++;
			ScoreSau = 0;
		}

		//�J��オ�菈��
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

	//�{�[�i�X�X�e�[�W���N���A�����s������
	if (scene->Getplayer()->Clear || scene->Getplayer()->Failed)
	{
		//�N���A�Ȃ�
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

		//���s������
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
