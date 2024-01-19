#include"ResultScene.h"
#include"../Object/RankingData.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

ResultScene::ResultScene() : back_ground(NULL), score(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

ResultScene::~ResultScene()
{
}

//����������
void ResultScene::Initialize()
{

	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back.bmp");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmp������܂���\n");
	}

	//�Q�[�����ʂ̓ǂݍ���
	ReadResultData();
}

//�X�V����
eSceneType ResultScene::Update()
{

	//B�{�^���Ń����L���O�ɑJ�ڂ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_RANKING_INPUT;
	}

	//A�{�^���Ń^�C�g���֖߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void ResultScene::Draw() const
{
	
	GraphFilter(back_ground, DX_GRAPH_FILTER_GAUSS, 16, 1400);

	//�w�i�摜��`��
	DrawGraph(0, 0, back_ground, TRUE);


	//�X�R�A���\���̈�
	DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), TRUE);
	DrawBox(150, 150, 490, 330, GetColor(255, 255, 255), FALSE);

	DrawBox(500, 0, 640, 480, GetColor(0, 0, 250), TRUE);

	SetFontSize(30);
	ChangeFont("�l�r ����");
	DrawString(200, 160, "�f�`�l�d�n�u�d�q", GetColor(255, 0, 0));
	SetFontSize(16);
	DrawString(180, 200, "���s����        ", GetColor(255, 255, 255));
	DrawFormatString(240, 200, GetColor(255, 255, 255), " =%6d", enemy_count[0]);


	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);

		DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x%4d=%6d",
			enemy_count[1], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);

		//DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x%4d=%6d",
			//enemy_count[i], (i + 1), (i + 1), enemy_count[i]);
	}

	DrawString(180, 290, "�X�R�A", GetColor(255, 255, 255));
	DrawFormatString(180, 290, 0xFFFFFF, "            =%6d", &score);

	SetFontSize(15);
	DrawString(340, 310, "'A'�^�C�g���֖߂�", GetColor(255, 100, 100));
	DrawString(152, 310, "'B'�����L���O�ɓo�^", GetColor(0, 255, 0));


}

//�I��������
void ResultScene::Finalize()
{

	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}

//���݂̃V�[�������擾
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//���U���g�f�[�^�̓ǂݍ���
void ResultScene::ReadResultData()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���ǂݍ��߂܂���\n");
	}

	//���ʂ�ǂݍ���
	fscanf_s(fp, "&6d,\n", &score);

	//���������Ɠ��_���擾
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%6d", &enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);
	
}