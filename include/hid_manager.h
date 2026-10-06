#ifndef HID_MANAGER_H
#define HID_MANAGER_H
#include <stdbool.h>

bool hid_manager_init(void);
void hid_manager_start_loop(void);

#endif // HID_MANAGER_H