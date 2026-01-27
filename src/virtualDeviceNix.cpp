#include <iostream>
#include <unistd.h>
#include "profileManagerNix.h"
#include "virtualDeviceNix.h"
#include <libevdev/libevdev-uinput.h>

VirtualDeviceNix::VirtualDeviceNix(){}
VirtualDeviceNix::~VirtualDeviceNix()
{
   
    //close(libevdev_uinput_get_fd(m_uinput));
    libevdev_free(m_dev);
    libevdev_uinput_destroy(m_uinput);
    std::cout<<"Destroyed m_uinput"<<std::endl;
    

}

int VirtualDeviceNix::initalize()
{
    // Create a device from scratch 
    m_dev = libevdev_new();

    /*
    * ENABLE MOUSE PROPERTIES HERE 
    */

    libevdev_set_name(m_dev, "Virtual Device");
    libevdev_enable_event_type(m_dev, EV_KEY);
    libevdev_enable_event_code(m_dev, EV_KEY, BTN_LEFT, nullptr);
    libevdev_enable_event_code(m_dev, EV_KEY, BTN_RIGHT, nullptr);
    libevdev_enable_event_code(m_dev, EV_KEY, BTN_MIDDLE, nullptr);

    /*
    * Enable every scancode from 1-248 (https://elixir.bootlin.com/linux/v6.17/source/include/uapi/linux/input-event-codes.h#L65)
    * 
    */

    for(unsigned int SCANCODE = 1;SCANCODE<=248;SCANCODE++)
    {
        libevdev_enable_event_code(m_dev, EV_KEY,SCANCODE,nullptr);
    }

    int duplicateDevice = libevdev_uinput_create_from_device(m_dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &m_uinput);
    
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
/*
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
/*
/*This is so ugly fix it later
void VirtualDeviceNix::pressWiiKey(int WII_BINDING)
{
    // Must have a profile available 
    
    // Get current profile
    //ProfileNix * current = m_profileManager->getCurrentProfile();

    /*Debug get name 
    std::cout<<"DEBUG: current profile -> "<<current->getProfileName();
    
    
    struct libevdev_uinput * device = getUinputDevice();

    int bindedButton = 0;

    // Get the key curently binded to button
    


    // With all the bindings and settings done execute the press

    // DIRTY DISGUSTING FILTHY MOD KEY TEST
    libevdev_uinput_write_event(device,EV_KEY,KEY_LEFTCTRL,1);
    libevdev_uinput_write_event(device,EV_KEY,bindedButton,1);
    libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

    libevdev_uinput_write_event(device,EV_KEY,KEY_LEFTCTRL,0);
    libevdev_uinput_write_event(device,EV_KEY,bindedButton,0);
    libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

    

                
}

*/