from os import *

def dir_or_file( fileX, ffile = None, fdir = None, deep = 0 ):

    if ( not fileX.startswith( '.' ) ) and path.exists( fileX ):

        if path.isdir( fileX ):

            print( 'file:', fileX, 'is a dir.' )
            if not fileX.endswith( '/' ): fileX = fileX + '/'
                 
            if fdir: fdir( fileX, deep )
            for fil in listdir( fileX ): dir_or_file( fileX + fil, ffile, fdir, deep + 2 )
            return True
                        
        elif path.isfile( fileX ):

            print( 'file:', fileX, 'is a file.' )           
            if ffile: ffile( fileX, deep )
            return False
