#pragma once

#include <pu/Plutonium>
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"
#include "GUI_Utils.h"
#include "GUI_GameInfo.h"

class WindowLayout : public pu::ui::Layout
{
public:
	WindowLayout();
	PU_SMART_CTOR(WindowLayout)
	bool isEmpty() { return game_list.empty(); }
	void Update();
	void OnInput(u64 Down, u64 Up, u64 Held, bool Touch);
	void ShowHelp(bool is_show);
	bool isShowHelp(){ return is_show_help; }
	void HelpOnInput(u64 Down, u64 Up, u64 Held, bool Touch);
	void ShowSetting(bool is_show);
	bool isShowSetting(){ return is_show_setting; }
	void SettingOnInput(u64 Down, u64 Up, u64 Held, bool Touch);
	pu::ui::elm::TYPE GetMeunType();


private:
    pu::ui::Color text_color;
	int old_select, now_select;
	vector<OnsGameInfo*> game_list;
    /* 主页面 */

	bool is_disable_menu = false;
	map<int,int> button_index; 
	vector<pu::ui::elm::Element::Ref> menu_elms;
	pu::ui::elm::MenuEX::Ref menu;

	
	/*帮助窗口 左侧 半屏幕*/
	bool is_show_help = false;
	vector<pu::ui::elm::Element::Ref> help_elms;
	pu::ui::elm::Rectangle::Ref help_window;
	pu::ui::elm::Rectangle::Ref help_window_rect;
	
	/*设置窗口 */
	bool is_show_setting = false;
	vector<pu::ui::elm::Element::Ref> setting_elms;

	enum SETTING{
		BEGIN,
		LANGUAGE,
		DARKMODE,
		ICONSTYLE,
		FULLSCREEN,
		FONTOUTLINE,
		END,
	};
	map<SETTING,int> setting_index; 
	SETTING focus_button;
	pu::ui::elm::Rectangle::Ref setting_window;
	pu::ui::elm::Rectangle::Ref setting_window_rect;



};
