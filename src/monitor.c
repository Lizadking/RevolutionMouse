
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <wayland-client.h>
#include <X11/extensions/Xrandr.h>

#include "monitor.h"


/*WAYLAND FUNCTION HEADERS */
static void output_mode(void *data, struct wl_output *output,uint32_t flags, int32_t width, int32_t height,int32_t refresh);
static void output_done(void *data, struct wl_output *output);
static void registry_global(void *data, struct wl_registry *registry,uint32_t name, const char *interface, uint32_t version);
static void registry_remove(void *data, struct wl_registry *registry, uint32_t name);

// wl_registry interface implementation
static const struct wl_registry_listener registry_listener = 
{
    .global = registry_global,
    .global_remove = registry_remove,
};


/*******/

void initMonitor(monitor *monitorObj)
{
    // UNIX: Get the display protocol

    const char *xdg_session_type = getenv("XDG_SESSION_TYPE");
    const char *wayland_display = getenv("WAYLAND_DISPLAY");

    if(strcmp(xdg_session_type,"wayland") == 0)
    {
        printf("Wayland session\n");
    }

    if(strcmp(xdg_session_type,"x11") == 0)
    {
        printf("X11 Session\n");
        getMonitorResolutionWayland(monitorObj);
    }

    
}

void getMonitorResolutionX11(monitor * monitorObj)
{

}


void getMonitorResolutionWayland(monitor * monitorObj)
{
    struct wl_display *display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "Failed to connect to Wayland display\n");
    }
 
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
 
    // Roundtrip: Process initial registry events
    wl_display_roundtrip(display);
 
    // Disconnect and clean up
    wl_display_disconnect(display);
}

/*  WAYLAND SPECIFIC FUNCTIONS */

// Callback for wl_output::mode events (resolutions)
static void output_mode(void *data, struct wl_output *output,uint32_t flags, int32_t width, int32_t height,int32_t refresh) 
{
    const char *mode_type = "";
    if (flags & WL_OUTPUT_MODE_CURRENT) mode_type = " (current)";
    if (flags & WL_OUTPUT_MODE_PREFERRED) mode_type = " (preferred)";
 
    printf("Mode: %dx%d @ %.2f Hz%s\n",
           width, height, refresh / 1000.0, mode_type);
}
 
// Callback for wl_output::geometry events (physical display info)
static void output_geometry(void *data, struct wl_output *output,
                           int32_t x, int32_t y, int32_t physical_width,
                           int32_t physical_height, int32_t subpixel,
                           const char *make, const char *model,
                           int32_t transform) {
    printf("Output: %s %s (physical size: %dx%d mm)\n", make, model,
           physical_width, physical_height);
}
 
// Callback for wl_output::done events (end of output info)
static void output_done(void *data, struct wl_output *output) {}
 
// Callback for wl_output::scale events (HiDPI scaling)
static void output_scale(void *data, struct wl_output *output, int32_t scale) {}
 
// wl_output interface implementation
static const struct wl_output_listener output_listener = 
{
    .geometry = output_geometry,
    .mode = output_mode,
    .done = output_done,
    .scale = output_scale,
};
 
// Callback for wl_registry::global events (compositor capabilities)
static void registry_global(void *data, struct wl_registry *registry,uint32_t name, const char *interface, uint32_t version) 
{
    if (strcmp(interface, "wl_output") == 0) {
        struct wl_output *output = wl_registry_bind(registry, name,
                                                   &wl_output_interface, 1);
        wl_output_add_listener(output, &output_listener, NULL);
    }
}
 
// Callback for wl_registry::global_remove events (ignored for this example)
static void registry_remove(void *data, struct wl_registry *registry, uint32_t name) {}
 
