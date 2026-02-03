#ifndef MONITOR_H
#define MONITOR_H

/*
    Structure: Monitor 
    Used to manage the display bounds 

*/
enum displayServer{X11,WAYLAND,WINAPI};

struct monitor_t;

typedef struct monitor_t
{
    unsigned int width;
    unsigned int height;

}monitor;

#endif