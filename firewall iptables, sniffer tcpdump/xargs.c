#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;

int main( int argc, char *argv[] )
{
    string prog = argv[ 1 ];

    while ( true )
    {
        string x = "";
        getline( cin, x );

        x = prog +" \""+ x +"\"";
        const char * y = x.c_str();
        system( y );
    }

    return 0;
}