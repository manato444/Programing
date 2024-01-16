#pragma once

#include"SceneBase.h"
#include"../Object/RankingData.h"

class RankingDispScene : public SceneBase
{

private:

public:

	//”wŒi‰æ‘œ
	int background_image;

	//ƒ‰ƒ“ƒLƒ“ƒOî•ñ
	RankingData* ranking;

public:

	RankingDispScene();
	virtual ~RankingDispScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;



};