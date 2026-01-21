/*
* profileManager.h
*
*/

#ifndef PROFILEMANAGERNIX_H
#define PROFILEMANAGERNIX_H
#pragma once

#include <iostream>
#include <memory>
#include "profileNix.h"
#include <list>

class ProfileManagerNix
{
    public:
        ProfileManagerNix();
        ~ProfileManagerNix();

        void addProfile(ProfileNix &profile);

        ProfileNix * getProfile(unsigned int profileLocation);

        ProfileNix & getCurrentProfile();

     
        void deleteProfile(int profileLocation); // TODO 
        
        void changeProfile();
        
        int getProfileListSize();



        
        




    private:
        int m_currentProfile = 0;
        std::list<ProfileNix*> m_profileList;



};

#endif