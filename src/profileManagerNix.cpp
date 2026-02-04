
#include <list>
#include <iterator>
#include <memory>
#include <iostream>
#include <iterator>
#include <libevdev/libevdev-uinput.h>

#include "profileNix.h"
#include "profileManagerNix.h"
#include "toml.hpp"



ProfileManagerNix::ProfileManagerNix(){}

ProfileManagerNix::~ProfileManagerNix()
{
    std::cout<<"Clearing memory from profile manager"<<std::endl; 
    m_profileList.clear();
}
void ProfileManagerNix::addProfile(std::shared_ptr<ProfileNix>  profile)
{
    m_profileList.push_front(profile);
    std::cout<<"Added Profile: "<<profile->getProfileName()<<std::endl;
}

void ProfileManagerNix::createProfile(std::string profileName = "unamed_profile")
{
    std::shared_ptr<ProfileNix> m_profile =  std::make_shared<ProfileNix>();
    m_profile->setProfileName(profileName);
    addProfile(m_profile);

}

ProfileNix &ProfileManagerNix::getCurrentProfile()
{
    auto it =  m_profileList.begin();
    std::advance(it,m_current);
    return **it;
}

ProfileNix &ProfileManagerNix::getProfile(int positon)
{
    auto it =  m_profileList.begin();
    std::advance(it,positon);

    return **it;
}

void ProfileManagerNix::deleteProfile(int profileLocation)
{
    auto it =  m_profileList.begin();
    
    /* The list is empty */
    if(it == m_profileList.end())
    {
        std::cerr<<"[WARNING] ProfileManagerNix::deleteProfile() : m_profileList is empty"<<std::endl;
    }

    /* OOB */
    else if(profileLocation < 0 || profileLocation > m_profileList.size() )
    {
        std::cerr<<"[WARNING] ProfileManagerNix::deleteProfile() : OOB "<<std::endl;
    }
    else
    {
    

    std::advance(it,profileLocation-1);
    m_profileList.erase(it);
    }
          
}

void ProfileManagerNix::changeProfile()
{
    if(m_current == m_profileList.size()-1)
    {
        std::cout<<"Wrap around detected"<<std::endl;
        m_current = 0;
       
        std::cout<<"currently at: "<<getProfile(m_current).getProfileName()<<std::endl;
    }
    else
    {
        m_current++;
        std::cout<<"currently at: "<<getProfile(m_current).getProfileName()<<std::endl;
    }
}

int ProfileManagerNix::getProfileListSize() {return m_profileList.size();}

void ProfileManagerNix::printProfiles()
{
    auto it =  m_profileList.begin();
    for(;it != m_profileList.end();++it)
    {
        std::shared_ptr<ProfileNix> curr = *it;
        std::cout<<curr->getProfileName()<<std::endl;
    }
}