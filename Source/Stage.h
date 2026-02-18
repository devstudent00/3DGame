#pragma once
#include <DxLib.h>
#include "../Library/GameObject.h"

class Stage : public GameObject {
private:
	int hModel;
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	bool CollideRay(VECTOR3 start, VECTOR3 end, VECTOR3* hit);
};