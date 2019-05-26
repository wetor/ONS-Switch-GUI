#include "GUI_Main.h"
#include <switch.h>
#include <twili.h>
// Main entrypoint, call the app here
int main()
{
	twiliInitialize();
	psmInitialize();
    // Create the application
    GUIMain *gmain = new GUIMain();
    // Show it. This function will finalize when the application's "Close()" function is called.
	gmain->Show();
	while (true) 
	{
		SDL_Delay(20);
		if (gmain->isExit())
			break;
	}
    // IMPORTANT! free the application to destroy allocated memory and to finalize graphics.
    delete gmain;
    // Exit

	twiliExit();
    return 0;
}