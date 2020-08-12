#include "other.h"
#include "dec.h"

char* subDecToBin( int numero, int i, char* x )
{
        if ( numero==0 ) return x;
        else return
                subDecToBin( numero/2, i+1, myAppend2( x,
                             intToChar( numero % 2 ) ));
}

char* decToBin( int numero )
{
        char* r= (char*) malloc( 1*sizeof( char ) );
        r[0]= '\0';
        return myReverse( subDecToBin( numero, 0, r ) );
}

char* decToAny( int numero, int base )
{
        char* bin= decToBin( numero );
        if ( base==2 ) return bin;
        else if ( base==8 ) return binToOtt( bin );
        else if ( base==16 ) return binToESA( bin );
}

int subAnyToDec( char* x, int base, int dec, int esp, int i )
{
        if ( i==(-1) ) return dec;
        else return
                subAnyToDec( x, base, dec +
                          elev( base, esp )*charToInt( x[ i ] ),
                          esp+1, i-1 );
}

int anyToDec( char* x, int base )
        { return subAnyToDec( x, base, 0, 0, len(x)-1 ); }