#include "GUI_Main.h"

using namespace std;

static pu::draw::Color text_color(0, 0, 0, 255);
static pu::draw::Color bg_color(225, 225, 225, 255);

LayoutWindow::LayoutWindow()
{
	menu_elms.clear();
	help_elms.clear();
	setting_elms.clear();

	pu::element::Image *image;
	pu::element::TextBlock *textblock;
	pu::element::Button *button;
	pu::element::Rectangle *rect;

	string path = DATA_PATH;
	path += "/";

	menu = new pu::element::MenuEX(0, TOP_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - TOP_HEIGHT - BOTTOM_HEIGHT, pu::draw::Color(150, 150, 150, 100), ICON_SIZE, ICON_SELECT_SIZE, ICON_NUM);
	int x = 0, y = 0;
	pu::element::MenuItem *item;
	vector<string> dirpath;
	GetGameDir(PATH, dirpath);

	for (int i = 0; i < (int)dirpath.size(); i++)
	{
		GameInfo *info_tmp = new GameInfo(dirpath[i]);
		game_list.push_back(info_tmp);
		item = new pu::element::MenuItem(game_list[i]->GetName());
		item->SetColor(text_color);
		item->SetIcon(game_list[i]->GetIconPath(0));
		string gamepath = this->game_list[i]->GetPath();
		item->AddOnClick([info_tmp]() { //RunGame
			RunGame(info_tmp);
		});
		//cout << game_list[i]->GetIconPath(0) << endl;
		x += ICON_SIZE + 10;
		menu->AddItem(item);
	}
	this->Add(menu);
	menu_elms.push_back(menu);
	if (dirpath.empty())
	{
		textblock = new pu::element::TextBlock(0, 0, text["txt_nogame"]);
		x = (SCREEN_WIDTH - textblock->GetWidth()) / 2;
		textblock->SetX(x);
		x = (SCREEN_HEIGHT - textblock->GetHeight()) / 2;
		textblock->SetY(x);
		this->Add(textblock);
		menu_elms.push_back(textblock);
	}

	old_select = -1;
	now_select = 0;

	//-----------------------顶部栏--------------------------------
	x = LEFT;

	rect = new pu::element::Rectangle(0, 0, SCREEN_WIDTH, TOP_HEIGHT, {255, 255, 255, 128}, 0);
	this->Add(rect);

	textblock = new pu::element::TextBlock(x, TOP, text["title"]);
	this->Add(textblock);

	x += textblock->GetWidth() + LEFT * 2;
	textblock = new pu::element::TextBlock(x, TOP, text["txt_version"] + text["version"]);
	this->Add(textblock);

	x = SCREEN_WIDTH - BATTERY_WIDTH - LEFT;
	battery_rect = new pu::element::Rectangle(x, TOP / 2, BATTERY_WIDTH + 6, BATTERY_HEIGHT + 8, {48, 48, 48, 200}, 0);
	this->Add(battery_rect);
	battery_bar = new pu::element::Rectangle(x + 3, TOP / 2 + 4, BATTERY_WIDTH, BATTERY_HEIGHT, {0, 220, 0, 255}, 0);
	this->Add(battery_bar);
	battery_text = new pu::element::TextBlock(0, TOP, "100%");
	x -= (LEFT + battery_text->GetWidth());
	battery_text->SetX(x);
	this->Add(battery_text);

	x -= (100 + LEFT);
	time_text = new pu::element::TextBlock(x, TOP, "00:00");
	this->Add(time_text);

	//-----------------浏览框 左右 图标-------------------
	rect = new pu::element::Rectangle(5, TOP_HEIGHT + ICON_SELECT_SIZE - BUTTON_HEIGHT - 5, BUTTON_HEIGHT, BUTTON_HEIGHT, {255, 255, 255, 128}, 0);
	this->Add(rect);

	image = new pu::element::Image(5, TOP_HEIGHT + ICON_SELECT_SIZE - BUTTON_HEIGHT - 5, path + onsdata[OKEY_DLEFT].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);

	rect = new pu::element::Rectangle(SCREEN_WIDTH - BUTTON_HEIGHT - 5, TOP_HEIGHT + ICON_SELECT_SIZE - BUTTON_HEIGHT - 5, BUTTON_HEIGHT, BUTTON_HEIGHT, {255, 255, 255, 128}, 0);
	this->Add(rect);
	image = new pu::element::Image(SCREEN_WIDTH - BUTTON_HEIGHT - 5, TOP_HEIGHT + ICON_SELECT_SIZE - BUTTON_HEIGHT - 5, path + onsdata[OKEY_DRIGHT].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//-----------------下方按钮-------------------

	x = LEFT;
	y = BUTTON_BOTTOM;

	rect = new pu::element::Rectangle(0, BOTTOM, SCREEN_WIDTH, BOTTOM_HEIGHT, {255, 255, 255, 128}, 0);
	this->Add(rect);

	//L 帮助
	image = new pu::element::Image(x, y, path + onsdata[OKEY_L].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, (settings["language"] == English ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH), BUTTON_HEIGHT, text["btn_help"], {0, 0, 0, 255}, {255, 255, 255, 0});
	button->SetOnClick([&]() {
		this->ShowHelp(!isShowHelp());
	});
	this->Add(button);
	button_index[OKEY_L] = menu_elms.size();
	menu_elms.push_back(button);

	//A 确定
	x += (settings["language"] == English ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH) + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_A].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_ok"], {0, 0, 0, 255}, {255, 255, 255, 0});
	button->SetOnClick([&]() {
		RunGame(game_list[menu->GetSelectedIndex()]); //启动游戏
	});
	this->Add(button);
	button_index[OKEY_A] = menu_elms.size();
	menu_elms.push_back(button);

	//B 取消
	x += BUTTON_WIDTH + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_B].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_back"], {0, 0, 0, 255}, {255, 255, 255, 0});
	button->SetOnClick([&] {
		if (this->isShowHelp())
			this->ShowHelp(false);
		if (this->isShowSetting())
			this->ShowSetting(false);
	});
	this->Add(button);
	button_index[OKEY_B] = menu_elms.size();
	menu_elms.push_back(button);

	//Y 信息
	x += BUTTON_WIDTH + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_Y].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, (settings["language"] == English ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH), BUTTON_HEIGHT, text["btn_info"], {0, 0, 0, 255}, {255, 255, 255, 0});
	this->Add(button);
	button_index[OKEY_Y] = menu_elms.size();
	menu_elms.push_back(button);

	//X 资源
	x += (settings["language"] == English ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH) + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_X].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_res"], {0, 0, 0, 255}, {255, 255, 255, 0});
	this->Add(button);
	button_index[OKEY_X] = menu_elms.size();
	menu_elms.push_back(button);

	//R播放器
	x += BUTTON_WIDTH + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_R].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_player"], {0, 0, 0, 255}, {255, 255, 255, 0});
	this->Add(button);
	button_index[OKEY_R] = menu_elms.size();
	menu_elms.push_back(button);

	//+ 设置
	x = SCREEN_WIDTH - BUTTON_HEIGHT - LEFT - (settings["language"] == English ? BUTTON_WIDTH : BUTTON_WIDTH / 2);
	image = new pu::element::Image(x, y, path + onsdata[OKEY_PLUS].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, (settings["language"] == English ? BUTTON_WIDTH : BUTTON_WIDTH / 2), BUTTON_HEIGHT, text["btn_setting"], {0, 0, 0, 255}, {255, 255, 255, 0});
	button->SetOnClick([&] {
		this->ShowSetting(!isShowSetting());
	});
	this->Add(button);
	button_index[OKEY_PLUS] = menu_elms.size();
	menu_elms.push_back(button);

	//- 刷新
	x -= ((settings["language"] == English ? BUTTON_WIDTH : BUTTON_WIDTH / 2) + BUTTON_HEIGHT + LEFT * 2);
	image = new pu::element::Image(x, y, path + onsdata[OKEY_MINUS].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	button = new pu::element::Button(x + BUTTON_HEIGHT, y, (settings["language"] == English ? BUTTON_WIDTH : BUTTON_WIDTH / 2), BUTTON_HEIGHT, text["btn_refresh"], {0, 0, 0, 255}, {255, 255, 255, 0});
	button->SetOnClick([&] {
		loop_exit = true;
	});
	this->Add(button);
	button_index[OKEY_MINUS] = menu_elms.size();
	menu_elms.push_back(button);

	//-----------------帮助窗口----------------------

	help_window_rect = new pu::element::Rectangle(HELP_WINDOW_LEFT, TOP_HEIGHT, (settings["language"] == English ? HELP_WINDOW_WIDTH * 4 / 3 : HELP_WINDOW_WIDTH), WINDOW_HEIGHT, {50, 50, 50, 172}, 0);
	this->Add(help_window_rect);
	help_elms.push_back(help_window_rect);

	help_window = new pu::element::Rectangle(HELP_WINDOW_LEFT + 4, TOP_HEIGHT + 4, (settings["language"] == English ? HELP_WINDOW_WIDTH * 4 / 3 : HELP_WINDOW_WIDTH) - 8, WINDOW_HEIGHT - 8, {225, 225, 225, 172}, 0);
	this->Add(help_window);
	help_elms.push_back(help_window);

	x = HELP_WINDOW_LEFT + 32;
	y = TOP_HEIGHT + 24;
	textblock = new pu::element::TextBlock(x, y, text["help_title"]);
	textblock->SetX((HELP_WINDOW_LEFT + HELP_WINDOW_WIDTH - textblock->GetTextWidth()) / 2);
	this->Add(textblock);
	help_elms.push_back(textblock);
	y += 32 + 16;

	string tmp_text[12] = {"help_A", "help_B", "help_X", "help_Y", "help_UP", "help_DOWN", "help_LEFT", "help_RIGHT", "help_L", "help_R", "help_LS", "help_RS"};
	int tmp_okey[12] = {OKEY_A, OKEY_B, OKEY_X, OKEY_Y, OKEY_DUP, OKEY_DDOWN, OKEY_DLEFT, OKEY_DRIGHT, OKEY_L, OKEY_R, OKEY_LSTICK, OKEY_RSTICK};
	for (int i = 0; i < 12; i++)
	{
		image = new pu::element::Image(x, y, path + onsdata[tmp_okey[i]].name);
		image->SetWidth(BUTTON_HEIGHT);
		image->SetHeight(BUTTON_HEIGHT);
		this->Add(image);
		help_elms.push_back(image);
		textblock = new pu::element::TextBlock(x + 48, y + 3, text[tmp_text[i]]);
		this->Add(textblock);
		help_elms.push_back(textblock);
		y += 32 + 10;
	}
	pu::element::Rectangle *tmp_rect = new pu::element::Rectangle(x + 2, y + 2, BUTTON_HEIGHT - 4, BUTTON_HEIGHT - 4, {0, 0, 0, 255}, 0);
	this->Add(tmp_rect);
	help_elms.push_back(tmp_rect);
	textblock = new pu::element::TextBlock(x + 48, y + 3, text["help_screen"]);
	this->Add(textblock);
	help_elms.push_back(textblock);
	this->ShowHelp(false);

	//-----------------设置窗口----------------------

	setting_window_rect = new pu::element::Rectangle(SETTING_WINDOW_LEFT, TOP_HEIGHT, SETTING_WINDOW_WIDTH, WINDOW_HEIGHT, {50, 50, 50, 172}, 0);
	this->Add(setting_window_rect);
	setting_elms.push_back(setting_window_rect);

	setting_window = new pu::element::Rectangle(SETTING_WINDOW_LEFT + 4, TOP_HEIGHT + 4, SETTING_WINDOW_WIDTH - 8, WINDOW_HEIGHT - 8, {225, 225, 225, 172}, 0);
	this->Add(setting_window);
	setting_elms.push_back(setting_window);
	x = SETTING_WINDOW_LEFT + SETTING_WINDOW_WIDTH / 2 / 4;
	y = TOP_HEIGHT + 24;

	textblock = new pu::element::TextBlock(x, y, text["setting_gui"]);
	textblock->SetX(SETTING_WINDOW_LEFT + (SETTING_WINDOW_WIDTH - textblock->GetTextWidth()) / 2);
	this->Add(textblock);
	setting_elms.push_back(textblock);
	y += 48;

	button = new pu::element::Button(x, y, SETTING_WINDOW_WIDTH * 3 / 4, BUTTON_HEIGHT + 10, text["setting_language"] + text["language"], {0, 0, 0, 255}, {255, 255, 255, 128});
	button->SetOnClick([&] {
		settings["language"]++;
		if (settings["language"] > English)
			settings["language"] = Chinese;
		((pu::element::Button *)setting_elms[setting_index[SET_LANGUAGE]])->SetContent(text["setting_language"] + text["language"]);
		WriteConfig();
		loop_exit = true;
	});
	this->Add(button);
	setting_index[SET_LANGUAGE] = setting_elms.size();
	setting_elms.push_back(button);
	y += 60;

	button = new pu::element::Button(x, y, SETTING_WINDOW_WIDTH * 3 / 4, BUTTON_HEIGHT + 10, text["setting_darkmode"] + (settings["darkmode"] ? text["on"] : text["off"]), {0, 0, 0, 255}, {255, 255, 255, 128});
	button->SetOnClick([&] {
		settings["darkmode"] = !settings["darkmode"];
		((pu::element::Button *)setting_elms[setting_index[SET_DARKMODE]])->SetContent(text["setting_darkmode"] + (settings["darkmode"] ? text["on"] : text["off"]));
		WriteConfig();
		loop_exit = true;
	});
	this->Add(button);
	setting_index[SET_DARKMODE] = setting_elms.size();
	setting_elms.push_back(button);
	y += 60;

	textblock = new pu::element::TextBlock(x, y, text["setting_game"]);
	textblock->SetX(SETTING_WINDOW_LEFT + (SETTING_WINDOW_WIDTH - textblock->GetTextWidth()) / 2);
	this->Add(textblock);
	setting_elms.push_back(textblock);
	y += 48;

	button = new pu::element::Button(x, y, SETTING_WINDOW_WIDTH * 3 / 4, BUTTON_HEIGHT + 10, text["setting_fullscreen"] + (settings["fullscreen"] ? text["on"] : text["off"]), {0, 0, 0, 255}, {255, 255, 255, 128});
	button->SetOnClick([&] {
		settings["fullscreen"] = !settings["fullscreen"];
		((pu::element::Button *)setting_elms[setting_index[SET_FULLSCREEN]])->SetContent(text["setting_fullscreen"] + (settings["fullscreen"] ? text["on"] : text["off"]));
		WriteConfig();
		focus_button = SET_FULLSCREEN;
	});
	this->Add(button);
	setting_index[SET_FULLSCREEN] = setting_elms.size();
	setting_elms.push_back(button);
	y += 60;

	this->ShowSetting(false);
}

void LayoutWindow::ShowHelp(bool is_show)
{
	is_show_help = is_show;
	is_disable_menu = is_show;
	for (int i = 0; i < (int)menu_elms.size(); i++)
	{
		menu_elms[i]->SetDisable(is_disable_menu);
	}
	if (is_show_help)
	{

		//L A B 和 - 启用，其他禁止
		menu_elms[button_index[OKEY_L]]->SetDisable(false);
		menu_elms[button_index[OKEY_B]]->SetDisable(false);
		menu_elms[button_index[OKEY_MINUS]]->SetDisable(false);
		if (is_show_setting)
		{
			//隐藏设置窗口
			is_show_setting = false;
			for (int i = 0; i < (int)setting_elms.size(); i++)
			{
				setting_elms[i]->SetVisible(is_show_setting);
			}
		}
	}

	//显示帮助窗口
	for (int i = 0; i < (int)help_elms.size(); i++)
	{
		help_elms[i]->SetVisible(is_show_help);
	}
}
void LayoutWindow::HelpOnInput(u64 Down, u64 Up, u64 Held, bool Touch)
{
	if (Touch)
	{
		touchPosition tch;
		hidTouchRead(&tch, 0);
		//点击窗口以外
		if (!(tch.px >= HELP_WINDOW_LEFT && tch.px <= HELP_WINDOW_LEFT + HELP_WINDOW_WIDTH && tch.py >= TOP_HEIGHT && tch.py <= TOP_HEIGHT + WINDOW_HEIGHT) && tch.py < BOTTOM)
		{
			ShowHelp(false);
		}
	}
}

void LayoutWindow::ShowSetting(bool is_show)
{

	is_show_setting = is_show;
	is_disable_menu = is_show;
	for (int i = 0; i < (int)menu_elms.size(); i++)
	{
		menu_elms[i]->SetDisable(is_disable_menu);
	}
	if (is_show_setting)
	{
		focus_button = (SETTING_BUTTON)(SET_BEGIN+1);
		((pu::element::Button *)setting_elms[setting_index[focus_button]])->SetColor({0, 128, 255, 128});
		//+ A B 和 - 启用，其他禁止
		menu_elms[button_index[OKEY_PLUS]]->SetDisable(false);
		//A_button->SetDisable(false);
		menu_elms[button_index[OKEY_B]]->SetDisable(false);
		menu_elms[button_index[OKEY_MINUS]]->SetDisable(false);
		if (is_show_help)
		{
			//隐藏帮组窗口
			is_show_help = false;
			for (int i = 0; i < (int)help_elms.size(); i++)
			{
				help_elms[i]->SetVisible(is_show_help);
			}
		}
	}

	//显示设置窗口
	for (int i = 0; i < (int)setting_elms.size(); i++)
	{
		setting_elms[i]->SetVisible(is_show_setting);
	}
}
void LayoutWindow::SettingOnInput(u64 Down, u64 Up, u64 Held, bool Touch)
{
	if (Touch)
	{
		touchPosition tch;
		hidTouchRead(&tch, 0);
		
		//点击窗口以外
		if (!(tch.px >= SETTING_WINDOW_LEFT && tch.px <= SETTING_WINDOW_LEFT + SETTING_WINDOW_WIDTH && tch.py >= TOP_HEIGHT && tch.py <= TOP_HEIGHT + WINDOW_HEIGHT) && tch.py < BOTTOM)
		{
			ShowSetting(false);
		}
	}
	if (Down & KEY_DOWN)
	{
		if (focus_button + 1 < SET_END)
			focus_button = (SETTING_BUTTON)(focus_button + 1);
		else
			focus_button = (SETTING_BUTTON)(SET_BEGIN + 1);
	}
	else if(Down & KEY_UP){
		if (focus_button - 1 > SET_BEGIN)
			focus_button = (SETTING_BUTTON)(focus_button - 1);
		else
			focus_button = (SETTING_BUTTON)(SET_END - 1);
	}
	else if(Down & KEY_A){

		((pu::element::Button *)setting_elms[setting_index[focus_button]])->OnClick();
	}
	for(int i = SET_BEGIN + 1;i<SET_END;i++){
		((pu::element::Button *)setting_elms[setting_index[(SETTING_BUTTON)i]])->SetColor({255, 255, 255, 128});
	}
	((pu::element::Button *)setting_elms[setting_index[focus_button]])->SetColor({0, 128, 255, 128});
}
void LayoutWindow::OnInput(u64 Down, u64 Up, u64 Held, bool Touch)
{
	if(Touch){
		touchPosition tch;
		hidTouchRead(&tch, 0);
	}
	if (Down & KEY_L)
	{
		ShowHelp(!isShowHelp());
	}
	else if (Down & KEY_PLUS)
	{
		ShowSetting(!isShowSetting());
	}
	else if (Down & KEY_B)
	{
		if (isShowHelp())
			ShowHelp(false);
		if (isShowSetting())
			ShowSetting(false);
	}
}
void LayoutWindow::Update()
{

	if (isEmpty())
		goto common_update;
	//--------------------当前选择变更------------------
	now_select = menu->GetSelectedIndex();
	if (old_select == now_select)
		goto common_update;

	cout << "update:" << game_list[now_select]->GetPath() << endl;
	old_select = now_select;

common_update:
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
}

/*
窗口初始化
全局按键设置
 */
GUIMain::GUIMain()
{

	if (settings["darkmode"])
	{
		text_color = pu::draw::Color(255, 255, 255, 255);
		bg_color = pu::draw::Color(32, 32, 32, 225);
	}
	else
	{
		text_color = pu::draw::Color(0, 0, 0, 255);
		bg_color = pu::draw::Color(225, 225, 225, 255);
	}

	pu::render::SetDefaultFontFromShared(pu::render::SharedFont::ChineseSimplified);
	//this->SetFPS(60);

	layout_window = new LayoutWindow();
	layout_window->SetBackgroundColor(bg_color);
	this->AddThread(std::bind(&GUIMain::Update, this));
	this->AddThread(std::bind(&LayoutWindow::Update, layout_window));
	this->LoadLayout(layout_window);
	this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch) mutable {
		layout_window->OnInput(Down, Up, Held, Touch);
		if (layout_window->isShowHelp())
		{
			layout_window->HelpOnInput(Down, Up, Held, Touch);
			return;
		}
		else if (layout_window->isShowSetting())
		{
			layout_window->SettingOnInput(Down, Up, Held, Touch);
			return;
		}

		if (Down & KEY_MINUS)
		{
			//settings["darkmode"]=settings["darkmode"]==1?0:1;
			//WriteConfig();
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
	});
}
void GUIMain::Update()
{
	if (loop_exit)
		this->Close();
}
