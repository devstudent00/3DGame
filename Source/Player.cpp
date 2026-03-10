#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stage.h"
#include "ChatUI.h"
#include "PlayScene.h"
#include "Screen.h"
#include "Axe.h"

namespace {
	static const float LIMIT_ROTATION = 50.0f;
}

Player::Player()
{
	//SetCameraPositionAndTarget_UpVecY(poston, target);

	hModel = MV1LoadModel("data/models/Character/Player/PC.mv1");
	assert(hModel > 0);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));
	MV1SetupCollInfo(hModel, -1);

	cameraRotationVec = VECTOR3(0, 0, 0);

	hasItemIdVector = std::vector<int>();
	for (int i = 0; i < 5; i++) {
		hasItemIdVector.push_back(-1);
	}
}

Player::~Player()
{
}

void Player::Update()
{
	PlayScene* playScene = (PlayScene*) SceneManager::CurrentScene();
	if (playScene->IsPause()) return;
	VECTOR3 mouseVec = playScene->GetMouseVec();
	
	ChatUI* chatUI = FindGameObject<ChatUI>();
	if (!chatUI->IsShowing()) {
		//if (CheckHitKey(KEY_INPUT_D)) {
		//	rotation.y += 3.0f * DegToRad;
		//}
		//if (CheckHitKey(KEY_INPUT_A)) {
		//	rotation.y -= 3.0f * DegToRad;
		//}
		if (mouseVec.x > 0) {
			cameraRotationVec.y += 3.0f * DegToRad;
			rotation.y += 3.0f * DegToRad;
		}
		else if (mouseVec.x < 0) {
			cameraRotationVec.y -= 3.0f * DegToRad;
			rotation.y -= 3.0f * DegToRad;
		}

		if (mouseVec.y > 0) {
			if (cameraRotationVec.x > LIMIT_ROTATION * DegToRad) {
				cameraRotationVec.x = LIMIT_ROTATION * DegToRad;
			}
			else {
				cameraRotationVec.x += 3.0f * DegToRad;
			}
		}
		else if (mouseVec.y < 0) {
			if (cameraRotationVec.x < -LIMIT_ROTATION * DegToRad) {
				cameraRotationVec.x = -LIMIT_ROTATION * DegToRad;
			}
			else {
				cameraRotationVec.x -= 3.0f * DegToRad;
			}
		}
		
		const float speed = 5.0f;
		float x = speed * sinf(rotation.y) * Time::DeltaTime();
		float z = speed * cosf(rotation.y) * Time::DeltaTime();
		if (CheckHitKey(KEY_INPUT_W)) {
			//postion.x += (5.0f * sinf(rotation.y)); 
			//postion.z += (5.0f * cosf(rotation.y));

			//velocity = VECTOR3(x, 0, z);
			velocity = VECTOR3(0, 0, 6.0) * MGetRotY(rotation.y);
			//         ↑回っていないときの移動ベクトル * 回転行列
			postion += velocity;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			//postion.x -= (5.0f * sinf(rotation.y));
			//postion.z -= (5.0f * cosf(rotation.y));
			velocity = VECTOR3(0, 0, -6.0f) * MGetRotY(rotation.y);
			postion += velocity;
		}

		if (Input::IsKeyOnTrig(KEY_INPUT_F5)) {
			cameraSelect = !cameraSelect;
		}

		if (Input::IsKeyOnTrig(KEY_INPUT_Q)) {
			// アイテムを消す
			for (int i = 0; i < hasItemIdVector.size(); i++) {
				hasItemIdVector[i] = -1;
				// ドロップの描画
				new Axe();
				
			}
		}
	}


	//const float JUMP = 15;
	//const float gravity = 1.0f;

	//if (CheckHitKey(KEY_INPUT_SPACE)) {
	//	velocity.y = 15;
	//}
	//postion.y -= velocity.y;
	//velocity.y -= gravity;

	//SetCameraPositionAndTarget_UpVecY(VECTOR3(0, 350, -500), VECTOR3(0, 250, 0));

	//カメラ位置は、回ってないプレイヤーとの相対位置 * プレイヤーの回転 + プレイヤーの位置

	if (cameraSelect) {
		canDraw = true;
		// 3人称視点
		VECTOR3 playerCameraPos = VECTOR3(0, 350, -600); //相対位置：プレイヤー - (0, 350, -600)
		MATRIX rotationMatX = MGetRotX(cameraRotationVec.x); //回転行列
		MATRIX rotationMatY = MGetRotY(rotation.y); //回転行列
		// MATRIX rotationMat = rotationMatY * rotationMatX; 
		MATRIX rotationMat = rotationMatX * rotationMatY;
		VECTOR3 cameraPos = playerCameraPos * rotationMat + postion;
		// VECTOR3 targetPos = VECTOR3(0, 250, 0) + postion;
		VECTOR3 targetPos = VECTOR3(0, 250, 0) * rotationMat + postion;
		SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);
	}
	else {
		canDraw = false;
		// 1人称視点
		VECTOR3 playerCameraPos = VECTOR3(0, 150, 50); //相対位置：プレイヤー - (0, 350, -600)
		MATRIX rotationMatX = MGetRotX(cameraRotationVec.x); //回転行列
		MATRIX rotationMatY = MGetRotY(rotation.y); //回転行列
		// MATRIX rotationMat = rotationMatY * rotationMatX; 
		MATRIX rotationMat = rotationMatX * rotationMatY;
		VECTOR3 cameraPos = playerCameraPos * rotationMat + postion;
		// VECTOR3 targetPos = VECTOR3(0, 250, 0) + postion;
		VECTOR3 targetPos = VECTOR3(0, 150, 100) * rotationMat + postion;
		SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);
	}


	//地面との当たり判定
	Stage* stage = FindGameObject<Stage>();
	VECTOR3 hitPos;
	if (stage->CollideRay(postion + VECTOR3(0, 1000, 0), postion + VECTOR3(0, -1000, 0), &hitPos)) {
		postion = hitPos; //当たってら、位置を当たった場所にする
	}

	SetMousePoint(Screen::WIDTH / 2, Screen::HEIGHT / 2);
}

void Player::AddItem(int itemID)
{
	for (int i = 0; i < hasItemIdVector.size(); i++) {
		if (hasItemIdVector[i] == -1) {
			hasItemIdVector[i] = itemID;
			return;
		}
	}
}

void Player::RemoveItem(int itemID)
{
	auto it = std::find(hasItemIdVector.begin(), hasItemIdVector.end(), itemID);
	if (it != hasItemIdVector.end()) { //ある（最後のイテレータじゃない）場合は追加
		hasItemIdVector.erase(it);
	}
}

bool Player::HasItem(int itemID) const
{
	if (std::find(hasItemIdVector.begin(), hasItemIdVector.end(), itemID) != hasItemIdVector.end()) { //ある（最後のイテレータじゃない）場合は追加
		return true;
	}
	return false;
}

int Player::GetItem(int index) const
{
	if (index >= 0 && index < hasItemIdVector.size()) {
		return hasItemIdVector[index];
	}
	return -1;
}
