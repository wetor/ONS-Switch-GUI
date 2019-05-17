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
		game_list.push_back(new GameInfo(dirpath[i]));
		item = new pu::element::MenuItem(game_list[i]->GetName());
		item->SetIcon(game_list[i]->GetIconPath(0));
		cout << game_list[i]->GetIconPath(0) << endl;
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


	x = LEFT;

	top_rect = new pu::element::Rectangle(0, 0, SCREEN_WIDTH, TOP_HEIGHT, { 255,255,255,128 }, 0);
	this->Add(top_rect);

	version_text = new pu::element::TextBlock(x, TOP, "Version: Alpha 0.1");

	x += version_text->GetWidth() + LEFT * 2;
	other_text = new pu::element::TextBlock(x, TOP, "中文测试？！@依旧AAAaaa#?!");
	//other_text->SetFont(font);
	//x += other_text->GetWidth() + 10;

	battery_text = new pu::element::TextBlock(0, TOP, " 50%");
	x = SCREEN_WIDTH - LEFT - battery_text->GetWidth();
	battery_text->SetX(x);

	time_text = new pu::element::TextBlock(0, TOP, "12:01");
	x -= time_text->GetWidth() + LEFT * 2;
	time_text->SetX(x);


	this->Add(version_text);
	this->Add(other_text);
	this->Add(battery_text);
	this->Add(time_text);


	
	pu::element::Image *image;
	string path = DATA_PATH;
	path += "/";
	x = LEFT;
	y = BUTTON_BOTTOM;
	//int w = BUTTON_HEIGHT + (BOTTOM_HEIGHT - BUTTON_HEIGHT) / 2;
	

	button_rect = new pu::element::Rectangle(0, BOTTOM, SCREEN_WIDTH, BOTTOM_HEIGHT, { 255,255,255,128 }, 0);
	this->Add(button_rect);

	image = new pu::element::Image(x, y, path + onsdata[OKEY_L].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//x += w;
	L_button = new pu::element::Button(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, "帮助", { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(L_button);
	x += BUTTON_WIDTH + LEFT * 2;

	
	image = new pu::element::Image(x, y, path + onsdata[OKEY_A].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//x += w;
	A_button = new pu::element::Button(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, "确认", { 0,0,0,255 }, {255,255,255,48});
	this->Add(A_button);
	x += BUTTON_WIDTH + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_B].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//x += w;
	B_button = new pu::element::Button(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, "返回", { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(B_button);
	x += BUTTON_WIDTH + LEFT * 2;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_Y].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//x += w;
	Y_button = new pu::element::Button(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, "信息", { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(Y_button);
	x += BUTTON_WIDTH + LEFT * 2;



	image = new pu::element::Image(x, y, path + onsdata[OKEY_R].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//x += w;
	R_button = new pu::element::Button(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, "播放器", { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(R_button);
	x += BUTTON_WIDTH + LEFT * 2;


	x = SCREEN_WIDTH - LEFT - BUTTON_WIDTH ;
	image = new pu::element::Image(x, y, path + onsdata[OKEY_PLUS].name);
	image->SetWidth(BUTTON_HEIGHT);
	image->SetHeight(BUTTON_HEIGHT);
	this->Add(image);
	//x += w;
	PLUS_button = new pu::element::Button(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, "退出", { 0,0,0,255 }, { 255,255,255,48 });
	this->Add(PLUS_button);
	x += BUTTON_WIDTH + LEFT * 2;
}


void LayoutMenu::Update() {
	//battery_text->SetText();
	//time_text->SetText();
}






GUIMain::GUIMain() {
	LoadConfig();
	WriteDefaultConfig();
	this->SetFPS(30);
	layout_menu = new LayoutMenu();
	this->AddThread(std::bind(&LayoutMenu::Update, layout_menu));
	this->LoadLayout(layout_menu);


	this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch)
	{
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
	WriteData();

	

	/*Load*/


}