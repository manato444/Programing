#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include"../Object/Item.h"

class GameMainScene : public SceneBase
{
private:

	int high_score;		 //ハイスコア
	int back_ground;	 //背景画像
	int barrier_image;	 //バリア画像
	int mileage;		 //走行距離
	int enemy_image[3];	 //敵画像
	int enemy_count[3];	 //通り過ぎた敵カウント
	Player* player;		 //プレイヤー
	Enemy** enemy;		 //敵

	Item* item;		//アイテム
	int item_image;	//アイテム画像

	//int item_count[1];	//アイテム追加したら多分使う

	int sound; //BGM
	int image;	//飾り(?)

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:

	//ハイスコア読み込み処理
	void ReadHighScore();

	void GameCount();	//なんでつくった

	//当たり判定
	bool IsHitCheck(Player* p, Enemy* e);
	bool IsHitCheck(Player* p, Item* i);
};

