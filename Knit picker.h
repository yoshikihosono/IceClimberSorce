#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*���̃\�[�X*/

class PlayScene;

static const int Knitwidth = 60;
static const int Knitheight = 60;

class Knitpicker
{
public:
	Knitpicker(PlayScene* _scene);
	~Knitpicker();
	void Update();
	void Draw();
	bool Collision(int px, int py, int pw, int ph);	//�����蔻��
private:
	int image;	//�摜�n���h��
	int animCounter;	//X���A�j���[�V�����p�J�E���^�[
	int pattern;		//�A�j���[�V����Y���p�J�E���^�[
public:
	bool alive;	//�����Ă���true
	float x, y;	//���̍��W
	int RefY;	//��������Ƃ��ɎQ�Ƃ�����W
	int MoveCounter;	//�ړ����Ǘ�����J�E���^�[
	int Count;	//��������܂ł̎���
	int spawn;	//���܂��ʒu
	bool Hit;	//�n���}�[�ɉ���ꂽ��true
	bool rightward;	//�E�����Ă���true
};
