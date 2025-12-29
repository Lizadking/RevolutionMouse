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
