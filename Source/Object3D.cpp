#include "Object3D.h"

Object3D::Object3D()
{
	hModel = -1;
	postion = VECTOR3(0, 0, 0);
	rotation = VECTOR3(0, 0, 0);
	velocity = VECTOR3(0, 0, 0);
}

Object3D::~Object3D()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Object3D::Draw() {
	MV1SetRotationXYZ(hModel, rotation);
	MV1SetPosition(hModel, postion);
	MV1DrawModel(hModel);
}
