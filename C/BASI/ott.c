#include "other.h"
#include "ott.h"

int ottToDec( char* x ) { return anyToDec( x, 8 ); }
char* ottToBin( char* x ) { return decToAny( ottToDec( x ), 2 ); }
char* ottToESA( char* x ) { return decToAny( ottToDec( x ), 16 ); }