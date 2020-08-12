#include "other.h"
#include "esa.h"

int esaToDec( char* x ) { return anyToDec( x, 16 ); }
char* esaToBin( char* x ) { return decToAny( esaToDec( x ), 2 ); }
char* esaToOtt( char* x ) { return decToAny( esaToDec( x ), 8 ); }