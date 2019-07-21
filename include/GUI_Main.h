#pragma once

#include <pu/Plutonium>
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"
#include "GUI_Utils.h"
#include "GUI_GameInfo.h"

extern bool loop_exit;
extern map<string,int> game_settings; 

class LayoutWindow : public pu::Layout
{
public:
	LayoutWindow();
	bool isEmpty() { return game_list.empty(); }
	void Update();
	void ShowHelp(bool is_show);
	bool isShowHelp(){ return is_show_help; }
	void ShowSetting(bool is_show);
	bool isShowSetting(){ return is_show_setting; }
	void ApplySetting();
private:
	int old_select, now_select;


	vector<GameInfo*> game_list;


/* 主页面 */

	bool is_disable_menu = false;
	pu::element::Rectangle *battery_bar;
	pu::element::Rectangle *battery_rect;

	pu::element::TextBlock *version_text;
	pu::element::TextBlock *time_text;
	pu::element::TextBlock *other_text;
	pu::element::TextBlock *battery_text;
	pu::element::TextBlock *menu_text;


	pu::element::Rectangle *top_rect;
	pu::element::Rectangle *button_rect;


	vector<pu::element::Element *> menu_elms;
	pu::element::MenuEX *menu;
	
	pu::element::Button *A_button;
	pu::element::Button *B_button;
	pu::element::Button *Y_button;
	pu::element::Button *L_button;
	pu::element::Button *X_button;
	pu::element::Button *R_button;
	pu::element::Button *PLUS_button;
	pu::element::Button *MINUS_button;

	/*帮助窗口 左侧 半屏幕*/
	bool is_show_help = false;
	vector<pu::element::Element *> help_elms;

	pu::element::Rectangle *help_window;
	pu::element::Rectangle *help_window_rect;
	vector<pu::element::Image *> help_images;
	vector<pu::element::TextBlock *> help_texts;
	

	



	/*设置窗口 */
	bool is_show_setting = false;
	vector<pu::element::Element *> setting_elms;

	pu::element::Rectangle *setting_window;
	pu::element::Rectangle *setting_window_rect;
	vector<pu::element::Button *> setting_buttons;
	vector<pu::element::TextBlock *> setting_texts;
	map<string,int> settings; 

};





class LayoutHelp : public pu::Layout
{
public:
	LayoutHelp();
private:

};

class GUIMain : public pu::Application
{
public:
	GUIMain();
	void Update();
	void LoadConfig();
private:

	// Layout instance

	LayoutWindow *layout_window;
};

