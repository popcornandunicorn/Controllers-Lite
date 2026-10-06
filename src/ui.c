#include "ui.h"
#include "common.h"
#include <stdio.h>


void ui_init(void) {
    // Clear screen and hide cursor
    printf("\033[2J\033[?25l");
    fflush(stdout);
}
void render_ui() {
    printf("\033[H"); // Move cursor to top-left corner
    printf("====================================================\n");
    printf("            CONTROLLERS LITE (macOS)                \n");
    printf("====================================================\n\n");

    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (!g_channels[i].active) continue;

        int us = g_channels[i].normalized_us;
        int bar_width = (us - 1000) / 40; // 0 to 25 characters

        printf("CH%02d [%4d µs] |", i + 1, us);
        for (int b = 0; b < 25; b++) {
            if (b < bar_width) printf("█");
            else printf(" ");
        }
        printf("|\n");
    }

    printf("\n----------------------------------------------------\n");
    printf(" Status: Active | Listening via IOKit HID Framework \n");
    printf(" Press Ctrl+C to exit.                             \n");
    fflush(stdout);
}