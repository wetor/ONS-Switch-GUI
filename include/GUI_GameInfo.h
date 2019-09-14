#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "SarReader.h"
#include "NsaReader.h"

using namespace std;

struct script_t{
	//*define
	int w,h;
	string caption;
	string versionstr;
	//*start
};

class OnsGameInfo {
public:
	OnsGameInfo() {};
	OnsGameInfo(string path);
	string GetPath() { return game_path; };
	string GetName() { return name; };
	bool GetComplete() { return complete; };
	string GetIconPath(int index);
	void SetStartTime(string time) { start_time = time; };
	string GetStartTime() { return start_time; };

private:
	bool complete;
	string game_path;
	string temp_path;
	string name;
	string cmd;
	vector<string> icon_path;
	string start_time;
	vector<string> files;
	script_t script_info;
	
};
class KrkrGameInfo {
public:
	KrkrGameInfo(){};

};