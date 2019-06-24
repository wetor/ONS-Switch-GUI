#include "GUI_GameInfo.h"
#include "GUI_Utils.h"
GameInfo::GameInfo(string path) {
	complete = CheckScript(path);
	game_path = path;
	int i = path.find_last_of('/') + 1;
	name = path.substr(i, path.length() - i);
	GetGameIcon(path, icon_path);
	printf("Found Game!   Path:%s\t\tfind script:%s\t\ticon num:%d\n", game_path.c_str(), complete ? "YES" : "NO", icon_path.size());
}

string GameInfo::GetIconPath(int index) 
{ 
	if (icon_path.size() == 0)
		return DEFAULT_ICON;
	else {
		if(index >= icon_path.size())
			return DEFAULT_ICON;
		else
			return icon_path[index];
	}
};