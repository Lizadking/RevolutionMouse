
#include <iostream>
#include <wiiuse.h>    
#include <math.h>
#include <unistd.h>   
#include <fcntl.h>
#include <string>
#include "profileNix.h"
#include "profileManagerNix.h"
#include "virtualDeviceNix.h"
#include "wiiusehelper.h"
#include "fileio.h"
#include <libevdev/libevdev-uinput.h>

#define MAX_WIIMOTES				1
#define STANDARD_TIMEOUT            5


int main()
{	
 
    /*********************************************************************
    ** 
    ** INITIAL DATA STRUCTURE  SETUP
    **
    *********************************************************************/

	Logger logger("logfile.txt"); /* Create Logger instance */
    std::unique_ptr<VirtualDeviceNix> virtualDev = std::make_unique<VirtualDeviceNix>(); /* Create Virtual Device */
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

    /* Initalize the array of wiimote objects (not connected yet) 
    wiimotes = wiiuse_init(MAX_WIIMOTES);
             
    /* Find Wiimote devices 
    found = wiiuse_find(wiimotes,MAX_WIIMOTES,STANDARD_TIMEOUT);

    if(!found)
    {
        printf("No Wiimotes found\n");
        return -1;
    }

    /* Connect to wiimotes 
    connected = wiiuse_connect(wiimotes,MAX_WIIMOTES);

    if(!connected)
    {
        printf("Failed to connect to wiimote\n");
        return -1;
    }

    wiiuse_set_leds(wiimotes[0],WIIMOTE_LED_1);
    wiiuse_set_aspect_ratio(wiimotes[0], WIIUSE_ASPECT_16_9);
    */

    /*********************************************************************
    ** 
    **  MAIN INPUT LOOP
    **
    *********************************************************************/
    /*
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
						/* a generic event occurred 
						handle_event(wiimotes[currWiimote],&virtualDev);
						break;

                    case WIIUSE_STATUS:
						/* a status event occurred 
						handle_ctrl_status(wiimotes[currWiimote]);
						break;

                    case WIIUSE_DISCONNECT:
					case WIIUSE_UNEXPECTED_DISCONNECT:
						/* the wiimote disconnected 
						handle_disconnect(wiimotes[currWiimote]);
						break;

                    default:
						break;
                }

            }
        }
        
        
    }
    
    
    */
    wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
    
   

    


    //std::cout<<profileManager->getCurrentProfile().getProfileName()<<std::endl;



    
    return 0;

}
