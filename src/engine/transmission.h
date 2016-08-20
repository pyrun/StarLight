#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <stdio.h>

#define hexbuffer_legth 4
#define transmission_char_legth ( 64 - 1 )
#define transmission_bit_legth ( 4 + 2 )
#define transmission_keytable   "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz<>"

char* transmission_input( unsigned int num);
int transmission_output( char *buffer);

#endif // TRANSMISSION_H
