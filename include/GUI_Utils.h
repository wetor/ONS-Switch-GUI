#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <filesystem>
#include <sys/stat.h>
#include <fstream>

#include <locale>
#include <codecvt>

#include <switch.h>


#include <map>
#include <libconfig.h++>


#include "GUI_define.h"
#include "GUI_GameInfo.h"
//#include "default_icon_png.h"
//#include "default_font_ttf.h"


// #include "A_png.h"
// #include "B_png.h"
// #include "X_png.h"
// #include "Y_png.h"
// #include "SL_png.h"
// #include "SR_png.h"
// #include "L_png.h"
// #include "R_png.h"
// #include "ZL_png.h"
// #include "ZR_png.h"
// #include "PLUS_png.h"
// #include "MINUS_png.h"
// #include "LEFT_png.h"
// #include "UP_png.h"
// #include "RIGHT_png.h"
// #include "DOWN_png.h"

using namespace std;
using namespace libconfig;

extern map<string, string> text;	//language
extern map<string,int> settings; 

struct data_t {
	string name;
};
static data_t onsdata[]{
	{"A.png"},
	{"B.png"},
	{"X.png"},
	{"Y.png"},
	{"SL.png"},
	{"SR.png"},
	{"L.png"},
	{"R.png"},
	{"ZL.png"},
	{"ZR.png"},
	{"PLUS.png" },
	{"MINUS.png"},
	{"LEFT.png" },
	{"UP.png"},
	{"RIGHT.png"},
	{"DOWN.png"},
	{"default_icon.png"},
	//{(uint8_t*)default_font_ttf,default_font_ttf_size,"default_font.ttf"}
};

enum ns_data{
	OKEY_A,
	OKEY_B,
	OKEY_X,
	OKEY_Y,
	OKEY_LSTICK,
	OKEY_RSTICK,
	OKEY_L,
	OKEY_R,
	OKEY_ZL,
	OKEY_ZR,
	OKEY_PLUS,
	OKEY_MINUS,
	OKEY_DLEFT,
	OKEY_DUP,
	OKEY_DRIGHT,
	OKEY_DDOWN,
	DATA_ICON,
	DATA_FONT
};

enum LANGUAGE{
	Chinese,
	English,
	Other
};



extern bool loop_exit;
extern bool loop_restart;
extern void RunGame(OnsGameInfo *info);



extern void WriteConfig(bool default0 = false);

extern void LoadConfig();
extern void LoadLanguage(int lang = 0);
extern int GetGameDir(string path, vector<string> &dirpath);
extern int GetGameIcon(string path, vector<string>&list);

extern string CheckScript(string path, vector<string>& files);
extern int CheckFile(string path);
extern bool CheckDir(string path);

extern string GetFullPath(string path);
extern string GetFileName(string path);
extern string GetExtensions(string path);

extern bool CopyFile(string Source, string Dest);
extern bool CreateDir(string path);
extern bool WriteFile(string path, uint8_t *data, int len);
extern void CreateDirs();


extern string GetCurrentTime(bool second = false);
extern string GetCurrentDate(bool isyear = true);
extern int GetBatteryLevel();
extern bool IsCharging();

extern void PreLoadScript(string path, script_t &info);