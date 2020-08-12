#ifndef OTHER
#define OTHER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dec.h"
#include "bin.h"
#include "ott.h"
#include "esa.h"

int len( char* x );
int elev( int x, int y );

char intToChar( int x );
int  charToInt( char x );
int  stringToInt( char* x );

char* myReverse( char* x );
int   myEquals( char* x, char* y );
char* myAppend( char* x, char* y );
char* myAppend2( char* x, char y );

#endif