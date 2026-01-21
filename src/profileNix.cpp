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
        {WII_A,0},
        {WII_B,0},
        {WII_ONE,0},
        {WII_TWO,0},
        {WII_PLUS,0},
        {WII_MINUS,0},
        {WII_UP,0},
        {WII_DOWN,0},
        {WII_LEFT,0},
        {WII_RIGHT,0},
        {WII_HOME,888}
    };
    m_profileName = "unamed_profile";
}

int ProfileNix::getButtonProfile(int button)
{
    switch(button)
    {
        case WII_A:
            return m_profileMap.at(WII_A);
        break;

        case WII_B:
            return m_profileMap.at(WII_B);
        break;

        case WII_ONE:
            return m_profileMap.at(WII_ONE);
        break;

        case WII_TWO:
            return m_profileMap.at(WII_TWO);
        break;

        case WII_PLUS:
            return m_profileMap.at(WII_PLUS);
        break;

        case WII_MINUS:
            return m_profileMap.at(WII_MINUS);
        break;

        case WII_UP:
            return m_profileMap.at(WII_UP);
        break;

        case WII_DOWN:
            return m_profileMap.at(WII_DOWN);
        break;

        case WII_LEFT:
            return m_profileMap.at(WII_LEFT);
        break;

        case WII_RIGHT:
            return m_profileMap.at(WII_RIGHT);
        break;

        case WII_HOME:
            return m_profileMap.at(WII_HOME);
        break;

        default:
            return -1;
    }

}

void ProfileNix::setButtonProfile(int button,int keycode)
{
    
    switch(button)
    {
        case WII_A:
            m_profileMap.at(WII_A) = keycode;
        break;

        case WII_B:
            m_profileMap.at(WII_B) = keycode;
        break;

        case WII_ONE:
             m_profileMap.at(WII_ONE) = keycode;
        break;

        case WII_TWO:
             m_profileMap.at(WII_TWO)= keycode;
        break;

        case WII_PLUS:
             m_profileMap.at(WII_PLUS)= keycode;
        break;

        case WII_MINUS:
             m_profileMap.at(WII_MINUS)= keycode;
        break;

        case WII_UP:
             m_profileMap.at(WII_UP)= keycode;
        break;

        case WII_DOWN:
             m_profileMap.at(WII_DOWN) = keycode;
        break;

        case WII_LEFT:
             m_profileMap.at(WII_LEFT) = keycode;
        break;

        case WII_RIGHT:
             m_profileMap.at(WII_RIGHT) = keycode;

        break;

        default:
            break;
    }

}

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
    std::cout << "WII_A:"<< m_profileMap.at(WII_A)<< std::endl;
    std::cout << "WII_B:"<< m_profileMap.at(WII_B)<< std::endl;
    std::cout << "WII_ONE:"<< m_profileMap.at(WII_ONE)<< std::endl;
    std::cout << "WII_TWO:"<< m_profileMap.at(WII_TWO)<< std::endl;
    std::cout << "WII_PLUS:"<< m_profileMap.at(WII_PLUS)<< std::endl;
    std::cout << "WII_MINUS:"<< m_profileMap.at(WII_MINUS)<< std::endl;
    std::cout << "WII_UP:"<< m_profileMap.at(WII_UP)<< std::endl;
    std::cout << "WII_DOWN:"<< m_profileMap.at(WII_DOWN)<< std::endl;
    std::cout << "WII_LEFT:"<< m_profileMap.at(WII_LEFT)<< std::endl;
    std::cout << "WII_RIGHT:"<< m_profileMap.at(WII_RIGHT)<< std::endl;
    std::cout<<"-----------------------------"<<std::endl;
}