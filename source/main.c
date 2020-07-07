// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

void openDesktopPage()
{
    Result res;
    WebCommonConfig mobileConfig;

    res = webPageCreate(&mobileConfig, "https://twitch.tv");

    if(R_SUCCEEDED(res)) {
        res = webConfigShow(&mobileConfig, NULL);
    } else {
        printf("Failed while making WebCommonConfig object.");
    }
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    consoleInit(NULL);

    printf("You shouldn't see this text. Press '+' to exit.\n");

    openDesktopPage();

    // Main loop
    while (appletMainLoop())
    {
        // Scan all the inputs. This should be done once for each frame
        hidScanInput();

        // hidKeysDown returns information about which buttons have been
        // just pressed in this frame compared to the previous one
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break; // break in order to return to hbmenu


        //Only open if not running in applet/album mode
        if(appletGetAppletType() == AppletType_Application){
            openDesktopPage();
        }

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
