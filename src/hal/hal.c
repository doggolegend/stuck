#include "hal.h"
#include "../GDT/gdt.h"
#include "../IDT/idt.h"
#include "../IDT/ISR/isr.h"
#include "../drivers/video.h"
#include "../drivers/irq.h"

void HAL_Initialize()
{
    system_print_string("[HAL] Initializing HAL \n", 1);
    system_print_string("[HAL] Initializing GDT \n", 2);
    i686_GDT_Initialize();
    system_print_string("[HAL] GDT Initialized \n", 2);
    system_print_string("[HAL] Initializing IDT \n", 2);
    i686_IDT_Initialize();
    system_print_string("[HAL] IDT Initialized \n", 2);
    system_print_string("[HAL] Initializing ISR \n", 2);   
    i686_ISR_Initialize();
    system_print_string("[HAL] ISR Initialized \n", 2);
    system_print_string("[HAL] Initializing IRQ \n", 2);
    i686_IRQ_Initialize();
    system_print_string("[HAL] IRQ Initialized \n", 2);
    system_print_string("[HAL] HAL Initialization complete. \n", 1);
};