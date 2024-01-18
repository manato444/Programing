#include"Barrier.h"
#include"DxLib.h"

Barrier::Barrier() : image(NULL), life_span(8000)
{
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/barrier.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}
}

Barrier::~Barrier()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);
}

//�`�揈��
void Barrier::Draw(const Vector2D& location)
{
	//���F�`
	GraphFilter(image, DX_GRAPH_FILTER_HSB, 0, 5, 8, 0);

	DrawRotaGraph(location.x, location.y, 1.0, 0.0, image, TRUE);
}

//�������s�������m�F���鏈��
bool Barrier::IsFinished(float speed)
{
	life_span -= speed;
	return(life_span <= 0);
}