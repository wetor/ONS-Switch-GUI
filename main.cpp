#include "GUI_Main.h"
#include <switch.h>
#include <twili.h>
extern u32 __nx_applet_type;
extern char *fake_heap_end;
extern "C"
{
	void __nx_win_init(void);
	void __libnx_init_time(void);

	void __appInit(void)
	{
		Result rc = smInitialize();
		if (R_FAILED(rc)) fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

		rc = setsysInitialize();
		if (R_SUCCEEDED(rc))
		{
			SetSysFirmwareVersion fw;
			rc = setsysGetFirmwareVersion(&fw);
			if (R_SUCCEEDED(rc)) hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
			setsysExit();
		}

		rc = timeInitialize();
		if (R_FAILED(rc)) fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_Time));

		__libnx_init_time();

		rc = fsInitialize();
		if (R_FAILED(rc)) fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

		fsdevMountSdmc();
	}
}


GUIMain *gmain;
bool loop_exit = false;

void RunGame(GameInfo *info) {
	printf("Run Game :%s\n", info->GetPath().c_str());
	/*RUN game*/
	envSetNextLoad("sdmc:/onsemu/ONS.nro", ("sdmc:/onsemu/ONS.nro " + info->GetPath()).c_str());
	//info->SetStartTime(GetCurrentDate() + " " + GetCurrentTime());
	gmain->Close();
	loop_exit = true;
	/*Write StartUp Info*/
	//loop_exit = true;
	//gmain->Close();
	
	//delete gmain;
	//twiliExit();
	//exit(0);

}


static void *ghaddr;
int main(int argc , char *argv[])
{
	twiliInitialize();
	

	srand(time(NULL));

	if (R_FAILED(svcSetHeapSize(&ghaddr, 0x10000000))) exit(1);
	fake_heap_end = (char*)ghaddr + 0x10000000;

	if (R_FAILED(appletInitialize()))	printf("test00\n");
	if (R_FAILED(hidInitialize()))		printf("test01\n");
	if (R_FAILED(accountInitialize()))	printf("test02\n");
	if (R_FAILED(ncmInitialize()))		printf("test03\n");
	if (R_FAILED(nsInitialize()))		printf("test04\n");
	if (R_FAILED(psmInitialize()))		printf("test05\n");
	if (R_FAILED(setInitialize()))		printf("test06\n");
	if (R_FAILED(setsysInitialize()))	printf("test07\n");
	if (R_FAILED(splInitialize()))		printf("test08\n");
	if (R_FAILED(bpcInitialize()))		printf("test09\n");
	if (R_FAILED(nifmInitialize()))		printf("test10\n");


    gmain = new GUIMain();
	gmain->Show();
	while (true) 
	{
		SDL_Delay(20);
		if (loop_exit)
			break;
	}


	//gmain->Close();
    delete gmain;
	twiliExit();


    return 0;
}