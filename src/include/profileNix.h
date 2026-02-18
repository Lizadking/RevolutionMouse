// ProfileNix.h
// Desc: This class will store the keyboard profiles for the UNIX input system

// Notes: 
/*
 * Refer to : https://elixir.bootlin.com/linux/v6.17/source/include/uapi/linux/input-event-codes.h#L65 for Keycode mappings 
 *
 */

#ifndef PROFILENIX_H
#define PROFILENIX_H
#pragma once

#include <iostream>
#include <libevdev/libevdev.h> /* This will contain all the keyboard definitions*/
#include <string>
#include <map>


// Wii remote buttons
#define WII_A           0
#define WII_B           1
#define WII_ONE         2
#define WII_TWO         3
#define WII_PLUS        4
#define WII_MINUS       5
#define WII_HOME        6
#define WII_UP          7
#define WII_DOWN        8
#define WII_LEFT        9
#define WII_RIGHT       10


// Special function codes (numbers are arbitrary)
#define PROFILE_SWAP            888
#define MOTION_MOUSE_ENABLE     777

/* Struct: Tuple
*
*  Tuple[0]: modifier key
*  Tuple[1]: Keycode
*/ 
typedef struct tuple
{
    int keys[2]; 
}tuple;


class ProfileNix
{
    public:
        ProfileNix();
        //~ProfileNix();
        
        tuple &getButtonProfile(int button);
        void setButtonProfile(int button, int keyCode);
        
        int getModifierKey(int button);
        void setModifierKey(int button, int keycode);

        int getKeycode(int button);
        void setKeycode(int button,int keycode);

        std::string getProfileName();
        void setProfileName(std::string name);
        void printProfile();

        
    private:
        std::string m_profileName = "";
        std::map<int,tuple> m_profileMap;


};
#endif