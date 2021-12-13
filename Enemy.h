#pragma once

class PlayScene;

class Enemy
{
public:
	Enemy(PlayScene* _scene);
	~Enemy();
	void Update();
	void Draw();
};