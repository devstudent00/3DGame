#pragma once
#include "Object3D.h"
#include <string>

class Axe : public Object3D {
private:
public:
	Axe();
	~Axe();
	void Update() override;
};