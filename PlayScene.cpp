#include "PlayScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Map.h"
#include "Seal.h"
#include "Knit picker.h"
#include "Whitebear.h"
#include "Wall.h"
#include "Cloud.h"
#include "Timer.h"
#include "Condor.h"
#include "Eggplant.h"
#include "Floor.h"
#include "app.h"
#include "ResultScene.h"
#include "Sound.h"

/*最終更新：2020/8/30*/
/*プレイシーンのソース*/
/*プレイシーンにあるものはすべてここで管理*/

PlayScene::PlayScene()
{
	frameCounter = 0;
	player = new Player(this);
	map = new Map(this);
	seal = new Seal(this);
	knitpicker = new Knitpicker(this);
	whitebear = new Whitebear(this);
	wall = new Wall(this);
	cloud = new Cloud(this);
	timer = new Timer(this);
	condor = new Condor(this);
	eggplant = new Eggplant(this);
	floor = new Floor(this);
	result = new ResultScene(this);
	sound = new Sound(this);
}

PlayScene::~PlayScene()
{
	if (player != nullptr)
		delete player;
	if (map != nullptr)
		delete map;
	if (seal != nullptr)
		delete seal;
	if (knitpicker != nullptr)
		delete knitpicker;
	if (whitebear != nullptr)
		delete whitebear;
	if (wall != nullptr)
		delete wall;
	if (cloud != nullptr)
		delete cloud;
	if (timer != nullptr)
		delete timer;
	if (condor != nullptr)
		delete condor;
	if (eggplant != nullptr)
		delete eggplant;
	if (floor != nullptr)
		delete floor;
	if (result != nullptr)
		delete result;
}

void PlayScene::Update()
{
	frameCounter++;
	if (player != nullptr)
		player->Update();
	if (map != nullptr)
		map->Update();
	if (seal != nullptr)
		seal->Update();
	if (knitpicker != nullptr)
		knitpicker->Update();
	if (whitebear != nullptr)
		whitebear->Update();
	if (wall != nullptr)
		wall->Update();
	if (cloud != nullptr)
		cloud->Update();
	if (timer != nullptr)
		timer->Update();
	if (condor != nullptr)
		condor->Update();
	if (floor != nullptr)
		floor->Update();
	if (result != nullptr)
		result->Update();
	if (sound != nullptr)
		sound->Update();
}

void PlayScene::Draw()
{
	if (wall != nullptr)
		wall->Draw();
	if (map != nullptr)
		map->Draw();
	if (timer != nullptr)
		timer->Draw();
	if (seal != nullptr)
		seal->Draw();
	if (floor != nullptr)
		floor->Draw();
	if (knitpicker != nullptr)
		knitpicker->Draw();
	if (whitebear != nullptr)
		whitebear->Draw();
	if (cloud != nullptr)
		cloud->Draw();
	if (condor != nullptr)
		condor->Draw();
	if (eggplant != nullptr)
		eggplant->Draw();
	if (result != nullptr)
		result->Draw();
	if (player != nullptr)
		player->Draw();
}
