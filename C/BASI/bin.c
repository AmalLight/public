#include "other.h"
#include "bin.h"

int binToDec( char* x ) { return anyToDec( x, 2 ); }

char* binToOtt( char* x ) { return binToAny( x, 3, 0, 0, 0 ); }

char* binToESA( char* x ) { return binToAny( x, 4, 0, 0, 0 ); }

char* binToAny( char* x, int y, int pow, int i2, int tot )
{
        char* str= (char*) malloc( len( x )*sizeof( char ) ); 
        for ( int i1 = len( x )-1; i1 > -1; i1--, pow++ )
                if ( pow+1 == y )
                {
                        tot += charToInt( x[ i1 ] )*elev( 2, pow );
                        str[ i2++ ] = intToChar( tot );
                        tot = 0; pow = -1;
                }
                else tot += charToInt( x[ i1 ] )*elev( 2, pow );

        if ( tot > 0 )
               str[ i2++ ] = intToChar( tot );
               str[ i2 ] = '\0';
        return myReverse( str );
}