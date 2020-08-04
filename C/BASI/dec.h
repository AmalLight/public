#ifndef DEC_H_
#define DEC_H_

char* subDecToBin( int numero, int i, char* x );
char* decToBin( int numero );

char* decToAny( int numero, int base );

int subAnyToDec( char* x, int base, int dec, int esp, int i );
int anyToDec( char* x, int base );

#endif