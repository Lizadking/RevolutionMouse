#ifndef MONITOR_H
#define MONITOR_H
#pragma once 
#include <X11/Xlib.h>
#include <memory>
#include "logger.h"


/*
    Structure: Monitor 
    Used to manage the display bounds 

*/
enum displayServer{X11,WAYLAND,WINAPI};

struct monitor_t;

typedef struct monitor_t
{
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int screenCount = 0;
    Display * screenDisplay = nullptr;


}monitor;

void createAndBindDisplay(monitor * monitorStruct);
void destroyMinitor(monitor * monitorStruct, Logger *log);
/*   
*   Use the X server to get the combined width of the display(s)
*/
int getScreenWidth(Display * bindedDisplay, Logger *log);
/*
*   Use the X server to get the combined height of the display(s)
*/
int getScreenHeight(Display * bindedDisplay, Logger *log);

int getScreenCount(Display * bindedDisplay, Logger *log);
#endif