#include "GUI_Main.h"
#include <switch.h>
#ifdef DEBUG
#include <twili.h>
#endif
// #include <Common.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
// #include <errno.h>
// extern int errno;

char *self_path;
GUIMain::Ref gmain;
map<string, int> settings;
bool loop_exit = false;
bool loop_restart = false;
void RunGame(OnsGameInfo *info)
{
	WriteConfig();
	if (CheckFile(ONSB_PATH) < 0)
	{
		gmain->CreateShowDialog(text["msg_not_found_self"], "", {text["msg_yes"]}, false);
		return;
	}
	if (CheckFile(ONS_PATH) < 0)
	{
		gmain->CreateShowDialog(text["msg_not_found"], "", {text["msg_yes"]}, false);
		return;
	}

	int opt = gmain->CreateShowDialog(text["msg_tip_run"], "", {text["msg_run"], text["msg_no"]}, true); // (using latest option as cancel option)
	if (opt == 0)
	{
		printf("Run Game :%s\n", info->GetPath().c_str());
		int setting = 0;
		if(settings["fullscreen"])
			setting |= 1;
		if(settings["fontoutline"])
			setting |= 2;
		if(settings["language"]==1) // english
			setting |= 4;
		/*RUN game*/
		// args:
		// 0 : ons NRO program path
		// 1 : ONScripter game folder
		// 2 : mode: 0 default; 1 fullscreen stretch; 2 fullscreen and outline
		// 3 : return nro path after game exit
		char args[512];
		sprintf(args, "\"%s\" \"%s\" %d \"%s\"", ONS_PATH, info->GetPath().c_str(), setting, self_path);
		envSetNextLoad(ONS_PATH, args);
		
		//info->SetStartTime(GetCurrentDate() + " " + GetCurrentTime());
		//gmain->Close();
		//printf("exec %s\n",(string(PATH) + " \"" + info->GetPath() + "\" " + setting).c_str());
		loop_exit = true;
	}
	/*Write StartUp Info*/

}
// static void *ghaddr;
int main(int argc, char *argv[])
{
#ifdef DEBUG
	twiliInitialize();
	twiliBindStdio();
#endif
	srand(time(NULL));
	romfsInit();
	if( envHasArgv() && argc>0)
		self_path = argv[0];
	else
		self_path = ONSB_PATH;
	//argv[0] = (char*)"sdmc:/onsemu/hanchan/arc.nsa";
	//nsadec_main(argv[0]);
	CreateDirs();
	WriteConfig(true);
	LoadConfig();
	LoadLanguage(settings["language"]);
	gmain = GUIMain::New();
	gmain->Show();

	if (loop_restart){
		envSetNextLoad(self_path, self_path);
	}
	romfsExit();
#ifdef DEBUG
	twiliExit();
#endif

	return EXIT_SUCCESS;
}