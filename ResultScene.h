#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*���U���g��ʂ̃\�[�X*/

class PlayScene;

class ResultScene
{
public:
	ResultScene(PlayScene* _scene);
	~ResultScene();
	void Update();
	void Draw();
	int score;	//�X�R�A�p�ϐ�
	int HaveEgg;	//�v���C���[���v���C���Ɏ�����i�X�p�̕ϐ�
	int HaveIce;	//�v���C���[���v���C���ɉ󂵂��X�p�̕ϐ�
	int HaveBird;	//�v���C���[���v���C���ɓ|�������p�̕ϐ�
	int HaveBlock;	//�v���C���[���v���C���ɉ󂵂��u���b�N�p�̕ϐ�
private:
	PlayScene* scene;
	int Clearimage[5];	//�N���A��ʂ̃C���[�W�p�ϐ�
	int Failedimage[5];	//���s��ʂ̃C���[�W�p�ϐ�
	int Playerimage, PlayerX, PlayerY;	//�v���C���[�C���[�W�p�ϐ�
	int AnimCounter;	//�v���C���[�̃A�j���[�V�����p�ϐ�
	int EggCounter;			//�i�X�J�E���^�[
	int EggCounterOne;		//�i�X�J�E���^�[��1�̈�
	int EggCounterTen;		//�i�X�J�E���^�[��10�̈�
	int IceCounter;			//�j�󂵂��X�p�J�E���^�[
	int IceCounterOne;		//�j�󂵂��X�p�J�E���^�[��1�̈�
	int IceCounterTen;		//�j�󂵂��X�p�J�E���^�[��10�̈�
	int BirdCounter;		//�|�������p�J�E���^�[
	int BirdCounterOne;		//�|�������p�J�E���^�[��1�̈�
	int BirdCounterTen;		//�|�������p�J�E���^�[��10�̈�
	int BlockCounter;		//�j�󂵂��u���b�N�p�J�E���^�[
	int BlockCounterOne;	//�j�󂵂��u���b�N�p�J�E���^�[��1�̈�
	int BlockCounterTen;	//�j�󂵂��u���b�N�p�J�E���^�[��10�̈�
	bool EggCalculation;	//�v���C��ʂłƂ����i�X�̐�
	bool IceCalculation;	//�v���C��ʂŔj�󂵂��X�̐�
	bool BirdCalculation;	//�v���C��ʂœ|�������̐�
	bool BlockCaculation;	//�v���C��ʂŔj�󂵂��u���b�N�̐�
	int ScoreOne;			//�X�R�A1�̈�
	int ScoreTen;			//�X�R�A10�̈�
	int ScoreHun;			//�X�R�A100�̈�
	int ScoreSau;			//�X�R�A1000�̈�
	int ScoreTenSau;		//�X�R�A10000�̈�
	int ScoreHunSau;		//�X�R�A100000�̈�
	int NumImage[10];		//�����̃C���[�W�p�ϐ�
};