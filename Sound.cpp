#include "Sound.h"
#include "DxLib.h"
#include "assert.h"

/*�ŏI�X�V�F2020/8/30*/
/*�T�E���h�̃\�[�X*/

Sound::Sound(PlayScene * _scene)
{
	BGMPlaying = true;
	BGMData = LoadSoundMem("data\\sound\\famipop3.mp3");
}

Sound::~Sound()
{
}

void Sound::Update()
{
	if (BGMPlaying == true)
	{
		PlaySoundMem(BGMData, DX_PLAYTYPE_LOOP);
		BGMPlaying = false;
	}
}
