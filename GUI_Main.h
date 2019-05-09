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
	pu::element::TextBlock *version_text;
	pu::element::TextBlock *time_text;
	pu::element::TextBlock *other_text;
	pu::element::TextBlock *battery_text;


	pu::element::Menu *menu;
	vector<pu::element::Image*> game;
	vector<GameInfo*> game_list;

};

class GUIMain : public pu::Application
{
public:
	GUIMain();
private:
	// Layout instance
	LayoutMenu *layout_menu;
	
};