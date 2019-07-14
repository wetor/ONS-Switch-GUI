#include "GUI_Main.h"

using namespace std;


LayoutWindow::LayoutWindow(){



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
		menu_text = new pu::element::TextBlock(0, 0, text["txt_noname"]);
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
	L_button->SetOnClick([&]() {	
			this->ShowHelp(!isShowHelp());
	});
	this->Add(L_button);

	x += (language == 1 ? BUTTON_WIDTH * 3 / 5 : BUTTON_WIDTH) + BUTTON_HEIGHT + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_A].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	A_button = new pu::element::Button(x + BUTTON_HEIGHT, y, BUTTON_WIDTH, BUTTON_HEIGHT, text["btn_ok"], { 0,0,0,255 }, {255,255,255,48});
	A_button->SetOnClick([&]() {	
		RunGame(game_list[menu->GetSelectedIndex()]);
	});
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


	//-----------------帮助窗口----------------------
	
	help_window_rect = new pu::element::Rectangle(0, TOP_HEIGHT , (language == 1 ? WINDOW_WIDTH * 4 / 3 : WINDOW_WIDTH), WINDOW_HEIGHT, { 50,50,50,172 }, 0);
	this->Add(help_window_rect);
	help_elms.push_back(help_window_rect);

	help_window = new pu::element::Rectangle(4, TOP_HEIGHT + 4 , (language == 1 ? WINDOW_WIDTH * 4 / 3 : WINDOW_WIDTH) - 8 , WINDOW_HEIGHT - 8, { 225,225,225,172 }, 0);
	this->Add(help_window);
	help_elms.push_back(help_window);

	pu::element::TextBlock *textblock;
	x = 32;
	y = TOP_HEIGHT + 24;
	textblock = new pu::element::TextBlock(x, y,  text["help_title"]);
	textblock->SetX( (0 + WINDOW_WIDTH - textblock->GetTextWidth()) / 2 );
	this->Add(textblock);
	help_elms.push_back(textblock);
	y += 32 + 16;


	string	tmp_text[12] = {"help_A", "help_B", "help_X", "help_Y","help_UP", "help_DOWN", "help_LEFT", "help_RIGHT","help_L", "help_R", "help_LS", "help_RS"};
	int		tmp_okey[12] = {OKEY_A,   OKEY_B,   OKEY_X,   OKEY_Y,  OKEY_DUP,   OKEY_DDOWN,   OKEY_DLEFT,   OKEY_DRIGHT,  OKEY_L,   OKEY_R,   OKEY_LSTICK,   OKEY_RSTICK};
	for(int i=0; i < 12; i++){
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
	pu::element::Rectangle *tmp_rect = new pu::element::Rectangle(x+2, y+2 , BUTTON_HEIGHT-4, BUTTON_HEIGHT-4, { 0,0,0,255 }, 0);
	this->Add(tmp_rect);
	help_elms.push_back(tmp_rect);
	textblock = new pu::element::TextBlock(x + 48, y + 3, text["help_screen"]);
	this->Add(textblock);
	help_elms.push_back(textblock);
	this->ShowHelp(false);

	
}

void LayoutWindow::ShowHelp(bool is_show){
	is_show_help = is_show;
	
	for(int i = 0;i<help_elms.size();i++){
		help_elms[i]->SetVisible(is_show_help);
	}
	

}
void LayoutWindow::Update(){
	if (isEmpty())  goto common_update;
	//--------------------当前选择变更------------------
	now_select = menu->GetSelectedIndex();
	if (old_select == now_select) goto common_update;

	cout << "update:"<<game_list[now_select]->GetPath() << endl;
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






GUIMain::GUIMain() {
	
	LoadConfig();
	WriteDefaultConfig();
	pu::render::SetDefaultFontFromShared(pu::render::SharedFont::ChineseSimplified);
	//this->SetFPS(60);


	layout_window = new LayoutWindow();

	this->AddThread(std::bind(&LayoutWindow::Update, layout_window));
	this->LoadLayout(layout_window);

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
		else if (Down & KEY_L) {
			layout_window->ShowHelp(!layout_window->isShowHelp());
		}
		else if (Down & KEY_X) // If A is pressed, start with our dialog questions!
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