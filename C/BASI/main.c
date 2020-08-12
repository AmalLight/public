#include "other.h"

int main( int argc, char *argv[], char *envp[] )
{
        int numero1 = -1;
        char* numero2 = NULL;

        if ( myEquals( argv[1], "dec" ) )
        {
                numero1 = stringToInt( argv[2] );
                
                if ( myEquals( argv[3], "bin" ) )
                        numero2 = decToAny( numero1, 2 );
                        
                else if ( myEquals( argv[3], "ott" ) )
                        numero2 = decToAny( numero1, 8 );

                else if ( myEquals( argv[3], "esa" ) )
                        numero2 = decToAny( numero1, 16 );
        }

        else if ( myEquals( argv[1], "bin" ) )
                if ( myEquals( argv[3], "dec" ) )
                        numero1 = binToDec( argv[2] );

                else if ( myEquals( argv[3], "ott" ) )
                        numero2 = binToOtt( argv[2] );
                        
                else if ( myEquals( argv[3], "esa" ) )
                        numero2 = binToESA( argv[2] );
                else;

        else if ( myEquals( argv[1], "ott" ) )
                if ( myEquals( argv[3], "dec" ) )
                        numero1 = ottToDec( argv[2] );

                else if ( myEquals( argv[3], "bin" ) )
                        numero2 = ottToBin( argv[2] );

                else if ( myEquals(argv[3], "esa") )
                        numero2 = ottToESA( argv[2] );
                else;

        else if ( myEquals( argv[1], "esa" ) )
                if ( myEquals( argv[3], "dec" ) )
                        numero1 = esaToDec( argv[2] );

                else if ( myEquals( argv[3], "bin" ) )
                        numero2 = esaToBin( argv[2] );

                else if ( myEquals( argv[3], "ott" ) )
                        numero2 = esaToOtt( argv[2] );
                else;
        
        printf( "From %s: %s To %s: ", argv[1], argv[2], argv[3] );
        if ( numero2 != NULL ) printf( "%s \n", numero2 );                        
        else printf( "%d \n", numero1 );
}