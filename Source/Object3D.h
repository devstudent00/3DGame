#pragma once
#include <DxLib.h>
#include "../Library/GameObject.h"

class Object3D : public GameObject {
protected:
	int hModel;
	VECTOR3 postion;
	VECTOR3 rotation;
	VECTOR3 velocity;
public:
	Object3D();
	virtual ~Object3D();
	// void Update() override;
	virtual void Draw() override;

	VECTOR3 GetPosition() const { return postion; }
	void SetPosition(const VECTOR3& pos) { postion = pos; }
	VECTOR3 GetRotation() const { return rotation; }
	void SetRotation(const VECTOR3& rot) { rotation = rot; }
	VECTOR3 GetVelocity() const { return velocity; }
	void SetVelocity(const VECTOR3& vel) { velocity = vel; }
};