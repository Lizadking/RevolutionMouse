
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

	/*FILE OPERATIONS: Load in all the profiles*/
	initalizeProfileDirectory(&logger);
	iterateProfileDirectory(&logger);
   

    std::unique_ptr<VirtualDeviceNix> virtualDev = std::make_unique<VirtualDeviceNix>();

	/* Initalize the profileManager */
    std::shared_ptr<ProfileManagerNix>  profileManager = std::make_shared<ProfileManagerNix>();
    
    /* Building the virtual device*/
    //virtualDev->initalize();
    if(virtualDev->initalize() != 0)
    {
        std::cout<<"Couldn't Inialize virtual device"<<std::endl;
        return -1;
    }

    profileManager->createProfile("Test");
    profileManager->createProfile("Test1");
    profileManager->createProfile("Test2");
    profileManager->createProfile("Test3");

    writeProfileToDisk(&profileManager->getCurrentProfile(),&logger);
    profileManager->changeProfile();
    writeProfileToDisk(&profileManager->getCurrentProfile(),&logger);
    profileManager->changeProfile();
    writeProfileToDisk(&profileManager->getCurrentProfile(),&logger);
    profileManager->changeProfile();
    writeProfileToDisk(&profileManager->getCurrentProfile(),&logger);
    profileManager->changeProfile();
    writeProfileToDisk(&profileManager->getCurrentProfile(),&logger);

    
    writeProfileToDisk(&profileManager->getCurrentProfile(),&logger);


    //std::cout<<profileManager->getCurrentProfile().getProfileName()<<std::endl;



    /*
    profileManager->createProfile("fdfd");
    profileManager->createProfile("rrrrr");
    profileManager->createProfile("");

    std::cout<<profileManager->getCurrentProfile().getProfileName()<<std::endl;
    */
    


    /*Testing profile switching*/

    


	/* Building the virtual device 
    VirtualDeviceNix * nixDevice_ptr = new VirtualDeviceNix();
    nixDevice_ptr->initalize();
    if(nixDevice_ptr->initalize() != 0)
    {
        std::cout<<"Couldn't Inialize virtual device"<<std::endl;
        return -1;
    }

	/* Bind profile manager to virtual device 
    nixDevice_ptr->setProfileManager(profileManager);

    /* CREATING TWO PROFILES FOR TESTING PURPOSES: A GENERAL MOUSE SETUP AND ANKI */

    
    return 0;

}
