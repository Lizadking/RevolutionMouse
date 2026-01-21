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

void iterateProfileDirectory(Logger *logger)
{
    std::filesystem::path directorypath = "profiles";

    /* Check if the profile directory is empty*/
    if(std::filesystem::is_empty(directorypath))
    {
        logger->log(INFO,"Profile Directory is empty, creating default profile");
        auto tbl = toml::table
        {
            {"PROFILE",toml::table{
                    {"NAME","default"},
                    {"WII_A",BTN_LEFT},
                    {"WII_B",BTN_RIGHT},
                    {"WII_UP",0},
                    {"WII_DOWN",0},
                    {"WII_LEFT",0},
                    {"WII_RIGHT",0},
                    {"WII_ONE",0},
                    {"WII_TWO",0},
                    {"WII_PLUS",0},
                    {"WII_MINUS",0},
                    {"WII_HOME",0}
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
            std::cout<< dir_entry<<std::endl;

        }
    }
}

void writeProfileToDisk(ProfileNix * profile,Logger * logger)
{
    /* Create TOML table and write */
    auto tbl = toml::table
    {
        {"PROFILE",toml::table{
                {"NAME",profile->getProfileName()},
                {"WII_A",profile->getButtonProfile(WII_A)},
                {"WII_B",profile->getButtonProfile(WII_B)},
                {"WII_UP",profile->getButtonProfile(WII_UP)},
                {"WII_DOWN",profile->getButtonProfile(WII_DOWN)},
                {"WII_LEFT",profile->getButtonProfile(WII_LEFT)},
                {"WII_RIGHT",profile->getButtonProfile(WII_RIGHT)},
                {"WII_ONE",profile->getButtonProfile(WII_ONE)},
                {"WII_TWO",profile->getButtonProfile(WII_TWO)},
                {"WII_PLUS",profile->getButtonProfile(WII_PLUS)},
                {"WII_MINUS",profile->getButtonProfile(WII_MINUS)},
                {"WII_HOME",profile->getButtonProfile(WII_HOME)}
            }}
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
