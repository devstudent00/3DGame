#include "Axe.h"
#include <cassert>
#include "Stage.h"
#include "../ImGui/imgui.h"

Axe::Axe()
{
	hModel = MV1LoadModel("data/models/Character/Weapon/Axe/Axe.mv1");
	assert(hModel > 0);
}

Axe::~Axe()
{
}

void Axe::Update()
{
	// ‰ñ“]‚ğ’²®
	rotation.y += 3.0f * DegToRad;
	rotation.z = -90.0f * DegToRad; 

	//’n–Ê‚Æ‚Ì“–‚½‚è”»’è
	Stage* stage = FindGameObject<Stage>();
	VECTOR3 hitPos;
	if (stage->CollideRay(postion + VECTOR3(0, 0, 0), postion + VECTOR3(0, 100, 0), &hitPos)) {
		postion = hitPos; //“–‚½‚Á‚Ä‚çAˆÊ’u‚ğ“–‚½‚Á‚½êŠ‚É‚·‚é
	}

	ImGui::Begin("Axe Info");
	ImGui::SliderFloat("RotX", &rotation.x, -180.0f, 180.0f);
	ImGui::SliderFloat("RotY", &rotation.y, -180.0f, 180.0f);
	ImGui::SliderFloat("RotZ", &rotation.z, -180.0f, 180.0f);
	ImGui::End();
}
