GIT IGNORE THIS FILE

12/12/2025

Starting this project and I just need to make a few notes on my technology choices and some technical documentation.
Wii Remote Bluetooth Proocall: Bluetooth 2.0-> This is not Bluetooth LE! I need to find a way to see if 

a) There is a C bluetooth spec that can support BT 2.0 
b) Is also supported by the linux kernel

> It looks like BlueZ will be the stack used. Just need to verify that it supports 2.0 
> After some installing of a few libraries (https://wiki.archlinux.org/title/Bluetooth) bluez-utils I am able to do a bluetooth connection with my wii remote. 
  At least I know that the BlueZ stack does work with my controller. I think the goal for today is actually just writing something in C that can make the controller discoverable and I can worry about
  reading inputs from there. 

> I think what I would like to have a small working demo of before I try to work on the mouse functionality is to integrate this with imgui to just draw a dot on the screen in a box and move it around. 
  from there I can see how I am reading the values and all that stuff (very scientific), I did already do some basic research into controlling the mouse and the goal is essentially a userspace implementation
  of a mouse. 

>> I should think about looking into userspace river. But for now a simple program that when activated I can connect to a wii remote and make it act like a mosue works, but the overall end goal is 
   userspace implementation. Mayeb my goals / current knowledge isn't enough and maybe I am confusing what my goals are and even if they NEED to be a userspace driver to begin with.

12/14/2025

I learned that I will need to speak to the wii remote using the HCI Bluetooth protocal 

> This is a primary source to use (https://github.com/xwiimote/xwiimote/blob/master/doc/PROTOCOL) this documents the entire Wiimote protocol 
>> Okay this is somethign cool that I found while researching HCI w/BlueZ. It's really cool to see I wasn't the only one trying to do wii pc stuff as I found this cool old project called 
   wii yourself (https://wiiyourself.gl.tter.org/)
>> Not only that but also Japanese people also doing the same thing (https://akihiko.shirai.as/projects/WiiRemote/) he even has a few chapters online at (https://akihiko.shirai.as/projects/WiiRemote/chapter3.html)
   the book is also on Amazon and Buyee for about 1000 yen so I would like to buy it and do a little afterwards talking about this stuff. The website is giga cooked but I need to find a way to archive it 
   and have it local so I can discuss it on my write up after. 
>> WOOAH okay so the author of the book actually does a lot of AI stuff rn and has a few books out. Maybe I can try and just talk to the guy after I finish this project and read some of his books?

12/15/2025

After some research into the protocol I need to use to communicate with the wiiMote. It uses the host controller interface (HCI). This is essentially
a socket, but I don't know too much about sockets and I watched a pretty good video explaining the foundational ideas (https://www.youtube.com/watch?v=D26sUZ6DHNQ) 

Essentially a bluetooth connection (for HCI) is just a connetion made using a socket. If I can learn sockets I can commmunicate with the wiiMote and 
go from there. This is also useful to know since it's how you can do IPC and read memeory from other processes.

understand sockets with C, understand bluetooth. It's just going from the network to radio. 


1/3/26
A lot of work has been done to get a very basic version of this done with the wiiUse library. The main approach is actually creating a virtual device 
on linux and then using that device as a mouse. However I have made the fool harty decission of deciding to take this from a simple tool I use only to me 
to a full release. 

The aim of this is to have a working but basic 0.1 Release (No ETA). 

Wii Mouse 0.1 (beta) release features:

1) There must be binaries built and tested for Windows and Linux 
2) There is no test suite for this build (0.1X release)
3) There must be basic support for mouse features including pointing, left/right click, and scoll
4) There must be basic keyboard support as in mapping keypresses to functions on the wiimote
5) There must be a gui implemented via the Imgui library to allow users to do the following:
   - Pairing must be done via the GUI 
   - Viewing currently connected remotes 
   - Setting actions from the mouse/keyboard to the buttons of the wiimote
   - Safely disconnecting the wiimotes from the system
   - Checking bluetooth connectivity status
6) The setup of the wii pointer bounds relative to display should be dynamic. (The virtual resolution of the pointer should map to the display without user input)
   - This virtual resolution can be modified via settings 
7) Support for profiles per wiimote (As in I should be able to set my wiimote to have bindings for Higurashi or something else)
8) DEV ONLY: Have a proper start up and initalization for the program
7) Source code will be hosted on Github AS A MIRROR for visability, the most recent branch will be hosted on forjo or codeberg. (While it will be FOSS, I will not personally be accepting pull requests )
8) Smoothed out wii cursor movements (control the jitter)

Design Notes:

Windows Support should be last. Prioritize linux as the platform 
Linux has two display servers X11 and Wayland. Support should be for both platforms 
This project should be built using Cmake as well as have conditional includes for headers not supported by it's platform
   - As in Wayland should only have wayland headers built and X11 as well
This project should also take inspiration for handling OS dependent functions and libraries


0.1XX version wishlist features:
- CLI interface for UNIX Platforms 
- Custom pointer icon (or even implment the rotation)

0.2 wishlist:
- Dynamic per monitor / session bounds (Have the sensitivity and other settings be on a per monitor basis and adjust to distance from monitor)
- Multiple resolution / orientation setup (Support mixed resolution and setups with multiple monitors)
- bounds for pointer (can select an area for the pointer to be active in)





I think my implementation if fundamentally wrong. I think I need to create a virtual HID device instead of my current generic virtual device approach 
I did notice that essentilaly we're using a HCI connection to emulate a HID device 

1/4/25

Not much work to be done today I just need to really pick a feature and get it out. I think the first feature that needs to be done is the dynamic virtual resolution settings. In fact since it's so core to the project I think I should get it done first and build around it. I have a decent
prototype that is the current version. But now I should start towards building a real project and I am going to do the dynamic virtual 
resolution for Wayland and X11 

configuration setting 

wait what the hell

1) rotating the wiimote fucks up the pointer so i need to correct for that
2) I think switching to HID would help with the lag that sometimes happens when the pointer is in use 


1/6/25

https://www.usb.org/sites/default/files/hid1_11.pdf
Needed HID spec for the Linux USB device gadget 


1/19/26

Holy memory leak. In the profile driver at 
=69081== 118 (48 direct, 70 indirect) bytes in 1 blocks are definitely lost in loss record 4 of 4
==69081==    at 0x485EC13: calloc (vg_replace_malloc.c:1675)
==69081==    by 0x48A58E6: UnknownInlinedFun (libevdev-uinput.c:37)
==69081==    by 0x48A58E6: libevdev_uinput_create_from_device (libevdev-uinput.c:377)
==69081==    by 0x4007AEE: VirtualDeviceNix::initalize() (in /run/media/lizadking/Programming/wiiMouse/src/profileDriver)
==69081==    by 0x4007E78: main (in /run/media/lizadking/Programming/wiiMouse/src/profileDriver)

it's 118 bytes but goddamn
   
1/22/26 
So much shit is happening but I finally got the mod keys working. check the spec sheet I made for notes but it seems like this may be feature complete minus the gui
all that is left for the profiles is to whip it all up in some smart pointers and it's done

1/26/26
This mouse just isn't responsive enough for my tastes. I think I may have to do multithreading and have the virtual device in it's own thread because the
Dependencies 
-------------
wiiuse
libevdev (linux)
toml (included doesn't need to be installed)
SDl2 
bluez (linux)
   

SOURCES (For write up)
----------------------
https://www.usb.org/hid - HID spec 
https://wiki.archlinux.org/title/Bluetooth 
https://github.com/xwiimote/xwiimote/blob/master/doc/PROTOCOL
https://www.youtube.com/watch?v=D26sUZ6DHNQ
https://wiiyourself.gl.tter.org/
https://akihiko.shirai.as/projects/WiiRemote/
https://www.usb.org/sites/default/files/hid1_11.pdf
https://elixir.bootlin.com/linux/v6.17/source/include/uapi/linux/input-event-co
https://john-salamon.com/The_Linux_Input_Complex/#fn7
