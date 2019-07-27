#pragma once

#include <pu/Plutonium>
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"
#include "GUI_Utils.h"
#include "GUI_GameInfo.h"

extern bool loop_exit;

class LayoutWindow : public pu::Layout
{
public:
	LayoutWindow();
	bool isEmpty() { return game_list.empty(); }
	void Update();
	void OnInput(u64 Down, u64 Up, u64 Held, bool Touch);
	void ShowHelp(bool is_show);
	bool isShowHelp(){ return is_show_help; }
	void HelpOnInput(u64 Down, u64 Up, u64 Held, bool Touch);
	void ShowSetting(bool is_show);
	bool isShowSetting(){ return is_show_setting; }
	void SettingOnInput(u64 Down, u64 Up, u64 Held, bool Touch);

private:
	int old_select, now_select;


	vector<GameInfo*> game_list;


/* 主页面 */

	bool is_disable_menu = false;
	pu::element::Rectangle *battery_bar;
	pu::element::Rectangle *battery_rect;

	pu::element::TextBlock *time_text;
	pu::element::TextBlock *battery_text;


	map<int,int> button_index; 
	vector<pu::element::Element *> menu_elms;
	pu::element::MenuEX *menu;
	

	/*帮助窗口 左侧 半屏幕*/
	bool is_show_help = false;
	vector<pu::element::Element *> help_elms;

	pu::element::Rectangle *help_window;
	pu::element::Rectangle *help_window_rect;
	

	



	/*设置窗口 */

	bool is_show_setting = false;
	vector<pu::element::Element *> setting_elms;

	enum SETTING_BUTTON{
		SET_BEGIN,
		SET_LANGUAGE,
		SET_DARKMODE,
		SET_FULLSCREEN,
		SET_END,
	};
	map<SETTING_BUTTON,int> setting_index; 
	SETTING_BUTTON focus_button;
	pu::element::Rectangle *setting_window;
	pu::element::Rectangle *setting_window_rect;



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
private:

	// Layout instance

	LayoutWindow *layout_window;
};

