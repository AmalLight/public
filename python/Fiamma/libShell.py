from subprocess import call
import action
from os import *
from io import open

def ShellGo( pre, user, cmd, start = 1 ):
        outPy = 'Fiamma_py.sh'
        home = ( '/' + pre + '/' + user + '/' )
        home = ( home +       'Fiamma_Files/' )
        fileX = home + outPy

        i = open( fileX, 'w' )
        i.write( '#!/bin/bash            \n' )
        i.write( '#python script by kaumi\n' )
        i.close()

        call( 'echo "#about it: $(date)" >> "' + fileX + '"', shell = True )
        call( 'echo                   "" >> "' + fileX + '"', shell = True )

        i = open( fileX, 'a' )
        if ( cmd != None and cmd != '' ): i.write( cmd + '\n' )
        i.close()

        if start > 0: return ShellExec( home, outPy, pre, user )
        else: return True

def ShellExec( home, outPy, pre, user ):
        call( 'cd "' + home + '" && echo           "" > Fiamma_err', shell = True )
        call( 'cd "' + home + '" && ./' + outPy + ' 2>> Fiamma_err', shell = True )

        outErr = ( home + 'Fiamma_err' )
        if path.exists( outErr ):
            i = open( outErr )
            for line in i.readlines():
                if line != '\n':
                    print( 'System Error, Find:' , outErr + '.' )
                    i.close()
                    return False
            i.close()
            return True
