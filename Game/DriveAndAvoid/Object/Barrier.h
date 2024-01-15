#pragma once

#include"../Utility/Vector2D.h"

class Barrier
{
private:

	//バリア画像
	int image;	

	//バリアの寿命
	float life_span;

public:
	//コンストラクタ(インスタンス生成時に最初に呼ばれる関数)
	Barrier();

	//デストラクタ
	~Barrier();

	//描画処理
	void Draw(const Vector2D& location);

	//寿命が尽きたか確認する処理
	bool IsFinished(float speed);

};