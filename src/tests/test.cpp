#include <iostream>
#include "toml.hpp"
#include "logger.h"


/*
*  THIS IS JUST A TEST FOR THE TOML FILE 
*/
int main(int argc, char** argv)
{
    toml::table tbl;
    try
    {
        tbl = toml::parse_file("config.toml");
        std::cout << tbl << "\n";
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << "Parsing failed:\n" << err << "\n";
        return 1;
    }

    Logger logger("logfile.txt"); // Create logger instance
    // Example usage of the logger
    logger.log(INFO, "Program started.");
    logger.log(DEBUG, "Debugging information.");
    logger.log(ERROR, "An error occurred.");

    return 0;
}