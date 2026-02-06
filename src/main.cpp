
#include <iostream>
#include <wiiuse.h>    
#include <math.h>
#include <unistd.h>   
#include <fcntl.h>
#include <string>
#include <memory>

#include "include/profileNix.h"
#include "include/profileManagerNix.h"
#include "include/virtualDeviceNix.h"
#include "include/wiiusehelper.h"
#include "include/fileio.h"
#include <libevdev/libevdev-uinput.h>
#include <SDL.h>


#define MAX_WIIMOTES				1
#define STANDARD_TIMEOUT            5


int main()
{	
    /*********************************************************************
    ** 
    ** SDL INIT
    **
    *********************************************************************/
    int initSDLEvent = SDL_Init(SDL_INIT_EVENTS);

    /*********************************************************************
    ** 
    ** INITIAL DATA STRUCTURE  SETUP
    **
    *********************************************************************/

	Logger logger("logfile.txt"); /* Create Logger instance */
    std::shared_ptr<VirtualDeviceNix> virtualDev = std::make_unique<VirtualDeviceNix>(); /* Create Virtual Device */
    std::shared_ptr<ProfileManagerNix>  profileManager = std::make_shared<ProfileManagerNix>(); /* Initalize the profileManager */
    
    /* Building the virtual device*/
    virtualDev->initalize();
    if(virtualDev->initalize() != 0)
    {
        std::cout<<"Couldn't Inialize virtual device"<<std::endl;
        return -1;
    }

    virtualDev->setProfileManager(profileManager); /* Bind the ProfileManager to the Virtual Device */

    /*FILE OPERATIONS: Load in all the profiles*/
	initalizeProfileDirectory(&logger);
	iterateProfileDirectory(&logger,*profileManager);

    /*********************************************************************
    ** 
    ** WIIMOTE SETUP
    **
    *********************************************************************/
    
    wiimote ** wiimotes; 
    int found = 0;
    int connected = 0;

    /* Initalize the array of wiimote objects (not connected yet) */
    wiimotes = wiiuse_init(MAX_WIIMOTES);
             
    /* Find Wiimote devices */
    found = wiiuse_find(wiimotes,MAX_WIIMOTES,STANDARD_TIMEOUT);

    if(!found)
    {
        printf("No Wiimotes found\n");
        return -1;
    }

    /* Connect to wiimotes */
    connected = wiiuse_connect(wiimotes,MAX_WIIMOTES);

    if(!connected)
    {
        printf("Failed to connect to wiimote\n");
        return -1;
    }

    wiiuse_set_leds(wiimotes[0],WIIMOTE_LED_1);
    wiiuse_set_aspect_ratio(wiimotes[0], WIIUSE_ASPECT_16_9);
    int height = 1300;
	int width = 2500;
    wiiuse_set_ir_vres(wiimotes[0],width * 1.2 ,height * 1.2 );

    wiiuse_set_ir_sensitivity(wiimotes[0],3);

    /*********************************************************************
    ** 
    **  MAIN INPUT LOOP
    **
    *********************************************************************/
    
  	while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) 
    {
       
        if(wiiuse_poll(wiimotes,MAX_WIIMOTES))
        {
            int currWiimote = 0;
            for(;currWiimote < MAX_WIIMOTES;currWiimote++)
            {
                switch (wiimotes[currWiimote]->event) 
                {
					case WIIUSE_EVENT:
						/* a generic event occurred */
						handle_event_debug_motion(wiimotes[currWiimote],virtualDev);
						break;

                    case WIIUSE_STATUS:
						/* a status event occurred */
						handle_ctrl_status(wiimotes[currWiimote]);
						break;

                    case WIIUSE_DISCONNECT:
					case WIIUSE_UNEXPECTED_DISCONNECT:
						/* the wiimote disconnected */
						handle_disconnect(wiimotes[currWiimote]);
						break;

                    default:
						break;
                }

            }
        }
        
        
    }
    
    /*********************************************************************
    ** 
    ** MEMORY CLEANUP
    **
    *********************************************************************/
    wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    
   

    


    //std::cout<<profileManager->getCurrentProfile().getProfileName()<<std::endl;



    
    return 0;

}
