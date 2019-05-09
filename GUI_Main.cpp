#include "GUI_Main.h"


using namespace std;



LayoutMenu::LayoutMenu() {
	
	//menu = new pu::element::Menu(0, 30, 1280,pu::draw::Color(150, 150, 150, 200), ICON_SIZE, 690/240);

	int x = 0;
	pu::element::Image* image;
	vector<string> dirpath; 
	GetGameDir(PATH, dirpath);
	for (int i = 0; i < dirpath.size();i++) {
		game_list.push_back(new GameInfo(dirpath[i]));
		image = new pu::element::Image(x, 40, game_list[i]->GetIconPath(0));
		image->SetWidth(ICON_SIZE);
		image->SetHeight(ICON_SIZE);
		cout << game_list[i]->GetIconPath(0) << endl;
		x += ICON_SIZE + 10;
		game.push_back(image);
		this->Add(image);
	}
	

	x = LEFT;
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


void LayoutMenu::Update() {
	//battery_text->SetText();
	//time_text->SetText();
}



GUIMain::GUIMain() {
	layout_menu = new LayoutMenu();
	cout << "01" << endl;
	this->AddThread(std::bind(&LayoutMenu::Update, layout_menu));
	cout << "02" << endl;
	this->LoadLayout(layout_menu);
	cout << "03" << endl;
}

