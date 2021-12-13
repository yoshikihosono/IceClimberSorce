#pragma once

/*最終更新：2020/8/30*/
/*サウンドのソース*/

class PlayScene;

class Sound
{
public:
	Sound(PlayScene* _scene);
	~Sound();
	void Update();
private:
	bool BGMPlaying;	//BGMを流すならtrue
	int BGMData;		//BGM用変数
};