
#include <iostream>
#include <wiiuse.h>    
#include <math.h>
#include <unistd.h>   
#include <fcntl.h>

#include "profileNix.h"
#include "profileManagerNix.h"
#include "virtualDeviceNix.h"
#include <libevdev/libevdev-uinput.h>

#define MAX_WIIMOTES				4
#define STANDARD_TIMEOUT            5



void handle_event(struct wiimote_t* wm,VirtualDeviceNix * virtualDev );
void handle_read(struct wiimote_t* wm, byte* data, unsigned short len);
void handle_ctrl_status(struct wiimote_t* wm);
void handle_disconnect(wiimote* wm);
short any_wiimote_connected(wiimote** wm, int wiimotes);

int main()
{
    ProfileManagerNix * profileManager = new ProfileManagerNix();

    /* CREATING TWO PROFILES FOR TESTING PURPOSES: A GENERAL MOUSE SETUP AND ANKI */

    // Creating General profile
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

    // Creating Dummy profile
    ProfileNix * dummy_ptr = new ProfileNix();
    dummy_ptr->setProfileName("Dummy");

    profileManager->addProfile(dummy_ptr);
    profileManager->addProfile(general_ptr);
    profileManager->addProfile(anki_ptr);

    // Print out profiles for a test
    profileManager->getProfile(0)->printProfile();
    profileManager->getProfile(1)->printProfile();

    
    // Building the virtual device 
    VirtualDeviceNix * nixDevice_ptr = new VirtualDeviceNix();
    nixDevice_ptr->initalize();
    if(nixDevice_ptr->initalize() != 0)
    {
        std::cout<<"Couldn't Inialize virtual device"<<std::endl;
        return -1;
    }
    nixDevice_ptr->setProfileManager(profileManager);
   

    /******Wii setup******/

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

short any_wiimote_connected(wiimote** wm, int wiimotes) 
{
	int i;
	if (!wm) {
		return 0;
	}

	for (i = 0; i < wiimotes; i++) {
		if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
			return 1;
		}
	}

	return 0;
}

void handle_disconnect(wiimote* wm) 
{
	printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}

void handle_ctrl_status(struct wiimote_t* wm) 
{
	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

	printf("attachment:      %i\n", wm->exp.type);
	printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
	printf("ir:              %i\n", WIIUSE_USING_IR(wm));
	printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	printf("battery:         %f %%\n", wm->battery_level);
}

void handle_read(struct wiimote_t* wm, byte* data, unsigned short len) 
{
	int i = 0;

	printf("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
	printf("finished read of size %i\n", len);
	for (; i < len; ++i) {
		if (!(i % 16)) {
			printf("\n");
		}
		printf("%x ", data[i]);
	}
	printf("\n\n");
}


void handle_event(struct wiimote_t* wm,VirtualDeviceNix * virtualDev) 
{
   
	printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

	/* if a button is pressed, report it */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_A)) {
		printf("A pressed\n");
        virtualDev->pressWiiKey(WII_A);
        std::cout<<virtualDev->getProfileManager()->getCurrentProfile()->getProfileName()<<std::endl;
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		printf("B pressed\n");
        virtualDev->pressWiiKey(WII_B);

	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		printf("UP pressed\n");
        virtualDev->pressWiiKey(WII_UP);
	}
		
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN)){
		printf("DOWN pressed\n");
        virtualDev->pressWiiKey(WII_DOWN);
	}
		
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	{
		printf("LEFT pressed\n");
        virtualDev->pressWiiKey(WII_LEFT);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	{
		printf("RIGHT pressed\n");
        virtualDev->pressWiiKey(WII_RIGHT);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	{
		printf("MINUS pressed\n");
        virtualDev->pressWiiKey(WII_MINUS);
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	{
		printf("PLUS pressed\n");
        virtualDev->pressWiiKey(WII_PLUS);
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		printf("ONE pressed\n");
        virtualDev->pressWiiKey(WII_ONE);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		printf("TWO pressed\n");
        virtualDev->pressWiiKey(WII_TWO);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	{
		printf("HOME pressed\n");
        virtualDev->getProfileManager()->changeProfile();
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) 
	{
		//wiiuse_set_ir(wm, 0);
	}


	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) 
	{
		//wiiuse_set_ir(wm, 1);

		
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B)) 
	{
		//wiiuse_toggle_rumble(wm);
	}
        

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		//wiiuse_set_ir(wm, 1);
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
		//wiiuse_set_ir(wm, 0);
	}

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		wiiuse_set_motion_plus(wm, 0); // off
	}
	/*
	 *	If IR tracking is enabled then print the coordinates
	 *	on the virtual screen that the wiimote is pointing to.
	 *
	 *	Also make sure that we see at least 1 dot.
	 */
	if (WIIUSE_USING_IR(wm)) 
	{
			
			
		
        
	}

}