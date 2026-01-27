/*
* profileManager.h
*
*/

#ifndef PROFILEMANAGERNIX_H
#define PROFILEMANAGERNIX_H
#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <iterator>
#include "profileNix.h"



class ProfileManagerNix
{
    public:
        ProfileManagerNix();
        ~ProfileManagerNix();

        void addProfile(std::shared_ptr<ProfileNix>  profile);

        void createProfile(std::string profileName);

        //ProfileNix &getProfile(unsigned int profileLocation);

        ProfileNix &getCurrentProfile();

        ProfileNix &getProfile(int positon);

        void deleteProfile(int profileLocation); 
        
        void changeProfile();
        
        int getProfileListSize();
        
        void printProfiles();

    private:
        
        std::list<std::shared_ptr<ProfileNix>> m_profileList;
        int  m_current =  0;
};

#endif