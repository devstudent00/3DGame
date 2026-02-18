#pragma once
#include <DxLib.h>
#include "../Library/GameObject.h"

class Player : public GameObject {
private:
	int hModel;
	VECTOR3 postion;
	VECTOR3 rotation;
	VECTOR3 velocity;
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	VECTOR3 GetPosition() const { return postion; }
	void SetPosition(const VECTOR3& pos) { postion = pos; }
	VECTOR3 GetRotation() const { return rotation; }
	void SetRotation(const VECTOR3& rot) { rotation = rot; }
	VECTOR3 GetVelocity() const { return velocity; }
	void SetVelocity(const VECTOR3& vel) { velocity = vel; }

	//デバック用
	// VECTOR3 poston = VECTOR3(0, 350, -500);
	// VECTOR3 target = VECTOR3(0, 250, 0);
};