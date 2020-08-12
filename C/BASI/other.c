#include "other.h"

int len( char* x ) { strlen( x )-1; }
int myEquals( char* x, char* y ) { return !strcmp( x, y ); }

char intToChar( int x )
{
        if ( x>=0 && x<=9 ) return ( x+'0' );
        else if ( x==10 ) return 'A';
        else if ( x==11 ) return 'B';
        else if ( x==12 ) return 'C';
        else if ( x==13 ) return 'D';
        else if ( x==14 ) return 'E';
        else if ( x==15 ) return 'F';
}

int charToInt( char x )
{
        for ( int i=0; i<16; i++ )
                if ( intToChar( i ) == x ) return i;
        return 0;
}

int stringToInt( char* x )
{
        int number=0;
        for ( int i=0; i < len( x ); i++ )
                if ( number == 0 ) number += charToInt( x[i] );
                else { number *= 10; number += charToInt( x[i] ); }
        return number;
}

int elev( int x, int y )
{
        if ( y == 0 ) return 1;
        else if ( y == 1 ) return x;
        else return x*elev( x, y-1 );
}

char* myAppend( char* x, char* y )
{
        int somma = len( x ) + len( y ) + 1;
        char* tmp = (char*) malloc( somma*sizeof( char ) );
        tmp = strcat( strcat( tmp, x ), y );
        free( x ); free( y );
        return tmp;
}

char* myAppend2( char* x, char y )
{
        char* s= (char*) malloc( 2*sizeof( char ) );
        s[0]= y; s[1]= '\0'; return myAppend( x, s );
}

char* myReverse( char* x )
{
        char* r= (char*) malloc( 1*sizeof( char ) );
        r[0]= '\0';
        for ( int i= len( x )-1; i > -1; i-- )
                r= myAppend2( r, x[ i ] );
        free( x );
        return r;
}