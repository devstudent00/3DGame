#pragma once
#include "../Library/GameObject.h"

class SlotUI : public GameObject {
private:
	int selectSlot;
public:
	SlotUI();
	~SlotUI();
	void Draw() override;
	void Update() override;

};