#include <iostream>
#include <unistd.h>
#include "profileManagerNix.h"
#include "virtualDeviceNix.h"
#include <libevdev/libevdev-uinput.h>

VirtualDeviceNix::VirtualDeviceNix(){}
VirtualDeviceNix::~VirtualDeviceNix()
{
   
    //close(libevdev_uinput_get_fd(m_uinput));
    libevdev_free(m_dev);
    libevdev_uinput_destroy(m_uinput);
    std::cout<<"Destroyed m_uinput"<<std::endl;
    

}

int VirtualDeviceNix::initalize()
{
    // Create a device from scratch 
    m_dev = libevdev_new();

    /*
    * ENABLE MOUSE PROPERTIES HERE 
    https://www.kernel.org/doc/html/latest/driver-api/input.html for abs info struct 
    https://github.com/torvalds/linux/blob/master/include/uapi/linux/input.h

     * struct input_absinfo - used by EVIOCGABS/EVIOCSABS ioctls
    * @value: latest reported value for the axis.
    * @minimum: specifies minimum value for the axis.
    * @maximum: specifies maximum value for the axis.
    * @fuzz: specifies fuzz value that is used to filter noise from
    *	the event stream.
    * @flat: values that are within this value will be discarded by
    *	joydev interface and reported as 0 instead.
    * @resolution: specifies resolution for the values reported for
    *	the axis.
    *
    * Note that input core does not clamp reported values to the
    * [minimum, maximum] limits, such task is left to userspace.
    *
    * The default resolution for main axes (ABS_X, ABS_Y, ABS_Z,
    * ABS_MT_POSITION_X, ABS_MT_POSITION_Y) is reported in units
    * per millimeter (units/mm), resolution for rotational axes
    * (ABS_RX, ABS_RY, ABS_RZ) is reported in units per radian.
    * The resolution for the size axes (ABS_MT_TOUCH_MAJOR,
    * ABS_MT_TOUCH_MINOR, ABS_MT_WIDTH_MAJOR, ABS_MT_WIDTH_MINOR)
    * is reported in units per millimeter (units/mm).
    * When INPUT_PROP_ACCELEROMETER is set the resolution changes.
    * The main axes (ABS_X, ABS_Y, ABS_Z) are then reported in
    * units per g (units/g) and in units per degree per second
    * (units/deg/s) for rotational axes (ABS_RX, ABS_RY, ABS_RZ).


    */
    //TEMP play with these values, add sliders too ball 
    struct input_absinfo absinfo{
    .value = 0,
    .minimum = 0,
    .maximum = 12372,
    .fuzz = 0,
    .flat = 0,
    .resolution = 40 //also dpi
    };

    libevdev_enable_property(m_dev,INPUT_PROP_POINTER);
    int absProp = libevdev_enable_event_code(m_dev, EV_ABS, ABS_X,&absinfo);
    int absPropY= libevdev_enable_event_code(m_dev, EV_ABS, ABS_Y,&absinfo);
   
    libevdev_set_name(m_dev, "Virtual Device");
    libevdev_enable_event_type(m_dev, EV_KEY);
    libevdev_enable_event_code(m_dev, EV_KEY, BTN_LEFT, nullptr);
    libevdev_enable_event_code(m_dev, EV_KEY, BTN_RIGHT, nullptr);
    libevdev_enable_event_code(m_dev, EV_KEY, BTN_MIDDLE, nullptr);

    /*
    * Enable every scancode from 1-248 (https://elixir.bootlin.com/linux/v6.17/source/include/uapi/linux/input-event-codes.h#L65)
    * 
    */

    for(unsigned int SCANCODE = 1;SCANCODE<=248;SCANCODE++)
    {
        libevdev_enable_event_code(m_dev, EV_KEY,SCANCODE,nullptr);
    }

    int duplicateDevice = libevdev_uinput_create_from_device(m_dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &m_uinput);
    
    return duplicateDevice;
}


struct libevdev_uinput * VirtualDeviceNix::getUinputDevice()
{
   // This needs to be checked later but we ball 
    return m_uinput;
    
}

void VirtualDeviceNix::setProfileManager(std::shared_ptr<ProfileManagerNix> profile)
{
    // TODO: This needs an assert 
    m_profileManager = profile;
    
}

std::string VirtualDeviceNix::virtualGetCurrentProfile()
{
    return getProfileManager()->getCurrentProfile().getProfileName();
}

void  VirtualDeviceNix::virtualChangeProfile()
{
    getProfileManager()->changeProfile();
}


std::shared_ptr<ProfileManagerNix> VirtualDeviceNix::getProfileManager()
{
    return m_profileManager;
}
/**

int VirtualDeviceNix::getProfileManagerSize()
{
    
    // Must have a profile manager binded to it
    if(m_profileManager == nullptr)
    {
        std::cout<<"ERROR: No binded profile manager to virtual device"<<std::endl;
        return -1;
    }

    else
    {
        int size = m_profileManager->getProfileListSize();
        return size;
    }
        
}

/*This is so ugly fix it later*/
void VirtualDeviceNix::pressWiiKey(int WII_BINDING)
{
    // Must have a profile available 

      
    
    
    struct libevdev_uinput * device = getUinputDevice();

    int keycode = m_profileManager->getCurrentProfile().getKeycode(WII_BINDING);
    int modkey = m_profileManager->getCurrentProfile().getModifierKey(WII_BINDING);

    //debug
    std::cout<<"DEBUG: current profile -> "<<getProfileManager()->getCurrentProfile().getProfileName()<<std::endl;
    std::cout<<"DEBUG: keycode ->"<<keycode<<std::endl;
    std::cout<<"DEBUG: modkey ->"<<modkey<<std::endl;


    // With all the bindings and settings done execute the press

    // DIRTY DISGUSTING FILTHY MOD KEY TEST
    libevdev_uinput_write_event(device,EV_KEY,modkey,1);
    libevdev_uinput_write_event(device,EV_KEY,keycode,1);
    libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

    libevdev_uinput_write_event(device,EV_KEY,modkey,0);
    libevdev_uinput_write_event(device,EV_KEY,keycode,0);
    libevdev_uinput_write_event(device,EV_SYN, SYN_REPORT, 0);

    

                
}

