#pragma once

/*最終更新：2020/8/30*/
/*プレイシーンのソース*/

class app;
class Player;
class Map;
class Seal;
class Knitpicker;
class Whitebear;
class Wall;
class Cloud;
class Timer;
class Condor;
class Eggplant;
class Floor;
class ResultScene;
class Sound;

class PlayScene {
public:
	PlayScene();
	~PlayScene();
	void Update();
	void Draw();
private:
	int frameCounter;	//フレーム数を数える
	Player* player;
	Map* map;
	Seal* seal;
	Knitpicker* knitpicker;
	Whitebear* whitebear;
	Wall* wall;
	Cloud* cloud;
	Timer* timer;
	Condor* condor;
	Eggplant* eggplant;
	Floor* floor;
	ResultScene* result;
	Sound* sound;
public:
	Player* Getplayer() { return player; }
	Map* Getmap() { return map; }
	Seal* Getseal() { return seal; }
	Knitpicker* Getknitpicker() { return knitpicker; }
	Whitebear* Getwhitebear() { return whitebear; }
	Wall* Getwall() { return wall; }
	Cloud* Getcloud() { return cloud; }
	Timer* Gettimer() { return timer; }
	Condor* Getcondor() { return condor; }
	Eggplant* Geteggplant() { return eggplant; }
	Floor* Getfloor() { return floor; }
	ResultScene* Getresult() { return result; }
	Sound* Getsound() { return sound; }
};