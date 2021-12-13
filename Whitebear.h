#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�V���N�}�̃\�[�X*/

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
	int x, y;	//���W
	int AppearCount;	//�o������܂ł̃J�E���g
	int moveCount;	//�ړ����Ă���ԃJ�E���g����
	bool alive;	//�����Ă���true
	int RefY;	//���܂�鎞�ɎQ�Ƃ���l
private:
	PlayScene* scene;
	int image;			//�V���N�}�C���[�W�p�ϐ�
	bool rightward;		//�E�����Ă���true
	bool hit;			//����ꂽ��true
	bool action;		//�W�����v�A�N�V����������true
	int pattern;		//�A�j���[�V����Y���p�J�E���^�[
	int animCounter;	//�A�j���[�V����X���p�J�E���^�[
};