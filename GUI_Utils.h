#pragma once
#include <iostream>
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

#include <switch.h>


#include <map>
#include <libconfig.h++>


#include "GUI_define.h"
#include "GUI_GameInfo.h"
#include "default_icon_png.h"
#include "default_font_ttf.h"



#include "A_png.h"
#include "B_png.h"
#include "X_png.h"
#include "Y_png.h"
#include "SL_png.h"
#include "SR_png.h"
#include "L_png.h"
#include "R_png.h"
#include "ZL_png.h"
#include "ZR_png.h"
#include "PLUS_png.h"
#include "MINUS_png.h"
#include "LEFT_png.h"
#include "UP_png.h"
#include "RIGHT_png.h"
#include "DOWN_png.h"

using namespace std;
using namespace libconfig;

static map<string, string> text;	//language


struct data {
	uint8_t * data;
	int len;
	string name;
};
static data onsdata[]{
	{(uint8_t*)A_png,A_png_size, "A.png"},
	{(uint8_t*)B_png,B_png_size ,"B.png"},
	{(uint8_t*)X_png,X_png_size, "X.png"},
	{(uint8_t*)Y_png,Y_png_size, "Y.png"},
	{(uint8_t*)SL_png,SL_png_size, "SL.png"},
	{(uint8_t*)SR_png,SR_png_size ,"SR.png"},
	{(uint8_t*)L_png,L_png_size ,"L.png"},
	{(uint8_t*)R_png,R_png_size, "R.png"},
	{(uint8_t*)ZL_png,ZL_png_size, "ZL.png"},
	{(uint8_t*)ZR_png,ZR_png_size ,"ZR.png"},
	{(uint8_t*)PLUS_png,PLUS_png_size,"PLUS.png" },
	{(uint8_t*)MINUS_png,MINUS_png_size, "MINUS.png"},
	{(uint8_t*)LEFT_png,LEFT_png_size,"LEFT.png" },
	{(uint8_t*)UP_png,UP_png_size, "UP.png"},
	{(uint8_t*)RIGHT_png,RIGHT_png_size, "RIGHT.png"},
	{(uint8_t*)DOWN_png,DOWN_png_size ,"DOWN.png"},
	{(uint8_t*)default_icon_png,default_icon_png_size,"default_icon.png"},
	{(uint8_t*)default_font_ttf,default_font_ttf_size,"default_font.ttf"}
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



extern void RunGame(GameInfo *info);
extern void WriteDefaultConfig();
extern int GetGameDir(string path, vector<string> &dirpath);
extern int GetGameIcon(string path, vector<string>&list);

extern bool CheckScript(string path);
extern int CheckFile(string path);
extern bool CheckDir(string path);



extern bool CopyFile(string Source, string Dest);
extern bool CreateDir(string path);
extern bool WriteFile(string path, uint8_t *data, int len);

extern void WriteData();


extern string GetCurrentTime(bool second = false);
extern string GetCurrentDate(bool isyear = true);
extern int GetBatteryLevel();
extern bool IsCharging();