#include "PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "ChatUI.h"
#include "Screen.h"
#include "Axe.h"

namespace {
	bool debug = true;
}

PlayScene::PlayScene()
{
	new Stage();
	new Player();
	new Axe();
	isPause = false;
	mouseVec = VECTOR3(0, 0, 0);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	static int beforeMouseX = 0;
	static int beforeMouseY = 0;
	
	GetMousePoint(&beforeMouseX, &beforeMouseY);
	mouseVec.x = beforeMouseX - Screen::WIDTH / 2;
	mouseVec.y = beforeMouseY - Screen::HEIGHT / 2;

	if (Input::IsKeyOnTrig(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (Input::IsKeyOnTrig(KEY_INPUT_ESCAPE)) {
		isPause = !isPause;
	}

	beforeMouseX = Screen::WIDTH / 2;
	beforeMouseY = Screen::HEIGHT / 2;
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", COL_WHITE);
	DrawString(100, 400, "Push [T]Key To Title", COL_WHITE);

	DrawFormatString(0, 100, GetColor(255, 255, 255), "Mouse Vec: (%.2f %.2f)", GetMouseVec().x, GetMouseVec().y);

	if (debug) {
		Player* player = ObjectManager::FindGameObject<Player>();
		ChatUI* chatUI = ObjectManager::FindGameObject<ChatUI>();
		VECTOR3 newRot = player->GetRotation();
		float newRotX = newRot.x;
		static float newRotY = newRot.y;
		float newRotZ = newRot.z;
		
		ImGui::Begin("Debug");
		ImGui::Text("Player Position: (%.2f, %.2f, %.2f)", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
		ImGui::Text("Player Rotation: (%.2f, %.2f, %.2f)", player->GetRotation().x, player->GetRotation().y, player->GetRotation().z);
		//ImGui::SliderFloat("RotationY", &newRotY, 0, 360);
		ImGui::Text("Player Velocity: (%.2f, %.2f, %.2f)", player->GetVelocity().x, player->GetVelocity().y, player->GetVelocity().z);
		ImGui::SliderInt(u8"チャットのフォントの大きさ", &chatUI->CHATFONT_SIZE, 1, 50);
		ImGui::End();

		//player->SetRotation();
	}
}
