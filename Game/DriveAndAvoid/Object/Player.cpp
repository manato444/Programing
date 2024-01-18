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

//����������
void Player::Initialize()
{

	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(26.0f, 54.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	fuel = 85000;
	barrier_count = 3;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/car1pol.bmp");
	//image = LoadGraph("Resource/images/gentuki.bmp");
	//image = LoadGraph("Resource/images/car1.bmp");



	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmp������܂���\n");
	}
}

//�X�V����
void Player::Update()
{

	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		angle += DX_PI_F / 10.0f;
		speed = 1.0f;

		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	//�R���̏���
	fuel -= speed;

	//�ړ�����
	Movement();

	SetLeft_Stick();

	//����������
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//�o���A���������ꂽ��A�X�V���s��
	if (barrier != nullptr)
	{

		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//�`�揈��
void Player::Draw()
{
	
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//�o���A���������ꂽ��A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpeed() const
{
	return this->speed;
}

//�R���擾����
float Player::GetFuel() const
{
	return this->fuel;
}

//�̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}

//�o���A�����擾����
int Player::GetBarrierCount() const
{
	return this->barrier_count;
}

//�o���A�L�����H���擾
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}


//���X�e�B�b�N�̒l���Z�b�g
float Player::SetLeft_Stick()
{
	stick2[0] = InputControl::GetLeft_Stick();
	
	return stick2[0];
}



//�ړ�����
void Player::Movement()
{
	float x, y;

	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
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
	if(InputControl::GetLeft_Stick)
	{
		move += Vector2D(stick2[0], 0.0f);

		if (stick2[0] >= 0.2f)
		{
			angle = DX_PI_F / 30;
			barrier != nullptr;
			barrier = new Barrier;
		}
		else if (stick2[0] <= -0.2f)
		{
			
			angle = -DX_PI_F / 30;
			barrier != nullptr;
			barrier = new Barrier;
		}
		else if (stick2[0] == 0.0f)
		{
		
			angle = -DX_PI_F / 30;
			barrier == nullptr;
			delete barrier;
		}

	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 170.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//����������
void Player::Acceleration()
{
	//LB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 3.0f;
	}

	//RB�{�^���������ꂽ��A��������(���E�˔j�X�s�[�h40�܂ł����܂�^^)
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 40.1f)
	{
		speed += 2.0f;
	}

	//�E�g���K�[�ŉ���
	if (InputControl::GetRightTrigger() && speed <= 30.0f)
	{
		speed += 0.3f;
	}
	else
	{
		/*(�����Ƃ�����茸��)
		for (int i = 0; i < speed - 4; i++)
		{
			speed -= 0.001f;
		}
		*/
	}
	//���g���K�[�Ō���
	if (InputControl::GetLeftTrigger() && speed > 1.0f)
	{
		speed -= 0.3f;
	}

}
