#include"Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int type, int handle) : type(type), image(handle),
									 speed(0.0f),location(0.0f),box_size(0.0f)
{
}

Enemy::~Enemy()
{
}

//����������
void Enemy::Initialize()
{

	//�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);

	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	
	//�����蔻��̐ݒ�
	box_size = Vector2D(26.0f, 54.0f);

	//�����̐ݒ�
	speed = (float)(this->type * 2);

}

void Enemy::Update(float speed)
{
	//int type = GetRand(3) % 3;

	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 27);
	

}

void Enemy::Draw() const
{
	//���ԍ��œG����F��(�ڂ��`�J�`�J���邱��)
	//GraphFilter(image, DX_GRAPH_FILTER_HSB, 0, 3, 8, 0);

	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Enemy::Finalize()
{
}

//�G�̃^�C�v���擾
int Enemy::GetType() const
{
	return type;
}

//�ʒu�����擾
Vector2D Enemy::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}