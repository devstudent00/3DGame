#pragma once
#include "Object3D.h"
#include <string>
#define ITEM_ID 0x000001

class Axe : public Object3D {
private:
	float pickTime;
public:
	Axe();
	Axe(VECTOR3 location);
	~Axe();
	void Update() override;
};