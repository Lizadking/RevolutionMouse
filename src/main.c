#include <stdio.h>                      
#include <wiiuse.h>                     
#include <unistd.h>   
#include <fcntl.h>
#include <stdlib.h>
#include <linux/uinput.h>
#include <math.h>

// THERE SHOULD be conditional compiles for these headers as they are X11 or Wayland exclusive !! 
// SHOULD ALSO HAVE CONDITIONALS IN THE MAKEFILE (ugh Cmake)

#include "monitor.h"

#define MAX_WIIMOTES				4
#define STANDARD_TIMEOUT 5
#define THRESEHOLD_VALUE 100
#define JUMP_PREVENTION 30



void debug_printVirtualIRdata(wiimote ** wiimotes);
void handle_event(struct wiimote_t* wm, int fd);
void handle_read(struct wiimote_t* wm, byte* data, unsigned short len);
void handle_ctrl_status(struct wiimote_t* wm);
void handle_disconnect(wiimote* wm);
void test(struct wiimote_t* wm, byte* data, unsigned short len);
short any_wiimote_connected(wiimote** wm, int wiimotes);

void emit(int fd, int type, int code, int val);
static void setup_abs(int fd, int type, int min, int max, int res);


int main(int argc, char ** agrv)
{
    wiimote ** wiimotes;
	monitor monitorSession;

	/*FOR NOW MANUALLY SET MONITOR RESOLUTIOn*/
	monitorSession.height = 1080;
	monitorSession.width = 2160;
    
    int found = 0;
    int connected = 0;

    /* Initalize the array of wiimote objects (not connected yet) */
    wiimotes = wiiuse_init(MAX_WIIMOTES);
             
    /* Find Wiimote devices */
    found = wiiuse_find(wiimotes,MAX_WIIMOTES,STANDARD_TIMEOUT);
    
    
    if(!found)
    {
        printf("No Wiimotes found\n");
        return -1;
    }

    /* Connect to wiimotes */
    connected = wiiuse_connect(wiimotes,MAX_WIIMOTES);

    if(!connected)
    {
        printf("Failed to connect to wiimote\n");
        return -1;
    }

    wiiuse_set_leds(wiimotes[0],WIIMOTE_LED_1);
	wiiuse_rumble(wiimotes[0], 1);

	/* Manual config */
    wiiuse_set_aspect_ratio(wiimotes[0], WIIUSE_ASPECT_16_9);
    wiiuse_set_ir_vres(wiimotes[0],monitorSession.width * 2,monitorSession.height * 2 );


    //debug_printVirtualIRdata(wiimotes);

   
   

    /* Virtual device creation */
    printf("Creating virtual device...");
    struct uinput_setup usetup; 
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    printf("Virtual Device File Descriptor: %i",fd);
    /*MESSY PLEASE FIX */
     /*
    * The ioctls below will enable the device that is about to be
    * created, to pass key events, in this case the space key.
    */
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(fd, UI_SET_KEYBIT, KEY_F1);

	

	/* Dirty validation for mouse check function setup abs */
	if(-1 == ioctl(fd, UI_SET_EVBIT, EV_ABS)) // mouse absolute input
	{
		printf("Error\n");
	}

    setup_abs(fd, ABS_X, 0, monitorSession.width, 1600); // mouse absolute input last value is dpi


	setup_abs(fd, ABS_Y, 0, monitorSession.height, 1600); // mouse absolute input

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Example device");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    sleep(1);

    int test = 0;

    /* Main Input loop */
  	while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) 
    {
       
        if(wiiuse_poll(wiimotes,MAX_WIIMOTES))
        {
            int currWiimote = 0;
            for(;currWiimote < MAX_WIIMOTES;currWiimote++)
            {
                switch (wiimotes[currWiimote]->event) 
                {
					case WIIUSE_EVENT:
						/* a generic event occurred */
						handle_event(wiimotes[currWiimote],fd);
						break;

                    case WIIUSE_STATUS:
						/* a status event occurred */
						handle_ctrl_status(wiimotes[currWiimote]);
						break;

                    case WIIUSE_DISCONNECT:
					case WIIUSE_UNEXPECTED_DISCONNECT:
						/* the wiimote disconnected */
						handle_disconnect(wiimotes[currWiimote]);
						break;

                    default:
						break;
                }

            }
        }
        
        
    }
    
    
    wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
    printf("cleaning up virtual device\n");
    sleep(1);

   ioctl(fd, UI_DEV_DESTROY);
   
   close(fd);

   return 0;
}

void debug_printVirtualIRdata(wiimote ** wiimotes)
{
    printf("Virtual resolution X: %i\n",wiimotes[0]->ir.vres[0]);
    printf("Virtual resolution Y: %i\n",wiimotes[0]->ir.vres[1]);
    printf("Virtual resolution Aspect Ratio: %i\n",wiimotes[0]->ir.aspect);
}


void handle_event(struct wiimote_t* wm, int fd) 
{
   
	printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

	/* if a button is pressed, report it */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_A)) {
		printf("A pressed\n");
        /*demo */
		
        emit(fd, EV_KEY, BTN_LEFT, 1);
        emit(fd, EV_SYN, SYN_REPORT, 0);
        emit(fd, EV_KEY, BTN_LEFT, 0);
        emit(fd, EV_SYN, SYN_REPORT, 0);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		printf("B pressed\n");
        emit(fd, EV_KEY,KEY_F1, 1);
        emit(fd, EV_SYN, SYN_REPORT, 0);
        emit(fd, EV_KEY, KEY_F1, 0);
        emit(fd, EV_SYN, SYN_REPORT, 0);
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		printf("UP pressed\n");
	}
		
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN)){
		printf("DOWN pressed\n");
	}
		
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	{
		printf("LEFT pressed\n");
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	{
		printf("RIGHT pressed\n");
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	{
		printf("MINUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	{
		printf("PLUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		printf("ONE pressed\n");
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		printf("TWO pressed\n");
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	{
		printf("HOME pressed\n");
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) 
	{
		wiiuse_set_ir(wm, 0);
	}


	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) 
	{
		wiiuse_set_ir(wm, 1);

		
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B)) 
	{
		//wiiuse_toggle_rumble(wm);
	}
        

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		//wiiuse_set_ir(wm, 1);
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
		//wiiuse_set_ir(wm, 0);
	}

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		wiiuse_set_motion_plus(wm, 0); // off
	}
	/*
	 *	If IR tracking is enabled then print the coordinates
	 *	on the virtual screen that the wiimote is pointing to.
	 *
	 *	Also make sure that we see at least 1 dot.
	 */
	if (WIIUSE_USING_IR(wm)) 
	{
		int i = 0;

		/* go through each of the 4 possible IR sources */
		for (; i < 4; ++i) {
			/* check if the source is visible */
			if (wm->ir.dot[i].visible) {
				printf("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
			}
		}
        
		printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
		printf("IR z distance: %f\n", wm->ir.z);
        printf("IR Virtual Res: (%u,%u)\n",wm->ir.vres[0],wm->ir.vres[1]);

		/*THIS IS OS BAD BUT IT WORKS*/
		printf("TEST FOR MOUSE INPUT\n");
		printf("-IR cursor: (%u, %u)-\n", wm->ir.x, wm->ir.y);

		/*only update the x and y cursor only if the current one is greater or less than the threshold value*/
		/* Sometimes the wii remote will also have a miss-read in values which causes a jump in value, check to also prevent */
			float newX = (1 + (wm->ir.x * 0.5));
			float newY = (1 + (wm->ir.y *0.5));
			emit(fd, EV_ABS, ABS_X,newX);
			emit(fd, EV_ABS, ABS_Y,newY);
			emit(fd, EV_SYN, SYN_REPORT, 0);
			/*this polling rate needs to be fixed 10000 = 100hz is the lower limmit
			*/
		
			
			
		
    
        
	}

}

void handle_read(struct wiimote_t* wm, byte* data, unsigned short len) 
{
	int i = 0;

	printf("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
	printf("finished read of size %i\n", len);
	for (; i < len; ++i) {
		if (!(i % 16)) {
			printf("\n");
		}
		printf("%x ", data[i]);
	}
	printf("\n\n");
}

void handle_ctrl_status(struct wiimote_t* wm) 
{
	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

	printf("attachment:      %i\n", wm->exp.type);
	printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
	printf("ir:              %i\n", WIIUSE_USING_IR(wm));
	printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	printf("battery:         %f %%\n", wm->battery_level);
}

void handle_disconnect(wiimote* wm) 
{
	printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}

void test(struct wiimote_t* wm, byte* data, unsigned short len) 
{
	printf("test: %i [%x %x %x %x]\n", len, data[0], data[1], data[2], data[3]);
}


short any_wiimote_connected(wiimote** wm, int wiimotes) 
{
	int i;
	if (!wm) {
		return 0;
	}

	for (i = 0; i < wiimotes; i++) {
		if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
			return 1;
		}
	}

	return 0;
}


void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   /* timestamp values below are ignored */
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}


static void setup_abs(int fd, int type, int min, int max, int res)
{
    struct uinput_abs_setup abs = 
	{
        .code = type,
        .absinfo = {
            .minimum = min,
            .maximum = max,
            .resolution = res
        }
    };

    if (-1 == ioctl(fd, UI_ABS_SETUP, &abs))
        printf("error\n");
}

/*this should eventually be moved to it's own file as well as take it's on config struct
int createVirtualDevice()
{
	 /*MESSY PLEASE FIX */
     /*
    * The ioctls below will enable the device that is about to be
    * created, to pass key events, in this case the space key.
    
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(fd, UI_SET_KEYBIT, KEY_F1);

	

	 Dirty validation for mouse check function setup abs 
	if(-1 == ioctl(fd, UI_SET_EVBIT, EV_ABS)) // mouse absolute input
	{
		printf("Error\n");
	}

    setup_abs(fd, ABS_X, 0, monitorSession.width, 96); // mouse absolute input


	setup_abs(fd, ABS_Y, 0, monitorSession.height, 96); // mouse absolute input

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234;  sample vendor 
    usetup.id.product = 0x5678; sample product *
    strcpy(usetup.name, "Example device");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    sleep(1);
}      
*/                                                                                                                                                                                                                   