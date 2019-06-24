#pragma once

#include <pu/Plutonium>
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"
#include "GUI_Utils.h"
#include "GUI_GameInfo.h"

extern bool loop_exit;

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

	pu::element::Button *A_button;//ȷ��
	pu::element::Button *B_button;//ȡ��
	//pu::element::Button *X_button;
	pu::element::Button *Y_button;//�鿴��Ϣ
	pu::element::Button *L_button;//����
	pu::element::Button *X_button;//��Դ�鿴
	pu::element::Button *R_button;//������
	pu::element::Button *PLUS_button;//����
	pu::element::Button *MINUS_button;//����
	

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

