#include "Stage.h"
#include <cassert>
#include "ChatUI.h"
#include "Screen.h"

Stage::Stage()
{
	hModel = MV1LoadModel("data/models/Stage/Stage00.mv1");
	assert(hModel > 0);
	MV1SetupCollInfo(hModel, -1);

	new ChatUI("Player");
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	MV1DrawModel(hModel);

	// アイテムUI
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	int sizeX = 500, sizeY = 150;
	int leftX = Screen::WIDTH / 2 - (sizeX / 2), leftY = Screen::HEIGHT - (sizeY / 2);
	int rightX = Screen::WIDTH / 2 + (sizeX / 2), rightY = Screen::HEIGHT;
	DrawBox(leftX, leftY, rightX, rightY, GetColor(0, 0, 0), true);
	
	//アイテムの仕切りを描画
	int itemNum = 5;
	for (int i = 0; i < itemNum + 1; i++) {
		int lineX = leftX + (sizeX / itemNum) * i;
		DrawLine(lineX, leftY, lineX, rightY, GetColor(255, 255, 255));
		DrawLine(leftX, leftY, rightX, leftY, GetColor(255, 255, 255));
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Stage::CollideRay(VECTOR3 start, VECTOR3 end, VECTOR3* hit) {

	MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(hModel, -1, start, end);
	if (result.HitFlag > 0) {
		if (hit != nullptr) {
			*hit = result.HitPosition;
		}
		return true;
	}
	return false;
}
