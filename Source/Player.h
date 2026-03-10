#pragma once
#include <DxLib.h>
// #include "../Library/GameObject.h"
#include "Object3D.h"
#include <vector>

class Player : public Object3D {
private:
	int cameraSelect = 0;
	VECTOR3 cameraRotationVec;
	std::vector<int> hasItemIdVector;
public:
	Player();
	~Player();
	void Update() override;

	void AddItem(int itemID);
	void RemoveItem(int itemID);
	bool HasItem(int itemID) const;
	int GetItem(int index) const;
};