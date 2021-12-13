#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�v���C���[�̃\�[�X*/

class PlayScene;
class App;

static const int PWidth = 48;	//�v���C���[�̉���
static const int PHeight = 80;	//�v���C���[�̍���

class Player {
public:
	Player(PlayScene* _scene);
	~Player();
	void Update();
	void Draw();
	int x, y;	//�L�����̍��W
	int TempX, TempY;	//�L�����̈ꎞ�I���W
	int ScrollCount;	//�X�N���[���p�J�E���g
	bool BonusStage;	//�{�[�i�X�X�e�[�W��������true
	bool Clear;			//�N���A������true
	bool Failed;		//�{�[�i�X�X�e�[�W�����s������true
	bool Scrolling;		//�X�N���[�����Ă���true
	int RefY;			//���A�p��Y�l
	bool Hit;	//�G�ɓ���������true
private:
	float Accel;	//X�̉����x
	int image;	//�摜�̃n���h��
	int Life;	//�c�@
	int LifeX, LifeY;	//�c�@�̍��W
	int Lifeimage;	//�c�@�̉摜
	int beforeJump;		//�W�����v�O��Y���W
	float velX, velY;	//���x
	int HummerX;	//�n���}�[��X�l
	int HummerY;	//�n���}�[��Y�l
	int HummerWidth;	//�n���}�[�̉���
	int HummerHeight;	//�n���}�[�̍���
	PlayScene* scene;
	int pattern;		//�A�j���[�V����Y���p�J�E���^�[
	int animCounter;	//�A�j���[�V����X���p�J�E���^�[
	bool Rightward;	//�E�����Ă���true
	bool jumping;	//�W�����v���Ă���true
	bool PushJump;	//Space�������Ă���true
	bool Attacking;	//�U�����Ă���true
	int RestTime;	//�������Ă���̖��G����
	int GameOverimage;	//�Q�[���I�[�o�[�C���[�W
	int OverX, OverY;	//�Q�[���I�[�o�[�C���[�W�̍��W
	bool reverse = false;
};
