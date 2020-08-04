#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

int len( string x, string y )
{
    int z = 0;
    for( int i = x.find( y ); x[ i ] != ','; i++ ) z++;
    return z;
}

string ifreplace( string x, string match, int num, string sub, bool r )
{
    if ( x.find( match ) < 300 )
         if ( !r ) return x.replace( x.find( match  ), num, sub );
         else      return x.replace( x.rfind( match ), num, sub );
    else return x;
}

int main( int argc, char *argv[] )
{
    string in_input = argv[1];

    if ( in_input.find( " > " ) < 300 && in_input.find( "proto"  ) < 300 &&
         in_input.find( "ttl" ) < 300 && in_input.find( "offset" ) < 300 &&
         in_input.find( "id"  ) < 300 && in_input.find( "flags"  ) < 300 )
    {
        string up = " MAC-src-" + in_input.replace( in_input.find( " > " ), 3, " e MAC-dst-" );

        int dist = 0;
        if ( up.find( "," ) < 300 && up.find( "," ) < up.find( "ttl" ) ) dist = up.find( "ttl" ) - up.find( "," );
        if ( dist > 0 ) up = up.replace( up.find( "," ), dist, "" );

        up = up.replace( up.find( "id" ),     len( up, "id"     )+2, "" );
        up = up.replace( up.find( "offset" ), len( up, "offset" )+2, "" );
        up = up.replace( up.find( "flags" ),  len( up, "flags"  )+2, "" );

        up = ifreplace( up, ")",    1, ",",  true  );
        up = ifreplace( up, "    ", 4, "\n", false );
        cout << ( up = "\n    "+ up );
    }

    else if ( in_input.find( " > " ) < 300 && in_input.find( ":" ) < 300 )
    {
        in_input = ifreplace( in_input, "    ", 4, "", false );
        string ip = " IP-src-" + in_input.replace( in_input.find( " > " ), 3, " e IP-dst-" );

        int dist = ip.length() - ip.find( ":" );
        if ( dist > 0 ) ip = ip.replace( ip.find( ":" ), dist, ";" );

        cout << ip;
    }

    else { cout << "\n    error here: " << in_input << endl; }
    return 0;
}
