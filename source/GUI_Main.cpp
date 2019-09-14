#include "GUI_Main.h"
#include "GUI_WindowLayout.h"
using namespace std;

/*
窗口初始化
全局按键设置
 */
GUIMain::GUIMain()
{

	if (settings["darkmode"])
	{
		bg_color = pu::draw::Color(32, 32, 32, 225);
	}
	else
	{
		bg_color = pu::draw::Color(225, 225, 225, 255);
	}
	pu::element::Image *image;
	pu::element::TextBlock *textblock;
	pu::element::Button *button;
	pu::element::Rectangle *rect;

	pu::render::SetDefaultFontFromShared(pu::render::SharedFont::ChineseSimplified);
	//this->SetFPS(60);

	this->window_layout = new WindowLayout();
	this->window_layout->SetBackgroundColor(bg_color);
	this->AddThread(std::bind(&GUIMain::Update, this));
	this->AddThread(std::bind(&WindowLayout::Update, window_layout));

	//-----------------------顶部栏--------------------------------
	int x = LEFT_SIZE;
	//顶部区域
	rect = new pu::element::Rectangle(0, 0, SCREEN_WIDTH, TOP_HEIGHT, {255, 255, 255, 128}, 0);
	this->window_layout->Add(rect);

	//顶部标题
	textblock = new pu::element::TextBlock(x, TOP_SIZE, text["title"]);
	this->window_layout->Add(textblock);

	//顶部版本号
	x += textblock->GetWidth() + LEFT_SIZE * 2;
	textblock = new pu::element::TextBlock(x, TOP_SIZE, text["txt_version"] + text["version"]);
	this->window_layout->Add(textblock);

	//电池、时间
	x = SCREEN_WIDTH - BATTERY_WIDTH - LEFT_SIZE;
	this->battery_rect = new pu::element::Rectangle(x, TOP_SIZE / 2, BATTERY_WIDTH + 6, BATTERY_HEIGHT + 8, {48, 48, 48, 200}, 0);
	this->battery_bar = new pu::element::Rectangle(x + 3, TOP_SIZE / 2 + 4, BATTERY_WIDTH, BATTERY_HEIGHT, {0, 220, 0, 255}, 0);
	this->battery_text = new pu::element::TextBlock(0, TOP_SIZE, "100%");
	x -= (LEFT_SIZE + battery_text->GetWidth());
	this->battery_text->SetX(x);
	x -= (100 + LEFT_SIZE);
	this->time_text = new pu::element::TextBlock(x, TOP_SIZE, "00:00");

	this->window_layout->Add(battery_rect);
	this->window_layout->Add(battery_bar);
	this->window_layout->Add(battery_text);
	this->window_layout->Add(time_text);
	this->SetOnInput(std::bind(&GUIMain::OnInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

	//-----------------------其他----------------------------------

	license_text = new pu::element::TextBlock(0, 0, text["license"]);

	license_text->SetFont(pu::render::LoadSharedFont(pu::render::SharedFont::ChineseSimplified, 16));
	license_text->SetColor({0x7F, 0x7F, 0x7F, 0xEE});
	license_text->SetX((SCREEN_WIDTH - license_text->GetWidth()) / 2);

	int t_top = TOP_HEIGHT + 10;
	switch (this->window_layout->GetMeunType())
	{
	case pu::element::TYPE::TOP:
		t_top = BOTTOM - license_text->GetHeight() - TOP_SIZE;
		break;
	case pu::element::TYPE::DOWN:
		t_top = TOP_HEIGHT + TOP_SIZE;
		break;
	default:
		break;
	}
	license_text->SetY(t_top);
	
	

	this->window_layout->Add(license_text);

	curr_layout = CURR_LAYOUT::WINDOW;
	this->LoadLayout(window_layout);
}
void GUIMain::OnInput(u64 Down, u64 Up, u64 Held, bool Touch)
{

	switch (curr_layout)
	{
	case CURR_LAYOUT::WINDOW:
	{
		this->window_layout->OnInput(Down, Up, Held, Touch);
		if (this->window_layout->isShowHelp())
		{
			this->window_layout->HelpOnInput(Down, Up, Held, Touch);
			return;
		}
		else if (this->window_layout->isShowSetting())
		{
			this->window_layout->SettingOnInput(Down, Up, Held, Touch);
			return;
		}
		break;
	}
	default:
		break;
	}
	//reload
	if (Down & KEY_MINUS)
	{
		this->Close();
		loop_exit = true;
	}
	else if (Down & KEY_X) // If A is pressed, start with our dialog questions!
	{
		int opt = this->CreateShowDialog("Question", "Do you like apples?", {"Yes!", "No...", "Cancel"}, true); // (using latest option as cancel option)
		if ((opt == -1) || (opt == -2))																			// -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
		{
			this->CreateShowDialog("Cancel", "Last question was canceled.", {"Ok"}, true);
		}
		else
		{
			switch (opt)
			{
			case 0: // "Yes" was selected
				this->CreateShowDialog("Answer", "Really? I like apples too!", {"Ok"}, true);
				break;
			case 1: // "No" was selected
				this->CreateShowDialog("Answer", "Oh... Then I guess you won't have an iPod...", {"(damnit, he caught me)"}, true);
				break;
			}
		}
	}
}

void GUIMain::Update()
{
	if (loop_exit)
		this->Close();

	time_text->SetText(GetCurrentTime(false));
	int battery_value = GetBatteryLevel();
	int battery_show = battery_value;
	if (IsCharging())
		battery_show = ((SDL_GetTicks() / 250) % 10 + 1) * 10;
	battery_bar->SetWidth(battery_show * BATTERY_WIDTH / 100.0);

	char *batterystr = new char[5];
	sprintf(batterystr, "%d%%", battery_value);
	battery_text->SetText(std::string(batterystr));
	delete batterystr;


	int t_top = TOP_HEIGHT + 10;
	switch (this->window_layout->GetMeunType())
	{
	case pu::element::TYPE::TOP:
		t_top = BOTTOM - license_text->GetHeight() - TOP_SIZE;
		break;
	case pu::element::TYPE::DOWN:
		t_top = TOP_HEIGHT + TOP_SIZE;
		break;
	default:
		break;
	}
	license_text->SetY(t_top);
}
