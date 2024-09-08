//Thanks to the script i found somehwere online, dont remeber where but really saved my life! :) osdev wiki script was not wroking :(

// unsigned char port_byte_in (unsigned short port);
// void port_byte_out (unsigned short port, unsigned char data);
// unsigned short port_word_in (unsigned short port);
// void port_word_out (unsigned short port, unsigned short data);

#include "stdint.h"

unsigned char port_byte_read(unsigned short port );
void port_byte_write(unsigned short port ,unsigned char data );
void iowait();

uint8_t __attribute__((cdecl)) EnableInterrupts();
uint8_t __attribute__((cdecl)) DisableInterrupts();