#include "GUI_GameInfo.h"
#include "GUI_Utils.h"
#include <pu/Plutonium>
OnsGameInfo::OnsGameInfo(string path)
{
	complete = CheckScript(path, files) != "";
	game_path = path;
	int i = path.find_last_of('/') + 1;
	name = path.substr(i, path.length() - i);
	GetGameIcon(path, icon_path);
#ifdef DEBUG
	printf("Found Game!   Path:%s\t\tfind script:%s\t\ticon num:%d\n", game_path.c_str(), complete ? "YES" : "NO", (int)icon_path.size());
#endif
	temp_path = string(TEMP_PATH) + "/" + name;
	if (!CheckDir(temp_path))
		CreateDir(temp_path);
	//PreLoadScript(path,script_info);
#ifdef DEBUG
	if(script_info.caption!=""){
		printf("%s\n",script_info.caption.c_str());
		
		//name = pu::String(script_info.caption).AsUTF8();
	}
#endif
}

string OnsGameInfo::GetIconPath(int index)
{
	if (icon_path.size() == 0)
		return DEFAULT_ICON;
	else
	{
		if (index >= (int)icon_path.size())
			return DEFAULT_ICON;
		else
			return icon_path[index];
	}
};