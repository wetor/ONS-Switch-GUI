#include "GUIMain.h"



LayoutText::LayoutText() {
	int x = LEFT;
	int space = 20;
	version_text = new pu::element::TextBlock(x, TOP, "Version: Alpha 0.1");
	
	x += version_text->GetWidth() + space;
	other_text = new pu::element::TextBlock(x, TOP, "This is a test gui.");
	//x += other_text->GetWidth() + 10;

	battery_text = new pu::element::TextBlock(0, TOP, " 50%");
	x = SCREEN_WIDTH - LEFT - battery_text->GetWidth();
	battery_text->SetX(x);

	time_text = new pu::element::TextBlock(0, TOP, "12:01");
	x -= time_text->GetWidth() + space;
	time_text->SetX(x);

	this->Add(version_text);
	this->Add(other_text);
	this->Add(battery_text);
	this->Add(time_text);
}
void LayoutText::Update() {
	//battery_text->SetText();
	//time_text->SetText();
}

GUIMain::GUIMain() {
	layout_text = new LayoutText();
	layout_game_menu = new LayoutGameMenu();

	this->AddThread(std::bind(&LayoutText::Update, layout_text));
	this->LoadLayout(this->layout_text);

}