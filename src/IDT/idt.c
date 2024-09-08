// #include "idt.h"
// #include "stdint.h"
// #include "binary.h"

// //extern void i686_IDT_Lod();

// typedef struct
// {
//     uint16_t BaseLow;
//     uint16_t SegmentSelector;
//     uint8_t Reserved;
//     uint8_t Flags;
//     uint16_t BaseHigh;
// } __attribute__((packed)) IDTEntry;

// typedef struct {
//     uint16_t Limit;
//     IDTEntry* Ptr;
// } __attribute__((packed)) IDTDescriptor;

// // typedef enum {
// //     IDT_FLAG_GATE_TASK              = 0x5,
// //     IDT_FLAG_GATE_16BIT_INT         = 0x6,
// //     IDT_FLAG_GATE_16BIT_TRAP        = 0x7,
// //     IDT_FLAG_GATE_32BIT_INT         = 0xE,
// //     IDT_FLAG_GATE_32BIT_TRAP        = 0xF,

// //     IDT_FLAG_RING0                  = (0 << 5),
// //     IDT_FLAG_RING1                  = (1 << 5),
// //     IDT_FLAG_RING2                  = (2 << 5),
// //     IDT_FLAG_RING3                  = (3 << 5),

// //     IDT_FLAG_PRESENT                = 0x80,
// // } IDT_FLAGS;

// IDTEntry g_IDT[256];

// IDTDescriptor g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

// void __attribute__((cdecl)) i686_IDT_LOAD(IDTDescriptor* idtDescriptor);

// void i686_IDT_SetGate(int interrupt, void* base, uint16_t segmentDescriptor, uint8_t flags)
// {
//     g_IDT[interrupt].BaseLow = ((uint32_t)base) & 0xFFFF;
//     g_IDT[interrupt].SegmentSelector = segmentDescriptor;
//     g_IDT[interrupt].Reserved = 0;
//     g_IDT[interrupt].Flags = flags;
//     g_IDT[interrupt].BaseHigh = ((uint32_t)base >> 16) & 0xFFFF;
// }

// void i686_IDT_EnableGate(int interrupt)
// {
//     FLAG_SET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
// }

// void i686_IDT_DisableGate(int interrupt)
// {
//     FLAG_UNSET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
// }

// void i686_IDT_Initialize()
// {
//     i686_IDT_LOAD(&g_IDTDescriptor);
// }


#include "idt.h"
#include <stdint.h>
#include "binary.h"

typedef struct
{
    uint16_t BaseLow;
    uint16_t SegmentSelector;
    uint8_t Reserved;
    uint8_t Flags;
    uint16_t BaseHigh;
} __attribute__((packed)) IDTEntry;

typedef struct
{
    uint16_t Limit;
    IDTEntry* Ptr;
} __attribute__((packed)) IDTDescriptor;


IDTEntry g_IDT[256];

IDTDescriptor g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

void __attribute__((cdecl)) i686_IDT_Load(IDTDescriptor* idtDescriptor);

void i686_IDT_SetGate(int interrupt, void* base, uint16_t segmentDescriptor, uint8_t flags)
{
    g_IDT[interrupt].BaseLow = ((uint32_t)base) & 0xFFFF;
    g_IDT[interrupt].SegmentSelector = segmentDescriptor;
    g_IDT[interrupt].Reserved = 0;
    g_IDT[interrupt].Flags = flags;
    g_IDT[interrupt].BaseHigh = ((uint32_t)base >> 16) & 0xFFFF;
}

void i686_IDT_EnableGate(int interrupt)
{
    FLAG_SET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
}

void i686_IDT_DisableGate(int interrupt)
{
    FLAG_UNSET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
}

void i686_IDT_Initialize()
{
    i686_IDT_Load(&g_IDTDescriptor);
}