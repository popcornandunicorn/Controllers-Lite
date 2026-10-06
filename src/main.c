#include "common.h"
#include "hid_manager.h"
#include "ui.h"
#include <stdio.h>

// Define global channel array storage
Channel g_channels[MAX_CHANNELS];

int normalize_to_us(int raw, int min_val, int max_val) {
    if (max_val == min_val) return 1500;
    int us = 1000 + ((raw - min_val) * 1000) / (max_val - min_val);
    if (us < 1000) us = 1000;
    if (us > 2000) us = 2000;
    return us;
}

int main(void) {
    // Initialize channel defaults
    for (int i = 0; i < MAX_CHANNELS; i++) {
        g_channels[i].min_val = -127;
        g_channels[i].max_val = 127;
        g_channels[i].normalized_us = 1500;
        g_channels[i].active = false;
    }

    ui_init();

    if (!hid_manager_init()) {
        printf("Failed to initialize macOS IOKit HID Manager.\n");
        return 1;
    }

    render_ui();
    hid_manager_start_loop();

    return 0;
}