//
//
//

#include <iostream>
#include <string>
#include <map>
#include "profileNix.h"


ProfileNix::ProfileNix()
{
    /* Create and init all map entries */
    m_profileMap = 
    {
        {WII_A,{0,0}},
        {WII_B,{0,0}},
        {WII_ONE,{0,0}},
        {WII_TWO,{0,0}},
        {WII_PLUS,{0,0}},
        {WII_MINUS,{0,0}},
        {WII_UP,{0,0}},
        {WII_DOWN,{0,0}},
        {WII_LEFT,{0,0}},
        {WII_RIGHT,{0,0}},
        {WII_HOME,{0,0}}
    };
    m_profileName = "unamed_profile";

}
/*
*
* notes: 
*/
tuple &ProfileNix::getButtonProfile(int button){return m_profileMap.at(button);}

int ProfileNix::getModifierKey(int button){return m_profileMap.at(button).keys[0];}

void ProfileNix::setModifierKey(int button, int keycode){m_profileMap.at(button).keys[0] = keycode;}

int ProfileNix::getKeycode(int button){return m_profileMap.at(button).keys[1];}

void ProfileNix::setKeycode(int button, int keycode){ m_profileMap.at(button).keys[1] = keycode;}

void ProfileNix::ProfileNix::setButtonProfile(int button,int keycode){}

std::string ProfileNix::getProfileName() {return m_profileName;}

void ProfileNix::setProfileName(std::string name)
{
    if(name.length() <= 0)
    {
        m_profileName = "untitled_profile";
    }
    else
    {
        m_profileName = name;
    }
}

void ProfileNix::printProfile()
{
    
    std::cout<<"Current Profile for: "<<getProfileName()<<std::endl;
    std::cout << "WII_A MOD:"<< getModifierKey(WII_A)<< std::endl;
    std::cout << "WII_A KEY:"<<getKeycode(WII_A)<< std::endl;
    std::cout << "WII_B MOD:"<< getModifierKey(WII_B)<< std::endl;
    std::cout << "WII_B KEY:"<<getKeycode(WII_B)<< std::endl;
    std::cout << "WII_ONE MOD:"<< getModifierKey(WII_ONE)<< std::endl;
    std::cout << "WII_ONE KEY:"<< getKeycode(WII_ONE)<< std::endl;
    std::cout << "WII_TWO MOD:"<< getModifierKey(WII_TWO)<< std::endl;
    std::cout << "WII_TWO KEY:"<< getKeycode(WII_TWO)<< std::endl;
    std::cout << "WII_PLUS MOD:"<< getModifierKey(WII_PLUS)<< std::endl;
    std::cout << "WII_PLUS KEY:"<< getKeycode(WII_PLUS)<< std::endl;
    std::cout << "WII_MINUS MOD:"<< getModifierKey(WII_MINUS)<< std::endl;
    std::cout << "WII_MINUS KEY:"<< getKeycode(WII_MINUS)<< std::endl;
    std::cout << "WII_UP MOD:"<< getModifierKey(WII_UP)<< std::endl;
    std::cout << "WII_UP KEY:"<< getKeycode(WII_UP)<< std::endl;
    std::cout << "WII_DOWN MOD:"<< getModifierKey(WII_DOWN)<< std::endl;
    std::cout << "WII_DOWN KEY:"<< getKeycode(WII_DOWN)<< std::endl;
    std::cout << "WII_LEFT MOD:"<< getModifierKey(WII_LEFT)<< std::endl;
    std::cout << "WII_LEFT KEY:"<< getKeycode(WII_LEFT)<< std::endl;
    std::cout << "WII_RIGHT MOD:"<< getModifierKey(WII_RIGHT)<< std::endl;
    std::cout << "WII_RIGHT KEY:"<< getKeycode(WII_RIGHT)<< std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    
}

