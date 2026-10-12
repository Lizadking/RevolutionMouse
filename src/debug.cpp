#include <iostream>
#include <stdio.h>

#include <filesystem>
#include <fstream>
#include <libevdev/libevdev.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <grp.h>
#include <wiiuse.h>    

#include "imgui.h"
#include"imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "include/wiiusehelper.h"

#include "include/glad.h"
#include <GLFW/glfw3.h>



#define MAX_WIIMOTES				1
#define STANDARD_TIMEOUT            5
/*
*   enumerateDeviceList: Iterates the /dev/inputs/ directory for all devices 
*   Post-Condition: Returns a list of all the devices found
*/
std::vector<libevdev*> emumerateDeviceList();
std::vector<std::string> getKbdDevices();
void imGuiMainRender();
void openglPrerender();
void openglPostrender();
#define eventDeviceCheck  20 // Number of event devices to check, should end up being an option 

int main()
{
  const unsigned int SCREEN_WIDTH = 800;
  const unsigned int SCREEN_HEIGHT = 600;

  /* Callback function to resize the viewport when the windows is resized */
  void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
  void processInput(GLFWwindow *window);

   /*-----------GLFW Init and configure--------*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*-----------GLFW Window Creation---------*/
    GLFWwindow * window = glfwCreateWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Revolution Mouse v0.1", NULL, NULL);
    if(window == NULL)
    {
        std::cout<<" Failed to create glfw window" <<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /*---------GLFW load all openGL function pointers-----------*/
    /* Need to use GLAD to manage function pointers for OpenGL */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
    }    

    /* Set the viewport to */
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    /*-----imgui init---------------*/
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");

    /*-----Wii Remote init---------*/
    wiimote ** wiimotes; 
    static int found = 0;
    static int connected = 0;
    /* Initalize the array of wiimote objects (not connected yet) */
    wiimotes = wiiuse_init(MAX_WIIMOTES);

    
    
    emumerateDeviceList();
     /* Begin the render loop*/
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        /* Rendering Events */
        /*Prepare to clear the color buffer */
        glClearColor(0.20f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*imgui render step / window creation */
        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static int selectedItem = 0;
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        const char* previewValue = items[selectedItem];
       
        /* Profile selection */
        ImGui::Text("Profile(s)");
        ImGui::PushItemWidth(200);
        if(ImGui::BeginCombo(("##XXX"),previewValue))
        {
          for (int i = 0; i < 4;i++)
          {
            const bool is_selected = (selectedItem == i);

            if(ImGui::Selectable(items[i]),is_selected)
            {
              selectedItem = i;
            }

            if(is_selected)
            {
              ImGui::SetItemDefaultFocus();
            }
          }
          ImGui::EndCombo();
          ImGui::PopItemWidth();
        }
        /*Save profile */
        ImGui::SameLine();
        if(ImGui::Button("Save"))
        {

        }
        /*Load profile */
        ImGui::SameLine();
        if(ImGui::Button("Load"))
        {
          
        }

        /*Device Selection */
        ImGui::Text("Device");
        ImGui::PushItemWidth(200);
        if(ImGui::BeginCombo(("##XX"),previewValue))
        {
          for (int i = 0; i < 4;i++)
          {
            const bool is_selected = (selectedItem == i);

            if(ImGui::Selectable(items[i]),is_selected)
            {
              selectedItem = i;
            }

            if(is_selected)
            {
              ImGui::SetItemDefaultFocus();
            }
          }
          ImGui::EndCombo();
          ImGui::PopItemWidth();   
        }

        /*---Wii Buttons---*/
        ImGui::SeparatorText("Buttons");
        /*--Wii Button TEMP Vectors */
        std::vector<int> wiiA = {1,30,0x100};
        /*Wii A*/
        ImGui::Text("A");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("B");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("1");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("2");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("-");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("+");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }

        /*---Wii D-PAD Buttons---*/
        ImGui::SeparatorText("D-Pad");
        /*--Wii Button TEMP Vectors */
        std::vector<int> wiiUp = {1,30,0x100};
        /*Wii Up*/
        ImGui::Text("Up");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("Down");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("Left");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {

        }
        ImGui::Text("Right");
        ImGui::SameLine();
        if(ImGui::Button("TEST BUTTON"))
        {
        }

        /*Connect Wii Remote */
        if(ImGui::Button("Connect Wii Remote "))
        {
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
          wiiuse_set_aspect_ratio(wiimotes[0], WIIUSE_ASPECT_16_9);
          int height = 1300;
          int width = 2500;
          wiiuse_set_ir_vres(wiimotes[0],width * 1.2 ,height * 1.2 );

          wiiuse_set_ir_sensitivity(wiimotes[0],3);

        }
        ImGui::SameLine();
        (connected) ? ImGui::Text("Wii Remote Connected") : ImGui::Text("No Wii Remote Connected");



        

  
        

          
        
   

        

        // Render the Imgui elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /*Call events and buffer swaps*/
        glfwSwapBuffers(window);
        glfwPollEvents();

        
    }

    // PLEASE DELETE ALL THIS MEMORY BRO !!! PWEEEESE 
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();



  /*
  struct libevdev *dev = nullptr;
  std::string pathToDevice = "/dev/input/event3";
  int fd = open(pathToDevice.c_str(), O_RDWR|O_CLOEXEC);
  if(fd == -1)
  {
    std::cout<<"Error couldn't find device"<<std::endl;
  }
    */

  
  return 0;
}

// This is a temporary thing just to manage the entire UI in one function, needs to be broken up and put into a single class eventually
void imGuiMainRender()
{


}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   
    glViewport(0,0,width,height);

}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
          glfwSetWindowShouldClose(window, true);
    }
}
/*
* Current issue, in order to run on linux you need root access to be able to read from /dev/ 
* THIS IS A NIX ONLY FUNCTION 
* This 100% leaks memory with the libevdev fix this later 
*/
std::vector<libevdev*> emumerateDeviceList()
{
  
  /* Get all the kbd devices */
  /* This function is incomplete as it needs to return something when the fd is -1 */
  std::vector<std::string> kbdPaths = getKbdDevices();
  std::vector<libevdev*> devices;
  
  /* Make this an iterator */
  for(int i = 0; i < kbdPaths.size(); i++)
  {
    struct libevdev *tempDev = nullptr;
    //std::cout<<kbdPaths.at(i)<<std::endl;
    int fd = open(kbdPaths.at(i).c_str(), O_RDWR|O_CLOEXEC);
    //std::cout<< fd<<std::endl;

    if(fd == -1)
    {
      // std::cout<<"Error couldn't find device"<<std::endl;
    }

    else
    {
      libevdev_new_from_fd(fd,&tempDev);
      devices.push_back(tempDev);
      
    }
    close(fd);
  }
  return devices;
  
}

std::vector<std::string> getKbdDevices()
{
  // TODO: Change this to by-path and test, testing still needs to be done
  std::filesystem::path directorypath = "/dev/input/by-path";
  std::string targetEvent = "kbd";
  std::vector<std::string> kbdPaths;

   /* Iterate Direcotry */
  for(auto const& dir_entry : std::filesystem::directory_iterator{directorypath})
  {
    std::string stringPath = dir_entry.path().string();
    std::string stringPathSubString =  stringPath.substr(stringPath.size()-3);

     if(stringPathSubString.compare(targetEvent) == 0)
    {
      kbdPaths.push_back(stringPath);
    }
      
  }

  return kbdPaths;
}
  /* Source Implemntation from : https://suricrasia.online/blog/turning-a-keyboard-into/ 
  struct libevdev * device = nullptr;
  for(int i = 0;i <= 4;i++) /*This is an UNSAFE read of the directory path will throw an CRASH
  {
    std::string path = "/dev/input/event" + std::to_string(i);
    int fd = open(path.c_str(),O_RDWR|O_CLOEXEC);
    if (fd == -1)
    {
      break;
    }

    if(libevdev_new_from_fd(fd,&device) == 0)
    {
      /* Get info on the devices 
      std::string physicalDev = libevdev_get_phys(device);
      std::string deviceName =  libevdev_get_name(device);

      std::cout<< path <<std::endl;
      std::cout<< "Physical Device:\t"<<physicalDev<<std::endl;
      std::cout<< "Device Name:\t "<<deviceName<<std::endl;

      libevdev_free(device);
    }
    close(fd);
  }

  */


