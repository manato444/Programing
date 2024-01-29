#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"


class Player
{
private:

	bool is_active;			//有効状態か？
	int image;				//画像データ
	Vector2D location;		//位置座標
	Vector2D box_size;		//当たり判定の大きさ
	float angle;			//角度
	float speed;			//速さ
	float hp;				//体力
	float fuel;				//燃料
	int barrier_count;		//バリアの枚数
	Barrier* barrier;		//バリア

	float fuel_max;

	int sound_c;	//クラッシュ効果音
	int sound_f;	//燃料回復効果音
	int sound_b;	//バリア効果音

	int crash;
;

public:

	//コンストラクタ(インスタンス生成時に最初に呼ばれる関数)
	Player();

	//デストラクタ
	~Player();

	void Initialize();		//初期化処理
	void Update();			//更新処理
	void Draw();			//描画処理
	void Finalize();		//終了時処理

public:

	void SetActive(bool flg);		//有効フラグ設定
	void DecreaseHp(float value);	//体力減少処理
	void DecreaseFuel(float value);			//減少じゃなくて増やす処理です

	void CarCrash();	//クラッシュ
	void FuelUp();		//燃料回復
	void BarrierSound();

	float SetFuel();	//なんだっけ

	Vector2D GetLocation() const;	//位置座標取得
	Vector2D GetBoxSize() const;	//当たり判定の大きさ取得

	float GetSpeed() const;			//速さ取得処理
	float GetFuel() const;			//燃料取得
	float GetHp() const;			//体力取得

	int GetBarrierCount() const;	//バリアの枚数取得
	bool IsBarrier() const;			//バリア有効か？を取得

private:

	//移動処理
	void Movement();
	
	//加速処理
	void Acceleration();

	static float SetLeft_Stick_X();	//左スティックX座標をセット
	static float SetLeft_Stick_Y();	//左スティックY座標をセット
	static float stick2[2];
};