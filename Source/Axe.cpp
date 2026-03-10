#include "Axe.h"
#include <cassert>
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "Player.h"

Axe::Axe()
{
	canDraw = true;
	hModel = MV1LoadModel("data/models/Character/Weapon/Axe/Axe.mv1");
	assert(hModel > 0);
	MV1SetupCollInfo(hModel, -1);
	pickTime = 10;
}

Axe::Axe(VECTOR3 location)
{
	canDraw = true;
	hModel = MV1LoadModel("data/models/Character/Weapon/Axe/Axe.mv1");
	postion = location;
	MV1SetupCollInfo(hModel, -1);
	pickTime = 10;
}

Axe::~Axe()
{
}

void Axe::Update()
{
	if (pickTime >= 0.0f) {
		pickTime -= Time::DeltaTime();
	}
	

	// 回転を調整
	rotation.y += 3.0f * DegToRad;
	rotation.z = -90.0f * DegToRad; 

	Stage* stage = FindGameObject<Stage>();
	VECTOR3 hitPos;
	if (stage->CollideRay(postion + VECTOR3(0, 1000, 0), postion + VECTOR3(0, -1000, 0), &hitPos)) {
		postion = hitPos; //当たってら、位置を当たった場所にする
	}

	Player* player = FindGameObject<Player>();
	if (player->CollideRay(postion + VECTOR3(0, 50, 0), postion + VECTOR3(0, -50, 0), &hitPos) && pickTime <= 0.0f) {
		// アイテムを取得
		player->AddItem(ITEM_ID);
		// アイテムを消す
		canDraw = false;
		DestroyMe();
	}

	ImGui::Begin("Axe Info");
	ImGui::Text("Position: (%.2f, %.2f, %.2f)", postion.x, postion.y, postion.z);
	ImGui::End();
}
