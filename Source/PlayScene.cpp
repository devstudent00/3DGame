#include "PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "../ImGui/imgui.h"

namespace {
	bool debug = true;
}

PlayScene::PlayScene()
{
	new Stage();
	new Player();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyOnTrig(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", COL_WHITE);
	DrawString(100, 400, "Push [T]Key To Title", COL_WHITE);

	if (debug) {
		Player* player = ObjectManager::FindGameObject<Player>();
		
		ImGui::Begin("Debug");
		ImGui::Text("Player Position: (%.2f, %.2f, %.2f)", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
		ImGui::Text("Player Rotation: (%.2f, %.2f, %.2f)", player->GetRotation().x, player->GetRotation().y, player->GetRotation().z);
		ImGui::Text("Player Velocity: (%.2f, %.2f, %.2f)", player->GetVelocity().x, player->GetVelocity().y, player->GetVelocity().z);
		ImGui::End();
	}
}
