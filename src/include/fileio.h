#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "toml.hpp"
#include "logger.h"
#include "profileNix.h"
#include "profileManagerNix.h"


/*
* 
*/
#define WII_A_TOML "WII_A"
#define WII_A_MOD_TOML "WII_A_MOD"
#define WII_B_TOML "WII_B"
#define WII_B_MOD_TOML "WII_B_MOD"
#define WII_UP_TOML "WII_UP"
#define WII_UP_MOD_TOML "WII_UP_MOD"
#define WII_DOWN_TOML "WII_DOWN"
#define WII_DOWN_MOD_TOML "WII_DOWN_MOD"
#define WII_LEFT_TOML "WII_LEFT"
#define WII_LEFT_MOD_TOML "WII_LEFT_MOD"
#define WII_RIGHT_TOML "WII_RIGHT"
#define WII_RIGHT_MOD_TOML "WII_RIGHT_MOD"
#define WII_ONE_TOML "WII_ONE"
#define WII_ONE_MOD_TOML "WII_ONE_MOD"
#define WII_TWO_TOML "WII_TWO"
#define WII_TWO_MOD_TOML "WII_TWO_MOD"
#define WII_PLUS_TOML "WII_PLUS"
#define WII_PLUS_MOD_TOML "WII_PLUS_MOD"
#define WII_MINUS_TOML "WII_MINUS"
#define WII_MINUS_MOD_TOML "WII_MINUS_MOD"
#define WII_HOME_TOML "WII_HOME"
#define WII_HOME_MOD_TOML "WII_HOME_MOD"


void initalizeProfileDirectory(Logger * logger)
{
    std::filesystem::path directorypath = "profiles";

    // Check if the directory exists and if not create it
    if(!std::filesystem::exists(directorypath))
    {
        logger->log(INFO,"Profile directory doesn't exist, creating...");
        std::filesystem::create_directory(directorypath);
        logger->log(INFO,"Profile directory created!");
    }
}

std::shared_ptr<ProfileNix> parseAndLoadProfile(toml::table tbl)
{
    std::shared_ptr<ProfileNix> m_profile =  std::make_shared<ProfileNix>();

        m_profile->setProfileName(**tbl["PROFILE"]["NAME"].as_string());
        m_profile->setKeycode(WII_A,**tbl["PROFILE"]["WII_A"].as_integer());
        
        m_profile->setModifierKey(WII_A,**tbl["PROFILE"]["WII_A_MOD"].as_integer());
        m_profile->setKeycode(WII_B,**tbl["PROFILE"]["WII_B"].as_integer());
        m_profile->setModifierKey(WII_B,**tbl["PROFILE"]["WII_B_MOD"].as_integer());
        m_profile->setKeycode(WII_DOWN,**tbl["PROFILE"]["WII_DOWN"].as_integer());
        m_profile->setModifierKey(WII_DOWN,**tbl["PROFILE"]["WII_DOWN_MOD"].as_integer());
        m_profile->setKeycode(WII_HOME,**tbl["PROFILE"]["WII_HOME"].as_integer());
        m_profile->setModifierKey(WII_HOME,**tbl["PROFILE"]["WII_HOME_MOD"].as_integer());
        m_profile->setKeycode(WII_LEFT,**tbl["PROFILE"]["WII_LEFT"].as_integer());
        m_profile->setModifierKey(WII_LEFT,**tbl["PROFILE"]["WII_LEFT_MOD"].as_integer());
        m_profile->setKeycode(WII_RIGHT,**tbl["PROFILE"]["WII_RIGHT"].as_integer());
        m_profile->setModifierKey(WII_RIGHT,**tbl["PROFILE"]["WII_RIGHT_MOD"].as_integer());
        m_profile->setKeycode(WII_TWO,**tbl["PROFILE"]["WII_TWO"].as_integer());
        m_profile->setModifierKey(WII_TWO,**tbl["PROFILE"]["WII_TWO_MOD"].as_integer());
        m_profile->setKeycode(WII_UP,**tbl["PROFILE"]["WII_UP"].as_integer());
        m_profile->setModifierKey(WII_UP,**tbl["PROFILE"]["WII_UP_MOD"].as_integer());

        // m_profile->printProfile();

    return m_profile;
}

void iterateProfileDirectory(Logger *logger,ProfileManagerNix &m_profile)
{
    std::filesystem::path directorypath = "profiles";
    toml::table tbl;

    /* Check if the profile directory is empty*/
    if(std::filesystem::is_empty(directorypath))
    {
        logger->log(INFO,"Profile Directory is empty, creating default profile");
        tbl = toml::table
        {
            {"PROFILE",toml::table{
                    {"NAME","default"},
                    {WII_A_TOML,0},
                    {WII_A_MOD_TOML,0},
                    {WII_B_TOML,0},
                    {WII_B_MOD_TOML,0},
                    {WII_UP_TOML,0},
                    {WII_UP_MOD_TOML,0},
                    {WII_DOWN_TOML,0},
                    {WII_DOWN_MOD_TOML,0},
                    {WII_LEFT_TOML,0},
                    {WII_LEFT_MOD_TOML,0},
                    {WII_RIGHT_TOML,0},
                    {WII_RIGHT_MOD_TOML,0},
                    {WII_ONE_TOML,0},
                    {WII_ONE_MOD_TOML,0},
                    {WII_TWO_TOML,0},
                    {WII_TWO_MOD_TOML,0},
                    {WII_PLUS_TOML,0},
                    {WII_PLUS_MOD_TOML,0},
                    {WII_MINUS_TOML,0},
                    {WII_MINUS_MOD_TOML,0},
                    {WII_HOME_TOML,0},
                    {WII_HOME_MOD_TOML,0}
                }}
        };

        /* This is a very dirty way to go about it try to patch it up later */
        std::string filename = "default";
        std::string fileExtension = ".toml";
        std::string completeFile = filename + fileExtension;
        std::string completePath = "profiles/"+ completeFile;

        std::ofstream fout(completePath);
        fout<<tbl<<std::endl;

        std::string logMsg = "Profile " + completeFile + " has been created at " + completePath + "!";

        logger->log(INFO,logMsg);


    }

    /* Not empty get every profile there and process it */
    else
    {
        logger->log(INFO,"Reading profile directory...");
        
        for(auto const& dir_entry : std::filesystem::directory_iterator{directorypath})
        {
          
            tbl = toml::parse_file(dir_entry.path().string());
            //std::cout<<tbl<<std::endl;
            /*
            * Could this be done with an interator->yes
            * Am I going to use an interator -> no
            */
            m_profile.addProfile(parseAndLoadProfile(tbl));

        }
        
    }
}


void writeProfileToDisk(ProfileNix * profile,Logger * logger)
{
    std::cout<<profile->getProfileName()<<std::endl;
    /* Create TOML table and write */
     auto tbl = toml::table
    {
        {"PROFILE",toml::table{
                {"NAME",profile->getProfileName()},
                {WII_A_TOML,profile->getKeycode(WII_A)},
                {WII_A_MOD_TOML,profile->getModifierKey(WII_A)},
                {WII_B_TOML,profile->getKeycode(WII_B)},
                {WII_B_MOD_TOML,profile->getModifierKey(WII_B)},
                {WII_UP_TOML,profile->getKeycode(WII_UP)},
                {WII_UP_MOD_TOML,profile->getModifierKey(WII_UP)},
                {WII_DOWN_TOML,profile->getKeycode(WII_DOWN)},
                {WII_DOWN_MOD_TOML,profile->getModifierKey(WII_DOWN)},
                {WII_LEFT_TOML,profile->getKeycode(WII_LEFT)},
                {WII_LEFT_MOD_TOML,profile->getModifierKey(WII_LEFT)},
                {WII_RIGHT_TOML,profile->getKeycode(WII_RIGHT)},
                {WII_RIGHT_MOD_TOML,profile->getModifierKey(WII_RIGHT)},
                {WII_ONE_TOML,profile->getKeycode(WII_ONE)},
                {WII_ONE_MOD_TOML,profile->getModifierKey(WII_ONE)},
                {WII_TWO_TOML,profile->getKeycode(WII_TWO)},
                {WII_TWO_MOD_TOML,profile->getModifierKey(WII_TWO)},
                {WII_PLUS_TOML,profile->getKeycode(WII_PLUS)},
                {WII_PLUS_MOD_TOML,profile->getModifierKey(WII_PLUS)},
                {WII_MINUS_TOML,profile->getKeycode(WII_MINUS)},
                {WII_MINUS_MOD_TOML,profile->getModifierKey(WII_MINUS)},
                {WII_HOME_TOML,profile->getKeycode(WII_HOME)},
                {WII_HOME_MOD_TOML,profile->getModifierKey(WII_HOME)}
            }
        }
    };

    /* This is a very dirty way to go about it try to patch it up later */
    std::string filename = profile->getProfileName();
    std::string fileExtension = ".toml";
    std::string completeFile = filename + fileExtension;
    std::string completePath = "profiles/"+ completeFile;

    std::ofstream fout(completePath);
    fout<<tbl<<std::endl;

    std::string logMsg = "Profile " + completeFile + " has been created at " + completePath + "!";

    logger->log(INFO,logMsg);
}

void emumerateDevicesNix()
{
    /* Enumerate the /dev/input/by-id/ path */
    
}