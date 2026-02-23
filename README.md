## About
RevolutionMouse is a userspace virtual device to simulate mouse and keyboard presses using the Nintendo Wii Remote!
## Features 
- Use the Nintendo Wii Remote as a mouse using its IR camera
- Bind keypresses to the Wii Remote face buttons to simulate keyboard input
- Use multiple profiles with various bindings to suit your needs 
- Swap between profiles on the fly using the home button

## Supported Platforms 
- Linux
    - Supported Display Protocols X11 (Wayland support is coming soon!)
## Build Instructions 
### Building the Main Binary
- If building using Ninja from the root project directory 
    - ```cmake -S . -B build -G Ninja && cmake --build build --target revMouse && cd build```
- If building uisng Make
    - ```cmake -S . -B build  && cmake --build build --target  debug && cd build```



## Dependencies 
RevolutionMouse currently operates on Linux with the following dependencies 
- Opengl3
- GLFW
- Wii Use (https://github.com/wiiuse/wiiuse)
- BlueZ Bluetooth Drivers must be installed 
- ImGui (https://github.com/ocornut/imgui)

## Hardware Requirements
- Official Nintendo Wii Remotes 
    - Required for use of the Virtual Keyboard
        - Supported Models: 
            - Gen 1.0 (Bluetooth name: RVL-CNT-01)
            - Gen 1.5 (Bluetooth name: RVL-CNT-01)
            - Gen 2.0 (Bluetooth name: RVL-CNT-01-TR)

- Nintendo Wii Sensor Bar 
    - Required for using the IR Mouse
        - USB sensor bars sold by third parties also work 