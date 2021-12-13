#include "Timer.h"
#include "DxLib.h"
#include "PlayScene.h"
#include "Player.h"
#include "ResultScene.h"

/*�ŏI�X�V�F2020/8/30*/
/*�{�[�i�X�X�e�[�W�̃^�C�}�[�̃\�[�X*/

Timer::Timer(PlayScene* _scene)
{
	image = LoadGraph("data\\texture\\Time.png");		//�g�g
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
	x = 80;		//�^�C�}�[��X���W
	y = -1585;	//�^�C�}�[��Y���W
	y2 = -2500;	//�^�C�}�[��Y���W2
	time = 1200;	//����
	one = 0;	//���Ԃ�1�̈�
	ten = 0;	//���Ԃ�10�̈�
	hun = 4;	//���Ԃ�100�̈�
	scene = _scene;
}

Timer::~Timer()
{

}

void Timer::Update()
{

	//�{�[�i�X�X�e�[�W���Ȃ�
	if (scene->Getplayer()->BonusStage && !scene->Getplayer()->Clear && !scene->Getplayer()->Failed)
	{
		one--;	//1�̈ʂ��ւ炷
	}

	//1�̈ʂ�0�����ɂȂ�����
	if (one < 0)
	{
		one = 99;	//1�̈ʂ�99��
		ten--;		//�P�O�̈ʂ�1�ւ炷
	}

	//10�̈ʂ�0�����ɂȂ�����
	if (ten < 0)
	{
		ten = 9;	//10�̈ʂ�9��
		hun--;		//100�̈ʂ�1�ւ炷
	}

	//�S��0�ɂȂ�����
	if (hun == 0 && ten == 0 && one == 0)
	{
		scene->Getplayer()->Failed = true;	//���s�t���O��true��
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
