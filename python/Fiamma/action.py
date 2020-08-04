import libs
from io import open
from libShell import call
from libShell import ShellGo
from os import makedirs, utime, path, rmdir, remove


def createX( fileX ):
        if not path.exists( fileX ):
            if path.isfile( fileX ):
                with open( fileX, 'a' ): os.utime( fileX, None ) 
                while not path.exists( fileX ): None
        
            elif path.isdir( fileX ):
                makedirs( fileX )
                while not path.exists( fileX ): None
        return fileX


def deleteX( fileX ):
        if path.exists( fileX ):
            if path.isfile( fileX ):
                if path.exists( fileX ): remove( fileX )
                while path.exists( fileX ): None

            elif path.isdir( fileX ):
                if path.exists( fileX ): rmdir( fileX )
                while path.exists( fileX ): None
        return fileX


class send():
        pre = None
        user = None
        argv = None
        home = None
        work = None
        err = None
        outTree = None
        fiammaFiles = None
        fiammaShell = None


        def __init__( self, argv, work, err, pre, user ):
                self.pre = pre
                self.user = user
                self.home = ( '/' + self.pre + '/' + self.user + '/' )
                self.argv = argv
                self.work = work
                self.err = err
                self.fiammaFiles = ( self.home + 'Fiamma_Files/' )
                self.outTree = ( self.fiammaFiles + 'Fiamma_tree' )
                self.fiammaShell = ( self.fiammaFiles + 'Fiamma_shell' )


        def find_line( self, fileX = None, deep = 0 ):
                try:
                    if path.isfile( fileX ) and fileX.endswith( self.argv[3] ):
                        print( 'find-line on file:', fileX + '.' )
                        libs.find_in_all_file( fileX, self.argv[4], self.work, self.err )

                except: self.err += [ fileX ]
                else:   self.err += [ fileX ]


        def find_name( self, fileX = None, deep = 0 ):
                def ok( fileX ):
                    if   path.isfile( fileX ): print( 'find-name on file:', fileX + '.' )
                    elif path.isdir(  fileX ): print( 'find-name on dir:',  fileX +'.'  )
                    return fileX

                if path.isfile( fileX ):
                    if path.basename( fileX ).count( self.argv[3] ):
                          self.work += [ok( fileX )]
                    else: self.err  += [ fileX ]

                elif path.isdir(  fileX ):
                    if path.basename( path.dirname( fileX ) ).count( self.argv[3] ):
                          self.work += [ok( fileX )]
                    else: self.err  += [ fileX ]
                        

        def count_obj( self, fileX = None, deep = 0 ):
                if self.argv[3].count( 'all' ):
                    if   path.isfile( fileX ): print( 'count file:', fileX + '.' )
                    elif path.isdir( fileX  ): print( 'count dir:',  fileX + '.' )
                    self.work += [ fileX ]
                
                elif path.isfile( fileX ) and fileX.endswith( self.argv[3] ):
                    print( 'count file:', fileX + '.' )
                    self.work += [ fileX ]
                        

        def delete( self, fileX = None, deep = 0 ):
                if self.argv[3].count( 'all' ):
                    print( 'delete fileX:', fileX + '.' )
                    self.work += [ deleteX( fileX ) ]

                elif path.isfile( fileX ) and fileX.endswith( self.argv[3] ):
                    print( 'delete fileX:', fileX + '.' )
                    self.work += [ deleteX( fileX ) ]
                else: self.err += [ fileX ]
                                

        def tree( self, fileX = None, deep = 0 ):
                i =  open( self.outTree,     'a' )
                i2 = open( self.fiammaShell, 'r' )
                draw, string, size = ( '|' + ( '_' * deep ) ), '', ''
                
                if fileX.count( '"' ):
                    i.close()
                    i2.close()
                    return None
                        
                elif ShellGo( self.pre, self.user, 'stat -c %s \"' + fileX + '\" > ' + self.fiammaShell ) == False:
                    i.close()
                    i2.close()
                    return None

                else:
                    size = i2.readline()
                    size = size[ :len( size )-1 ]
                    size = int( int( size ) / 1048576 )

                    if path.isfile( fileX ):
                          string = ( path.basename( fileX ) + ' is a file, size: ' + str( size ) + ', in Megabyte.' )
                    else: string = ( path.basename( path.dirname( fileX ) ) + ' is a dir.' )

                    i.write( draw + string + '\n' )
                    i.close()
                    i2.close()
