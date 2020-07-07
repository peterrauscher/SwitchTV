// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

void openPage()
{
    Result res;
    WebCommonConfig cfg;

    res = webPageCreate(&cfg, "http://m.twitch.tv");

    if(R_SUCCEEDED(res)) {
        res = webConfigSetWhitelist(&cfg, "^http*");
        if(R_SUCCEEDED(res)){
            res = webConfigShow(&cfg, NULL);
        } else {
            printf("Something went wrong.");
        }
    } else {
        printf("Failed while making WebCommonConfig object.");
    }
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    consoleInit(NULL);

    printf("You shouldn't see this text. Press '+' to exit.\n");
    printf(CONSOLE_RESET "SwitchTV - butforme\n");
    printf(CONSOLE_GREEN "Press X to start\n");
    
    openPage();

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

        if (kDown & KEY_X)
        {
            //Only open if not running in applet/album mode
            if(appletGetAppletType() == AppletType_Application){
                openPage();
            } else {
                printf(CONSOLE_RED "Refusing to launch. Do not run SwitchTV in album or applet mode.\n");
            }
        }
        
        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
