#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�{�[�i�X�X�e�[�W�̃^�C�}�[�̃\�[�X*/

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
	int image;	//�^�C�}�[�̘g
	int NumImage[10];	//�����̃C���[�W
	int one;	//1�̈ʗp
	int ten;	//10�̈ʗp
	int hun;	//100�̈ʗp
};