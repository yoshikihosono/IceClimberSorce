#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
	image = LoadGraph("data\\texture\\Title.png");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	DrawGraph(0, 0, image, true);
}
