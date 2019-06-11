#include "GUI_Main.h"
#include <switch.h>
#include <twili.h>

GUIMain *gmain;

void RunGame(GameInfo *info) {
	printf("Run Game :%s\n", info->GetPath().c_str());
	/*RUN game*/
	envSetNextLoad(info->GetPath().c_str(), (info->GetPath() + " " + info->GetPath()).c_str());
	info->SetStartTime(GetCurrentDate() + " " + GetCurrentTime());

	/*Write StartUp Info*/

	gmain->Close();
	delete gmain;
	twiliExit();
	exit(0);

}


int main(int argc , char *argv[])
{
	twiliInitialize();


	psmInitialize();

    gmain = new GUIMain();
	gmain->Show();
	while (true) 
	{
		SDL_Delay(20);
	}



    delete gmain;
	twiliExit();
    return 0;
}