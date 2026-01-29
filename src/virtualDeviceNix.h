/*
*
*
*/
#ifndef VIRTUALDEVICENIX_H
#define VIRTUALDEVICENIX_H
#pragma once

#include <iostream>
#include "profileManagerNix.h"
#include <libevdev/libevdev-uinput.h>
#include <memory>

class VirtualDeviceNix 
{
    public:
      
        VirtualDeviceNix();

        ~VirtualDeviceNix();

        int initalize();

        struct libevdev_uinput * getUinputDevice();

        void setProfileManager( std::shared_ptr<ProfileManagerNix> profile);

        std::shared_ptr<ProfileManagerNix> getProfileManager(); 

        std::string virtualGetCurrentProfile();

        void virtualChangeProfile();


        //int getProfileManagerSize();

        void pressWiiKey(int WII_BINDING);
        

    private:
        struct libevdev *m_dev;
        struct libevdev_uinput * m_uinput;
        std::shared_ptr<ProfileManagerNix> m_profileManager;


};

#endif  