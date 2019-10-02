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


class GUIMain : public pu::ui::Application
{
public:
	GUIMain();
	PU_SMART_CTOR(GUIMain)
	void Update();
	void OnInput(u64 Down, u64 Up, u64 Held, bool Touch);
private:
	pu::ui::elm::Rectangle::Ref battery_bar;
	pu::ui::elm::Rectangle::Ref battery_rect;

	pu::ui::elm::TextBlock::Ref time_text;
	pu::ui::elm::TextBlock::Ref battery_text;

	pu::ui::elm::TextBlock::Ref license_text;

	pu::ui::Color bg_color;

	// Layout instance
	CURR_LAYOUT curr_layout;
	WindowLayout::Ref window_layout;
	PlayerLayout* player_layout;
};

