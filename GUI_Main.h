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
	bool isEmpty() { return game_list.empty(); }
	void Update();
private:
	int old_select, now_select;


	vector<GameInfo*> game_list;
	pu::render::NativeFont font;


	pu::element::Rectangle *battery_bar;
	pu::element::Rectangle *battery_rect;

	pu::element::TextBlock *version_text;
	pu::element::TextBlock *time_text;
	pu::element::TextBlock *other_text;
	pu::element::TextBlock *battery_text;
	pu::element::TextBlock *menu_text;

	pu::element::MenuEX *menu;
	

	pu::element::Rectangle *top_rect;
	pu::element::Rectangle *button_rect;

	pu::element::Button *A_button;//确认
	pu::element::Button *B_button;//取消
	//pu::element::Button *X_button;
	pu::element::Button *Y_button;//查看信息
	pu::element::Button *L_button;//帮助
	pu::element::Button *X_button;//资源查看
	pu::element::Button *R_button;//播放器
	pu::element::Button *PLUS_button;//设置
	pu::element::Button *MINUS_button;//重载
	

};

class GUIMain : public pu::Application
{
public:
	GUIMain();
	void LoadConfig();
private:
	// Layout instance
	LayoutMenu *layout_menu;
	
};

