#pragma once

/*�ŏI�X�V�F2020/8/30*/
/*�T�E���h�̃\�[�X*/

class PlayScene;

class Sound
{
public:
	Sound(PlayScene* _scene);
	~Sound();
	void Update();
private:
	bool BGMPlaying;	//BGM�𗬂��Ȃ�true
	int BGMData;		//BGM�p�ϐ�
};