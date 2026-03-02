#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class PlayScene : public SceneBase
{
private:
	bool isPause;
	VECTOR3 mouseVec;
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	bool IsPause() const { return isPause; }
	VECTOR3 GetMouseVec() const { return mouseVec; }
};
