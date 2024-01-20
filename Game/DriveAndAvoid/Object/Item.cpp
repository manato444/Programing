
#include"Item.h"
#include"DxLib.h"

Item::Item(int type) : type(type), image(NULL),
speed(0.0f), location(0.0f), box_size(0.0f)
{
}

Item::~Item()
{
}

//初期化処理
void Item::Initialize()
{

	image = LoadGraph("Resource/images/gasoline.bmp");

	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);

	//生成位置の設定
	location = Vector2D(random_x, -50.0f);

	//当たり判定の設定
	box_size = Vector2D(20.0f, 30.0f);

	//速さの設定
	speed = 0.5f; // (float)(this->type * 2);

}

void Item::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed);// +speed - 28);
}

void Item::Draw() const
{
	//アイテム画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Item::Finalize()
{

}

//タイプを取得
int Item::GetType() const
{
	return type;
}

//位置情報を取得
Vector2D Item::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Item::GetBoxSize() const
{
	return box_size;
}
