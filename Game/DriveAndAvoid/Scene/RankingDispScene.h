#pragma once

#include"SceneBase.h"
#include"../Object/RankingData.h"

class RankingDispScene : public SceneBase
{

private:

public:

	//�w�i�摜
	int background_image;

	//�����L���O���
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