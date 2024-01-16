#pragma once

#include "SceneBase.h"

//�Œ艻����t���[�����[�g�l
#define TARGET_FREAM_RATE (60)

//1�t���[��������̎��ԁi�}�C�N���b�j
#define DELTA_SECOND (1000000 / TARGET_FREAM_RATE)

//�V�[���}�l�[�W���[�N���X
class SceneManager
{
	
private:

	//���݃V�[�����
	SceneBase* current_scene;

public:

	SceneManager();
	~SceneManager();

	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�I��������
	void Finalize();

private:

	//�`�揈��
	void Draw() const;

	//�V�[���؂�ւ�����
	void ChangeScene(eSceneType scene_type);

	//�V�[����������
	SceneBase* CreateScene(eSceneType scene_type);

};