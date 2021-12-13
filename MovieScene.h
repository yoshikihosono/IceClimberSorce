#pragma once

/*最終更新：2020/8/30*/
/*ムービー用のソース*/

class MovieScene
{
public:
	MovieScene();
	~MovieScene();
	void Update();
private:
	int MovieGraphHandle;	//動画用の変数
};