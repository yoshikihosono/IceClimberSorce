#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�{�[�i�X�X�e�[�W�̕ǂ̃\�[�X*/

class PlayScene;

static const int WallWidth = 100;
static const int WallHeight = 204;
static const int HalfHeight = 116;


class Wall
{
public:
	Wall(PlayScene* _scene);
	~Wall();
	void Update();
	void Draw();
	bool LeftWallCollision(int px, int py, int pw, int ph,int lwx,int lwy);
	bool RightWallCollision(int px, int py, int pw, int ph,int rwx,int rwy);
	int LeftX[7], LeftY[7];		//���̕ǂ̍��W
	int RightX[7], RightY[7];	//�E�̕ǂ̍��W	
private:
	PlayScene* scene;
	int image;		//�ǂ̃C���[�W
	int Halfimage;	//�����̕ǂ̃C���[�W
};
