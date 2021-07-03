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
#include <errno.h>
extern int errno;

extern u32 __nx_applet_type;
extern char *fake_heap_end;
// extern "C"
// {

// 	void __libnx_init_time(void);
// 	void __appInit(void)
// 	{
// 		Result rc = smInitialize();
// 		if (R_FAILED(rc))
// 			fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));
// 		rc = setsysInitialize();
// 		if (R_SUCCEEDED(rc))
// 		{
// 			SetSysFirmwareVersion fw;
// 			rc = setsysGetFirmwareVersion(&fw);
// 			if (R_SUCCEEDED(rc))
// 				hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
// 			setsysExit();
// 		}
// 		rc = timeInitialize();
// 		if (R_FAILED(rc))
// 			fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_Time));
// 		__libnx_init_time();

// 		rc = fsInitialize();
// 		if (R_FAILED(rc))
// 			fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

// 		fsdevMountSdmc();
// 	}
// }
GUIMain::Ref gmain;
map<string, int> settings;
bool loop_exit = false;
void RunGame(OnsGameInfo *info)
{
	WriteConfig();
	if (CheckFile("sdmc:/onsemu/exefs/ONScripter.nro") < 0)
	{
		gmain->CreateShowDialog(text["msg_not_found"], "", {text["msg_yes"]}, false);
		return;
	}

	int opt = gmain->CreateShowDialog(text["msg_tip_run"], "", {text["msg_run"], text["msg_no"]}, true); // (using latest option as cancel option)
	if (opt == 0)
	{
		printf("Run Game :%s\n", info->GetPath().c_str());
		string setting = "0";
		if (!settings["fontoutline"] && settings["fullscreen"])
			setting = "1";
		else if (settings["fontoutline"] && !settings["fullscreen"])
			setting = "2";
		else if (settings["fontoutline"] && settings["fullscreen"])
			setting = "3";
		

		/*RUN game*/
		envSetNextLoad("sdmc:/onsemu/exefs/ONScripter.nro", (string(DATA_PATH) + " \"" + info->GetPath() + "\" " + setting).c_str());
		//info->SetStartTime(GetCurrentDate() + " " + GetCurrentTime());
		//gmain->Close();
		loop_exit = true;
	}
	/*Write StartUp Info*/
	//loop_exit = true;
	//gmain->Close();
	//delete gmain;
	//twiliExit();
	//exit(0);
}

static void *ghaddr;
int main(int argc, char *argv[])
{
#ifdef DEBUG
	twiliInitialize();
	twiliBindStdio();
#endif
	srand(time(NULL));
	if (R_FAILED(svcSetHeapSize(&ghaddr, 0x10000000)))
		exit(1);
	fake_heap_end = (char *)ghaddr + 0x10000000;
	if (R_FAILED(appletInitialize()))
		printf("applet error!\n");
	if (R_FAILED(hidInitialize()))
		printf("hid error!\n");
	// if (R_FAILED(accountInitialize(AccountServiceType_System)))
	// 	printf("account error!\n");
	// if (R_FAILED(avmInitialize()))
	// 	printf("ncm error!\n");
	// if (R_FAILED(ncmInitialize()))
	// 	printf("ncm error!\n");
	// if (R_FAILED(nsInitialize()))
	// 	printf("ns error!\n");
	// if (R_FAILED(psmInitialize()))
	// 	printf("psm error!\n");
	// if (R_FAILED(setInitialize()))
	// 	printf("set error!\n");
	// if (R_FAILED(setsysInitialize()))
	// 	printf("setsys error!\n");
	// if (R_FAILED(nifmInitialize(NifmServiceType_User)))
	// 	printf("nifm error!\n");


	//argv[0] = (char*)"sdmc:/onsemu/hanchan/arc.nsa";
	//nsadec_main(argv[0]);
	printf("hello world\n");
	WriteData();
	WriteConfig(true);
	printf("write over\n");
	LoadConfig();
	LoadLanguage(settings["language"]);
	gmain = GUIMain::New();
	gmain->Show();
	while (true)
	{
		SDL_Delay(100);
		if (loop_exit)
			break;
	}
	//envSetNextLoad("sdmc:/onsemu/ONScripter.nro", "sdmc:/onsemu/ONScripter.nro test233sdmc:/onsemu/ONScripter.nro");
	// nifmExit();
	// bpcExit();
	// splExit();
	// setsysExit();
	// setExit();
	// psmExit();
	// nsExit();
	// avmExit();
	// ncmExit();
	// accountExit();
	hidExit();
	appletExit();
	svcSetHeapSize(&ghaddr, ((u8 *)envGetHeapOverrideAddr() + envGetHeapOverrideSize()) - (u8 *)ghaddr);
#ifdef DEBUG
	twiliExit();
#endif
	return 0;
}