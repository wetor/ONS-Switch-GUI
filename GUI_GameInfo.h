#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "GUI_define.h"
using namespace std;
class GameInfo {
public:
	GameInfo() {};
	GameInfo(string path);
	string GetPath() { return game_path; };
	string GetName() { return name; };
	bool GetComplete() { return complete; };
	string GetIconPath(int index);
	void SetStartTime(string time) { start_time = time; };
	string GetStartTime() { return start_time; };
private:
	bool complete;
	string game_path;
	string name;
	string cmd;
	vector<string> icon_path;
	string start_time;

};