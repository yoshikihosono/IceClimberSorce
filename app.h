#pragma once

/*最終更新：2020/8/30*/

class PlayScene;

void AppInit();		//初期化処理

void AppUpdate();	//更新処理

void AppDraw();		//描画処理

void AppRelease();	//

enum scene
{
	title,
	movie,
	play,
	result,
};


