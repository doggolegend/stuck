; uint8_t __attribute__((cdecl)) EnableInterrupts();
; uint8_t __attribute__((cdecl)) DisableInterrupts();

global EnableInterrupts
EnableInterrupts:
    sti
    ret

global DisableInterrupts
DisableInterrupts:
    cli
    ret