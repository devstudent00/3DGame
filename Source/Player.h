#pragma once
#include <DxLib.h>
// #include "../Library/GameObject.h"
#include "Object3D.h"

class Player : public Object3D {
private:
	int cameraSelect = 0;
	VECTOR3 cameraRotationVec;
public:
	Player();
	~Player();
	void Update() override;
};