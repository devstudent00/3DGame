#include "SlotUI.h"
#include "Screen.h"

namespace {
	const int MAX_SLOT = 5;
}

SlotUI::SlotUI() {
	selectSlot = 0;
}

SlotUI::~SlotUI() {
}

void SlotUI::Draw() {

	//
	int mouseWheel = GetMouseWheelRotVol();
	if (mouseWheel > 0) {
		selectSlot--;
		if (selectSlot < 0) {
			selectSlot = MAX_SLOT - 1;
		}
	}
	else if (mouseWheel < 0) {
		selectSlot++;
		if (selectSlot >= MAX_SLOT) {
			selectSlot = 0;
		}
	}

	// アイテムUI
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	int sizeX = 500, sizeY = 150;
	int leftX = Screen::WIDTH / 2 - (sizeX / 2), leftY = Screen::HEIGHT - (sizeY / 2);
	int rightX = Screen::WIDTH / 2 + (sizeX / 2), rightY = Screen::HEIGHT;
	DrawBox(leftX, leftY, rightX, rightY, GetColor(0, 0, 0), true);

	//選択中のスロットを描画
	int oneSlotSize = (sizeX / MAX_SLOT); //例：500[※全ての大きさ] / 5[※スロット数]：100
	int selectLeftX = leftX + (oneSlotSize * (selectSlot)); //例：左の座標 + (1個の幅*0～4)
	int selectRightX = leftX + (oneSlotSize * (selectSlot + 1)); //例（右は1個隣の左座標）： 左の座標 + (1この幅*1～5)
	DrawBox(selectLeftX, leftY, selectRightX, rightY, GetColor(255, 255, 255), false);

	//アイテムの仕切りを描画
	int itemNum = 5;
	for (int i = 0; i < itemNum + 1; i++) {
		int lineX = leftX + (sizeX / itemNum) * i;
		DrawLine(lineX, leftY, lineX, rightY, GetColor(255, 255, 255));
		DrawLine(leftX, leftY, rightX, leftY, GetColor(255, 255, 255));
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SlotUI::Update() {
}
