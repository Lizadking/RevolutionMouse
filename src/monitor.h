#ifndef MONITOR_H
#define MONITOR_H

/*
    Structure: Monitor 
    Used to manage the display bounds 

*/
enum displayServer{X11,WAYLAND,WINAPI};
//TODO: As of 1/3/2026  there is no need as of yet to manage multiple sub monitors (As in multi display setups), however 
//      keep in mind there could be a need to handle multiple displays of mixed resolutions and orientations and thus 
//      there could be a need to manage the mouse on a per monitor basis once it crosses bounds 

struct monitor_t;

typedef struct monitor_t
{
    unsigned int width;
    unsigned int height;

}monitor;
void initMonitor(monitor *monitorObj);
void getMonitorResolutionX11(monitor * monitorObj);
void getMonitorResolutionWayland(monitor * monitorObj);
#endif