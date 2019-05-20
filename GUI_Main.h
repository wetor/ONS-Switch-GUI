#pragma once

#include <pu/Plutonium>
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"
#include "GUI_Utils.h"
#include "GUI_GameInfo.h"



class LayoutMenu : public pu::Layout
{
public:
	LayoutMenu();
	void Update();
private:
	pu::render::NativeFont font;

	pu::element::TextBlock *version_text;
	pu::element::TextBlock *time_text;
	pu::element::TextBlock *other_text;
	pu::element::TextBlock *battery_text;
	pu::element::TextBlock *menu_text;

	pu::element::MenuEX *menu;
	vector<GameInfo*> game_list;

	pu::element::Rectangle *top_rect;
	pu::element::Rectangle *button_rect;

	pu::element::Button *A_button;//确认
	pu::element::Button *B_button;//取消
	//pu::element::Button *X_button;
	pu::element::Button *Y_button;//查看信息
	pu::element::Button *L_button;
	pu::element::Button *R_button;
	pu::element::Button *PLUS_button;//退出

};

class GUIMain : public pu::Application
{
public:
	GUIMain();
	bool isExit() { return exit; };
	void LoadConfig();
private:
	bool exit;
	// Layout instance
	LayoutMenu *layout_menu;
	
};