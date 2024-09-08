#include "drivers/video.h"
#include "hal/hal.h"
#include "crash_test.h"

extern void main(){
    clear_screen();
    // boot info
    system_print_string("[KERNEL] Boot complete. \n", 1);
    system_print_string("[KERNEL] Starting HAL. \n", 1);
    HAL_Initialize();
    print_string("what! \n");
    //crash_test();
    return;
}