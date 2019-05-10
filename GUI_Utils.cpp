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
		if (strcmp(ptr->d_name, "onsdata") == 0 || strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    //current dir OR parrent dir
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
bool CheckDir(string path) {
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
int CheckFile(string path) {
	FILE *fp = fopen(path.c_str(), "rb");
	if (!fp) return -1;
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

bool CopyFile(string Source, string Dest)
{
	FILE *inf = fopen(Source.c_str(), "rb");
	if (!inf) return false;
	FILE *of = fopen(Dest.c_str(), "wb");
	uint8_t buf[8192] = { 0 };
	size_t rsize = 0;
	while ((rsize = fread(buf, 1, 8192, inf)) > 0)
	{
		fwrite(buf, 1, rsize, of);
	}
	fclose(inf);
	fclose(of);
	return true;
}
bool WriteFile(string path, uint8_t *data,int len) {
	FILE *of = fopen(path.c_str(), "wb");
	fwrite(data, len, 1, of);
	fclose(of);
	return true;
}
void WriteData() {

	if (!CheckDir(PATH))
		CreateDir(PATH);
	if (!CheckDir(DATA_PATH))
		CreateDir(DATA_PATH);
	string path = DATA_PATH;
	path += "/";
	for (int i = 0; i < 18; i++) {
		if (CheckFile(path + onsdata[i].name) != onsdata[i].len) {
			WriteFile(path + onsdata[i].name, onsdata[i].data, onsdata[i].len);
			cout << path + onsdata[i].name << endl;
		}
			
	}
}