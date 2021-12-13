#include "Sound.h"
#include "DxLib.h"
#include "assert.h"

/*最終更新：2020/8/30*/
/*サウンドのソース*/

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
