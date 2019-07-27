#include "GUI_Utils.h"
map<string, string> text;

void LoadLanguage(int lang)
{
	settings["language"] = lang;
	text["title"] = "ONScripter-Jh for Nintendo Switch";

	switch (lang) //中文

	{
	case 0:
		text["language"] = "简体中文";
		text["version"] = "内测 0.1";
		text["txt_version"] = "版本:";
		text["btn_help"] = "游戏帮助";
		text["btn_ok"] = "确认/开始";
		text["btn_back"] = "返回/取消";
		text["btn_info"] = "详细信息";
		text["btn_res"] = "资源查看";
		text["btn_player"] = "播放器";
		text["btn_setting"] = "设置";
		text["btn_refresh"] = "重载";
		text["txt_nogame"] = "未发现ONS游戏！请将ONS游戏文件夹放至储存卡的\"/onsemu\"文件夹中。";
		text["msg_title_tip"] = "提示";
		text["msg_title_error"] = "错误";
		text["msg_title_info"] = "信息";
		text["msg_tip_run"] = "确定开始游戏？";
		text["msg_run"] = "开始游戏";
		text["msg_yes"] = "确定";
		text["msg_no"] = "取消";

		text["help_title"] = "游戏中操作帮助";
		text["help_A"] = "下一页、确定、选中";
		text["help_B"] = "按下快进";
		text["help_X"] = "下一页";
		text["help_Y"] = "显示、隐藏菜单";
		text["help_UP"] = "上一个选项";
		text["help_DOWN"] = "下一个选项";
		text["help_LEFT"] = "回想模式：上一页";
		text["help_RIGHT"] = "回想模式：下一页";
		text["help_L"] = "改变文本显示速度";
		text["help_R"] = "快进模式开关";
		text["help_LS"] = "按下：显示、隐藏焦点框";
		text["help_RS"] = "同方向键";
		text["help_screen"] = "截屏键：截取当前画面";

		text["on"] = "开启";
		text["off"] = "关闭";
		text["setting_gui"] = "启动器设置";
		text["setting_language"] = "语言：";
		text["setting_darkmode"] = "夜间模式：";
		text["setting_game"] = "游戏设置";
		text["setting_fullscreen"] = "全屏模式：";

		break;
	case 1:
	default:
		text["language"] = "English";
		text["version"] = "alpha 0.1";
		text["txt_version"] = "Version:";
		text["btn_help"] = "Help";
		text["btn_ok"] = "Confirm";
		text["btn_back"] = "Cancel";
		text["btn_info"] = "Info";
		text["btn_res"] = "Resource";
		text["btn_player"] = "Player";
		text["btn_setting"] = "Setting";
		text["btn_refresh"] = "Refresh";
		text["txt_nogame"] = "Not found ONS-Game. Please put ONS-Game-Directory in \"sdmc:/onsemu/\".";
		text["msg_title_tip"] = "Tips";
		text["msg_title_error"] = "Error";
		text["msg_title_info"] = "Information";
		text["msg_tip_run"] = "Are you sure to start the game?";
		text["msg_run"] = "Start";
		text["msg_yes"] = "Confirm";
		text["msg_no"] = "Cancel";

		text["help_title"] = "Game control help";
		text["help_A"] = "Next page, Confirm or Selected";
		text["help_B"] = "Press force skip";
		text["help_X"] = "Next page";
		text["help_Y"] = "Show, hide menu";
		text["help_UP"] = "Previous selection";
		text["help_DOWN"] = "Next selection";
		text["help_LEFT"] = "Log mode: previous page";
		text["help_RIGHT"] = "Log mode: next page";
		text["help_L"] = "Change the text display speed";
		text["help_R"] = "Switch force skip mode ";
		text["help_LS"] = "Press: show or hide the focus frame";
		text["help_RS"] = "Same direction key";
		text["help_screen"] = "Screenshot: save the current screen";
		
		text["on"] = "ON";
		text["off"] = "OFF";
		text["setting_gui"] = "Gui Setting";
		text["setting_language"] = "Language: ";
		text["setting_darkmode"] = "DarkTheme: ";
		text["setting_game"] = "Game Setting";
		text["setting_fullscreen"] = "FullScreen: ";

		/*
	
text["help_title"] 	="Game control help";
	
		text["help_A"] 	="Next page, Confirm or Selected";

		text["help_B"] 		="Press force skip";

		text["help_X"] 		="Next page";

		text["help_Y"] 		="Show, hide menu";

		text["help_UP"] 	="Previous selection";
	text["help_DOWN"] 	="Next selection";
	text["help_LEFT"] 	="Log mode: previous page";
text["help_RIGHT"]  ="Log mode: next page";

		text["help_L"] 		="Change the text display speed";

		text["help_R"] 		="Switch force skip mode ";

		text["help_LS"] 	="Press: show or hide the focus frame";

		text["help_RS"] 	="Same direction key";
text["help_screen"] ="Screenshot: save the current screen";
		
		 */
		break;
	}
}

void ReadConfig(string file)
{
}
/*
void WriteCmd(string file, vector<string> cmd_list) {
	Config cfg;
	cfg.setOptions(Config::OptionFsync
		| Config::OptionSemicolonSeparators
		| Config::OptionColonAssignmentForGroups
		| Config::OptionOpenBraceOnSeparateLine);

	cfg.readFile(file);
	Setting &root = cfg.getRoot();
	Setting &cmd = root.add("command", Setting::TypeGroup);

}
string ReadCmd(string path) {
	string file = CMD_FILE;
	file = path + "/" + file;
	if (CheckFile(file) <= 0) {

	}
	
}*/

int GetGameDir(string path, vector<string> &list)
{
	DIR *dir;
	list.clear();
	struct dirent *ptr;
	if ((dir = opendir(path.c_str())) == NULL)
	{
		return 0;
	}
	while ((ptr = readdir(dir)) != NULL)
	{
		/*
		exefs	:	模块文件
		temp	:	临时文件
		media	:	视频文件
		onsdata	:	配置文件
		*/
		if (strcmp(ptr->d_name, "exefs") == 0 || strcmp(ptr->d_name, "temp") == 0 || strcmp(ptr->d_name, "media") == 0 || strcmp(ptr->d_name, "onsdata") == 0 || strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) //current dir OR parrent dir
			continue;
		else if (ptr->d_type == 4) //dir
		{
			string temp = path + "/" + ptr->d_name;
			list.push_back(temp);
		}
	}
	closedir(dir);
	return list.size();
}

bool CheckScript(string path)
{
	DIR *dir;
	struct dirent *ptr;
	if ((dir = opendir(path.c_str())) == NULL)
	{
		return false;
	}
	bool exist = false;
	while ((ptr = readdir(dir)) != NULL)
	{
		if (ptr->d_type == 8) //file
		{
			if (!strcmp(ptr->d_name, "0.txt"))
				exist = true;
			else if (!strcmp(ptr->d_name, "00.txt"))
				exist = true;
			else if (!strcmp(ptr->d_name, "nscr_sec.dat"))
				exist = true;
			else if (!strcmp(ptr->d_name, "nscript.___"))
				exist = true;
			else if (!strcmp(ptr->d_name, "nscript.dat"))
				exist = true;
		}
		if (exist)
			break;
	}
	closedir(dir);
	if (exist)
		return true;
	else
		return false;
}

int GetGameIcon(string path, vector<string> &list)
{
	DIR *dir;
	list.clear();
	struct dirent *ptr;
	if ((dir = opendir(path.c_str())) == NULL)
	{
		return 0;
	}
	int icon_num = -1;
	while ((ptr = readdir(dir)) != NULL)
	{
		if (ptr->d_type == 8) //file
		{
			string fn = "icon";
			if (icon_num == -1)
				fn += ".png";
			else
				fn += to_string(icon_num) + ".png";
			if (!strcmp(ptr->d_name, fn.c_str()))
			{
				list.push_back(path + "/" + fn);
				icon_num++;
			}
		}
	}
	closedir(dir);
	return list.size();
}
bool CheckDir(string path)
{
	DIR *dir;
	if ((dir = opendir(path.c_str())) == NULL)
		return false;
	closedir(dir);
	return true;
}
bool CreateDir(string path)
{
	mkdir(path.c_str(), 777);
	return CheckDir(path);
}
int CheckFile(string path)
{
	FILE *fp = fopen(path.c_str(), "rb");
	if (!fp)
		return -1;
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

bool CopyFile(string Source, string Dest)
{
	FILE *inf = fopen(Source.c_str(), "rb");
	if (!inf)
		return false;
	FILE *of = fopen(Dest.c_str(), "wb");
	uint8_t buf[8192] = {0};
	size_t rsize = 0;
	while ((rsize = fread(buf, 1, 8192, inf)) > 0)
	{
		fwrite(buf, 1, rsize, of);
	}
	fclose(inf);
	fclose(of);
	return true;
}
bool WriteFile(string path, uint8_t *data, int len)
{
	FILE *of = fopen(path.c_str(), "wb");
	fwrite(data, len, 1, of);
	fclose(of);
	return true;
}
void WriteData()
{

	if (!CheckDir(PATH))
		CreateDir(PATH);
	if (!CheckDir(DATA_PATH))
		CreateDir(DATA_PATH);
	string path = DATA_PATH;
	path += "/";
	for (int i = 0; i < 18; i++)
	{
		if (CheckFile(path + onsdata[i].name) != onsdata[i].len)
		{
			WriteFile(path + onsdata[i].name, onsdata[i].data, onsdata[i].len);
			cout << path + onsdata[i].name << endl;
		}
	}
}

string GetCurrentTime(bool second)
{
	time_t timet = time(NULL);
	struct tm *times = localtime((const time_t *)&timet);
	int h = times->tm_hour;
	int min = times->tm_min;
	int s = times->tm_sec;
	char timestr[9];
	if (second)
	{
		sprintf(timestr, "%02d:%02d:%02d", h, min, s);
	}
	else
	{
		sprintf(timestr, "%02d:%02d", h, min);
	}
	return std::string(timestr);
}
string GetCurrentDate(bool isyear)
{
	time_t timet = time(NULL);
	struct tm *times = localtime((const time_t *)&timet);
	int year = 1900 + times->tm_year;
	int mon = 1 + times->tm_mon;
	int day = times->tm_mday;
	char timestr[9];
	if (isyear)
	{
		sprintf(timestr, "%02d-%02d-%02d", year, mon, day);
		//2019-6-11 18:56:32
	}
	else
	{
		sprintf(timestr, "%02d-%02d", mon, day);
	}
	return std::string(timestr);
}

int GetBatteryLevel()
{
	uint bat = 0;
	psmGetBatteryChargePercentage(&bat);
	return (int)bat;
}

bool IsCharging()
{
	ChargerType charger = ChargerType_None;
	psmGetChargerType(&charger);
	return (charger > ChargerType_None);
}

void WriteConfig(bool default0)
{
	string fn = DATA_PATH;
	fn += "setting.txt";
	
	if (default0)
	{

		if (CheckFile(fn) > 0)
		{
			Config t_cfg;
			t_cfg.readFile(fn.c_str()); //读取配置文件
			Setting &t_root = t_cfg.getRoot();
			const Setting &t_gui = t_root["gui"];
			int t_ver = 0;
			t_gui.lookupValue("version", t_ver);
			if(t_ver==GUI_VERSION)
				return;
		}
		
		//cfg.setOptions(Config::OptionFsync | Config::OptionSemicolonSeparators | Config::OptionColonAssignmentForGroups | Config::OptionOpenBraceOnSeparateLine);
		Config cfg;
		Setting &root = cfg.getRoot();
		Setting &gui = root.add("gui", Setting::TypeGroup);
		gui.add("version", Setting::TypeInt) = GUI_VERSION;
		gui.add("language", Setting::TypeInt) = Chinese;
		gui.add("darkmode", Setting::TypeInt) = 0;

		Setting &game = root.add("game", Setting::TypeGroup);
		game.add("fullscreen", Setting::TypeInt) = 1;

		cfg.writeFile(fn.c_str());
		printf("init setting: version:%d\n",GUI_VERSION);
	}else{

		Config cfg;
		Setting &root = cfg.getRoot();
		Setting &gui = root.add("gui", Setting::TypeGroup);
		gui.add("version", Setting::TypeInt) = GUI_VERSION;
		gui.add("language", Setting::TypeInt) = settings["language"];
		gui.add("darkmode", Setting::TypeInt) = settings["darkmode"];

		Setting &game = root.add("game", Setting::TypeGroup);
		game.add("fullscreen", Setting::TypeInt) = settings["fullscreen"];

		cfg.writeFile(fn.c_str());
		printf("save setting: language:%d darkmode:%d fullscreen:%d\n",settings["language"],settings["darkmode"],settings["fullscreen"]);
		
	}
	
}
void LoadConfig()
{
	string fn = DATA_PATH;
	fn += "setting.txt";
	if (CheckFile(fn) < 0)
		exit(0);
	Config cfg;				  //1.声明 Config对象
	cfg.readFile(fn.c_str()); //读取配置文件
	const Setting &root = cfg.getRoot();
	const Setting &gui = root["gui"];
	const Setting &game = root["game"];
	//settings["language"]
	gui.lookupValue("language", settings["language"]);
	gui.lookupValue("darkmode", settings["darkmode"]);
	game.lookupValue("fullscreen", settings["fullscreen"]);
	printf("load setting: language:%d darkmode:%d fullscreen:%d\n",settings["language"],settings["darkmode"],settings["fullscreen"]);
}