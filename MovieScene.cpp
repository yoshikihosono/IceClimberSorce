#include "MovieScene.h"
#include "DxLib.h"
#include "assert.h"

/*最終更新：2020/8/30*/
/*ムービーのソース*/

MovieScene::MovieScene()
{
	// ムービーファイルをロードします。
	MovieGraphHandle = LoadGraph("data\\texture\\Ice.mp4");

}

MovieScene::~MovieScene()
{
}

void MovieScene::Update()
{
	// ムービーを再生状態にします
	PlayMovieToGraph(MovieGraphHandle);

	// ムービー映像を画面いっぱいに描画します
	DrawGraph(-125, 210, MovieGraphHandle, TRUE);

}