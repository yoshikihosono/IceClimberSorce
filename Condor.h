#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�R���h���̃\�[�X*/

class PlayScene;

static const int CondorWidth = 112;
static const int CondorHeight = 59;

class Condor
{
public:
	Condor(PlayScene* _scene);
	~Condor();
	void Update();
	void Draw();
	bool Collision(int px,int py, int pw,int ph);
	int x, y;
private:
	int image;
	int animcounter;
};