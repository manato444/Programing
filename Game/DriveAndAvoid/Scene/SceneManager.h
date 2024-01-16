#pragma once

#include "SceneBase.h"

//固定化するフレームレート値
#define TARGET_FREAM_RATE (60)

//1フレーム当たりの時間（マイクロ秒）
#define DELTA_SECOND (1000000 / TARGET_FREAM_RATE)

//シーンマネージャークラス
class SceneManager
{
	
private:

	//現在シーン情報
	SceneBase* current_scene;

public:

	SceneManager();
	~SceneManager();

	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	//終了時処理
	void Finalize();

private:

	//描画処理
	void Draw() const;

	//シーン切り替え処理
	void ChangeScene(eSceneType scene_type);

	//シーン生成処理
	SceneBase* CreateScene(eSceneType scene_type);

};