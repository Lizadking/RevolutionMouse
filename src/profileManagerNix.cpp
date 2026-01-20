
#include <list>
#include <iterator>
#include <iostream>
#include "profileNix.h"
#include "profileManagerNix.h"
#include <libevdev/libevdev-uinput.h>

ProfileManagerNix::ProfileManagerNix()
{
   
}

ProfileManagerNix::~ProfileManagerNix()
{
    std::cout<<"Clearing memory from profile manager"<<std::endl; 
    for(auto it = m_profileList.begin(); it != m_profileList.end(); ++it)
    {
        delete *it;
    }
    m_profileList.clear();
}
void ProfileManagerNix::addProfile(ProfileNix * profile)
{
    m_profileList.push_front(profile);
    std::cout<<"added "<<profile->getProfileName()<<std::endl;
}

ProfileNix * ProfileManagerNix::getProfile(unsigned int profileLocation)
{
    if(m_profileList.empty())
    {
        std::cout<<"Profile Manager is empty cannot return"<<std::endl;
        return nullptr;
    }

    else if(profileLocation >= m_profileList.size())
    {
        std::cout<<"Error: manager access is out of bounds "<<std::endl;
        return nullptr;
    }
    else
    {
        auto listFront = m_profileList.begin();
        std::advance(listFront,profileLocation);
        return *listFront;
    }
}

ProfileNix * ProfileManagerNix::getCurrentProfile()
{
    if(m_profileList.empty())
    {
        std::cout<<"Profile Manager is empty cannot return"<<std::endl;
        return nullptr;
    }

    else if(m_currentProfile >= m_profileList.size())
    {
        std::cout<<"Error: manager access is out of bounds "<<std::endl;
        return nullptr;
    }
    else
    {

        auto it = m_profileList.begin();

        std::advance(it,m_currentProfile);

        return *it;
        
    }
}
void ProfileManagerNix::changeProfile()
{
   m_currentProfile++;
   if(m_currentProfile >= m_profileList.size())
   {
        std::cout<<"Wrap around detected"<<std::endl;
        m_currentProfile = 0;
   }
}
 int ProfileManagerNix::getProfileListSize() {return m_profileList.size();}

