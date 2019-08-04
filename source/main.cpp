#include "GUI_Main.h"
#include <switch.h>
#include <twili.h>
#include <Common.h>

extern u32 __nx_applet_type;
extern char *fake_heap_end;
extern "C"
{
	void __nx_win_init(void);
	void __libnx_init_time(void);

	void __appInit(void)
	{
		Result rc = smInitialize();
		if (R_FAILED(rc))
			fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

		rc = setsysInitialize();
		if (R_SUCCEEDED(rc))
		{
			SetSysFirmwareVersion fw;
			rc = setsysGetFirmwareVersion(&fw);
			if (R_SUCCEEDED(rc))
				hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
			setsysExit();
		}

		rc = timeInitialize();
		if (R_FAILED(rc))
			fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_Time));

		__libnx_init_time();

		rc = fsInitialize();
		if (R_FAILED(rc))
			fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

		fsdevMountSdmc();
	}
}

GUIMain *gmain;
map<string,int> settings; 
bool loop_exit = false;

void RunGame(OnsGameInfo *info)
{
	int opt = gmain->CreateShowDialog(text["msg_tip_run"], "", {text["msg_run"], text["msg_no"]}, true); // (using latest option as cancel option)
	if(opt==0){
		printf("Run Game :%s\n", info->GetPath().c_str());
		/*RUN game*/
		envSetNextLoad("sdmc:/onsemu/ONS.nro", ("sdmc:/onsemu/ONS.nro " + info->GetPath() + " " + (settings["fullscreen"]==1?"1":"0")).c_str());
		//info->SetStartTime(GetCurrentDate() + " " + GetCurrentTime());
		gmain->Close();
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

	twiliInitialize();

	srand(time(NULL));

	if (R_FAILED(svcSetHeapSize(&ghaddr, 0x10000000)))
		exit(1);
	fake_heap_end = (char *)ghaddr + 0x10000000;

	if (R_FAILED(appletInitialize()))
		printf("applet error!\n");
	if (R_FAILED(hidInitialize()))
		printf("hid error!\n");
	if (R_FAILED(accountInitialize()))
		printf("account error!\n");
	if (R_FAILED(ncmInitialize()))
		printf("ncm error!\n");
	if (R_FAILED(nsInitialize()))
		printf("ns error!\n");
	if (R_FAILED(psmInitialize()))
		printf("psm error!\n");
	if (R_FAILED(setInitialize()))
		printf("set error!\n");
	if (R_FAILED(setsysInitialize()))
		printf("setsys error!\n");
	if (R_FAILED(splInitialize()))
		printf("spl error!\n");
	if (R_FAILED(bpcInitialize()))
		printf("bpc error!\n");
	if (R_FAILED(nifmInitialize()))
		printf("nifm error!\n");
	

	//argv[0] = (char*)"sdmc:/onsemu/hanchan/arc.nsa";
	//nsadec_main(argv[0]);

	WriteData();
	WriteConfig(true);
	LoadConfig();
	LoadLanguage(settings["language"]);
	gmain = new GUIMain();
	gmain->Show();
	while (true)
	{
		SDL_Delay(20);
		if (loop_exit){
			gmain->Close();
			break;
		}

	}
	//gmain->Close();
	delete gmain;
	//envSetNextLoad("sdmc:/onsemu/ONScripter.nro", "sdmc:/onsemu/ONScripter.nro test233sdmc:/onsemu/ONScripter.nro");
	nifmExit();
	bpcExit();
	splExit();
	setsysExit();
	setExit();
	psmExit();
	nsExit();
	ncmExit();
	accountExit();
	hidExit();
	appletExit();
	svcSetHeapSize(&ghaddr, ((u8 *)envGetHeapOverrideAddr() + envGetHeapOverrideSize()) - (u8 *)ghaddr);
	twiliExit();
	



	return 0;
}