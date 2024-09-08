//Thanks to the script i found somehwere online, dont remeber where but really saved my life! :) osdev wiki script was not wroking :(
// anything from ----------------- to ------------------ is taken, rest is developed by me :)

// ------------------------------------

//read data from pin
unsigned char port_byte_read(unsigned short port ) {

unsigned char result ;
__asm__ ( "in %%dx,%%al":"=a"( result ):"d"( port ));
return result ;

}
//write data to pin
void port_byte_write(unsigned short port ,unsigned char data ) {

__asm__ ("out %%al,%%dx" : : "a"( data ) ,"d"( port ));
}

// ---------------------------------------

#define UNUSED_PORT 0x80

void iowait()
{
    port_byte_write(UNUSED_PORT, 0);
}

