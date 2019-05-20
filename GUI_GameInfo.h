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
	string GetIconPath(int index) { return icon_path.size() == 0 ? DEFAULT_ICON : (index >= icon_path.size() ? DEFAULT_ICON : icon_path[index]); };
private:
	bool complete;
	string game_path;
	string name;
	string cmd;
	vector<string> icon_path;

	



};