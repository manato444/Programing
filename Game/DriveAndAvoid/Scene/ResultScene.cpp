#include"ResultScene.h"
#include"../Object/RankingData.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

ResultScene::ResultScene() : back_ground(NULL), score(0), mileage(0)
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

//初期化処理
void ResultScene::Initialize()
{

	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);


	//GraphFilter(back_ground, DX_GRAPH_FILTER_GAUSS, 32, 1000);


	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}

	//ゲーム結果の読み込み
	ReadResultData();
}

//更新処理
eSceneType ResultScene::Update()
{

	//Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_RANKING_INPUT;
	}

	//Aボタンでタイトルへ戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	GraphFilter(back_ground, DX_GRAPH_FILTER_GAUSS, 32, 300);

	//背景画像を描画
	DrawGraph(0, 0, back_ground, TRUE);
	

	//スコア等表示領域
	DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), TRUE);
	DrawBox(150, 150, 490, 330, GetColor(255, 255, 255), FALSE);

	DrawBox(500, 0, 640, 480, GetColor(0, 0, 250), TRUE);

	

	SetFontSize(30);
	ChangeFont("ＭＳ 明朝");
	DrawString(200, 160, "ＧＡＭＥＯＶＥＲ", GetColor(255, 0, 0));
	SetFontSize(16);
	DrawString(180, 200, "走行距離        ", GetColor(255, 255, 255));
	DrawFormatString(260, 200, GetColor(255, 255, 255), "%6d x%4d=%6d", mileage, 10,  mileage * 10);


	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);

		DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x%4d=%6d",
			enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);

		//DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x%4d=%6d",
			//enemy_count[i], (i + 1), (i + 1), enemy_count[i]);
	}

	DrawString(200, 290, "スコア", GetColor(255, 255, 255));
	DrawFormatString(260, 290, 0xFFFFFF, "            =%6d", score);

	SetFontSize(15);
	//DrawString(340, 310, "'A'タイトルへ戻る", GetColor(255, 100, 100));
	DrawString(170, 310, "-- Bボタンでランキングに登録する --", GetColor(0, 255, 0));

	DrawString(150, 450, "---- Aボタンを押してタイトルへ戻る ----", 0xffffff, 0);


}

//終了時処理
void ResultScene::Finalize()
{

	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読み込み
void ResultScene::ReadResultData()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%6d,\n", &score);
	fscanf_s(fp, "%6d,\n", &mileage);
	//避けた数と得点を取得
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%6d,\n", &enemy_count[i]);
	}
	

	//ファイルクローズ
	fclose(fp);
	
}