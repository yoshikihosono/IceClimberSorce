#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�w�i�̉��ɂ��鐔�������Ă����*/

class PlayScene;

class Floor
{
public:
	Floor(PlayScene* _scene);
	~Floor();
	void Update();
	void Draw();
	int LeftX, LeftY[8];
	int RightX, RightY[8];
private:
	int Leftimage;
	int Rightimage;
};