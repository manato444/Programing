#pragma once

#include"../Utility/Vector2D.h"
//#include"../Utility/InputControl.h"
#include"Barrier.h"

class Player
{
private:

	bool is_active;			//�L����Ԃ��H
	int image;				//�摜�f�[�^
	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//�����蔻��̑傫��
	float angle;			//�p�x
	float speed;			//����
	float hp;				//�̗�
	float fuel;				//�R��
	int barrier_count;		//�o���A�̖���
	Barrier* barrier;		//�o���A

	float fuel_max;

public:

	//�R���X�g���N�^(�C���X�^���X�������ɍŏ��ɌĂ΂��֐�)
	Player();

	//�f�X�g���N�^
	~Player();

	void Initialize();		//����������
	void Update();			//�X�V����
	void Draw();			//�`�揈��
	void Finalize();		//�I��������

public:

	void SetActive(bool flg);		//�L���t���O�ݒ�
	void DecreaseHp(float value);	//�̗͌�������
	void DecreaseFuel(float value);			//

	float SetFuel();

	Vector2D GetLocation() const;	//�ʒu���W�擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫���擾

	float GetSpeed() const;			//�����擾����
	float GetFuel() const;			//�R���擾
	float GetHp() const;			//�̗͎擾

	int GetBarrierCount() const;	//�o���A�̖����擾
	bool IsBarrier() const;			//�o���A�L�����H���擾

private:

	//�ړ�����
	void Movement();
	
	//��������
	void Acceleration();

	static float SetLeft_Stick();
	static float stick2[2];
};