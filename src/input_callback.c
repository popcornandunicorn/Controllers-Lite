
#include "hid_manager.h"
#include "common.h"
#include "ui.h"

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDManager.h>
#include <stdio.h>

void input_callback(void *context, IOReturn result, void *sender, IOHIDValueRef value) {
    (void)context;
    (void)result;
    (void)sender;
    
    
    IOHIDElementRef element = IOHIDValueGetElement(value);
    uint32_t usagePage = IOHIDElementGetUsagePage(element);
    uint32_t usage = IOHIDElementGetUsage(element);
    CFIndex rawVal = IOHIDValueGetIntegerValue(value);

     int ch = -1;
    // Filter for Joystick Axes 
    if (usagePage == kHIDPage_GenericDesktop) {
        if (usage >= 0x30 && usage <= 0x38) {
            ch = usage - 0x30;
        }
    } 
    // Button Page (Switches / Channels 9+)
    else if (usagePage == kHIDPage_Button) {
        ch = 8 + (usage - 1);
    }

    if (ch >= 0 && ch < MAX_CHANNELS) {
        g_channels[ch].active = true;
        g_channels[ch].raw_value = (int)rawVal;

        if (rawVal < g_channels[ch].min_val) g_channels[ch].min_val = (int)rawVal;
        if (rawVal > g_channels[ch].max_val) g_channels[ch].max_val = (int)rawVal;

        g_channels[ch].normalized_us = normalize_to_us(
            (int)rawVal, 
            g_channels[ch].min_val, 
            g_channels[ch].max_val
        );

        render_uis();
    }
}






bool hid_manager_init(void){
    IOHIDManagerRef hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    if (!hidManager) return false;
    IOHIDManagerSetDeviceMatching(hidManager, NULL);
    IOHIDManagerRegisterInputValueCallback(hidManager, input_callback, NULL);
    IOHIDManagerScheduleWithRunLoop(hidManager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    if (IOHIDManagerOpen(hidManager, kIOHIDOptionsTypeNone) != kIOReturnSuccess) {
        return false;
    }
    return true;
}

void hid_manager_start_loop(void) {
    CFRunLoopRun();
}
