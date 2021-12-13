#include "app.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "MovieScene.h"
#include "ResultScene.h"
#include "DxLib.h"

/*最終更新：2020/8/30*/

TitleScene* titlescene = nullptr;
PlayScene* playscene = nullptr;
MovieScene* moviescene = nullptr;

int Gamestate;

void AppInit()
{
	Gamestate = play;
	playscene = new PlayScene();
}

void AppUpdate() 
{
	playscene->Update();
}

void AppDraw() 
{	
	playscene->Draw();
}

void AppRelease() 
{
	delete titlescene;
	delete moviescene;
	delete playscene;
}