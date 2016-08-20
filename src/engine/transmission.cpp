#include "transmission.h"

char hexchars[] = transmission_keytable;   // Hexadezimaler Zeichensatz
char dec2hex_buffer[] = "00000";

// Helper
int transmission_ipow(int base, int exp) {
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

char* transmission_input( unsigned int num) {

    // 32 bit
    for(unsigned int i = 0; i != hexbuffer_legth-1; i++) {
        dec2hex_buffer[hexbuffer_legth +1 - i] = hexchars[ num >> (i * transmission_bit_legth) & transmission_char_legth];
    }

    // rückgabe
    return dec2hex_buffer;
}

int transmission_output( char *buffer) {
    int i = 0;
    int i_int = 0;
    int i_size = 0;

    for( i_size = 0; i_size < hexbuffer_legth; i_size++) {
        for( i = 0; i < transmission_char_legth; i++)
            if( buffer[ hexbuffer_legth+1 - i_size] == hexchars[i] )
                break;
        if( i == 0)
            i_int += i;
        else
            i_int += i * transmission_ipow( (transmission_char_legth+1), i_size);
    }

    return i_int;
}
