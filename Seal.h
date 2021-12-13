#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�A�U���V�̃\�[�X*/

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
	int image;	//�A�U���V�̃C���[�W�p�ϐ�
	int iceimage;	//�X�̃C���[�W�p�ϐ�
	int pattern[MaxSeal];		//�A�j���[�V����Y���p�J�E���^�[
	int animCounter[MaxSeal];	//�A�j���[�V����X���p�J�E���^�[
	int spawn;
public:
	int x[MaxSeal], y[MaxSeal];	//�A�U���V�̍��W
	int RefY[MaxSeal];	//�A�U���V�����A����Ƃ��Ɏg��Y
	int iceX[MaxSeal], iceY[MaxSeal];	//�X�̍��W
	bool iceExist[MaxSeal];	//�X�����݂��Ă���true
	bool rightward[MaxSeal];	//�������Ă���true
	bool alive[MaxSeal];	//�����Ă���true
	bool Hit[MaxSeal];	//�n���}�[�ɉ���ꂽ��true
	bool HummerRight[MaxSeal];	//�n���}�[�ɉE���牣��ꂽ��true
	bool HummerLeft[MaxSeal];	//�n���}�[�ɍ����牣��ꂽ��true
	bool FindHole[MaxSeal];	//���𔭌�������true
	bool Falling[MaxSeal];	//�������Ȃ�true
	int Count[MaxSeal];	//�o������Ƃ��̃J�E���^�[
};