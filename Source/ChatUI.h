#pragma once
#include "../Library/GameObject.h"
#include <map>
#include <string>
#include <vector>

class ChatUI : public GameObject {
private:
	// std::map<std::string, std::string> chatHistory;
	std::vector<std::string> chatNameHistory;
	std::vector<std::string> chatStringHistory;

	std::string playerName_;
	bool isShowing;
	int inputHandle;
	char chatString[256] = {};
public:
	int CHATFONT_SIZE = 30;

	ChatUI(std::string playerName);
	~ChatUI();
	void Update() override;
	void Draw() override;

	bool IsShowing() { return isShowing; };
};