
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
	/*Create Logger instance */
	Logger logger("logfile.txt"); 

	/*FILE OPERATIONS: Load in all the profiles *
	initalizeProfileDirectory(&logger);
	iterateProfileDirectory(&logger,profileManager);

	/* Initalize the profileManager */
    ProfileManagerNix * profileManager = new ProfileManagerNix();

	/* Building the virtual device */
    VirtualDeviceNix * nixDevice_ptr = new VirtualDeviceNix();
    nixDevice_ptr->initalize();
    if(nixDevice_ptr->initalize() != 0)
    {
        std::cout<<"Couldn't Inialize virtual device"<<std::endl;
        return -1;
    }

	/* Bind profile manager to virtual device */
    nixDevice_ptr->setProfileManager(profileManager);

    /* CREATING TWO PROFILES FOR TESTING PURPOSES: A GENERAL MOUSE SETUP AND ANKI */

    /*Creating General profile */
    ProfileNix * general_ptr = new ProfileNix();
    general_ptr->setProfileName("General");
    general_ptr->setButtonProfile(WII_A,BTN_LEFT);
    general_ptr->setButtonProfile(WII_B,BTN_RIGHT);
    general_ptr->setButtonProfile(WII_ONE,KEY_F1);
    general_ptr->setButtonProfile(WII_UP,KEY_PAGEUP);
    general_ptr->setButtonProfile(WII_DOWN,KEY_PAGEDOWN);



    // Creating Anki profile
    ProfileNix * anki_ptr = new ProfileNix();
    anki_ptr->setProfileName("Anki");
    anki_ptr->setButtonProfile(WII_A,KEY_SPACE);
    anki_ptr->setButtonProfile(WII_B,KEY_1);
	anki_ptr->setButtonProfile(WII_UP,KEY_UP);
	anki_ptr->setButtonProfile(WII_DOWN,KEY_DOWN);


	profileManager->addProfile(anki_ptr);

    
    
   
	// Note Assert: At this point there should be a valid virtual device AND binded with a profile manager
    /******Wiiuse setup******/
	
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
	
    /* Main Input loop */
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
						handle_event(wiimotes[currWiimote],nixDevice_ptr);
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
    
    
    wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
	
    delete(profileManager);
    delete(nixDevice_ptr);
    return 0;

}
