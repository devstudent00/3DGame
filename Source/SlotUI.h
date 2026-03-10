#pragma once
#include "../Library/GameObject.h"

namespace {
	const int MAX_SLOT = 5;
}

class SlotUI : public GameObject {
private:
	int selectSlot;
	int axe;
public:
	SlotUI();
	~SlotUI();
	void Draw() override;
	void Update() override;

	int GetSelectSlot() const { return selectSlot; }
};