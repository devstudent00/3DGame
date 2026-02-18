#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stage.h"

Player::Player()
{
	//SetCameraPositionAndTarget_UpVecY(poston, target);

	hModel = MV1LoadModel("data/models/Character/Player/PC.mv1");
	assert(hModel > 0);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));
}

Player::~Player()
{
}

void Player::Update()
{
	//
	if (CheckHitKey(KEY_INPUT_D)) {
		rotation.y += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		rotation.y -= 3.0f * DegToRad;
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

	//const float JUMP = 15;
	//const float gravity = 1.0f;

	//if (CheckHitKey(KEY_INPUT_SPACE)) {
	//	velocity.y = 15;
	//}
	//postion.y -= velocity.y;
	//velocity.y -= gravity;

	//SetCameraPositionAndTarget_UpVecY(VECTOR3(0, 350, -500), VECTOR3(0, 250, 0));

	//カメラ位置は、回ってないプレイヤーとの相対位置 * プレイヤーの回転 + プレイヤーの位置

	VECTOR3 playerCameraPos = VECTOR3(0, 350, -600); //相対位置：プレイヤー - (0, 350, -600)
	MATRIX rotationMat = MGetRotY(rotation.y); //回転行列
	VECTOR3 cameraPos = playerCameraPos * rotationMat + postion; 
	VECTOR3 targetPos = VECTOR3(0, 250, 0) + postion;
	SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);

	//地面との当たり判定
	Stage* stage = FindGameObject<Stage>();
	VECTOR3 hitPos;
	if (stage->CollideRay(postion + VECTOR3(0, 1000, 0), postion + VECTOR3(0, -1000, 0), &hitPos)) {
		postion = hitPos; //当たってら、位置を当たった場所にする
	}

}