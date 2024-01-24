#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

float Player::stick2[2] = {};


Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f), angle(0.0f),
				                                  speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0),
barrier(nullptr)
{
}

Player::~Player()
{
}

//初期化処理
void Player::Initialize()
{

	is_active = true;
	//location = Vector2D(320.0f, 380.0f);
	location = Vector2D(250.0f, 380.0f);
	box_size = Vector2D(26.0f, 54.0f);
	angle = 0.0f;
	speed = 24.5f;
	hp = 1000;
	fuel = 85000;
	//fuel_max = 85000;
	barrier_count = 4;
	fuel_max = fuel;

	//画像の読み込み
	image = LoadGraph("Resource/images/car1pol.bmp");
	//image = LoadGraph("Resource/images/gentuki.bmp");
	//image = LoadGraph("Resource/images/car1.bmp");

	//効果音
	sound_c = LoadSoundMem("Resource/sound/carcrash.mp3");
	sound_f = LoadSoundMem("Resource/sound/Fuelup.mp3");


	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}


//更新処理
void Player::Update()
{
	
	//操作不可状態であれば、自身を回転させる
	if (!is_active)
	{
		
		angle += DX_PI_F / 10.0f;
		speed = 8.0f;

		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
				GraphFilter(image, DX_GRAPH_FILTER_INVERT);
			
		}
		return;
	}

	//燃料の消費
	fuel -= speed;

	//移動処理
	Movement();

	//取得した左スティックの値をセットする
	SetLeft_Stick_X();
	SetLeft_Stick_Y();

	//加減速処理
	Acceleration();

	//STARTボタンで回転する（多分）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//バリア処理(Bボタン)
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}
	/*
	if (CheckHitKey(KEY_INPUT_SPACE) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}
	*/


	//バリアが生成されたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//バリアが生成されたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//燃料回復させるための処理（減少処理ではない）
void Player::DecreaseFuel(float value)
{
	this->fuel += value;
}

//クラッシュ効果音
void Player::CarCrash()
{
	if (!is_active)
	{
		PlaySoundMem(sound_c, TRUE);
		GraphFilter(image, DX_GRAPH_FILTER_INVERT);
		
	}
}

//燃料回復効果音
void Player::FuelUp()
{
	PlaySoundMem(sound_f, TRUE);
}

//なんだっけ
float Player::SetFuel()
{
	return this->fuel_max;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed() const
{
	return this->speed;
}

//燃料取得処理
float Player::GetFuel() const
{
	return this->fuel;
	//return GetFuel();
}

//体力取得処理
float Player::GetHp() const
{
	return this->hp;
}

//バリア枚数取得処理
int Player::GetBarrierCount() const
{
	return this->barrier_count;
}

//バリア有効か？を取得
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}


//左スティックの値をセット
float Player::SetLeft_Stick_X()
{
	stick2[0] = InputControl::GetLeft_Stick_X();
	
	return stick2[0];
}

//右スティックの値をセット
float Player::SetLeft_Stick_Y()
{
	stick2[1] = InputControl::GetLeft_Stick_Y();

	return stick2[1];
}

//移動処理
void Player::Movement()
{
	float x, y;

	Vector2D move = Vector2D(0.0f, 0.0f);
	angle = 0.0f;

	//十字移動処理
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-3.0f, 0.0f);
		angle = -DX_PI_F / 18;

	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(3.0f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -3.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 3.0f);
	}

	//スティック移動処理
	if (InputControl::GetLeft_Stick_X)
	{
		move += Vector2D(stick2[0], 0.0f);

		if (stick2[0] >= 0.2f)
		{
			angle = DX_PI_F / 25;
		}
		else if (stick2[0] <= -0.2f)
		{
			angle = -DX_PI_F / 25;
		}
		else if (stick2[0] == 0.0f)
		{
			angle = -DX_PI_F / 25;
		}
	}

	if (InputControl::GetLeft_Stick_Y)
	{
		move -= Vector2D(0.0f, stick2[1]);
	}
	
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		move += Vector2D(-3.5f, 0.0f);
		angle = -DX_PI_F / 18;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		move += Vector2D(3.5f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		move += Vector2D(0.0f, -3.5f);
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		move += Vector2D(0.0f, 3.5f);
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		move += Vector2D(-3.5f, 0.0f);
		angle = -DX_PI_F / 18;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		move += Vector2D(3.5f, 0.0f);
		angle = DX_PI_F / 18;
	}
	

	location += move;

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 640.0f - 170.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//加減速処理
void Player::Acceleration()
{
	//LBボタンが押されたら、減速する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 3.0f;
	}

	//RBボタンが押されたら、加速する(限界突破スピード40までだせます^^)
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 40.1f)
	{
		speed += 2.0f;
	}

	//右トリガーで加速
	if (InputControl::GetRightTrigger() && speed <= 30.0f)
	{
		speed += 0.3f;
	}
	else
	{
		/*(離すとゆっくり減速)
		for (int i = 0; i < speed - 4; i++)
		{
			speed -= 0.001f;
		}
		*/
	}
	//左トリガーで減速
	if (InputControl::GetLeftTrigger() && speed > 1.0f)
	{
		speed -= 0.3f;
	}

	if (CheckHitKey(KEY_INPUT_W) && speed <= 30.0f)
	{
		speed += 0.3f;
	}
	if (CheckHitKey(KEY_INPUT_S) && speed > 1.0f)
	{
		speed -= 0.3f;

	}
}
