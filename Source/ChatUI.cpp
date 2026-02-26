#include "ChatUI.h"
#include "../Library/Input.h"
#include "../Source/Screen.h"
#include <string>

namespace {
	const int CHATBOX_SIZE = 50;
	const int CHATHISTORY_SIZE = 100;
}

ChatUI::ChatUI(std::string playerName) {
	isShowing = false;
	inputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	playerName_ = playerName;
}

ChatUI::~ChatUI() {
}

void ChatUI::Update() {
	if (Input::IsKeyOnTrig(KEY_INPUT_F1)) {
		isShowing = !isShowing;

		if (isShowing) {
			SetActiveKeyInput(inputHandle);
		}
		else {
			SetKeyInputString("", inputHandle);
			SetActiveKeyInput(-1);
		}
	}

	if (Input::IsKeyOnTrig(KEY_INPUT_RETURN)) {
		if (isShowing) {
			std::string convertChat(chatString);
			chatNameHistory.push_back(playerName_);
			chatStringHistory.push_back(convertChat);
			SetKeyInputString("", inputHandle);

			isShowing = false;
			SetActiveKeyInput(-1);
		}
	}

	if (isShowing) {
		SetActiveKeyInput(inputHandle);
		GetKeyInputString(chatString, inputHandle);
	}
}

void ChatUI::Draw() {
	if (!isShowing) return;
	const int chatBoxLeftY = Screen::HEIGHT - CHATBOX_SIZE;
	
	//—š—ð‚ÌUI
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, chatBoxLeftY - CHATHISTORY_SIZE, Screen::WIDTH, chatBoxLeftY, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int fontSize = GetFontSize();
	SetFontSize(CHATFONT_SIZE);
	int maxCount = CHATHISTORY_SIZE / GetFontSize();
	const int viewMaxSize = chatNameHistory.size() <= maxCount ? chatNameHistory.size() : maxCount;
	for (int n = 0; n < viewMaxSize; n++) {
		int index = chatNameHistory.size() - 1 - n;
		std::string name = chatNameHistory[index];
		std::string chat = chatStringHistory[index];

		std::string chatFormat = "<" + name + ">: " + chat;
		DrawString(0, chatBoxLeftY - (GetFontSize() * (n+1)), chatFormat.c_str(), GetColor(255, 255, 255));
	}
	SetFontSize(fontSize);


	//“ü—Í—“‚ÌUI
	fontSize = GetFontSize();
	DrawBox(0, chatBoxLeftY, Screen::WIDTH, Screen::HEIGHT, GetColor(0,0,0), true);
	SetFontSize(40);
	DrawString(0, chatBoxLeftY, chatString, GetColor(255, 255, 255));
	SetFontSize(fontSize);
}
