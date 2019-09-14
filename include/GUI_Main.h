#pragma once

#include <pu/Plutonium>
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"
#include "GUI_Utils.h"
#include "GUI_GameInfo.h"
#include "GUI_ExplorerLayout.h"
#include "GUI_PlayerLayout.h"
#include "GUI_WindowLayout.h"

enum CURR_LAYOUT{
	WINDOW,
	PLAYER,
};


class GUIMain : public pu::Application
{
public:
	GUIMain();
	void Update();
	void OnInput(u64 Down, u64 Up, u64 Held, bool Touch);
private:
	pu::element::Rectangle *battery_bar;
	pu::element::Rectangle *battery_rect;

	pu::element::TextBlock *time_text;
	pu::element::TextBlock *battery_text;

	pu::element::TextBlock *license_text;

	pu::draw::Color bg_color;

	// Layout instance
	CURR_LAYOUT curr_layout;
	WindowLayout *window_layout;
	PlayerLayout *player_layout;
};

