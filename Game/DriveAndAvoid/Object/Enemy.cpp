#include"Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int type, int handle) : type(type), image(handle),
									 speed(0.0f),location(0.0f),box_size(0.0f)
{
}

Enemy::~Enemy()
{
}

//初期化処理
void Enemy::Initialize()
{

	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);

	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	
	//当たり判定の設定
	box_size = Vector2D(26.0f, 54.0f);

	//速さの設定
	speed = (float)(this->type * 2);

}

void Enemy::Update(float speed)
{
	//int type = GetRand(3) % 3;

	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 27);
	

}

void Enemy::Draw() const
{
	//時間差で敵を虹色に(目がチカチカするこれ)
	//GraphFilter(image, DX_GRAPH_FILTER_HSB, 0, 3, 8, 0);

	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Enemy::Finalize()
{
}

//敵のタイプを取得
int Enemy::GetType() const
{
	return type;
}

//位置情報を取得
Vector2D Enemy::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}