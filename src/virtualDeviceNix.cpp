#include <iostream>
#include "profileManagerNix.h"
#include "virtualDeviceNix.h"
#include <libevdev/libevdev-uinput.h>

VirtualDeviceNix::VirtualDeviceNix(){}
VirtualDeviceNix::~VirtualDeviceNix()
{
    libevdev_uinput_destroy(m_uinput);
    std::cout<<"Destroyed m_uinput"<<std::endl;
    m_profileManager = nullptr;

}
int VirtualDeviceNix::initalize()
{
    // Create a device from scratch 
    struct libevdev *dev = libevdev_new();

    /*
    * ENABLE MOUSE PROPERTIES HERE 
    */

    libevdev_set_name(dev, "Virtual Device");
    libevdev_enable_event_type(dev, EV_KEY);
    libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, nullptr);
    libevdev_enable_event_code(dev, EV_KEY, BTN_RIGHT, nullptr);
    libevdev_enable_event_code(dev, EV_KEY, BTN_MIDDLE, nullptr);

    /*
    * Enable every scancode from 1-248 (https://elixir.bootlin.com/linux/v6.17/source/include/uapi/linux/input-event-codes.h#L65)
    * 
    */

    for(unsigned int SCANCODE = 1;SCANCODE<=248;SCANCODE++)
    {
        libevdev_enable_event_code(dev, EV_KEY,SCANCODE,nullptr);
    }

    int duplicateDevice = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &m_uinput);
    libevdev_free(dev); // Don't need this anymore 
    return duplicateDevice;
}


struct libevdev_uinput * VirtualDeviceNix::getUinputDevice()
{
   // This needs to be checked later but we ball 
    return m_uinput;
    
}

void VirtualDeviceNix::setProfileManager(ProfileManagerNix * profile)
{
    if(profile == nullptr)
    {
        std::cout<<"ERROR binding a nullptr to virtual device"<<std::endl;
        m_profileManager = nullptr;
    }
    else
    {
        m_profileManager = profile;
    }
}

ProfileManagerNix * VirtualDeviceNix::getProfileManager()
{
    return m_profileManager;
}
int VirtualDeviceNix::getProfileManagerSize()
{
    // Must have a profile manager binded to it
    if(m_profileManager == nullptr)
    {
        std::cout<<"ERROR: No binded profile manager to virtual device"<<std::endl;
        return -1;
    }

    else
    {
        int size = m_profileManager->getProfileListSize();
        return size;
    }
}
/*This is so ugly fix it later*/
void VirtualDeviceNix::pressWiiKey(int WII_BINDING)
{
    // Must have a profile available 
    
    // Get current profile
    ProfileNix * current = m_profileManager->getCurrentProfile();

    /*Debug get name 
    std::cout<<"DEBUG: current profile -> "<<current->getProfileName();*/
    

    struct libevdev_uinput * device = getUinputDevice();

    int bindedButton = 0;

    // Get the key curently binded to button
    switch(WII_BINDING)
    {
        case WII_A:
            bindedButton = current->getButtonProfile(WII_A);
        break;

        case WII_B:
            bindedButton = current->getButtonProfile(WII_B);
        break;

        case WII_ONE:
            bindedButton = current->getButtonProfile(WII_ONE);
        break;

        case WII_TWO:
            bindedButton = current->getButtonProfile(WII_TWO);
        break;

        case WII_PLUS:
            bindedButton = current->getButtonProfile(WII_PLUS);
        break;

        case WII_MINUS:
            bindedButton = current->getButtonProfile(WII_MINUS);
        break;

        case WII_UP:
            bindedButton = current->getButtonProfile(WII_UP);
        break;

        case WII_DOWN:
            bindedButton = current->getButtonProfile(WII_DOWN);
        break;

        case WII_LEFT:
            bindedButton = current->getButtonProfile(WII_LEFT);
        break;

        case WII_RIGHT:
            bindedButton = current->getButtonProfile(WII_RIGHT);
        break;

        default:
            break;
    }

    // TEMP SOLUTION:
    /*
    * for mouse left they go into hex 0x110 (272) mouse right 0x111(273) anything above 255 should be converted to their corresponding mouse code 
    

    if(bindedButton >= 255)
    {
        std::cout<<"Temperoary mouse button adjustment"<<std::endl;
        std::cout<<"Val: "<<bindedButton<<std::endl;
        switch(bindedButton)
        {
            case 272:
                libevdev_uinput_write_event(device,EV_KEY,BTN_LEFT,1);
                libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

                libevdev_uinput_write_event(device,EV_KEY,BTN_LEFT,0);
                libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);
                break;
            case 273:
                libevdev_uinput_write_event(device,EV_KEY,BTN_RIGHT,1);
                libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

                libevdev_uinput_write_event(device,EV_KEY,BTN_RIGHT,0);
                libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);
                break;

        }
    }
        */
 
        // With all the bindings and settings done execute the press
        int test = libevdev_uinput_write_event(device,EV_KEY,bindedButton,1);
        //std::cout<<bindedButton<<std::endl;
        libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

        libevdev_uinput_write_event(device,EV_KEY,bindedButton,0);
        libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

    


}