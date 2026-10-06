#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

#define MAX_CHANNELS 16

typedef struct {
    int raw_value;
    int min_val;
    int max_val;
    int normalized_us; // RC microsecond value: 1000 - 2000 us
    bool active;
} Channel;

// Global channels array declaration
extern Channel g_channels[MAX_CHANNELS];

// Helper: Maps raw input to 1000-2000us PWM range
int normalize_to_us(int raw, int min_val, int max_val);

#endif // COMMON_H