/*
#include"Item.h"
#include"DxLib.h"

Item::Item(int type, int handle) : type(type), image(handle),
speed(0.0f), location(0.0f), box_size(0.0f)
{
}

Item::~Item()
{
}

//����������
void Item::Initialize()
{

	//�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);

	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);

	//�����蔻��̐ݒ�
	box_size = Vector2D(20.0f, 30.0f);

	//�����̐ݒ�
	speed = (float)(this->type * 2);

}

void Item::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 27);
}

void Item::Draw() const
{
	//�A�C�e���摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	//DrawGraph(location.x, location.y, image, TRUE);
}

void Item::Finalize()
{
}

//�G�̃^�C�v���擾
int Item::GetType() const
{
	return type;
}

//�ʒu�����擾
Vector2D Item::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Item::GetBoxSize() const
{
	return box_size;
}
*/