#pragma once

#include"../Utility/Vector2D.h"

class Barrier
{
private:

	//�o���A�摜
	int image;	

	//�o���A�̎���
	float life_span;

public:
	//�R���X�g���N�^(�C���X�^���X�������ɍŏ��ɌĂ΂��֐�)
	Barrier();

	//�f�X�g���N�^
	~Barrier();

	//�`�揈��
	void Draw(const Vector2D& location);

	//�������s�������m�F���鏈��
	bool IsFinished(float speed);

};