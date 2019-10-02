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
		text["version"] = "1.0";

		text["license"] = "ONS GameBrowser  created by wetor (http://www.wetor.top)";
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
		text["msg_not_found"] = "未找到\"/onsemu/exefs/ONScripter.nro\"主程序！";

		text["help_title"] = "游戏中操作帮助";
		text["help_A"] = "确定选中项、下一页";
		text["help_B"] = "按下快进";
		text["help_X"] = "下一页";
		text["help_Y"] = "显示、隐藏菜单";
		text["help_UP"] = "上一个选项";
		text["help_DOWN"] = "下一个选项";
		text["help_LEFT"] = "回想模式：上一页";
		text["help_RIGHT"] = "回想模式：下一页";
		text["help_L"] = "改变文本显示速度";
		text["help_R"] = "快进模式开关";
		text["help_LS"] = "移动鼠标  按下：显示/隐藏";
		text["help_RS"] = "同方向键";
		text["help_screen"] = "截屏键：截取当前画面";

		text["on"] = "开启";
		text["off"] = "关闭";
		text["setting_gui"] = "启动器设置";
		text["setting_language"] = "语言：";
		text["setting_darkmode"] = "夜间模式：";
		text["setting_iconstyle"] = "菜单样式：";

		text["setting_text_top"] = "上方";
		text["setting_text_down"] = "下方";
		text["setting_game"] = "游戏设置";
		text["setting_fullscreen"] = "全屏模式：";
		text["setting_fontoutline"] = "文字描边：";

		break;
	case 1:
	default:
		text["language"] = "English";
		text["version"] = "1.0";
		text["license"] = "ONS GameBrowser  created by wetor (http://www.wetor.top)";

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
		text["help_A"] = "Select the selected item ,Next page";
		text["help_B"] = "Press force skip";
		text["help_X"] = "Next page";
		text["help_Y"] = "Show, hide menu";
		text["help_UP"] = "Previous selection";
		text["help_DOWN"] = "Next selection";
		text["help_LEFT"] = "Log mode: previous page";
		text["help_RIGHT"] = "Log mode: next page";
		text["help_L"] = "Change the text display speed";
		text["help_R"] = "Switch force skip mode ";
		text["help_LS"] = "Move mouse ,press: show/hide";
		text["help_RS"] = "Same direction key";
		text["help_screen"] = "Screenshot: save the current screen";

		text["on"] = "ON";
		text["off"] = "OFF";
		text["setting_gui"] = "Gui Setting";
		text["setting_language"] = "Language: ";
		text["setting_darkmode"] = "DarkTheme: ";
		text["setting_iconstyle"] = "Menu Style: ";

		text["setting_text_top"] = "Top";
		text["setting_text_down"] = "Bottom";
		text["setting_game"] = "Game Setting";
		text["setting_fullscreen"] = "FullScreen: ";
		text["setting_fontoutline"] = "Font Outline: ";

		text["msg_not_found"] = "\"/onsemu/exefs/ONScripter.nro\" not found!";

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
string GetFileName(string path)
{
	int pos = path.find_last_of('/');
	if (pos >= 0 && pos < (int)path.length())
		return path.substr(pos + 1);
	else
		return "";
}
string GetFullPath(string path)
{
	int pos = path.find_last_of('/');
	if (pos >= 0 && pos < (int)path.length())
		return path.substr(0, pos);
	else
		return "";
}
string GetExtensions(string path)
{
	int pos = path.find_last_of('.');
	if (pos >= 0 && pos < (int)path.length())
		return path.substr(pos + 1);
	else
		return "";
}
string CheckScript(string path, vector<string> &files)
{
	files.clear();
	DIR *dir;
	struct dirent *ptr;
	if ((dir = opendir(path.c_str())) == NULL)
	{
		return "";
	}
	bool exist = false;
	string script = "";
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
			else
				files.push_back(ptr->d_name);
		}
		if (exist)
		{
			script = string(ptr->d_name);
			break;
		}
	}
	closedir(dir);
	if (exist)
		return script;
	else
		return "";
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
	if (!CheckDir(EXEPATH))
		CreateDir(EXEPATH);
	if (!CheckDir(TEMP_PATH))
		CreateDir(TEMP_PATH);
	if (!CheckDir(DATA_PATH))
		CreateDir(DATA_PATH);
	string path = DATA_PATH;
	path += "/";
	for (int i = 0; i < 17; i++)
	{
		if (CheckFile(path + onsdata[i].name) != (int)onsdata[i].len)
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
	char timestr[12];
	if (second)
	{
		snprintf(timestr, 10, "%02d:%02d:%02d", h, min, s);
	}
	else
	{
		snprintf(timestr, 6, "%02d:%02d", h, min);
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
	char timestr[12];
	if (isyear)
	{
		snprintf(timestr, 10, "%02d-%02d-%02d", year, mon, day);
		//2019-6-11 18:56:32
	}
	else
	{
		snprintf(timestr, 6, "%02d-%02d", mon, day);
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
	string fn = string(DATA_PATH) + "/setting.txt";

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
			if (t_ver == GUI_VERSION)
				return;
		}

		//cfg.setOptions(Config::OptionFsync | Config::OptionSemicolonSeparators | Config::OptionColonAssignmentForGroups | Config::OptionOpenBraceOnSeparateLine);
		Config cfg;
		Setting &root = cfg.getRoot();
		Setting &gui = root.add("gui", Setting::TypeGroup);
		gui.add("version", Setting::TypeInt) = GUI_VERSION;
		gui.add("language", Setting::TypeInt) = Chinese;
		gui.add("darkmode", Setting::TypeInt) = 0;
		gui.add("iconstyle", Setting::TypeInt) = 0;
		gui.add("lastselect", Setting::TypeInt) = 0;
		Setting &game = root.add("game", Setting::TypeGroup);
		game.add("fullscreen", Setting::TypeInt) = 0;
		game.add("fontoutline", Setting::TypeInt) = 0;
		cfg.writeFile(fn.c_str());
#ifdef DEBUG
		printf("init setting: version:%d\n", GUI_VERSION);
#endif
	}
	else
	{

		Config cfg;
		Setting &root = cfg.getRoot();
		Setting &gui = root.add("gui", Setting::TypeGroup);
		gui.add("version", Setting::TypeInt) = GUI_VERSION;
		gui.add("language", Setting::TypeInt) = settings["language"];
		gui.add("darkmode", Setting::TypeInt) = settings["darkmode"];
		gui.add("iconstyle", Setting::TypeInt) = settings["iconstyle"];
		gui.add("lastselect", Setting::TypeInt) = settings["lastselect"];
		Setting &game = root.add("game", Setting::TypeGroup);
		game.add("fullscreen", Setting::TypeInt) = settings["fullscreen"];
		game.add("fontoutline", Setting::TypeInt) = settings["fontoutline"];

		cfg.writeFile(fn.c_str());
		//printf("save setting: language:%d darkmode:%d iconstyle:%d fullscreen:%d\n", settings["language"], settings["darkmode"], settings["iconstyle"], settings["fullscreen"]);
	}
}
void LoadConfig()
{
	string fn = string(DATA_PATH) + "/setting.txt";
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
	gui.lookupValue("iconstyle", settings["iconstyle"]);
	gui.lookupValue("lastselect", settings["lastselect"]);
	game.lookupValue("fullscreen", settings["fullscreen"]);
	game.lookupValue("fontoutline", settings["fontoutline"]);
	//printf("load setting: language:%d darkmode:%d iconstyle:%d fullscreen:%d\n", settings["language"], settings["darkmode"], settings["iconstyle"], settings["fullscreen"]);
}
#define SKIP_SPACE(p)                   \
	while (*(p) == ' ' || *(p) == '\t') \
	(p)++
#define IS_TWO_BYTE(x) \
	(((unsigned char)(x) > (unsigned char)0x80) && ((unsigned char)(x) != (unsigned char)0xff))

void PreLoadScreen(char *script_buffer, int script_buffer_length, int &screen_width, int &screen_height)
{
	screen_width = 640;
	screen_height = 480;
	int variable_range = 4096;
	int global_variable_border = 200;

	char *buf = script_buffer;
	while (buf < script_buffer + script_buffer_length)
	{
		if (*buf == ';')
			break;
		if (IS_TWO_BYTE(*buf))
			buf++;
		buf++;
	}

	while (++buf >= script_buffer + script_buffer_length)
		return;

	SKIP_SPACE(buf);
	bool config_flag = false;
	if (buf[0] == '$')
	{
		config_flag = true;
		buf++;
	}

	while (*buf && *buf != 0x0a)
	{
		SKIP_SPACE(buf);
		if (!strncmp(buf, "mode", 4))
		{
			buf += 4;
			if (!strncmp(buf, "800", 3))
			{
				screen_width = 800;
				screen_height = 600;
				buf += 3;
			}
			else if (!strncmp(buf, "400", 3))
			{
				screen_width = 400;
				screen_height = 300;
				buf += 3;
			}
			else if (!strncmp(buf, "320", 3))
			{
				screen_width = 320;
				screen_height = 240;
				buf += 3;
			}
			else
				break;
		}
		else if (!strncmp(buf, "value", 5) ||
				 *buf == 'g' || *buf == 'G')
		{
			if (*buf == 'g' || *buf == 'G')
				buf++;
			else
				buf += 5;
			SKIP_SPACE(buf);
			global_variable_border = 0;
			while (*buf >= '0' && *buf <= '9')
				global_variable_border = global_variable_border * 10 + *buf++ - '0';
		}
		else if (*buf == 'v' || *buf == 'V')
		{
			buf++;
			SKIP_SPACE(buf);
			variable_range = 0;
			while (*buf >= '0' && *buf <= '9')
				variable_range = variable_range * 10 + *buf++ - '0';
		}
		else if (*buf == 's' || *buf == 'S')
		{
			buf++;
			if (!(*buf >= '0' && *buf <= '9'))
				break;
			screen_width = 0;
			while (*buf >= '0' && *buf <= '9')
				screen_width = screen_width * 10 + *buf++ - '0';
			while (*buf == ',' || *buf == ' ' || *buf == '\t')
				buf++;
			screen_height = 0;
			while (*buf >= '0' && *buf <= '9')
				screen_height = screen_height * 10 + *buf++ - '0';
		}
		else if (*buf == 'l' || *buf == 'L')
		{
			buf++;
			SKIP_SPACE(buf);
			while (*buf >= '0' && *buf <= '9')
				buf++;
		}
		else if (*buf != ',')
			break;

		SKIP_SPACE(buf);
		if (!config_flag && *buf != ',')
			break;
		if (*buf == ',')
			buf++;
	}
}

//加载配置文件或预加载脚本，获取游戏信息
void PreLoadScript(string path, script_t &info)
{

	if (CheckFile(path + "/title.txt") > 0)
	{
	}

	vector<string> files;
	string script_file = CheckScript(path, files);
	files.clear();
	int encrypt_mode = 0;
	if (script_file == "0.txt")
		encrypt_mode = 0;
	else if (script_file == "00.txt")
		encrypt_mode = 0;
	else if (script_file == "nscr_sec.dat")
		encrypt_mode = 2;
	else if (script_file == "nscript.___")
		encrypt_mode = 3;
	else if (script_file == "nscript.dat")
		encrypt_mode = 1;

	//------------------------------------
	FILE *fp = NULL;
	unsigned char magic[5] = {0x79, 0x57, 0x0d, 0x80, 0x04};
	int magic_counter = 0;
	bool newline_flag = true;
	bool cr_flag = false;
	bool newlabel_flag = false;
	int num_of_labels = 0;
	unsigned char key_table[256];
	for (int i = 0; i < 256; i++)
		key_table[i] = i;
	if ((fp = fopen(string(path + "/" + script_file).c_str(), "rb")) == NULL)
		return;

	bool read_label = false;
	string curr_label = "";
	string last_label = "";
	string curr_line = "";
	string script_buffer = "";
	unsigned char *tmp_script_buf = new unsigned char[4096];

	fseek(fp, 0, SEEK_END);
	int estimated_buffer_length = ftell(fp) + 1;

	fseek(fp, 0, SEEK_SET);
	size_t len = 0, count = 0;
	while (1)
	{
		if (len == count)
		{
			len = fread(tmp_script_buf, 1, 4096, fp);
			if (len == 0)
			{
				if (cr_flag)
					script_buffer += 0x0a;
				break;
			}
			count = 0;
		}
		unsigned char ch = tmp_script_buf[count++];
		if (encrypt_mode == 1)
			ch ^= 0x84;
		else if (encrypt_mode == 2)
		{
			ch = (ch ^ magic[magic_counter++]) & 0xff;
			if (magic_counter == 5)
				magic_counter = 0;
		}
		else if (encrypt_mode == 3)
		{
			ch = key_table[(unsigned char)ch] ^ 0x84;
		}

		if (cr_flag && ch != 0x0a)
		{
			script_buffer += 0x0a;
			newline_flag = true;
			cr_flag = false;
		}

		if (ch == '*' && newline_flag && !newlabel_flag)
		{
			num_of_labels++;
			newlabel_flag = true;
			read_label = true;
		}
		else
		{
			newlabel_flag = false;
		}

		if (ch == 0x0d)
		{
			cr_flag = true;
			continue;
		}
		if (ch == 0x0a)
		{
			script_buffer += 0x0a;
			newline_flag = true;
			cr_flag = false;
		}
		else
		{
			script_buffer += ch;
			if (ch != ' ' && ch != '\t')
				newline_flag = false;
		}
		if (read_label)
		{
			curr_label += ch;
			if (newline_flag)
			{
				if (last_label.substr(0, 7) == "*define") //上一个标签是define
					break;
				//cout << curr_label << endl;
				last_label = curr_label;
				curr_label = "";
				read_label = false;
			}
		}
		if (newline_flag)
		{
			if (curr_line.substr(0, 10) == "versionstr")
			{
				int a = curr_line.find('\"');
				info.versionstr = curr_line.substr(a + 1, curr_line.find('\"', a + 1) - a - 1);
			}
			if (curr_line.substr(0, 7) == "caption")
			{
				int a = curr_line.find('\"');
				info.caption = curr_line.substr(a + 1, curr_line.find('\"', a + 1) - a - 1);
				break;
			}
			curr_line = "";
		}
		else
		{
			curr_line += ch;
		}
	}

	script_buffer += 0x0a;

	fclose(fp);
	delete[] tmp_script_buf;
	//printf("%s\n", string(path + "/" + script_file).c_str());
	//printf("script length:%d\n", script_buffer.length());
	PreLoadScreen((char *)script_buffer.c_str(), script_buffer.length(), info.w, info.h);
	//printf("%s %s %d %d\n", info.versionstr.c_str(), info.caption.c_str(), info.w, info.h);
}