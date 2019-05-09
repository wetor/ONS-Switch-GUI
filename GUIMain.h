#pragma once
#include <pu/Plutonium>
#include "define.h"
class LayoutText : public pu::Layout
{
public:
	LayoutText();
	void Update();
private:
	// An easy way to keep objects is to have them as private pointer members
	pu::element::TextBlock *version_text;
	pu::element::TextBlock *time_text;
	pu::element::TextBlock *other_text;
	pu::element::TextBlock *battery_text;
};

class LayoutGameMenu : public pu::Layout
{
public:
	LayoutGameMenu() {};
private:
	pu::element::Menu *game_menu;

};

class GUIMain : public pu::Application
{
public:
	GUIMain();
private:
	// Layout instance
	LayoutText *layout_text;
	LayoutGameMenu *layout_game_menu;
};