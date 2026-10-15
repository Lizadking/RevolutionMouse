
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

#include "include/monitor.h"
#include "include/logger.h"


void createAndBindDisplay(monitor * monitorStruct)
{
    Display * tmp = XOpenDisplay(NULL);
    monitorStruct->screenDisplay = tmp;
    
}

void destroyMinitor(monitor * monitorStruct, Logger *log)
{
    log->log(INFO,"Freeing monitor's binded display");
    free(monitorStruct->screenDisplay);
    monitorStruct->screenDisplay = nullptr;
}
int getScreenWidth(Display * bindedDisplay, Logger *log)
{
    
    // Do not do this operation if the display has yet to be binded yet
    if(bindedDisplay == nullptr)
    {
        log->log(INFO,"getScreenWidth: NO BINDED DISPLAY");
        return 0;
    }
    else
    { 
        return XWidthOfScreen(XDefaultScreenOfDisplay(bindedDisplay)); 
    }
    
}

int getScreenHeight(Display * bindedDisplay, Logger *log)
{
    // Do not do this operation if the display has yet to be binded yet
    if(bindedDisplay == nullptr)
    {
        log->log(INFO,"getScreenHeight: NO BINDED DISPLAY");
        return 0;
    }
    else
    { 
        return XHeightOfScreen(XDefaultScreenOfDisplay(bindedDisplay)); 
    }
    
}

int getScreenCount(Display * bindedDisplay, Logger *log)
{
    int count = 0; 
    // Do not do this operation if the display has yet to be binded yet
    if(bindedDisplay == nullptr)
    {
        log->log(INFO,"getScreenCount: NO BINDED DISPLAY");
        return 0;
    }
    else
    { 
        count = ScreenCount(bindedDisplay);
        log->log(INFO,"Number of screens: " + count);
        return count;
    }
}