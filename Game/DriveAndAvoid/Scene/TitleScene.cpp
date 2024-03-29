#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"



TitleScene::TitleScene() : background_image(NULL), menu_image(NULL), sound(NULL),
						   cursor_image(NULL), menu_cursor(0)
{
}

TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{

	
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Title.bmp");
	//background_image = LoadGraph("Resource/images/End.bmp");

	menu_image = LoadGraph("Resource/images/menu.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//効果音
	sound = LoadSoundMem("Resource/sound/engine.mp3");

	GraphFilter(menu_image, DX_GRAPH_FILTER_HSB, 0, 1, 0, 0);
	GraphFilter(background_image, DX_GRAPH_FILTER_LEVEL, 30, 210, 120, 0, 255);

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
	
}

//更新処理
eSceneType TitleScene::Update()
{
	bool flg = TRUE;
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || CheckHitKey(KEY_INPUT_DOWN) > 0)
	{
		if (flg == TRUE)
		{
			menu_cursor++;
		}
		else
		{
			flg = TRUE;
		}
		flg = FALSE;
		//1番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
		
	}

	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP) || CheckHitKey(KEY_INPUT_UP) > 0)
	{
		menu_cursor--;
		//1番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//カーソル決定(決定した画面に遷移する)
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_RETURN))
	{
		PlaySoundMem(sound, TRUE);
		
		switch (menu_cursor) 
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();

}

//描画処理
void TitleScene::Draw() const
{
	//メニューチカチカ〜
	GraphFilter(menu_image, DX_GRAPH_FILTER_HSB, 0, 2, 3, 5);

	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//メニュー画像の描画
	DrawGraph(120, 200, menu_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);

	//DrawGraph(20, 300, menu_image, TRUE);
	//DrawRotaGraph(250, 320 + menu_cursor * 40, 0.7, DX_PI / -2.0, cursor_image, TRUE);

	//DrawString(8, 460, "B:決定", 0xffffff, 0);
}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}