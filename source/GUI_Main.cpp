#include "GUI_Main.h"

using namespace std;






LayoutMenu::LayoutMenu() {

	//font = pu::render::LoadFont("sdmc:/onsemu/yuanzhikong/default.ttf", 25);
	//printf("load 1 font %d\n", font != NULL);

	pu::render::SetGlobalFont(pu::render::SharedFont::ChineseSimplified);
	

	menu = new pu::element::MenuEX(0, TOP_HEIGHT, SCREEN_WIDTH, pu::draw::Color(150, 150, 150, 200), ICON_SIZE, ICON_SELECT_SIZE, ICON_NUM);

	int x = 0,y=0;
	pu::element::MenuItem *item;
	vector<string> dirpath;
	GetGameDir(PATH, dirpath);

	for (int i = 0; i < dirpath.size(); i++) {
		GameInfo *info_tmp = new GameInfo(dirpath[i]);
		game_list.push_back(info_tmp);
		item = new pu::element::MenuItem(game_list[i]->GetName());
		item->SetIcon(game_list[i]->GetIconPath(0));
		string gamepath = this->game_list[i]->GetPath();
		item->AddOnClick([info_tmp]() {					//RunGame
			RunGame(info_tmp);
		});
		//cout << game_list[i]->GetIconPath(0) << endl;
		x += ICON_SIZE + 10;
		menu->AddItem(item);
	}
	this->Add(menu);
	if (dirpath.empty()) {
		menu_text = new pu::element::TextBlock(0, 0, "Not found ONS-Game. Please put ONS-Game-Directory in sdmc:/onsemu/ .");
		x =(SCREEN_WIDTH - menu_text->GetWidth()) / 2;
		menu_text->SetX(x);
		x = (SCREEN_HEIGHT - menu_text->GetHeight()) / 2;
		menu_text->SetY(x);
		this->Add(menu_text);
	}

	old_select = -1;
	now_select = 0;
	//-----------------------顶部栏--------------------------------
	x = LEFT;

	top_rect = new pu::element::Rectangle(0, 0, SCREEN_WIDTH, TOP_HEIGHT, { 255,255,255,128 }, 0);
	this->Add(top_rect);

	
	other_text = new pu::element::TextBlock(x, TOP, text["title"]);
	this->Add(other_text);

	x += other_text->GetWidth() + LEFT * 2;
	version_text = new pu::element::TextBlock(x, TOP, text["txt_version"] + text["version"]);
	this->Add(version_text);

	x = SCREEN_WIDTH - BATTERY_WIDTH - LEFT;
	battery_rect = new pu::element::Rectangle(x, TOP / 2, BATTERY_WIDTH + 6, BATTERY_HEIGHT + 8, { 48,48,48,200 }, 0);
	this->Add(battery_rect);
	battery_bar = new pu::element::Rectangle(x + 3, TOP / 2 + 4, BATTERY_WIDTH, BATTERY_HEIGHT, { 0,220,0,255 }, 0);
	this->Add(battery_bar);
	battery_text = new pu::element::TextBlock(0, TOP, "100%");
	x -= (LEFT + battery_text->GetWidth());
	battery_text->SetX(x);
	this->Add(battery_text);

	x -= (100 + LEFT);
	time_text = new pu::element::TextBlock(x, TOP, "00:00");
	this->Add(time_text);
	//-----------------------顶部栏 结束--------------------------------

	
	pu::element::Image *image;
	string path = DATA_PATH;
	path += "/";
	
	//-----------------浏览框 左右 图标-------------------

	image = new pu::element::Image(5, TOP_HEIGHT + ICON_SELECT_SIZE - BUTTON_HEIGHT - 5, path + onsdata[OKEY_DLEFT].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);

	image = new pu::element::Image(SCREEN_WIDTH - BUTTON_HEIGHT - 5, TOP_HEIGHT + ICON_SELECT_SIZE - BUTTON_HEIGHT - 5, path + onsdata[OKEY_DRIGHT].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//-----------------下方按钮-------------------

	x = LEFT;
	y = BUTTON_BOTTOM;

	button_rect = new pu::element::Rectangle(0, BOTTOM, SCREEN_WIDTH, BOTTOM_HEIGHT, { 255,255,255,128 }, 0);
	this->Add(button_rect);


	image = new pu::element::Image(x, y, path + onsdata[OKEY_L].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	L_button = new pu::element::Button(x + BUTTON_HEIGHT, y, (language == 1 ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH), BUTTON_HEIGHT, text["btn_help"], { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(L_button);

	x += (language == 1 ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH) + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_A].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	A_button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_ok"], { 0,0,0,255 }, {255,255,255,48});
	this->Add(A_button);

	x += BUTTON_WIDTH + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_B].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	B_button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_back"], { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(B_button);

	x += BUTTON_WIDTH + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_Y].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	Y_button = new pu::element::Button(x + BUTTON_HEIGHT, y, (language == 1 ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH), BUTTON_HEIGHT, text["btn_info"], { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(Y_button);

	x += (language == 1 ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH) + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_X].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	X_button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_res"], { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(X_button);

	x += BUTTON_WIDTH + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_R].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	R_button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_player"], { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(R_button);



	x = SCREEN_WIDTH - BUTTON_HEIGHT - LEFT - (language == 1 ? BUTTON_WIDTH : BUTTON_WIDTH / 2) ;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_PLUS].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	PLUS_button = new pu::element::Button(x + BUTTON_HEIGHT, y, (language == 1 ? BUTTON_WIDTH : BUTTON_WIDTH / 2), BUTTON_HEIGHT, text["btn_setting"], { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(PLUS_button);

	x -= ((language == 1 ? BUTTON_WIDTH : BUTTON_WIDTH / 2) + BUTTON_HEIGHT + LEFT * 2);
	image = new pu::element::Image(x, y, path + onsdata[OKEY_MINUS].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	MINUS_button = new pu::element::Button(x + BUTTON_HEIGHT, y, (language == 1 ? BUTTON_WIDTH : BUTTON_WIDTH / 2), BUTTON_HEIGHT, text["btn_refresh"], { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(MINUS_button);
}


void LayoutMenu::Update() {
	
	if (isEmpty())  goto common_update;
	//--------------------当前选择变更------------------
	now_select = menu->GetSelectedIndex();
	if (old_select == now_select) goto common_update;



	cout << "update:"<<game_list[now_select]->GetPath() << endl;

	



	old_select = now_select;
	//--------------------全局更新------------------
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



	return;
	//battery_text->SetText();
	//time_text->SetText();
}






GUIMain::GUIMain() {
	
	LoadConfig();
	WriteDefaultConfig();

	this->SetFPS(60);
	layout_menu = new LayoutMenu();
	this->AddThread(std::bind(&LayoutMenu::Update, layout_menu));
	this->LoadLayout(layout_menu);

	this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch) mutable
	{
		if (Down & KEY_MINUS) {
			this->Close();
			loop_exit = true;
			/*int opt = this->CreateShowDialog("确定要退出？", "", { "退出", "取消" }, true); // (using latest option as cancel option)
			if(opt == 0)
			{
				
			}*/
		}
		if (Down & KEY_X) // If A is pressed, start with our dialog questions!
		{
			int opt = this->CreateShowDialog("Question", "Do you like apples?", { "Yes!", "No...", "Cancel" }, true); // (using latest option as cancel option)
			if ((opt == -1) || (opt == -2)) // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
			{
				this->CreateShowDialog("Cancel", "Last question was canceled.", { "Ok" }, true);
			}
			else
			{
				switch (opt)
				{
				case 0: // "Yes" was selected
					this->CreateShowDialog("Answer", "Really? I like apples too!", { "Ok" }, true);
					break;
				case 1: // "No" was selected
					this->CreateShowDialog("Answer", "Oh... Then I guess you won't have an iPod...", { "(damnit, he caught me)" }, true);
					break;
				}
			}
		}
	});



}

void GUIMain::LoadConfig() {

	LoadLanguage(0);
	WriteData();

	

	/*Load*/


}