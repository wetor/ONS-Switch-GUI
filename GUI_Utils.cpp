#include "GUI_Utils.h"

int GetGameDir(string path, vector<string>&list)
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
		if (strcmp(ptr->d_name, "config") == 0 || strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    //current dir OR parrent dir
			continue;
		else if (ptr->d_type == 4)    //dir
		{
			string temp = path + "/" + ptr->d_name;
			list.push_back(temp);
		}
	}
	closedir(dir);
	return list.size();
}

bool CheckScript(string path) {
	DIR *dir;
	struct dirent *ptr;
	if ((dir = opendir(path.c_str())) == NULL)
	{
		return false;
	}
	bool exist = false;
	while ((ptr = readdir(dir)) != NULL)
	{
		if (ptr->d_type == 8)    //file
		{
			if (!strcmp(ptr->d_name, "0.txt")) exist = true;
			else if (!strcmp(ptr->d_name, "00.txt")) exist = true;
			else if (!strcmp(ptr->d_name, "nscr_sec.dat")) exist = true;
			else if (!strcmp(ptr->d_name, "nscript.___")) exist = true;
			else if (!strcmp(ptr->d_name, "nscript.dat")) exist = true;
		}
		if (exist) break;
	}
	closedir(dir);
	if (exist)	return true;
	else return false;
}

int GetGameIcon(string path, vector<string>&list)
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
		if (ptr->d_type == 8)    //file
		{
			string fn = "icon";
			if (icon_num == -1)
				fn += ".png";
			else
				fn += to_string(icon_num) + ".png";
			if (!strcmp(ptr->d_name, fn.c_str())) {
				list.push_back(path + "/" + fn);
				icon_num++;
			}
		}
	}
	closedir(dir);
	return list.size();

}